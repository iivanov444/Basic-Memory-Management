#ifndef CUSTOM_PLATFORM_DETECT_H
#define CUSTOM_PLATFORM_DETECT_H


#ifndef __linux__
	#error "This code works only on Linux operating systems"
#endif


/* Architecture enum */
typedef enum {
	CUSTOM_ARCH_X86_64	= 1,
	CUSTOM_ARCH_X86_32	= 2,
	CUSTOM_ARCH_ARM64	= 3,
	CUSTOM_ARCH_ARM32	= 4,
	CUSTOM_ARCH_RISCV64	= 5,
	CUSTOM_ARCH_RISCV32	= 6
} custom_arch_t;


/* Architecture identification helper */
#ifndef CUSTOM_ARCH_DETECTED
	#if defined(__x86_64__) || defined(__x86_64) || defined(__amd64__) || defined(__amd64)
		#define CUSTOM_ARCH_DETECTED		CUSTOM_ARCH_X86_64
		#define CUSTOM_ARCH_DETECTED_NAME	"x86-64"

	#elif defined(__i386__) || defined(__i386) || defined(i386)
		#define CUSTOM_ARCH_DETECTED		CUSTOM_ARCH_X86_32
		#define CUSTOM_ARCH_DETECTED_NAME	"x86-32"

	#elif defined(__aarch64__)
		#define CUSTOM_ARCH_DETECTED		CUSTOM_ARCH_ARM64
		#define CUSTOM_ARCH_DETECTED_NAME	"ARM64"

	#elif defined(__arm__)
		#define CUSTOM_ARCH_DETECTED		CUSTOM_ARCH_ARM32
		#define CUSTOM_ARCH_DETECTED_NAME	"ARM32"

	#elif defined(__riscv) && (__riscv_xlen == 64)
		#define CUSTOM_ARCH_DETECTED		CUSTOM_ARCH_RISCV64
		#define CUSTOM_ARCH_DETECTED_NAME	"RISC-V 64"

	#elif defined(__riscv) && (__riscv_xlen == 32)
		#define CUSTOM_ARCH_DETECTED		CUSTOM_ARCH_RISCV32
		#define CUSTOM_ARCH_DETECTED_NAME	"RISC-V 32"

	#else
		#error "Unsupported architecture."
	#endif
#endif


#endif	/* CUSTOM_PLATFORM_DETECT_H */
