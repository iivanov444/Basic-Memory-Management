#include "custom_helper_headers/custom_types.h"

void *custom_sbrk(custom_intptr_t increment) {
    void *current_break;
    void *new_break;
    long result;
    
    /* Get current break value - Linux ARM64 */
    __asm__ volatile (
        "mov x8, #214\n"              /* Set x8 to the syscall number for brk */
        "mov x0, xzr\n"            	/* Move zero into x0 (xzr is zero register) */
        "svc #0\n"                     	/* Invoke the SuperVisor call */
        : "=r" (current_break)          /* Output: result goes to current_break variable */
        : 
        : "x8", "memory"        	/* Clobbered registers - lists all registers, flags, memory-locations etc. that gets modified in the assembler code */
    );
    
    if (increment == 0) return current_break;
    
    /* Calculate new break */
    new_break = (char*)current_break + increment;
    
    /* Set new break - Linux ARM64 */
    __asm__ volatile (
        "mov x8, #214\n"              /* Set x8 to the syscall number for brk */
        "svc #0\n"                     	/* Invoke the SuperVisor call */
        : "=r" (result)                 /* Output: result from the Linux syscall */
        : "r" (new_break)               /* Input: new_break in x0 */
        : "x8", "memory"        	/* Clobbered registers */
    );
    
    return ((void*)result == new_break) ? current_break : (void*)-1;
    /* current_break  ->  success
       (void*)-1      ->  error */
}

/* https://github.com/torvalds/linux/blob/master/tools/scripts/syscall.tbl */
