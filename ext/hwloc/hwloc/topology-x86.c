/*
 * Copyright © 2010-2015 Inria.  All rights reserved.
 * Copyright © 2010-2013 Université Bordeaux
 * Copyright © 2010-2011 Cisco Systems, Inc.  All rights reserved.
 * See COPYING in top-level directory.
 *
 *
 * This backend is only used when the operating system does not export
 * the necessary hardware topology information to user-space applications.
 * Currently, only the FreeBSD backend relies on this x86 backend.
 *
 * Other backends such as Linux have their own way to retrieve various
 * pieces of hardware topology information from the operating system
 * on various architectures, without having to use this x86-specific code.
 */

#include <private/autogen/config.h>
#include <hwloc.h>
#include <private/private.h>
#include <private/debug.h>
#include <private/misc.h>

#include <private/cpuid-x86.h>

#include <sys/types.h>
#include <dirent.h>

struct hwloc_x86_backend_data_s {
  unsigned nbprocs;
  hwloc_bitmap_t apicid_set;
  int apicid_unique;
  char *src_cpuiddump_path;
};

/************************************
 * Management of cpuid dump as input
 */

struct cpuiddump {
  unsigned nr;
  struct cpuiddump_entry {
    unsigned inmask; /* which of ine[abcd]x are set on input */
    unsigned ineax;
    unsigned inebx;
    unsigned inecx;
    unsigned inedx;
    unsigned outeax;
    unsigned outebx;
    unsigned outecx;
    unsigned outedx;
  } *entries;
};

static void
cpuiddump_free(struct cpuiddump *cpuiddump)
{
  if (cpuiddump->nr)
    free(cpuiddump->entries);
  free(cpuiddump);
}

static struct cpuiddump *
cpuiddump_read(const char *dirpath, unsigned idx)
{
  struct cpuiddump *cpuiddump;
  struct cpuiddump_entry *cur;
  char *filename;
  size_t filenamelen = strlen(dirpath) + 15;
  FILE *file;
  char line[128];
  unsigned nr;

  cpuiddump = malloc(sizeof(*cpuiddump));
  cpuiddump->nr = 0; /* return a cpuiddump that will raise errors because it matches nothing */

  filename = malloc(filenamelen);
  snprintf(filename, filenamelen, "%s/pu%u", dirpath, idx);
  file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Could not read dumped cpuid file %s\n", filename);
    free(filename);
    return cpuiddump;
  }
  free(filename);

  nr = 0;
  while (fgets(line, sizeof(line), file))
    nr++;
  cpuiddump->entries = malloc(nr * sizeof(struct cpuiddump_entry));

  fseek(file, 0, SEEK_SET);
  cur = &cpuiddump->entries[0];
  nr = 0;
  while (fgets(line, sizeof(line), file)) {
    if (*line == '#')
      continue;
    if (sscanf(line, "%x %x %x %x %x => %x %x %x %x",
	      &cur->inmask,
	      &cur->ineax, &cur->inebx, &cur->inecx, &cur->inedx,
	      &cur->outeax, &cur->outebx, &cur->outecx, &cur->outedx) == 9) {
      cur++;
      nr++;
    }
  }
  cpuiddump->nr = nr;
  fclose(file);
  return cpuiddump;
}

static void
cpuiddump_find_by_input(unsigned *eax, unsigned *ebx, unsigned *ecx, unsigned *edx, struct cpuiddump *cpuiddump)
{
  unsigned i;

  for(i=0; i<cpuiddump->nr; i++) {
    struct cpuiddump_entry *entry = &cpuiddump->entries[i];
    if ((entry->inmask & 0x1) && *eax != entry->ineax)
      continue;
    if ((entry->inmask & 0x2) && *ebx != entry->inebx)
      continue;
    if ((entry->inmask & 0x4) && *ecx != entry->inecx)
      continue;
    if ((entry->inmask & 0x8) && *edx != entry->inedx)
      continue;
    *eax = entry->outeax;
    *ebx = entry->outebx;
    *ecx = entry->outecx;
    *edx = entry->outedx;
    return;
  }

  fprintf(stderr, "Couldn't find %x,%x,%x,%x in dumped cpuid, returning 0s.\n",
	  *eax, *ebx, *ecx, *edx);
  *eax = 0;
  *ebx = 0;
  *ecx = 0;
  *edx = 0;
}

static void cpuid_or_from_dump(unsigned *eax, unsigned *ebx, unsigned *ecx, unsigned *edx, struct cpuiddump *src_cpuiddump)
{
  if (src_cpuiddump) {
    cpuiddump_find_by_input(eax, ebx, ecx, edx, src_cpuiddump);
  } else {
    hwloc_x86_cpuid(eax, ebx, ecx, edx);
  }
}

/*******************************
 * Core detection routines and structures
 */

#define has_topoext(features) ((features)[6] & (1 << 22))
#define has_x2apic(features) ((features)[4] & (1 << 21))

struct cacheinfo {
  unsigned type;
  unsigned level;
  unsigned nbthreads_sharing;

  unsigned linesize;
  unsigned linepart;
  int ways;
  unsigned sets;
  unsigned long size;
  char inclusiveness;

};

struct procinfo {
  unsigned present;
  unsigned apicid;
  unsigned max_log_proc;
  unsigned max_nbcores;
  unsigned max_nbthreads;
  unsigned packageid;
  unsigned nodeid;
  unsigned unitid;
  unsigned logprocid;
  unsigned threadid;
  unsigned coreid;
  unsigned *otherids;
  unsigned levels;
  unsigned numcaches;
  struct cacheinfo *cache;
  char cpuvendor[13];
  char cpumodel[3*4*4+1];
  unsigned cpustepping;
  unsigned cpumodelnumber;
  unsigned cpufamilynumber;
};

enum cpuid_type {
  intel,
  amd,
  unknown
};

static void fill_amd_cache(struct procinfo *infos, unsigned level, int type, unsigned cpuid)
{
  struct cacheinfo *cache;
  unsigned cachenum;
  unsigned long size = 0;

  if (level == 1)
    size = ((cpuid >> 24)) << 10;
  else if (level == 2)
    size = ((cpuid >> 16)) << 10;
  else if (level == 3)
    size = ((cpuid >> 18)) << 19;
  if (!size)
    return;

  cachenum = infos->numcaches++;
  infos->cache = realloc(infos->cache, infos->numcaches*sizeof(*infos->cache));
  cache = &infos->cache[cachenum];

  cache->type = type;
  cache->level = level;
  if (level <= 2)
    cache->nbthreads_sharing = 1;
  else
    cache->nbthreads_sharing = infos->max_log_proc;
  cache->linesize = cpuid & 0xff;
  cache->linepart = 0;
  if (level == 1) {
    cache->inclusiveness = 0;//get inclusiveness old AMD ( suposed to be L1 false)

    cache->ways = (cpuid >> 16) & 0xff;
    if (cache->ways == 0xff)
      /* Fully associative */
      cache->ways = -1;
  } else {
    cache->inclusiveness = 1;//get inclusivenessold AMD ( suposed to be L2 L3 true)

    static const unsigned ways_tab[] = { 0, 1, 2, 0, 4, 0, 8, 0, 16, 0, 32, 48, 64, 96, 128, -1 };
    unsigned ways = (cpuid >> 12) & 0xf;
    cache->ways = ways_tab[ways];
  }
  cache->size = size;
  cache->sets = 0;

  hwloc_debug("cache L%u t%u linesize %u ways %u size %luKB\n", cache->level, cache->nbthreads_sharing, cache->linesize, cache->ways, cache->size >> 10);
}

/* Fetch information from the processor itself thanks to cpuid and store it in
 * infos for summarize to analyze them globally */
static void look_proc(struct hwloc_backend *backend, struct procinfo *infos, unsigned highest_cpuid, unsigned highest_ext_cpuid, unsigned *features, enum cpuid_type cpuid_type, struct cpuiddump *src_cpuiddump)
{
  struct hwloc_x86_backend_data_s *data = backend->private_data;
  unsigned eax, ebx, ecx = 0, edx;
  unsigned cachenum;
  struct cacheinfo *cache;
  unsigned regs[4];
  unsigned _model, _extendedmodel, _family, _extendedfamily;

  infos->present = 1;

  /* on return from this function, the following fields must be set in infos:
   * packageid, nodeid, unitid, coreid, threadid, or -1
   * apicid
   * levels and levels slots in otherids[]
   * numcaches and numcaches slots in caches[]
   *
   * max_log_proc, max_nbthreads, max_nbcores, logprocid
   * are only used temporarily inside this function and its callees.
   */

  /* Get apicid, max_log_proc, packageid, logprocid from cpuid 0x01 */
  eax = 0x01;
  cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
  infos->apicid = ebx >> 24;
  if (edx & (1 << 28))
    infos->max_log_proc = 1 << hwloc_flsl(((ebx >> 16) & 0xff) - 1);
  else
    infos->max_log_proc = 1;
  hwloc_debug("APIC ID 0x%02x max_log_proc %u\n", infos->apicid, infos->max_log_proc);
  infos->packageid = infos->apicid / infos->max_log_proc;
  infos->logprocid = infos->apicid % infos->max_log_proc;
  hwloc_debug("phys %u thread %u\n", infos->packageid, infos->logprocid);

  /* Get cpu model/family/stepping numbers from same cpuid */
  _model          = (eax>>4) & 0xf;
  _extendedmodel  = (eax>>16) & 0xf;
  _family         = (eax>>8) & 0xf;
  _extendedfamily = (eax>>20) & 0xff;
  if ((cpuid_type == intel || cpuid_type == amd) && _family == 0xf) {
    infos->cpufamilynumber = _family + _extendedfamily;
  } else {
    infos->cpufamilynumber = _family;
  }
  if ((cpuid_type == intel && (_family == 0x6 || _family == 0xf))
      || (cpuid_type == amd && _family == 0xf)) {
    infos->cpumodelnumber = _model + (_extendedmodel << 4);
  } else {
    infos->cpumodelnumber = _model;
  }
  infos->cpustepping = eax & 0xf;

  /* Get cpu vendor string from cpuid 0x00 */
  memset(regs, 0, sizeof(regs));
  regs[0] = 0;
  cpuid_or_from_dump(&regs[0], &regs[1], &regs[3], &regs[2], src_cpuiddump);
  memcpy(infos->cpuvendor, regs+1, 4*3);
  /* infos was calloc'ed, already ends with \0 */

  /* Get cpu model string from cpuid 0x80000002-4 */
  if (highest_ext_cpuid >= 0x80000004) {
    memset(regs, 0, sizeof(regs));
    regs[0] = 0x80000002;
    cpuid_or_from_dump(&regs[0], &regs[1], &regs[2], &regs[3], src_cpuiddump);
    memcpy(infos->cpumodel, regs, 4*4);
    regs[0] = 0x80000003;
    cpuid_or_from_dump(&regs[0], &regs[1], &regs[2], &regs[3], src_cpuiddump);
    memcpy(infos->cpumodel + 4*4, regs, 4*4);
    regs[0] = 0x80000004;
    cpuid_or_from_dump(&regs[0], &regs[1], &regs[2], &regs[3], src_cpuiddump);
    memcpy(infos->cpumodel + 4*4*2, regs, 4*4);
    /* infos was calloc'ed, already ends with \0 */
  }

  /* Get core/thread information from cpuid 0x80000008
   * (not supported on Intel)
   */
  if (cpuid_type != intel && highest_ext_cpuid >= 0x80000008) {
    unsigned coreidsize;
    eax = 0x80000008;
    cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
    coreidsize = (ecx >> 12) & 0xf;
    hwloc_debug("core ID size: %u\n", coreidsize);
    if (!coreidsize) {
      infos->max_nbcores = (ecx & 0xff) + 1;
    } else
      infos->max_nbcores = 1 << coreidsize;
    hwloc_debug("Thus max # of cores: %u\n", infos->max_nbcores);
    /* Still no multithreaded AMD */
    infos->max_nbthreads = 1 ;
    hwloc_debug("and max # of threads: %u\n", infos->max_nbthreads);
    /* The legacy max_log_proc is deprecated, it can be smaller than max_nbcores,
     * which is the maximum number of cores that the processor could theoretically support
     * (see "Multiple Core Calculation" in the AMD CPUID specification).
     * Recompute packageid/logprocid/threadid/coreid accordingly.
     */
    infos->packageid = infos->apicid / infos->max_nbcores;
    infos->logprocid = infos->apicid % infos->max_nbcores;
    infos->threadid = infos->logprocid % infos->max_nbthreads;
    infos->coreid = infos->logprocid / infos->max_nbthreads;
    hwloc_debug("this is thread %u of core %u\n", infos->threadid, infos->coreid);
  }

  infos->numcaches = 0;
  infos->cache = NULL;

  /* Get apicid, nodeid, unitid from cpuid 0x8000001e
   * and cache information from cpuid 0x8000001d
   * (AMD topology extension)
   */
  if (cpuid_type != intel && has_topoext(features)) {
    unsigned apic_id, node_id, nodes_per_proc, unit_id, cores_per_unit;

    eax = 0x8000001e;
    cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
    infos->apicid = apic_id = eax;
    infos->nodeid = node_id = ecx & 0xff;
    nodes_per_proc = ((ecx >> 8) & 7) + 1;
    if (nodes_per_proc > 2) {
      hwloc_debug("warning: undefined value %d, assuming it means %d\n", nodes_per_proc, nodes_per_proc);
    }
    infos->unitid = unit_id = ebx & 0xff;
    cores_per_unit = ((ebx >> 8) & 3) + 1;
    hwloc_debug("x2APIC %08x, %d nodes, node %d, %d cores in unit %d\n", apic_id, nodes_per_proc, node_id, cores_per_unit, unit_id);

    for (cachenum = 0; ; cachenum++) {
      unsigned type;
      eax = 0x8000001d;
      ecx = cachenum;
      cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
      type = eax & 0x1f;
      if (type == 0)
	break;
      infos->numcaches++;
    }

    cache = infos->cache = malloc(infos->numcaches * sizeof(*infos->cache));

    for (cachenum = 0; ; cachenum++) {
      unsigned long linesize, linepart, ways, sets;
      unsigned type;
      eax = 0x8000001d;
      ecx = cachenum;
      cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);

      type = eax & 0x1f;

      if (type == 0)
	break;

      cache->type = type;
      cache->level = (eax >> 5) & 0x7;
      /* Note: actually number of cores */
      cache->nbthreads_sharing = ((eax >> 14) &  0xfff) + 1;

      cache->linesize = linesize = (ebx & 0xfff) + 1;
      cache->linepart = linepart = ((ebx >> 12) & 0x3ff) + 1;
      ways = ((ebx >> 22) & 0x3ff) + 1;

      if (eax & (1 << 9))
	/* Fully associative */
	cache->ways = -1;
      else
	cache->ways = ways;
      cache->sets = sets = ecx + 1;
      cache->size = linesize * linepart * ways * sets;
      cache->inclusiveness = edx & 0x2;


      hwloc_debug("cache %u type %u L%u t%u c%u linesize %lu linepart %lu ways %lu sets %lu, size %uKB\n", cachenum, cache->type, cache->level, cache->nbthreads_sharing, infos->max_nbcores, linesize, linepart, ways, sets, cache->size >> 10);

      cache++;
    }
  } else {
    /* If there's no topoext,
     * get cache information from cpuid 0x80000005 and 0x80000006
     * (not supported on Intel)
     */
    if (cpuid_type != intel && highest_ext_cpuid >= 0x80000005) {
      eax = 0x80000005;
      cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
      fill_amd_cache(infos, 1, 1, ecx); /* L1d */
      fill_amd_cache(infos, 1, 2, edx); /* L1i */
    }
    if (cpuid_type != intel && highest_ext_cpuid >= 0x80000006) {
      eax = 0x80000006;
      cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
      if (ecx & 0xf000)
	/* This is actually supported on Intel but LinePerTag isn't returned in bits 8-11.
	 * Could be useful if some Intels (at least before Core micro-architecture)
	 * support this leaf without leaf 0x4.
	 */
	fill_amd_cache(infos, 2, 3, ecx); /* L2u */
      if (edx & 0xf000)
	fill_amd_cache(infos, 3, 3, edx); /* L3u */
      /* FIXME: AMD MagnyCours family 0x10 model 0x9 with 8 cores or more actually
       * have the L3 split in two halves, and associativity is divided as well (48)
       */
    }
  }

  /* Get thread/core + cache information from cpuid 0x04
   * (not supported on AMD)
   */
  if (cpuid_type != amd && highest_cpuid >= 0x04) {
    for (cachenum = 0; ; cachenum++) {
      unsigned type;
      eax = 0x04;
      ecx = cachenum;
      cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);

      type = eax & 0x1f;

      hwloc_debug("cache %u type %u\n", cachenum, type);

      if (type == 0)
	break;
      infos->numcaches++;

      if (!cachenum) {
	/* by the way, get thread/core information from the first cache */
	infos->max_nbcores = ((eax >> 26) & 0x3f) + 1;
	infos->max_nbthreads = infos->max_log_proc / infos->max_nbcores;
	hwloc_debug("thus %u threads\n", infos->max_nbthreads);
	infos->threadid = infos->logprocid % infos->max_nbthreads;
	infos->coreid = infos->logprocid / infos->max_nbthreads;
	hwloc_debug("this is thread %u of core %u\n", infos->threadid, infos->coreid);
      }
    }

    cache = infos->cache = malloc(infos->numcaches * sizeof(*infos->cache));

    for (cachenum = 0; ; cachenum++) {
      unsigned long linesize, linepart, ways, sets;
      unsigned type;
      eax = 0x04;
      ecx = cachenum;
      cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);

      type = eax & 0x1f;

      if (type == 0)
	break;

      cache->type = type;
      cache->level = (eax >> 5) & 0x7;
      cache->nbthreads_sharing = ((eax >> 14) & 0xfff) + 1;

      cache->linesize = linesize = (ebx & 0xfff) + 1;
      cache->linepart = linepart = ((ebx >> 12) & 0x3ff) + 1;
      ways = ((ebx >> 22) & 0x3ff) + 1;
      if (eax & (1 << 9))
        /* Fully associative */
        cache->ways = -1;
      else
        cache->ways = ways;
      cache->sets = sets = ecx + 1;
      cache->size = linesize * linepart * ways * sets;
      cache->inclusiveness = edx & 0x2;

      hwloc_debug("cache %u type %u L%u t%u c%u linesize %lu linepart %lu ways %lu sets %lu, size %uKB\n", cachenum, cache->type, cache->level, cache->nbthreads_sharing, infos->max_nbcores, linesize, linepart, ways, sets, cache->size >> 10);

      cache++;
    }
  }

  /* Get package/core/thread information from cpuid 0x0b
   * (Intel x2APIC)
   */
  if (cpuid_type == intel && has_x2apic(features)) {
    unsigned level, apic_nextshift, apic_number, apic_type, apic_id = 0, apic_shift = 0, id;
    for (level = 0; ; level++) {
      ecx = level;
      eax = 0x0b;
      cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
      if (!eax && !ebx)
        break;
    }
    if (level) {
      infos->levels = level;
      infos->otherids = malloc(level * sizeof(*infos->otherids));
      for (level = 0; ; level++) {
	ecx = level;
	eax = 0x0b;
	cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
	if (!eax && !ebx)
	  break;
	apic_nextshift = eax & 0x1f;
	apic_number = ebx & 0xffff;
	apic_type = (ecx & 0xff00) >> 8;
	apic_id = edx;
	id = (apic_id >> apic_shift) & ((1 << (apic_nextshift - apic_shift)) - 1);
	hwloc_debug("x2APIC %08x %d: nextshift %d num %2d type %d id %2d\n", apic_id, level, apic_nextshift, apic_number, apic_type, id);
	infos->apicid = apic_id;
	infos->otherids[level] = UINT_MAX;
	switch (apic_type) {
	case 1:
	  infos->threadid = id;
	  break;
	case 2:
	  infos->coreid = id;
	  break;
	default:
	  hwloc_debug("x2APIC %d: unknown type %d\n", level, apic_type);
	  infos->otherids[level] = apic_id >> apic_shift;
	  break;
	}
	apic_shift = apic_nextshift;
      }
      infos->apicid = apic_id;
      infos->packageid = apic_id >> apic_shift;
      hwloc_debug("x2APIC remainder: %d\n", infos->packageid);
      hwloc_debug("this is thread %u of core %u\n", infos->threadid, infos->coreid);
    }
  }

  if (hwloc_bitmap_isset(data->apicid_set, infos->apicid))
    data->apicid_unique = 0;
  else
    hwloc_bitmap_set(data->apicid_set, infos->apicid);
}

static void
hwloc_x86_add_cpuinfos(hwloc_obj_t obj, struct procinfo *info, int nodup)
{
  char number[8];
  hwloc_obj_add_info_nodup(obj, "CPUVendor", info->cpuvendor, nodup);
  snprintf(number, sizeof(number), "%u", info->cpufamilynumber);
  hwloc_obj_add_info_nodup(obj, "CPUFamilyNumber", number, nodup);
  snprintf(number, sizeof(number), "%u", info->cpumodelnumber);
  hwloc_obj_add_info_nodup(obj, "CPUModelNumber", number, nodup);
  if (info->cpumodel[0]) {
    const char *c = info->cpumodel;
    while (*c == ' ')
      c++;
    hwloc_obj_add_info_nodup(obj, "CPUModel", c, nodup);
  }
  snprintf(number, sizeof(number), "%u", info->cpustepping);
  hwloc_obj_add_info_nodup(obj, "CPUStepping", number, nodup);
}

/* Analyse information stored in infos, and build/annotate topology levels accordingly */
static void summarize(struct hwloc_backend *backend, struct procinfo *infos, int fulldiscovery)
{
  struct hwloc_topology *topology = backend->topology;
  struct hwloc_x86_backend_data_s *data = backend->private_data;
  unsigned nbprocs = data->nbprocs;
  hwloc_bitmap_t complete_cpuset = hwloc_bitmap_alloc();
  unsigned i, j, l, level, type;
  unsigned nbpackages = 0;
  int one = -1;
  unsigned next_group_depth = topology->next_group_depth;

  for (i = 0; i < nbprocs; i++)
    if (infos[i].present) {
      hwloc_bitmap_set(complete_cpuset, i);
      one = i;
    }

  if (one == -1) {
    hwloc_bitmap_free(complete_cpuset);
    return;
  }

  /* Ideally, when fulldiscovery=0, we could add any object that doesn't exist yet.
   * But what if the x86 and the native backends disagree because one is buggy? Which one to trust?
   * Only annotate existing objects for now.
   */

 /*Anotate previously existing objects*/
  if(!fulldiscovery){
    hwloc_obj_t pu;
    nbpackages = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_PACKAGE);
    for(pu = hwloc_get_next_obj_by_type(topology,HWLOC_OBJ_PU  ,NULL);
     pu!=NULL;
     pu = hwloc_get_next_obj_by_type(topology,HWLOC_OBJ_PU ,pu)){
      unsigned infoId = pu->os_index;
      if(infoId<0)
        continue;
      
      int numCaches = infos[infoId].numcaches;
      struct cacheinfo **caches = malloc(numCaches*sizeof(struct cacheinfo*));
      int i;
      for(i = 0 ;i<numCaches;i++){
        caches[i] = &(infos[infoId].cache[i]);
      }


      hwloc_obj_t object;
      for(object = pu;object!=NULL;object = object->parent) {
        switch(object->type){
        /* Annotate packages previously-existing cache */
        case HWLOC_OBJ_CACHE:
          {
            if (hwloc_obj_get_info_by_name(object,"inclusiveness"))
              break;
            unsigned char type = 0;
            switch(object->attr->cache.type){
              case HWLOC_OBJ_CACHE_DATA : type = 1;
                break;
              case HWLOC_OBJ_CACHE_INSTRUCTION : type = 2;
                break;
              case HWLOC_OBJ_CACHE_UNIFIED : type = 3;
                break;
            }
            int cacheId =-1; 
            for(i=0;i<numCaches;i++)
              if(caches[i]->level == object->attr->cache.depth){ // the level is exact, not always the type. If at the level there is a cache with the good type we return it. Else we return a random cache of the level. 
                cacheId = i;
                if(caches[i]->type == type)
                  break;
              }
            if (cacheId >= 0)
                hwloc_obj_add_info(object,"inclusiveness",caches[cacheId]->inclusiveness?"true":"false");

          }
          break;
        case HWLOC_OBJ_PACKAGE:
          { 
            /* Annotate packages previously-existing package */
	    // FIXME: ideally, we should check all bits in case x86 and the native backend disagree. 
	       
            //We already know the pakage from topology-linux. We only check if the package detected by x86 doesn't disagree
	    if (infos[i].packageid == object->os_index || object->os_index == (unsigned) -1) { 
	      hwloc_x86_add_cpuinfos(object, &infos[infoId], 1);
            }
          }
        break;
	default:
	break;
	}
      }
      free(caches);
    }
  }


  /* Look for packages */
  if (fulldiscovery) {
    hwloc_bitmap_t packages_cpuset = hwloc_bitmap_dup(complete_cpuset);
    hwloc_bitmap_t package_cpuset;
    hwloc_obj_t package;

    while ((i = hwloc_bitmap_first(packages_cpuset)) != (unsigned) -1) {
      unsigned packageid = infos[i].packageid;

      package_cpuset = hwloc_bitmap_alloc();
      for (j = i; j < nbprocs; j++) {
        if (infos[j].packageid == packageid) {
          hwloc_bitmap_set(package_cpuset, j);
          hwloc_bitmap_clr(packages_cpuset, j);
        }
      }
      package = hwloc_alloc_setup_object(HWLOC_OBJ_PACKAGE, packageid);
      package->cpuset = package_cpuset;

      hwloc_x86_add_cpuinfos(package, &infos[i], 0);

      hwloc_debug_1arg_bitmap("os package %u has cpuset %s\n",
          packageid, package_cpuset);
      hwloc_insert_object_by_cpuset(topology, package);
      nbpackages++;
    }
    hwloc_bitmap_free(packages_cpuset);

  }

  /* If there was no package, annotate the Machine instead */
  if ((!nbpackages) && infos[0].cpumodel[0]) {
    hwloc_x86_add_cpuinfos(hwloc_get_root_obj(topology), &infos[0], 1);
  }

  /* Look for Numa nodes inside packages */
  if (fulldiscovery) {
    hwloc_bitmap_t nodes_cpuset = hwloc_bitmap_dup(complete_cpuset);
    hwloc_bitmap_t node_cpuset;
    hwloc_obj_t node;

    /* FIXME: if there's memory inside the root object, divide it into NUMA nodes? */

    while ((i = hwloc_bitmap_first(nodes_cpuset)) != (unsigned) -1) {
      unsigned packageid = infos[i].packageid;
      unsigned nodeid = infos[i].nodeid;

      if (nodeid == (unsigned)-1) {
        hwloc_bitmap_clr(nodes_cpuset, i);
	continue;
      }

      node_cpuset = hwloc_bitmap_alloc();
      for (j = i; j < nbprocs; j++) {
	if (infos[j].nodeid == (unsigned) -1) {
	  hwloc_bitmap_clr(nodes_cpuset, j);
	  continue;
	}

        if (infos[j].packageid == packageid && infos[j].nodeid == nodeid) {
          hwloc_bitmap_set(node_cpuset, j);
          hwloc_bitmap_clr(nodes_cpuset, j);
        }
      }
      node = hwloc_alloc_setup_object(HWLOC_OBJ_NUMANODE, nodeid);
      node->cpuset = node_cpuset;
      node->nodeset = hwloc_bitmap_alloc();
      hwloc_bitmap_set(node->nodeset, nodeid);
      hwloc_debug_1arg_bitmap("os node %u has cpuset %s\n",
          nodeid, node_cpuset);
      hwloc_insert_object_by_cpuset(topology, node);
    }
    hwloc_bitmap_free(nodes_cpuset);
  }

  /* Look for Compute units inside packages */
  if (fulldiscovery) {
    hwloc_bitmap_t units_cpuset = hwloc_bitmap_dup(complete_cpuset);
    hwloc_bitmap_t unit_cpuset;
    hwloc_obj_t unit;

    while ((i = hwloc_bitmap_first(units_cpuset)) != (unsigned) -1) {
      unsigned packageid = infos[i].packageid;
      unsigned unitid = infos[i].unitid;

      if (unitid == (unsigned)-1) {
        hwloc_bitmap_clr(units_cpuset, i);
	continue;
      }

      unit_cpuset = hwloc_bitmap_alloc();
      for (j = i; j < nbprocs; j++) {
	if (infos[j].unitid == (unsigned) -1) {
	  hwloc_bitmap_clr(units_cpuset, j);
	  continue;
	}

        if (infos[j].packageid == packageid && infos[j].unitid == unitid) {
          hwloc_bitmap_set(unit_cpuset, j);
          hwloc_bitmap_clr(units_cpuset, j);
        }
      }
      unit = hwloc_alloc_setup_object(HWLOC_OBJ_GROUP, unitid);
      unit->cpuset = unit_cpuset;
      hwloc_debug_1arg_bitmap("os unit %u has cpuset %s\n",
          unitid, unit_cpuset);
      hwloc_insert_object_by_cpuset(topology, unit);
    }
    hwloc_bitmap_free(units_cpuset);
  }

  /* Look for unknown objects */
  if (infos[one].otherids) {
    for (level = infos[one].levels-1; level <= infos[one].levels-1; level--) {
      if (infos[one].otherids[level] != UINT_MAX) {
	hwloc_bitmap_t unknowns_cpuset = hwloc_bitmap_dup(complete_cpuset);
	hwloc_bitmap_t unknown_cpuset;
	hwloc_obj_t unknown_obj;

	while ((i = hwloc_bitmap_first(unknowns_cpuset)) != (unsigned) -1) {
	  unsigned unknownid = infos[i].otherids[level];

	  unknown_cpuset = hwloc_bitmap_alloc();
	  for (j = i; j < nbprocs; j++) {
	    if (infos[j].otherids[level] == unknownid) {
	      hwloc_bitmap_set(unknown_cpuset, j);
	      hwloc_bitmap_clr(unknowns_cpuset, j);
	    }
	  }
	  unknown_obj = hwloc_alloc_setup_object(HWLOC_OBJ_GROUP, unknownid);
	  unknown_obj->cpuset = unknown_cpuset;
	  unknown_obj->attr->group.depth = topology->next_group_depth + level;
	  if (next_group_depth <= topology->next_group_depth + level)
	    next_group_depth = topology->next_group_depth + level + 1;
	  hwloc_debug_2args_bitmap("os unknown%d %u has cpuset %s\n",
	      level, unknownid, unknown_cpuset);
	  hwloc_insert_object_by_cpuset(topology, unknown_obj);
	}
	hwloc_bitmap_free(unknowns_cpuset);
      }
    }
  }

  /* Look for cores */
  if (fulldiscovery) {
    hwloc_bitmap_t cores_cpuset = hwloc_bitmap_dup(complete_cpuset);
    hwloc_bitmap_t core_cpuset;
    hwloc_obj_t core;

    while ((i = hwloc_bitmap_first(cores_cpuset)) != (unsigned) -1) {
      unsigned packageid = infos[i].packageid;
      unsigned coreid = infos[i].coreid;

      if (coreid == (unsigned) -1) {
        hwloc_bitmap_clr(cores_cpuset, i);
	continue;
      }

      core_cpuset = hwloc_bitmap_alloc();
      for (j = i; j < nbprocs; j++) {
	if (infos[j].coreid == (unsigned) -1) {
	  hwloc_bitmap_clr(cores_cpuset, j);
	  continue;
	}

        if (infos[j].packageid == packageid && infos[j].coreid == coreid) {
          hwloc_bitmap_set(core_cpuset, j);
          hwloc_bitmap_clr(cores_cpuset, j);
        }
      }
      core = hwloc_alloc_setup_object(HWLOC_OBJ_CORE, coreid);
      core->cpuset = core_cpuset;
      hwloc_debug_1arg_bitmap("os core %u has cpuset %s\n",
          coreid, core_cpuset);
      hwloc_insert_object_by_cpuset(topology, core);
    }
    hwloc_bitmap_free(cores_cpuset);
  }

  /* Look for caches */
  /* First find max level */
  level = 0;
  for (i = 0; i < nbprocs; i++)
    for (j = 0; j < infos[i].numcaches; j++)
      if (infos[i].cache[j].level > level)
        level = infos[i].cache[j].level;

  /* Look for known types */
  if (fulldiscovery) while (level > 0) {
    for (type = 1; type <= 3; type++) {
      /* Look for caches of that type at level level */
      {
	hwloc_bitmap_t caches_cpuset = hwloc_bitmap_dup(complete_cpuset);
	hwloc_bitmap_t cache_cpuset;
	hwloc_obj_t cache;

	while ((i = hwloc_bitmap_first(caches_cpuset)) != (unsigned) -1) {
	  unsigned packageid = infos[i].packageid;

	  for (l = 0; l < infos[i].numcaches; l++) {
	    if (infos[i].cache[l].level == level && infos[i].cache[l].type == type)
	      break;
	  }
	  if (l == infos[i].numcaches) {
	    /* no cache Llevel of that type in i */
	    hwloc_bitmap_clr(caches_cpuset, i);
	    continue;
	  }

	  /* Found a matching cache, now look for others sharing it */
	  {
	    unsigned cacheid = infos[i].apicid / infos[i].cache[l].nbthreads_sharing;

	    cache_cpuset = hwloc_bitmap_alloc();
	    for (j = i; j < nbprocs; j++) {
	      unsigned l2;
	      for (l2 = 0; l2 < infos[j].numcaches; l2++) {
		if (infos[j].cache[l2].level == level && infos[j].cache[l2].type == type)
		  break;
	      }
	      if (l2 == infos[j].numcaches) {
		/* no cache Llevel of that type in j */
		hwloc_bitmap_clr(caches_cpuset, j);
		continue;
	      }
	      if (infos[j].packageid == packageid && infos[j].apicid / infos[j].cache[l2].nbthreads_sharing == cacheid) {
		hwloc_bitmap_set(cache_cpuset, j);
		hwloc_bitmap_clr(caches_cpuset, j);
	      }
	    }
	    cache = hwloc_alloc_setup_object(HWLOC_OBJ_CACHE, cacheid);
	    cache->attr->cache.depth = level;
	    cache->attr->cache.size = infos[i].cache[l].size;
	    cache->attr->cache.linesize = infos[i].cache[l].linesize;
	    cache->attr->cache.associativity = infos[i].cache[l].ways;
	    switch (infos[i].cache[l].type) {
	      case 1:
		cache->attr->cache.type = HWLOC_OBJ_CACHE_DATA;
		break;
	      case 2:
		cache->attr->cache.type = HWLOC_OBJ_CACHE_INSTRUCTION;
		break;
	      case 3:
		cache->attr->cache.type = HWLOC_OBJ_CACHE_UNIFIED;
		break;
	    }
            hwloc_obj_add_info(cache,"inclusiveness",infos[i].cache[l].inclusiveness?"true":"false");
	    cache->cpuset = cache_cpuset;
	    hwloc_debug_2args_bitmap("os L%u cache %u has cpuset %s\n",
		level, cacheid, cache_cpuset);
	    hwloc_insert_object_by_cpuset(topology, cache);
	  }
	}
	hwloc_bitmap_free(caches_cpuset);
      }
    }
    level--;
  }

  for (i = 0; i < nbprocs; i++) {
    free(infos[i].cache);
    if (infos[i].otherids)
      free(infos[i].otherids);
  }

  hwloc_bitmap_free(complete_cpuset);
  topology->next_group_depth = next_group_depth;
}

static int
look_procs(struct hwloc_backend *backend, struct procinfo *infos, int fulldiscovery,
	   unsigned highest_cpuid, unsigned highest_ext_cpuid, unsigned *features, enum cpuid_type cpuid_type,
	   int (*get_cpubind)(hwloc_topology_t topology, hwloc_cpuset_t set, int flags),
	   int (*set_cpubind)(hwloc_topology_t topology, hwloc_const_cpuset_t set, int flags))
{
  struct hwloc_x86_backend_data_s *data = backend->private_data;
  struct hwloc_topology *topology = backend->topology;
  unsigned nbprocs = data->nbprocs;
  hwloc_bitmap_t orig_cpuset = NULL;
  hwloc_bitmap_t set = NULL;
  unsigned i;

  if (!data->src_cpuiddump_path) {
    orig_cpuset = hwloc_bitmap_alloc();
    if (get_cpubind(topology, orig_cpuset, HWLOC_CPUBIND_STRICT)) {
      hwloc_bitmap_free(orig_cpuset);
      return -1;
    }
    set = hwloc_bitmap_alloc();
  }

  for (i = 0; i < nbprocs; i++) {
    struct cpuiddump *src_cpuiddump = NULL;
    if (data->src_cpuiddump_path) {
      src_cpuiddump = cpuiddump_read(data->src_cpuiddump_path, i);
    } else {
      hwloc_bitmap_only(set, i);
      hwloc_debug("binding to CPU%d\n", i);
      if (set_cpubind(topology, set, HWLOC_CPUBIND_STRICT)) {
	hwloc_debug("could not bind to CPU%d: %s\n", i, strerror(errno));
	continue;
      }
    }

    look_proc(backend, &infos[i], highest_cpuid, highest_ext_cpuid, features, cpuid_type, src_cpuiddump);

    if (data->src_cpuiddump_path) {
      cpuiddump_free(src_cpuiddump);
    }
  }

  if (!data->src_cpuiddump_path) {
    set_cpubind(topology, orig_cpuset, 0);
    hwloc_bitmap_free(set);
    hwloc_bitmap_free(orig_cpuset);
  }

  if (!data->apicid_unique)
    fulldiscovery = 0;
  summarize(backend, infos, fulldiscovery);
  return fulldiscovery; /* success, but objects added only if fulldiscovery */
}

#if defined HWLOC_FREEBSD_SYS && defined HAVE_CPUSET_SETID
#include <sys/param.h>
#include <sys/cpuset.h>
typedef cpusetid_t hwloc_x86_os_state_t;
static void hwloc_x86_os_state_save(hwloc_x86_os_state_t *state, struct cpuiddump *src_cpuiddump)
{
  if (!src_cpuiddump) {
    /* temporary make all cpus available during discovery */
    cpuset_getid(CPU_LEVEL_CPUSET, CPU_WHICH_PID, -1, state);
    cpuset_setid(CPU_WHICH_PID, -1, 0);
  }
}
static void hwloc_x86_os_state_restore(hwloc_x86_os_state_t *state, struct cpuiddump *src_cpuiddump)
{
  if (!src_cpuiddump) {
    /* restore initial cpuset */
    cpuset_setid(CPU_WHICH_PID, -1, *state);
  }
}
#else /* !defined HWLOC_FREEBSD_SYS || !defined HAVE_CPUSET_SETID */
typedef void * hwloc_x86_os_state_t;
static void hwloc_x86_os_state_save(hwloc_x86_os_state_t *state __hwloc_attribute_unused, struct cpuiddump *src_cpuiddump __hwloc_attribute_unused) { }
static void hwloc_x86_os_state_restore(hwloc_x86_os_state_t *state __hwloc_attribute_unused, struct cpuiddump *src_cpuiddump __hwloc_attribute_unused) { }
#endif /* !defined HWLOC_FREEBSD_SYS || !defined HAVE_CPUSET_SETID */


#define INTEL_EBX ('G' | ('e'<<8) | ('n'<<16) | ('u'<<24))
#define INTEL_EDX ('i' | ('n'<<8) | ('e'<<16) | ('I'<<24))
#define INTEL_ECX ('n' | ('t'<<8) | ('e'<<16) | ('l'<<24))

#define AMD_EBX ('A' | ('u'<<8) | ('t'<<16) | ('h'<<24))
#define AMD_EDX ('e' | ('n'<<8) | ('t'<<16) | ('i'<<24))
#define AMD_ECX ('c' | ('A'<<8) | ('M'<<16) | ('D'<<24))

/* fake cpubind for when nbprocs=1 and no binding support */
static int fake_get_cpubind(hwloc_topology_t topology __hwloc_attribute_unused,
			    hwloc_cpuset_t set __hwloc_attribute_unused,
			    int flags __hwloc_attribute_unused)
{
  return 0;
}
static int fake_set_cpubind(hwloc_topology_t topology __hwloc_attribute_unused,
			    hwloc_const_cpuset_t set __hwloc_attribute_unused,
			    int flags __hwloc_attribute_unused)
{
  return 0;
}

static
int hwloc_look_x86(struct hwloc_backend *backend, int fulldiscovery)
{
  struct hwloc_x86_backend_data_s *data = backend->private_data;
  unsigned nbprocs = data->nbprocs;
  unsigned eax, ebx, ecx = 0, edx;
  unsigned i;
  unsigned highest_cpuid;
  unsigned highest_ext_cpuid;
  /* This stores cpuid features with the same indexing as Linux */
  unsigned features[10] = { 0 };
  struct procinfo *infos = NULL;
  enum cpuid_type cpuid_type = unknown;
  hwloc_x86_os_state_t os_state;
  struct hwloc_binding_hooks hooks;
  struct hwloc_topology_support support;
  struct hwloc_topology_membind_support memsupport __hwloc_attribute_unused;
  int (*get_cpubind)(hwloc_topology_t topology, hwloc_cpuset_t set, int flags) = NULL;
  int (*set_cpubind)(hwloc_topology_t topology, hwloc_const_cpuset_t set, int flags) = NULL;
  struct cpuiddump *src_cpuiddump = NULL;
  int ret = -1;

  if (data->src_cpuiddump_path) {
    /* just read cpuid from the dump */
    src_cpuiddump = cpuiddump_read(data->src_cpuiddump_path, 0);
  } else {
    /* otherwise check if binding works */
    memset(&hooks, 0, sizeof(hooks));
    support.membind = &memsupport;
    hwloc_set_native_binding_hooks(&hooks, &support);
    if (hooks.get_thisproc_cpubind && hooks.set_thisproc_cpubind) {
      get_cpubind = hooks.get_thisproc_cpubind;
      set_cpubind = hooks.set_thisproc_cpubind;
    } else if (hooks.get_thisthread_cpubind && hooks.set_thisthread_cpubind) {
      get_cpubind = hooks.get_thisthread_cpubind;
      set_cpubind = hooks.set_thisthread_cpubind;
    } else {
      /* we need binding support if there are multiple PUs */
      if (nbprocs > 1)
	goto out;
      get_cpubind = fake_get_cpubind;
      set_cpubind = fake_set_cpubind;
    }
  }

  if (!src_cpuiddump && !hwloc_have_x86_cpuid())
    goto out;

  infos = calloc(nbprocs, sizeof(struct procinfo));
  if (NULL == infos)
    goto out;
  for (i = 0; i < nbprocs; i++) {
    infos[i].nodeid = (unsigned) -1;
    infos[i].packageid = (unsigned) -1;
    infos[i].unitid = (unsigned) -1;
    infos[i].coreid = (unsigned) -1;
    infos[i].threadid = (unsigned) -1;
  }

  eax = 0x00;
  cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
  highest_cpuid = eax;
  if (ebx == INTEL_EBX && ecx == INTEL_ECX && edx == INTEL_EDX)
    cpuid_type = intel;
  if (ebx == AMD_EBX && ecx == AMD_ECX && edx == AMD_EDX)
    cpuid_type = amd;

  hwloc_debug("highest cpuid %x, cpuid type %u\n", highest_cpuid, cpuid_type);
  if (highest_cpuid < 0x01) {
      goto out_with_infos;
  }

  eax = 0x01;
  cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
  features[0] = edx;
  features[4] = ecx;

  eax = 0x80000000;
  cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
  highest_ext_cpuid = eax;

  hwloc_debug("highest extended cpuid %x\n", highest_ext_cpuid);

  if (highest_cpuid >= 0x7) {
    eax = 0x7;
    cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
    features[9] = ebx;
  }

  if (cpuid_type != intel && highest_ext_cpuid >= 0x80000001) {
    eax = 0x80000001;
    cpuid_or_from_dump(&eax, &ebx, &ecx, &edx, src_cpuiddump);
    features[1] = edx;
    features[6] = ecx;
  }

  hwloc_x86_os_state_save(&os_state, src_cpuiddump);

  ret = look_procs(backend, infos, fulldiscovery,
		   highest_cpuid, highest_ext_cpuid, features, cpuid_type,
		   get_cpubind, set_cpubind);
  if (ret >= 0)
    /* success, we're done */
    goto out_with_os_state;

  if (nbprocs == 1) {
    /* only one processor, no need to bind */
    look_proc(backend, &infos[0], highest_cpuid, highest_ext_cpuid, features, cpuid_type, src_cpuiddump);
    summarize(backend, infos, fulldiscovery);
    ret = fulldiscovery;
  }

out_with_os_state:
  hwloc_x86_os_state_restore(&os_state, src_cpuiddump);

out_with_infos:
  if (NULL != infos) {
      free(infos);
  }

out:
  if (src_cpuiddump)
    cpuiddump_free(src_cpuiddump);
  return ret;
}

static int
hwloc_x86_discover(struct hwloc_backend *backend)
{
  struct hwloc_x86_backend_data_s *data = backend->private_data;
  struct hwloc_topology *topology = backend->topology;
  int alreadypus = 0;
  int ret;

  if (!data->src_cpuiddump_path) {
    data->nbprocs = hwloc_fallback_nbprocessors(topology);

    if (!topology->is_thissystem) {
      hwloc_debug("%s", "\nno x86 detection (not thissystem)\n");
      return 0;
    }
  }

  if (topology->levels[0][0]->cpuset) {
    /* somebody else discovered things */
    if (topology->nb_levels == 2 && topology->level_nbobjects[1] == data->nbprocs) {
      /* only PUs were discovered, as much as we would, complete the topology with everything else */
      alreadypus = 1;
      goto fulldiscovery;
    }

    /* several object types were added, we can't easily complete, just annotate a bit */
    ret = hwloc_look_x86(backend, 0);
    if (ret)
      hwloc_obj_add_info(topology->levels[0][0], "Backend", "x86");
    return 0;
  } else {
    /* topology is empty, initialize it */
    hwloc_alloc_obj_cpusets(topology->levels[0][0]);
  }

fulldiscovery:
  hwloc_look_x86(backend, 1);
  /* if failed, just continue and create PUs */

  if (!alreadypus)
    hwloc_setup_pu_level(topology, data->nbprocs);

  hwloc_obj_add_info(topology->levels[0][0], "Backend", "x86");

  if (!data->src_cpuiddump_path) { /* CPUID dump works for both x86 and x86_64 */
#ifdef HAVE_UNAME
    hwloc_add_uname_info(topology, NULL); /* we already know is_thissystem() is true */
#else
    /* uname isn't available, manually setup the "Architecture" info */
#ifdef HWLOC_X86_64_ARCH
    hwloc_obj_add_info(topology->levels[0][0], "Architecture", "x86_64");
#else
    hwloc_obj_add_info(topology->levels[0][0], "Architecture", "x86");
#endif
#endif
  }

  return 1;
}

static int
hwloc_x86_check_cpuiddump_input(const char *src_cpuiddump_path, hwloc_bitmap_t set)
{
  struct dirent *dirent;
  DIR *dir;
  char *path;
  FILE *file;
  char line [32];

  dir = opendir(src_cpuiddump_path);
  if (!dir)
    return -1;

  path = malloc(strlen(src_cpuiddump_path) + strlen("/hwloc-cpuid-info") + 1);
  if (!path)
    goto out_with_dir;

  sprintf(path, "%s/hwloc-cpuid-info", src_cpuiddump_path);
  file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "Couldn't open dumped cpuid summary %s\n", path);
    free(path);
    goto out_with_dir;
  }
  if (!fgets(line, sizeof(line), file)) {
    fprintf(stderr, "Found read dumped cpuid summary in %s\n", path);
    fclose(file);
    free(path);
    goto out_with_dir;
  }
  fclose(file);
  if (strcmp(line, "Architecture: x86\n")) {
    fprintf(stderr, "Found non-x86 dumped cpuid summary in %s: %s\n", path, line);
    free(path);
    goto out_with_dir;
  }
  free(path);

  while ((dirent = readdir(dir)) != NULL) {
    if (!strncmp(dirent->d_name, "pu", 2)) {
      char *end;
      unsigned long idx = strtoul(dirent->d_name+2, &end, 10);
      if (!*end)
	hwloc_bitmap_set(set, idx);
      else
	fprintf(stderr, "Ignoring invalid dirent `%s' in dumped cpuid directory `%s'\n",
		dirent->d_name, src_cpuiddump_path);
    }
  }
  closedir(dir);

  if (hwloc_bitmap_iszero(set)) {
    fprintf(stderr, "Did not find any valid pu%%u entry in dumped cpuid directory `%s'\n",
	    src_cpuiddump_path);
    return -1;
  } else if (hwloc_bitmap_last(set) != hwloc_bitmap_weight(set) - 1) {
    /* The x86 backends enforces contigous set of PUs starting at 0 so far */
    fprintf(stderr, "Found non-contigous pu%%u range in dumped cpuid directory `%s'\n",
	    src_cpuiddump_path);
    return -1;
  }

  return 0;

out_with_dir:
  closedir(dir);
  return -1;
}

static void
hwloc_x86_backend_disable(struct hwloc_backend *backend)
{
  struct hwloc_x86_backend_data_s *data = backend->private_data;
  hwloc_bitmap_free(data->apicid_set);
  if (data->src_cpuiddump_path)
    free(data->src_cpuiddump_path);
  free(data);
}

static struct hwloc_backend *
hwloc_x86_component_instantiate(struct hwloc_disc_component *component,
				const void *_data1 __hwloc_attribute_unused,
				const void *_data2 __hwloc_attribute_unused,
				const void *_data3 __hwloc_attribute_unused)
{
  struct hwloc_backend *backend;
  struct hwloc_x86_backend_data_s *data;
  const char *src_cpuiddump_path;

  backend = hwloc_backend_alloc(component);
  if (!backend)
    goto out;

  data = malloc(sizeof(*data));
  if (!data) {
    errno = ENOMEM;
    goto out_with_backend;
  }

  backend->private_data = data;
  backend->flags = HWLOC_BACKEND_FLAG_NEED_LEVELS;
  backend->discover = hwloc_x86_discover;
  backend->disable = hwloc_x86_backend_disable;

  /* default values */
  data->apicid_set = hwloc_bitmap_alloc();
  data->apicid_unique = 1;
  data->src_cpuiddump_path = NULL;

  src_cpuiddump_path = getenv("HWLOC_CPUID_PATH");
  if (src_cpuiddump_path) {
    hwloc_bitmap_t set = hwloc_bitmap_alloc();
    if (!hwloc_x86_check_cpuiddump_input(src_cpuiddump_path, set)) {
      backend->is_thissystem = 0;
      data->src_cpuiddump_path = strdup(src_cpuiddump_path);
      data->nbprocs = hwloc_bitmap_weight(set);
    } else {
      fprintf(stderr, "Ignoring dumped cpuid directory.\n");
    }
    hwloc_bitmap_free(set);
  }

  return backend;

 out_with_backend:
  free(backend);
 out:
  return NULL;
}

static struct hwloc_disc_component hwloc_x86_disc_component = {
  HWLOC_DISC_COMPONENT_TYPE_CPU,
  "x86",
  HWLOC_DISC_COMPONENT_TYPE_GLOBAL,
  hwloc_x86_component_instantiate,
  45, /* between native and no_os */
  NULL
};

const struct hwloc_component hwloc_x86_component = {
  HWLOC_COMPONENT_ABI,
  NULL, NULL,
  HWLOC_COMPONENT_TYPE_DISC,
  0,
  &hwloc_x86_disc_component
};
