#include "custom_helper_headers/custom_types.h"
#include <unistd.h>

void *custom_sbrk(custom_intptr_t increment) {
    void *current_break;
    void *new_break;
    long result;
    
    /* Get current break value - Linux x86-32 */
    __asm__ volatile (
        "movl $45, %%eax\n"             		/* Set eax to the syscall number for brk */
        "xorl %%ebx, %%ebx\n"           		/* XOR ebx with ebx to get 0 */
        "int $0x80\n"                   		/* Invoke the syscall */
        : "=a" (current_break)          		/* Output: result goes to current_break variable */
        : 
        : "ebx", "ecx", "edx", "esi", "edi", "memory"	/* Clobbered registers - lists all registers, flags, memory-locations etc. that gets modified in the assembler code */
    );
    
    if (increment == 0) return current_break;
    
    /* Calculate new break */
    new_break = (char*)current_break + increment;
    
    /* Set new break - Linux x86-32 */
    __asm__ volatile (
        "mov $45, %%eax\n"              	/* Set eax to the syscall number for brk */
        "int $0x80\n"                   	/* Invoke the syscall */
        : "=a" (result)                 	/* Output: result from the Linux syscall in eax */
        : "b" (new_break)               	/* Input: new_break in ebx */
        : "ecx", "edx", "esi", "edi", "memory"	/* Clobbered registers */
    );
    
    return ((void*)result == new_break) ? current_break : (void*)-1;
    /* current_break  ->  success
       (void*)-1      ->  error */
}

/* https://github.com/torvalds/linux/blob/master/arch/x86/entry/syscalls/syscall_32.tbl */
