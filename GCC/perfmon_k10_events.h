/* DONT TOUCH: GENERATED FILE! */

#define NUM_ARCH_EVENTS_K10 330

static PerfmonEvent  k10_arch_events[NUM_ARCH_EVENTS_K10] = {
 {"DISPATCHED_FP_OP_ADD_PIPE", "PMC", 0x00,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCHED_FP_OP_MULTIPLY_PIPE", "PMC", 0x00,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCHED_FP_OP_STORE_PIPE", "PMC", 0x00,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCHED_FP_OP_ADD_PIPE_LOAD", "PMC", 0x00,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCHED_FP_OP_MULTIPLY_PIPE_LOAD", "PMC", 0x00,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCHED_FP_OP_STORE_PIPE_LOAD", "PMC", 0x00,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FPU_EMPTY", "PMC", 0x01,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCHED_FAST_FPU", "PMC", 0x02,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_ADD_SINGLE_UOPS", "PMC", 0x03,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_MULT_SINGLE_UOPS", "PMC", 0x03,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_DIV_SINGLE_UOPS", "PMC", 0x03,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_ADD_DOUBLE_UOPS", "PMC", 0x03,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_MULT_DOUBLE_UOPS", "PMC", 0x03,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_DIV_DOUBLE_UOPS", "PMC", 0x03,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_ADD_SINGLE_FLOPS", "PMC", 0x03,0x41,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_MULT_SINGLE_FLOPS", "PMC", 0x03,0x42,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_DIV_SINGLE_FLOPS", "PMC", 0x03,0x44,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_ADD_DOUBLE_FLOPS", "PMC", 0x03,0x48,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_MULT_DOUBLE_FLOPS", "PMC", 0x03,0x50,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SSE_RETIRED_DIV_DOUBLE_FLOPS", "PMC", 0x03,0x60,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MOVE_RETIRED_LOW_MERGE", "PMC", 0x04,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MOVE_RETIRED_HIGH_MERGE", "PMC", 0x04,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MOVE_RETIRED_MERGE", "PMC", 0x04,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MOVE_RETIRED_ALL", "PMC", 0x04,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SERIAL_RETIRED_SSE_BOTTOM_EXE", "PMC", 0x05,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SERIAL_RETIRED_SSE_BOTTOM_SERIAL", "PMC", 0x05,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SERIAL_RETIRED_X87_BOTTOM_EXE", "PMC", 0x05,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SERIAL_RETIRED_X87_BOTTOM_SERIAL", "PMC", 0x05,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SERIAL_CYCLES_FP_EXE", "PMC", 0x06,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SERIAL_CYCLES_FP_SERIAL", "PMC", 0x06,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"PIPELINE_RESTART_SELF_MOD", "PMC", 0x21,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"PIPELINE_RESTART_PROBE_HIT", "PMC", 0x22,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"LS_BUFFER_FULL", "PMC", 0x23,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"LOCKED_OPERATION_INSTRUCTIONS", "PMC", 0x24,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"LOCKED_OPERATION_SPECULATIVE_CYC", "PMC", 0x24,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"LOCKED_OPERATION_NON_SPECULATIVE_CYC", "PMC", 0x24,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"LOCKED_OPERATION_WAIT_CACHE_HIT_CYC", "PMC", 0x24,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"RETIRED_CLFLUSH", "PMC", 0x26,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"RETIRED_CPUID", "PMC", 0x27,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"STORE_TO_LOAD_FORWARD_CANCEL_ADDRESS_MISMATCH", "PMC", 0x2A,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"STORE_TO_LOAD_FORWARD_CANCEL_SIZE_MISMATCH", "PMC", 0x2A,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"STORE_TO_LOAD_FORWARD_CANCEL_MISALIGNED", "PMC", 0x2A,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"NUM_SMI", "PMC", 0x2B,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_ACCESSES", "PMC", 0x40,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_MISSES", "PMC", 0x41,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_NORTHBRIDGE", "PMC", 0x42,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_L2_SHARED", "PMC", 0x42,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_L2_EXCLUSIVE", "PMC", 0x42,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_L2_OWNED", "PMC", 0x42,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_L2_MODIFIED", "PMC", 0x42,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_L2_ALL", "PMC", 0x42,0x1E,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_NORTHBRIDGE_INVALID", "PMC", 0x43,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_NORTHBRIDGE_SHARED", "PMC", 0x43,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_NORTHBRIDGE_EXCLUSIVE", "PMC", 0x43,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_NORTHBRIDGE_OWNED", "PMC", 0x43,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_NORTHBRIDGE_MODIFIED", "PMC", 0x43,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_REFILLS_NORTHBRIDGE_ALL", "PMC", 0x43,0x1E,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_EVICTED_INVALID", "PMC", 0x44,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_EVICTED_SHARED", "PMC", 0x44,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_EVICTED_EXCLUSIVE", "PMC", 0x44,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_EVICTED_OWNED", "PMC", 0x44,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_EVICTED_MODIFIED", "PMC", 0x44,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_EVICTED_PREFETCH_NTA", "PMC", 0x44,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_EVICTED_NOT_PREFETCH_NTA", "PMC", 0x44,0x40,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_CACHE_EVICTED_ALL", "PMC", 0x44,0x1F,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L2_HIT_4KB", "PMC", 0x45,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L2_HIT_2MB", "PMC", 0x45,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L2_HIT_1GB", "PMC", 0x45,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L2_HIT_ALL", "PMC", 0x45,0x07,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L2_MISS_4KB", "PMC", 0x46,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L2_MISS_2MB", "PMC", 0x46,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L2_MISS_1GB", "PMC", 0x46,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L2_MISS_ALL", "PMC", 0x46,0x07,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MISALIGNED_ACCESS", "PMC", 0x47,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"LATE_CANCEL_ACCESS", "PMC", 0x48,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"EARLY_CANCEL_ACCESS", "PMC", 0x49,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SINGLE_BIT_ERRORS_SCRUBBER", "PMC", 0x4A,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SINGLE_BIT_ERRORS_PIGGYBACK", "PMC", 0x4A,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SINGLE_BIT_ERRORS_LOAD_PIPE", "PMC", 0x4A,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SINGLE_BIT_ERRORS_STORE_PIPE", "PMC", 0x4A,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"PREFETCH_INSTRUCTION_DISPATCHED_LOAD", "PMC", 0x4B,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"PREFETCH_INSTRUCTION_DISPATCHED_STORE", "PMC", 0x4B,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"PREFETCH_INSTRUCTION_DISPATCHED_NTA", "PMC", 0x4B,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DCACHE_LOCK_MISS", "PMC", 0x4C,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L1_HIT_4KB", "PMC", 0x4D,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L1_HIT_2MB", "PMC", 0x4D,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L1_HIT_1GB", "PMC", 0x4D,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DTLB_L1_HIT_ANY", "PMC", 0x4D,0x07,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SW_PREFETCH_HIT_L1", "PMC", 0x52,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SW_PREFETCH_HIT_L2", "PMC", 0x52,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"GLOBAL_TLB_FLUSH", "PMC", 0x54,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MEMORY_REQUEST_NON_CACHEABLE", "PMC", 0x65,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MEMORY_REQUEST_WRITE_COMBINED", "PMC", 0x65,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MEMORY_REQUEST_STREAMING_STORE", "PMC", 0x65,0x80,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_PREFETCHER_CANCELED", "PMC", 0x67,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DATA_PREFETCHER_ATTEMPTS", "PMC", 0x67,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"NORTHBRIDGE_READ_RESPONSE_EXCLUSIVE", "PMC", 0x6C,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"NORTHBRIDGE_READ_RESPONSE_MODIFIED", "PMC", 0x6C,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"NORTHBRIDGE_READ_RESPONSE_SHARED", "PMC", 0x6C,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"NORTHBRIDGE_READ_RESPONSE_ALL", "PMC", 0x6C,0x07,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"NORTHBRIDGE_READ_RESPONSE_OWNED", "PMC", 0x6C,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"NORTHBRIDGE_READ_RESPONSE_DATA_ERROR", "PMC", 0x6C,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"OCTWORDS_WRITE_TRANSFERS", "PMC", 0x6D,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_CLOCKS_UNHALTED", "PMC", 0x76,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_REQUESTS_ICACHE_FILL", "PMC", 0x7D,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_REQUESTS_DCACHE_FILL", "PMC", 0x7D,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_REQUESTS_TLBCACHE_FILL", "PMC", 0x7D,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_REQUESTS_ALL", "PMC", 0x7D,0x07,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_REQUESTS_TAG_SNOOP_REQUEST", "PMC", 0x7D,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_REQUESTS_CANCELLED_REQUEST", "PMC", 0x7D,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_REQUESTS_HARDWARE_PREFETCH", "PMC", 0x7D,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_MISSES_ICACHE_FILL", "PMC", 0x7E,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_MISSES_DCACHE_FILL", "PMC", 0x7E,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_MISSES_TLB_WALK", "PMC", 0x7E,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_MISSES_ALL", "PMC", 0x7E,0x07,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_MISSES_HARDWARE_PREFETCH", "PMC", 0x7E,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_FILL_VICTIMS", "PMC", 0x7F,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_FILL_WRITEBACKS", "PMC", 0x7F,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L2_FILL_ALL", "PMC", 0x7F,0x03,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ICACHE_FETCHES", "PMC", 0x80,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ICACHE_MISSES", "PMC", 0x81,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ICACHE_REFILLS_L2", "PMC", 0x82,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ICACHE_REFILLS_MEM", "PMC", 0x83,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ITLB_L2_HIT", "PMC", 0x84,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ITLB_L2_MISS_4KB", "PMC", 0x85,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ITLB_L2_MISS_2MB", "PMC", 0x85,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ITLB_L2_MISS_ANY", "PMC", 0x85,0x03,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"PIPELINE_RESTART_STREAM_PROBE", "PMC", 0x86,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"INSTRUCTION_FETCH_STALL", "PMC", 0x87,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"RETURN_STACK_HITS", "PMC", 0x88,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"RETURN_STACK_OVERFLOW", "PMC", 0x89,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ICACHE_VICTIMS", "PMC", 0x8B,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ICACHE_LINES_INVALIDATED_NOHIT", "PMC", 0x8C,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ICACHE_LINES_INVALIDATED_HIT", "PMC", 0x8C,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ITLB_RELOADS", "PMC", 0x99,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"ITLB_RELOADS_ABORTED", "PMC", 0x9A,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"INSTRUCTIONS_RETIRED", "PMC", 0xC0,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"UOPS_RETIRED", "PMC", 0xC1,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"BRANCH_RETIRED", "PMC", 0xC2,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"BRANCH_MISPREDICT_RETIRED", "PMC", 0xC3,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"BRANCH_TAKEN_RETIRED", "PMC", 0xC4,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"BRANCH_TAKEN_MISPREDICTED_RETIRED", "PMC", 0xC5,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"TRANSFER_FAR_CONTROL_RETIRED", "PMC", 0xC6,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"BRANCH_RESYNCS_RETIRED", "PMC", 0xC7,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"NEAR_RETURNS_RETIRED", "PMC", 0xC8,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"NEAR_RETURNS_MISPREDICTED_RETIRED", "PMC", 0xC9,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"BRANCH_INDIRECT_MISPREDICT_RETIRED", "PMC", 0xCA,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FP_INSTRUCTIONS_RETIRED_X87", "PMC", 0xCB,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FP_INSTRUCTIONS_RETIRED_MMX", "PMC", 0xCB,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FP_INSTRUCTIONS_RETIRED_SSE", "PMC", 0xCB,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FP_INSTRUCTIONS_RETIRED_ALL", "PMC", 0xCB,0x07,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FASTPATH_RETIRED_0", "PMC", 0xCC,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FASTPATH_RETIRED_1", "PMC", 0xCC,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FASTPATH_RETIRED_2", "PMC", 0xCC,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"INTERRUPTS_MASKED_CYCLES", "PMC", 0xCE,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"INTERRUPTS_TAKEN", "PMC", 0xCF,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DECODER_EMPTY_CYCLES", "PMC", 0xD0,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCH_STALLS", "PMC", 0xD1,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCH_STALLS_BRANCH", "PMC", 0xD2,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCH_STALLS_SERIAL", "PMC", 0xD3,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCH_STALLS_SEGMENT_LOAD", "PMC", 0xD4,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCH_STALLS_ROB_FULL", "PMC", 0xD5,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCH_STALLS_RES_FULL", "PMC", 0xD6,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCH_STALLS_FPU_FULL", "PMC", 0xD7,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCH_STALLS_LS_FULL", "PMC", 0xD8,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCH_STALLS_ALL_QUIT", "PMC", 0xD9,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DISPATCH_STALLS_DRAIN", "PMC", 0xDA,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FPU_EXCEPTIONS_X87_RECLASS", "PMC", 0xDB,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FPU_EXCEPTIONS_SSE_RETYPE", "PMC", 0xDB,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FPU_EXCEPTIONS_SSE_RECLASS", "PMC", 0xDB,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FPU_EXCEPTIONS_MICROTRAPS", "PMC", 0xDB,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"FPU_EXCEPTIONS_ALL", "PMC", 0xDB,0x0F,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"X87_FLOPS_RETIRED_ADD", "PMC", 0x1C0,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"X87_FLOPS_RETIRED_MULT", "PMC", 0x1C0,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"X87_FLOPS_RETIRED_DIV", "PMC", 0x1C0,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"LFENCE_RETIRED", "PMC", 0x1D3,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"SFENCE_RETIRED", "PMC", 0x1D4,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MFENCE_RETIRED", "PMC", 0x1D5,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_ACCESSES_DCT0_HIT", "PMC", 0xE0,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_ACCESSES_DCTO_MISS", "PMC", 0xE0,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_ACCESSES_DCTO_CONFLICT", "PMC", 0xE0,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_ACCESSES_DCTO_ALL", "PMC", 0xE0,0x07,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_ACCESSES_DCT1_HIT", "PMC", 0xE0,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_ACCESSES_DCT1_MISS", "PMC", 0xE0,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_ACCESSES_DCT1_CONFLICT", "PMC", 0xE0,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_ACCESSES_DCT1_ALL", "PMC", 0xE0,0x38,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_PAGE_TABLE_OVERFLOW_ALL", "PMC", 0xE1,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_PAGE_TABLE_OVERFLOW_DCT0", "PMC", 0xE1,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_PAGE_TABLE_OVERFLOW_DCT1", "PMC", 0xE1,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_COMMAND_SLOTS_MISSED_ALL", "PMC", 0xE2,0x00,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_COMMAND_SLOTS_MISSED_DCT0", "PMC", 0xE2,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_COMMAND_SLOTS_MISSED_DCT1", "PMC", 0xE2,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_CONTROLLER_TURNAROUNDS_DCT0_CHIP_SELECT", "PMC", 0xE3,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_CONTROLLER_TURNAROUNDS_DCT0_READ_TO_WRITE", "PMC", 0xE3,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_CONTROLLER_TURNAROUNDS_DCT0_WRITE_TO_READ", "PMC", 0xE3,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_CONTROLLER_TURNAROUNDS_DCT1_CHIP_SELECT", "PMC", 0xE3,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_CONTROLLER_TURNAROUNDS_DCT1_READ_TO_WRITE", "PMC", 0xE3,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_CONTROLLER_TURNAROUNDS_DCT1_WRITE_TO_READ", "PMC", 0xE3,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_CONTROLLER_BYPASS_SATURATION_HIGH", "PMC", 0xE4,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_CONTROLLER_BYPASS_SATURATION_MEDIUM", "PMC", 0xE4,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_CONTROLLER_BYPASS_SATURATION_DCT0", "PMC", 0xE4,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"DRAM_CONTROLLER_BYPASS_SATURATION_DCT1", "PMC", 0xE4,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CACHE_BLOCK_COMMANDS_VICTIM", "PMC", 0xEA,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CACHE_BLOCK_COMMANDS_READ", "PMC", 0xEA,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CACHE_BLOCK_COMMANDS_READ_SHARED", "PMC", 0xEA,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CACHE_BLOCK_COMMANDS_READ_MODIFIED", "PMC", 0xEA,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CACHE_BLOCK_COMMANDS_DIRTY", "PMC", 0xEA,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MEMORY_REQUESTS_WRITE", "PMC", 0x1F0,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MEMORY_REQUESTS_READ", "PMC", 0x1F0,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MEMORY_REQUESTS_PREFETCH", "PMC", 0x1F0,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MEMORY_REQUESTS_WRITE_32", "PMC", 0x1F0,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MEMORY_REQUESTS_WRITE_64", "PMC", 0x1F0,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MEMORY_REQUESTS_READ_32", "PMC", 0x1F0,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MEMORY_REQUESTS_READ_64", "PMC", 0x1F0,0x40,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"MEMORY_REQUESTS_READ_WHILE_WRITE", "PMC", 0x1F0,0x80,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_D_EXCLUSIVE_CORE_0", "PMC", 0x4E0,0x11,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_I_SHARED_CORE_0", "PMC", 0x4E0,0x12,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_MODIFY_CORE_0", "PMC", 0x4E0,0x14,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_D_EXCLUSIVE_CORE_1", "PMC", 0x4E0,0x21,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_I_SHARED_CORE_1", "PMC", 0x4E0,0x22,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_MODIFY_CORE_1", "PMC", 0x4E0,0x24,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_D_EXCLUSIVE_CORE_2", "PMC", 0x4E0,0x41,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_I_SHARED_CORE_2", "PMC", 0x4E0,0x42,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_MODIFY_CORE_2", "PMC", 0x4E0,0x44,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_D_EXCLUSIVE_CORE_3", "PMC", 0x4E0,0x81,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_I_SHARED_CORE_3", "PMC", 0x4E0,0x82,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_MODIFY_CORE_3", "PMC", 0x4E0,0x84,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_ALL_CORE_0", "PMC", 0x4E0,0x17,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_ALL_CORE_1", "PMC", 0x4E0,0x27,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_ALL_CORE_2", "PMC", 0x4E0,0x47,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_ALL_CORE_3", "PMC", 0x4E0,0x87,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_READ_REQUEST_ALL_ALL_CORES", "PMC", 0x4E0,0xF7,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_D_EXCLUSIVE_CORE_0", "PMC", 0x4E1,0x11,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_I_SHARED_CORE_0", "PMC", 0x4E1,0x12,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_MODIFY_CORE_0", "PMC", 0x4E1,0x14,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_D_EXCLUSIVE_CORE_1", "PMC", 0x4E1,0x21,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_I_SHARED_CORE_1", "PMC", 0x4E1,0x22,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_MODIFY_CORE_1", "PMC", 0x4E1,0x24,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_D_EXCLUSIVE_CORE_2", "PMC", 0x4E1,0x41,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_I_SHARED_CORE_2", "PMC", 0x4E1,0x42,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_MODIFY_CORE_2", "PMC", 0x4E1,0x44,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_D_EXCLUSIVE_CORE_3", "PMC", 0x4E1,0x81,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_I_SHARED_CORE_3", "PMC", 0x4E1,0x82,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_MODIFY_CORE_3", "PMC", 0x4E1,0x84,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_ALL_CORE_0", "PMC", 0x4E1,0x17,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_ALL_CORE_1", "PMC", 0x4E1,0x27,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_ALL_CORE_2", "PMC", 0x4E1,0x47,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_ALL_CORE_3", "PMC", 0x4E1,0x87,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_MISSES_ALL_ALL_CORES", "PMC", 0x4E1,0xF7,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_SHARED_CORE_0", "PMC", 0x4E2,0x11,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_EXCLUSIVE_CORE_0", "PMC", 0x4E2,0x12,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_OWNED_CORE_0", "PMC", 0x4E2,0x14,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_MODIFY_CORE_0", "PMC", 0x4E2,0x18,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_SHARED_CORE_1", "PMC", 0x4E2,0x21,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_EXCLUSIVE_CORE_1", "PMC", 0x4E2,0x22,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_OWNED_CORE_1", "PMC", 0x4E2,0x24,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_MODIFY_CORE_1", "PMC", 0x4E2,0x28,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_SHARED_CORE_2", "PMC", 0x4E2,0x41,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_EXCLUSIVE_CORE_2", "PMC", 0x4E2,0x42,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_OWNED_CORE_2", "PMC", 0x4E2,0x44,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_MODIFY_CORE_2", "PMC", 0x4E2,0x48,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_SHARED_CORE_3", "PMC", 0x4E2,0x81,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_EXCLUSIVE_CORE_3", "PMC", 0x4E2,0x82,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_OWNED_CORE_3", "PMC", 0x4E2,0x84,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_MODIFY_CORE_3", "PMC", 0x4E2,0x88,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_SHARED_ALL_CORES", "PMC", 0x4E2,0xF1,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_EXCLUSIVE_ALL_CORES", "PMC", 0x4E2,0xF2,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_OWNED_ALL_CORES", "PMC", 0x4E2,0xF4,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_MODIFY_ALL_CORES", "PMC", 0x4E2,0xF8,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_FILLS_ALL_ALL_CORES", "PMC", 0x4E2,0xFF,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_EVICTS_SHARED", "PMC", 0x4E3,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_EVICTS_EXCLUSIVE", "PMC", 0x4E3,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_EVICTS_OWNED", "PMC", 0x4E3,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"L3_EVICTS_MODIFY", "PMC", 0x4E3,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_TO_DRAM_LOCAL_TO_0", "PMC", 0x1E0,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_TO_DRAM_LOCAL_TO_1", "PMC", 0x1E0,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_TO_DRAM_LOCAL_TO_2", "PMC", 0x1E0,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_TO_DRAM_LOCAL_TO_3", "PMC", 0x1E0,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_TO_DRAM_LOCAL_TO_4", "PMC", 0x1E0,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_TO_DRAM_LOCAL_TO_5", "PMC", 0x1E0,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_TO_DRAM_LOCAL_TO_6", "PMC", 0x1E0,0x40,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_TO_DRAM_LOCAL_TO_7", "PMC", 0x1E0,0x80,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"IO_TO_DRAM_LOCAL_TO_0", "PMC", 0x1E1,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"IO_TO_DRAM_LOCAL_TO_1", "PMC", 0x1E1,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"IO_TO_DRAM_LOCAL_TO_2", "PMC", 0x1E1,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"IO_TO_DRAM_LOCAL_TO_3", "PMC", 0x1E1,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"IO_TO_DRAM_LOCAL_TO_4", "PMC", 0x1E1,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"IO_TO_DRAM_LOCAL_TO_5", "PMC", 0x1E1,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"IO_TO_DRAM_LOCAL_TO_6", "PMC", 0x1E1,0x40,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"IO_TO_DRAM_LOCAL_TO_7", "PMC", 0x1E1,0x80,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_READ_COMMAND_LATENCY_READ_BLOCK", "PMC", 0x1E2,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_READ_COMMAND_LATENCY_READ_BLOCK_SHARED", "PMC", 0x1E2,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_READ_COMMAND_LATENCY_READ_BLOCK_MODIFIED", "PMC", 0x1E2,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_READ_COMMAND_LATENCY_CHANGE_TO_DIRTY", "PMC", 0x1E2,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_READ_COMMAND_LATENCY_LOCAL_TO_0", "PMC", 0x1E2,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_READ_COMMAND_LATENCY_LOCAL_TO_1", "PMC", 0x1E2,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_READ_COMMAND_LATENCY_LOCAL_TO_2", "PMC", 0x1E2,0x40,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"CPU_READ_COMMAND_LATENCY_LOCAL_TO_3", "PMC", 0x1E2,0x80,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK0_COMMAND_DWORD_SENT", "PMC", 0xF6,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK0_DATA_DWORD_SENT", "PMC", 0xF6,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK0_BUFFER_DWORD_SENT", "PMC", 0xF6,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK0_NOP_DWORD_SENT", "PMC", 0xF6,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK0_ADDRESS_DWORD_SENT", "PMC", 0xF6,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK0_PER_PACKET_CRC_SENT", "PMC", 0xF6,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK0_SUBLINK_MASK", "PMC", 0xF6,0x80,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK0_ALL_SENT", "PMC", 0xF6,0x37,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK1_COMMAND_DWORD_SENT", "PMC", 0xF7,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK1_DATA_DWORD_SENT", "PMC", 0xF7,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK1_BUFFER_DWORD_SENT", "PMC", 0xF7,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK1_NOP_DWORD_SENT", "PMC", 0xF7,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK1_ADDRESS_DWORD_SENT", "PMC", 0xF7,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK1_PER_PACKET_CRC_SENT", "PMC", 0xF7,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK1_SUBLINK_MASK", "PMC", 0xF7,0x80,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK1_ALL_SENT", "PMC", 0xF7,0x37,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK2_COMMAND_DWORD_SENT", "PMC", 0xF8,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK2_DATA_DWORD_SENT", "PMC", 0xF8,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK2_BUFFER_DWORD_SENT", "PMC", 0xF8,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK2_NOP_DWORD_SENT", "PMC", 0xF8,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK2_ADDRESS_DWORD_SENT", "PMC", 0xF8,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK2_PER_PACKET_CRC_SENT", "PMC", 0xF8,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK2_SUBLINK_MASK", "PMC", 0xF8,0x80,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK2_ALL_SENT", "PMC", 0xF8,0x37,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK3_COMMAND_DWORD_SENT", "PMC", 0x1F9,0x01,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK3_DATA_DWORD_SENT", "PMC", 0x1F9,0x02,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK3_BUFFER_DWORD_SENT", "PMC", 0x1F9,0x04,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK3_NOP_DWORD_SENT", "PMC", 0x1F9,0x08,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK3_ADDRESS_DWORD_SENT", "PMC", 0x1F9,0x10,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK3_PER_PACKET_CRC_SENT", "PMC", 0x1F9,0x20,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK3_SUBLINK_MASK", "PMC", 0x1F9,0x80,0,0,0,EVENT_OPTION_NONE_MASK,{}}
, {"HYPERTRANSPORT_LINK3_ALL_SENT", "PMC", 0x1F9,0x37,0,0,0,EVENT_OPTION_NONE_MASK,{}}
};
