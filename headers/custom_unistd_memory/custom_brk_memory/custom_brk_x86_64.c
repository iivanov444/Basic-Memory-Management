#include "custom_helper_headers/custom_types.h"

int custom_brk(void *absolute_address) {
    long result;
    
    /* IMPORTANT: brk(0); -> Integer 0 is converted to (void*)0 */
    if (absolute_address == 0) return 0;       /* Success - standard brk */

    /* Set new break - Linux x86-64 */
    __asm__ volatile (
        "mov $12, %%rax\n"              /* Set rax to the syscall number for brk */
        "syscall\n"                     /* Invoke the syscall */
        : "=a" (result)                 /* Output: result from the Linux syscall in rax */
        : "D" (absolute_address)        /* Input: absolute_address in rdi */
        : "rcx", "r11", "memory"        /* Clobbered registers */
    );
    
    return ((void*)result == absolute_address) ? 0 : -1;
    /* 0 -> success
      -1 -> error */
}

/* https://github.com/torvalds/linux/blob/master/arch/x86/entry/syscalls/syscall_64.tbl */
