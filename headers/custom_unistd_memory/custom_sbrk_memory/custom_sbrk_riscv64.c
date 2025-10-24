#include "custom_helper_headers/custom_types.h"

void *custom_sbrk(custom_intptr_t increment) {
    void *current_break;
    void *new_break;
    long result;
    
    /* Get current break value - Linux RISC-V 64 */
    __asm__ volatile (
        "li a7, 214\n"              	/* Set a7 to the syscall number for brk */
        "li a0, 0\n"            	/* 0 = get current break */
        "ecall\n"                     	/* Invoke the environment call */
        : "=r" (current_break)          /* Output: result goes to current_break variable in a0 */
        : 
        : "a7", "memory"        	/* Clobbered registers - lists all registers, flags, memory-locations etc. that gets modified in the assembler code */
    );
    
    if (increment == 0) return current_break;
    
    /* Calculate new break */
    new_break = (char*)current_break + increment;
    
    /* Set new break - Linux RISC-V 64 */
    __asm__ volatile (
        "li a7, 214\n"              	/* Set a7 to the syscall number for brk */
        "ecall\n"                     	/* Invoke the environment call */
        : "=r" (result)                 /* Output: result from the Linux syscall */
        : "r" (new_break)               /* Input: new_break in a0 */
        : "a7", "memory"        	/* Clobbered registers */
    );
    
    return ((void*)result == new_break) ? current_break : (void*)-1;
    /* current_break  ->  success
       (void*)-1      ->  error */
}

/* https://github.com/torvalds/linux/blob/master/tools/scripts/syscall.tbl */
