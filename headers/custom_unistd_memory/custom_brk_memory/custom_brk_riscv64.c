#include "custom_helper_headers/custom_types.h"

int custom_brk(void *absolute_address) {
    long result;
    
    /* IMPORTANT: brk(0); -> Integer 0 is converted to (void*)0 */
    if (absolute_address == 0) return 0;       /* Success - standard brk */

    /* Set new break - Linux RISC-V 64 */
    __asm__ volatile (
        "li a7, 214\n"              	/* Set a7 to the syscall number for brk */
        "ecall\n"                     	/* Invoke the environment call */
        : "=r" (result)                 /* Output: result from the Linux syscall in a0 */
        : "r" (absolute_address)        /* Input: absolute_address in a0 */
        : "a7", "memory"        	    /* Clobbered registers */
    );
    
    return ((void*)result == absolute_address) ? 0 : -1;
    /* 0 -> success
      -1 -> error */
}

/* https://github.com/torvalds/linux/blob/master/tools/scripts/syscall.tbl */
