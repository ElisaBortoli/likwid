elisa@elisa-N552VW ~/Scrivania/MHPC/likwid[master*] $ make
===>  ENTER  /home/elisa/Scrivania/MHPC/likwid/ext/hwloc
make[1]: Nessuna operazione da eseguire per "all".
===>  ENTER  /home/elisa/Scrivania/MHPC/likwid/ext/lua
make[1]: Nessuna operazione da eseguire per "all".
===>  CREATE SHARED LIB  liblikwid.so
===>  ENTER  bench
===>  ASSEMBLE  GCC/triad_sp_avx.o
===>  ASSEMBLE  GCC/daxpy_sp_avx_fma.o
===>  ASSEMBLE  GCC/copy.o
===>  ASSEMBLE  GCC/clload.o
===>  ASSEMBLE  GCC/store_mem_avx.o
===>  ASSEMBLE  GCC/load_avx.o
===>  ASSEMBLE  GCC/triad_mem_avx_fma.o
===>  ASSEMBLE  GCC/sum_avx.o
===>  ASSEMBLE  GCC/daxpy_sp_sse_fma.o
===>  ASSEMBLE  GCC/triad_sp_mem_avx_fma.o
===>  ASSEMBLE  GCC/stream_sp_sse.o
===>  ASSEMBLE  GCC/daxpy_sp_mem_avx_fma.o
===>  ASSEMBLE  GCC/sum.o
===>  ASSEMBLE  GCC/copy_sse.o
===>  ASSEMBLE  GCC/load_sse.o
===>  ASSEMBLE  GCC/ddot_avx512.o
===>  ASSEMBLE  GCC/store_sse.o
===>  ASSEMBLE  GCC/daxpy_sp_mem_sse.o
===>  ASSEMBLE  GCC/store_mem_sse.o
===>  ASSEMBLE  GCC/daxpy_avx_fma.o
===>  ASSEMBLE  GCC/stream.o
===>  ASSEMBLE  GCC/daxpy_sp_mem_sse_fma.o
===>  ASSEMBLE  GCC/daxpy_sp.o
===>  ASSEMBLE  GCC/stream_sp_mem_avx_fma.o
===>  ASSEMBLE  GCC/triad_mem_avx.o
===>  ASSEMBLE  GCC/clcopy.o
===>  ASSEMBLE  GCC/update.o
===>  ASSEMBLE  GCC/sum_sp.o
===>  ASSEMBLE  GCC/triad_avx_fma.o
===>  ASSEMBLE  GCC/sum_sp_avx.o
===>  ASSEMBLE  GCC/triad_sp_mem_sse_fma.o
===>  ASSEMBLE  GCC/triad_mem_sse_fma.o
===>  ASSEMBLE  GCC/store_mem.o
===>  ASSEMBLE  GCC/ddot.o
===>  ASSEMBLE  GCC/triad_mem_sse.o
===>  ASSEMBLE  GCC/daxpy.o
===>  ASSEMBLE  GCC/load.o
===>  ASSEMBLE  GCC/daxpy_avx.o
===>  ASSEMBLE  GCC/stream_avx_fma.o
===>  ASSEMBLE  GCC/triad_sse_fma.o
===>  ASSEMBLE  GCC/sum_sp_sse.o
===>  ASSEMBLE  GCC/daxpy_mem_avx.o
===>  ASSEMBLE  GCC/store_avx.o
===>  ASSEMBLE  GCC/daxpy_sp_mem_avx.o
===>  ASSEMBLE  GCC/daxpy_sse_fma.o
===>  ASSEMBLE  GCC/stream_avx512.o
===>  ASSEMBLE  GCC/triad_sp_avx_fma.o
===>  ASSEMBLE  GCC/stream_mem_sse_fma.o
===>  ASSEMBLE  GCC/triad_sp_sse.o
===>  ASSEMBLE  GCC/triad_sp_mem_avx.o
===>  ASSEMBLE  GCC/daxpy_sse.o
===>  ASSEMBLE  GCC/triad_avx512.o
===>  ASSEMBLE  GCC/ddot_avx.o
===>  ASSEMBLE  GCC/triad_sp_mem_sse.o
===>  ASSEMBLE  GCC/store.o
===>  ASSEMBLE  GCC/triad.o
===>  ASSEMBLE  GCC/daxpy_sp_avx.o
===>  ASSEMBLE  GCC/stream_mem_avx.o
===>  ASSEMBLE  GCC/triad_sp_sse_fma.o
===>  ASSEMBLE  GCC/triad_sse.o
===>  ASSEMBLE  GCC/stream_sp_avx_fma.o
===>  ASSEMBLE  GCC/ddot_sse.o
===>  ASSEMBLE  GCC/stream_sp_mem_sse_fma.o
===>  ASSEMBLE  GCC/daxpy_avx512.o
===>  ASSEMBLE  GCC/triad_sp.o
===>  ASSEMBLE  GCC/update_sse.o
===>  ASSEMBLE  GCC/copy_avx512.o
===>  ASSEMBLE  GCC/stream_mem_sse.o
===>  ASSEMBLE  GCC/daxpy_sp_sse.o
===>  ASSEMBLE  GCC/ddot_sp.o
===>  ASSEMBLE  GCC/stream_mem.o
===>  ASSEMBLE  GCC/sum_avx512.o
===>  ASSEMBLE  GCC/stream_sse_fma.o
===>  ASSEMBLE  GCC/stream_sp_mem_avx.o
===>  ASSEMBLE  GCC/copy_avx.o
===>  ASSEMBLE  GCC/update_avx.o
===>  ASSEMBLE  GCC/copy_mem.o
===>  ASSEMBLE  GCC/load_mem.o
===>  ASSEMBLE  GCC/copy_mem_avx.o
===>  ASSEMBLE  GCC/clstore.o
===>  ASSEMBLE  GCC/ddot_sp_sse.o
===>  ASSEMBLE  GCC/triad_avx.o
===>  ASSEMBLE  GCC/store_avx512.o
===>  ASSEMBLE  GCC/stream_avx.o
===>  ASSEMBLE  GCC/stream_sp_mem_sse.o
===>  ASSEMBLE  GCC/daxpy_mem_sse.o
===>  ASSEMBLE  GCC/stream_sp_sse_fma.o
===>  ASSEMBLE  GCC/load_avx512.o
===>  ASSEMBLE  GCC/copy_mem_sse.o
===>  ASSEMBLE  GCC/stream_mem_avx_fma.o
===>  ASSEMBLE  GCC/ddot_sp_avx.o
===>  ASSEMBLE  GCC/stream_sse.o
===>  ASSEMBLE  GCC/update_avx512.o
===>  ASSEMBLE  GCC/daxpy_mem_avx_fma.o
===>  ASSEMBLE  GCC/daxpy_mem_sse_fma.o
===>  ASSEMBLE  GCC/sum_sse.o
===>  ASSEMBLE  GCC/stream_sp.o
===>  LINKING  likwid-bench

elisa@elisa-N552VW ~/Scrivania/MHPC/likwid[master*] $ ls -ltr
totale 11676
-rw-rw-r--  1 elisa elisa     4902 apr  5 10:52 README.md
-rw-rw-r--  1 elisa elisa    30086 apr  5 10:52 Makefile
-rw-rw-r--  1 elisa elisa     8304 apr  5 10:52 INSTALL
-rw-rw-r--  1 elisa elisa    32473 apr  5 10:52 COPYING
-rw-rw-r--  1 elisa elisa     5578 apr  5 10:52 CHANGELOG
drwxrwxr-x  2 elisa elisa     4096 apr  5 10:52 examples
drwxrwxr-x  4 elisa elisa     4096 apr  5 10:52 doc
drwxrwxr-x  4 elisa elisa     4096 apr  5 10:52 ext
drwxrwxr-x  2 elisa elisa     4096 apr  5 10:52 filters
drwxrwxr-x  2 elisa elisa     4096 apr  5 10:52 kernel
drwxrwxr-x 30 elisa elisa     4096 apr  5 10:52 groups
drwxrwxr-x  2 elisa elisa     4096 apr  5 10:52 perl
drwxrwxr-x  4 elisa elisa     4096 apr  5 10:52 packaging
drwxrwxr-x  3 elisa elisa     4096 apr  5 10:52 monitoring
drwxrwxr-x  2 elisa elisa     4096 apr  5 10:52 make
drwxrwxr-x  4 elisa elisa     4096 apr  5 10:52 test
drwxrwxr-x  6 elisa elisa     4096 apr  5 10:52 src
-rw-rw-r--  1 elisa elisa     5695 apr  5 10:56 config.mk
drwxrwxr-x  2 elisa elisa     4096 apr  5 11:04 GCC
-rwxrwxr-x  1 elisa elisa    14456 apr  5 11:04 liblikwidpin.so
-rw-rw-r--  1 elisa elisa    33567 apr  5 11:04 likwid-perfctr
-rw-rw-r--  1 elisa elisa    11220 apr  5 11:04 likwid-pin
-rw-rw-r--  1 elisa elisa    15051 apr  5 11:04 likwid-powermeter
-rw-rw-r--  1 elisa elisa    17209 apr  5 11:04 likwid-topology
-rw-rw-r--  1 elisa elisa     3114 apr  5 11:04 likwid-memsweeper
-rw-rw-r--  1 elisa elisa    78264 apr  5 11:04 likwid-mpirun
-rw-rw-r--  1 elisa elisa     7439 apr  5 11:04 likwid-features
-rw-rw-r--  1 elisa elisa    20138 apr  5 11:04 likwid-perfscope
-rw-rw-r--  1 elisa elisa     6084 apr  5 11:04 likwid-genTopoCfg
-rw-rw-r--  1 elisa elisa    17486 apr  5 11:04 likwid-setFrequencies
-rw-rw-r--  1 elisa elisa    43960 apr  5 11:04 likwid.lua
-rwxrwxr-x  1 elisa elisa    57832 apr  5 11:04 likwid-accessD
-rwxrwxr-x  1 elisa elisa    23816 apr  5 11:04 likwid-setFreq
lrwxrwxrwx  1 elisa elisa       12 ago 31 18:05 liblikwid.so.4.3 -> liblikwid.so
-rwxrwxr-x  1 elisa elisa 11411984 ago 31 18:05 liblikwid.so
-rw-rw-r--  1 elisa elisa      101 ago 31 18:05 likwid-config.cmake
drwxrwxr-x 11 elisa elisa     4096 ago 31 18:05 bench

elisa@elisa-N552VW ~/Scrivania/MHPC/likwid[master*] $ sudo make install
[sudo] password di elisa: 
===> INSTALL access daemon to /usr/local/sbin/likwid-accessD
===> INSTALL setFrequencies tool to /usr/local/sbin/likwid-setFreq
===> INSTALL applications to /usr/local/bin
===> INSTALL helper applications to /usr/local/bin
===> INSTALL lua to likwid interface to /usr/local/share/lua
===> INSTALL libraries to /usr/local/lib
===> INSTALL man pages to /usr/local/man/man1
===> INSTALL headers to /usr/local/include
===> INSTALL groups to /usr/local/share/likwid/perfgroups
===> INSTALL docs and examples to /usr/local/share/likwid/docs
===> INSTALL filters to /usr/local/share/likwid/filter