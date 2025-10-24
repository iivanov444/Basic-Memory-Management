#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H


#include "custom_platform_detect.h"


#ifndef CUSTOM_ARCH_DETECTED
	#error "custom_platform_detect.h must be included before custom_types.h"
#endif


#ifdef CUSTOM_USE_COMPATIBILITY
	/* Old compatibility names for C types.  */
	typedef unsigned long int ulong;
	typedef unsigned short int ushort;
	typedef unsigned int uint;
#endif


#if CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_X86_64
	typedef unsigned long		custom_size_t;
	typedef signed long		custom_ssize_t;

	typedef long			custom_ptrdiff_t;
	typedef long			custom_intptr_t;
	typedef unsigned long		custom_uintptr_t;

	#define CUSTOM_SIZE_MAX     	0xFFFFFFFFFFFFFFFFUL
    	#define CUSTOM_SIZE_MIN     	0UL
    	#define CUSTOM_SSIZE_MAX    	0x7FFFFFFFFFFFFFFFL
    	#define CUSTOM_SSIZE_MIN    	0x8000000000000000L
    	#define CUSTOM_PTRDIFF_MAX  	CUSTOM_SSIZE_MAX
    	#define CUSTOM_PTRDIFF_MIN  	CUSTOM_SSIZE_MIN
    	#define CUSTOM_INTPTR_MAX   	CUSTOM_SSIZE_MAX
    	#define CUSTOM_INTPTR_MIN   	CUSTOM_SSIZE_MIN
    	#define CUSTOM_UINTPTR_MAX  	CUSTOM_SIZE_MAX
    	#define CUSTOM_UINTPTR_MIN  	0UL

	#define CUSTOM_ALIGN(x) 	((((x) + 7) >> 3) << 3)	/* 8 byte alignment */


#elif CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_X86_32
	typedef unsigned int		custom_size_t;
	typedef signed int		custom_ssize_t;

	typedef int			custom_ptrdiff_t;
	typedef int			custom_intptr_t;
	typedef unsigned int		custom_uintptr_t;

	#define CUSTOM_SIZE_MAX     	0xFFFFFFFFU
    	#define CUSTOM_SIZE_MIN     	0U
    	#define CUSTOM_SSIZE_MAX    	0x7FFFFFFF
    	#define CUSTOM_SSIZE_MIN    	0x80000000
    	#define CUSTOM_PTRDIFF_MAX  	CUSTOM_SSIZE_MAX
    	#define CUSTOM_PTRDIFF_MIN  	CUSTOM_SSIZE_MIN
    	#define CUSTOM_INTPTR_MAX   	CUSTOM_SSIZE_MAX
    	#define CUSTOM_INTPTR_MIN   	CUSTOM_SSIZE_MIN
    	#define CUSTOM_UINTPTR_MAX  	CUSTOM_SIZE_MAX
    	#define CUSTOM_UINTPTR_MIN  	0U

	#define CUSTOM_ALIGN(x) 	((((x) + 3) >> 2) << 2)	/* 4 byte alignment */


#elif CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_ARM64
	typedef unsigned long		custom_size_t;
	typedef signed long		custom_ssize_t;

	typedef long			custom_ptrdiff_t;
	typedef long			custom_intptr_t;
	typedef unsigned long		custom_uintptr_t;

	#define CUSTOM_SIZE_MAX     	0xFFFFFFFFFFFFFFFFUL
    	#define CUSTOM_SIZE_MIN     	0UL
    	#define CUSTOM_SSIZE_MAX    	0x7FFFFFFFFFFFFFFFL
    	#define CUSTOM_SSIZE_MIN    	0x8000000000000000L
    	#define CUSTOM_PTRDIFF_MAX  	CUSTOM_SSIZE_MAX
    	#define CUSTOM_PTRDIFF_MIN  	CUSTOM_SSIZE_MIN
    	#define CUSTOM_INTPTR_MAX   	CUSTOM_SSIZE_MAX
    	#define CUSTOM_INTPTR_MIN   	CUSTOM_SSIZE_MIN
    	#define CUSTOM_UINTPTR_MAX  	CUSTOM_SIZE_MAX
    	#define CUSTOM_UINTPTR_MIN  	0UL

	#define CUSTOM_ALIGN(x) 	((((x) + 7) >> 3) << 3)	/* 8 byte alignment */


#elif CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_ARM32
	typedef unsigned int		custom_size_t;
	typedef signed int		custom_ssize_t;

	typedef int			custom_ptrdiff_t;
	typedef int			custom_intptr_t;
	typedef unsigned int		custom_uintptr_t;

	#define CUSTOM_SIZE_MAX     	0xFFFFFFFFU
    	#define CUSTOM_SIZE_MIN     	0U
    	#define CUSTOM_SSIZE_MAX    	0x7FFFFFFF
    	#define CUSTOM_SSIZE_MIN    	0x80000000
    	#define CUSTOM_PTRDIFF_MAX  	CUSTOM_SSIZE_MAX
    	#define CUSTOM_PTRDIFF_MIN  	CUSTOM_SSIZE_MIN
    	#define CUSTOM_INTPTR_MAX   	CUSTOM_SSIZE_MAX
    	#define CUSTOM_INTPTR_MIN   	CUSTOM_SSIZE_MIN
    	#define CUSTOM_UINTPTR_MAX  	CUSTOM_SIZE_MAX
    	#define CUSTOM_UINTPTR_MIN  	0U

	#define CUSTOM_ALIGN(x) 	((((x) + 3) >> 2) << 2)	/* 4 byte alignment */


#elif CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_RISCV64
	typedef unsigned long		custom_size_t;
	typedef signed long		custom_ssize_t;

	typedef long			custom_ptrdiff_t;
	typedef long			custom_intptr_t;
	typedef unsigned long		custom_uintptr_t;

	#define CUSTOM_SIZE_MAX     	0xFFFFFFFFFFFFFFFFUL
    	#define CUSTOM_SIZE_MIN     	0UL
    	#define CUSTOM_SSIZE_MAX    	0x7FFFFFFFFFFFFFFFL
    	#define CUSTOM_SSIZE_MIN    	0x8000000000000000L
    	#define CUSTOM_PTRDIFF_MAX  	CUSTOM_SSIZE_MAX
    	#define CUSTOM_PTRDIFF_MIN  	CUSTOM_SSIZE_MIN
    	#define CUSTOM_INTPTR_MAX   	CUSTOM_SSIZE_MAX
    	#define CUSTOM_INTPTR_MIN   	CUSTOM_SSIZE_MIN
    	#define CUSTOM_UINTPTR_MAX  	CUSTOM_SIZE_MAX
    	#define CUSTOM_UINTPTR_MIN  	0UL

	#define CUSTOM_ALIGN(x) 	((((x) + 7) >> 3) << 3)	/* 8 byte alignment */


#elif CUSTOM_ARCH_DETECTED == CUSTOM_ARCH_RISCV32
	typedef unsigned int		custom_size_t;
	typedef signed int		custom_ssize_t;

	typedef int			custom_ptrdiff_t;
	typedef int			custom_intptr_t;
	typedef unsigned int		custom_uintptr_t;

	#define CUSTOM_SIZE_MAX     	0xFFFFFFFFU
    	#define CUSTOM_SIZE_MIN     	0U
    	#define CUSTOM_SSIZE_MAX    	0x7FFFFFFF
    	#define CUSTOM_SSIZE_MIN    	0x80000000
    	#define CUSTOM_PTRDIFF_MAX  	CUSTOM_SSIZE_MAX
    	#define CUSTOM_PTRDIFF_MIN  	CUSTOM_SSIZE_MIN
    	#define CUSTOM_INTPTR_MAX   	CUSTOM_SSIZE_MAX
    	#define CUSTOM_INTPTR_MIN   	CUSTOM_SSIZE_MIN
    	#define CUSTOM_UINTPTR_MAX  	CUSTOM_SIZE_MAX
    	#define CUSTOM_UINTPTR_MIN  	0U

	#define CUSTOM_ALIGN(x) 	((((x) + 3) >> 2) << 2)	/* 4 byte alignment */


#else
	#error "Unsupported architecture."

#endif


/* Boolean type */
typedef unsigned char custom_bool;
#define custom_bool_FALSE 0
#define custom_bool_TRUE 1


/* NULL type */
#ifndef custom_NULL
	#ifdef __cplusplus
		#define custom_NULL 0
	#else
		#define custom_NULL ((void *)0)
	#endif
#endif


#endif	/* CUSTOM_TYPES_H */
