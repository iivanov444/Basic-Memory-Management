#include "custom_helper_headers/custom_types.h"

int custom_brk(void *absolute_address) {
    long result;
    
    /* IMPORTANT: brk(0); -> Integer 0 is converted to (void*)0 */
    if (absolute_address == 0) return 0;       /* Success - standard brk */

    /* Set new break - Linux ARM64 */
    __asm__ volatile (
        "mov r7, #45\n"              	/* Set r7 to the syscall number for brk */
	    "svc #0\n"                      /* Invoke the SuperVisor Call */
        : "=r" (result)                 /* Output: result from the Linux syscall in r0 */
        : "r" (absolute_address)        /* Input: new_break in any register in r0 */
        : "r7", "memory"                /* Clobbered registers */
    );
    
    return ((void*)result == absolute_address) ? 0 : -1;
    /* 0 -> success
      -1 -> error */
}

/* https://github.com/torvalds/linux/blob/master/tools/perf/arch/arm/entry/syscalls/syscall.tbl */
