#include "custom_helper_headers/custom_types.h"

int custom_brk(void *absolute_address) {
    long result;
    
    /* IMPORTANT: brk(0); -> Integer 0 is converted to (void*)0 */
    if (absolute_address == 0) return 0;	/* Success - standard brk */

    /* Set new break - Linux x86-32 */
    __asm__ volatile (
        "movl $45, %%eax\n"             	/* Set rax to the syscall number for brk */
        "int $0x80\n"                   	/* Invoke the syscall */
        : "=a" (result)                 	/* Output: result from the Linux syscall in eax */
        : "b" (absolute_address)        	/* Input: new_break in ebx */
        : "ecx", "edx", "esi", "edi", "memory"	/* Clobbered registers */
    );
    
    return ((void*)result == absolute_address) ? 0 : -1;
    /* 0 -> success
      -1 -> error */
}

/* https://github.com/torvalds/linux/blob/master/arch/x86/entry/syscalls/syscall_32.tbl */
