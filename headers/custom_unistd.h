#ifndef CUSTOM_UNISTD_H
#define CUSTOM_UNISTD_H


#if CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_X86_64
	#include "custom_unistd_memory/custom_brk_memory/custom_brk_x86_64.c"
	#include "custom_unistd_memory/custom_sbrk_memory/custom_sbrk_x86_64.c"


#elif CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_X86_32
	#include "custom_unistd_memory/custom_brk_memory/custom_brk_x86_32.c"
	#include "custom_unistd_memory/custom_sbrk_memory/custom_sbrk_x86_32.c"


#elif CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_ARM64
	#include "custom_unistd_memory/custom_brk_memory/custom_brk_arm64.c"
	#include "custom_unistd_memory/custom_sbrk_memory/custom_sbrk_arm64.c"


#elif CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_ARM32
	#include "custom_unistd_memory/custom_brk_memory/custom_brk_arm32.c"
	#include "custom_unistd_memory/custom_sbrk_memory/custom_sbrk_arm32.c"


#elif CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_RISCV64
	#include "custom_unistd_memory/custom_brk_memory/custom_brk_riscv64.c"
	#include "custom_unistd_memory/custom_sbrk_memory/custom_sbrk_riscv64.c"


#elif CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_RISCV32
	#include "custom_unistd_memory/custom_brk_memory/custom_brk_riscv32.c"
	#include "custom_unistd_memory/custom_sbrk_memory/custom_sbrk_riscv32.c"


#else
	#error "Architecture not supported."
#endif	/* CUSTOM_ARCH_DETECTED */


#endif	/* CUSTOM_UNISTD_H */
