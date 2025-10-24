#include "custom_helper_headers/custom_types.h"

void *custom_sbrk(custom_intptr_t increment) {
    void *current_break;
    void *new_break;
    long result;
    
    /* Get current break value - Linux ARM32 */
    __asm__ volatile (
        "mov r7, #45\n"              	/* Set r7 to the syscall number for brk */
        "mov r0, #0\n"            	/* Move zero into r0 (ARM32 doesn't have xzr (zero register)) */
        "svc #0\n"                     	/* Invoke the SuperVisor call */
        : "=r" (current_break)          /* Output: result goes to current_break variable */
        : 
        : "r7", "memory"        	/* Clobbered registers - lists all registers, flags, memory-locations etc. that gets modified in the assembler code */
    );
    
    if (increment == 0) return current_break;
    
    /* Calculate new break */
    new_break = (char*)current_break + increment;
    
    /* Set new break - Linux ARM32 */
    __asm__ volatile (
        "mov r7, #45\n"              	/* Set r7 to the syscall number for brk */
        "svc #0\n"                     	/* Invoke the SuperVisor call */
        : "=r" (result)                 /* Output: result from the Linux syscall */
        : "r" (new_break)               /* Input: new_break in r0 */
        : "r7", "memory"        	/* Clobbered registers */
    );
    
    return ((void*)result == new_break) ? current_break : (void*)-1;
    /* current_break  ->  success
       (void*)-1      ->  error */
}

/* https://github.com/torvalds/linux/blob/master/tools/perf/arch/arm/entry/syscalls/syscall.tbl */
