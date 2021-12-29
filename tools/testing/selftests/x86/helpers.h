// SPDX-License-Identifier: GPL-2.0-only
#ifndef __SELFTESTS_X86_HELPERS_H
#define __SELFTESTS_X86_HELPERS_H

#include <asm/processor-flags.h>

static inline unsigned long get_eflags(void)
{
<<<<<<< HEAD
#ifdef __x86_64__
	return __builtin_ia32_readeflags_u64();
#else
	return __builtin_ia32_readeflags_u32();
#endif
=======
	unsigned long eflags;

	asm volatile (
#ifdef __x86_64__
		"subq $128, %%rsp\n\t"
		"pushfq\n\t"
		"popq %0\n\t"
		"addq $128, %%rsp"
#else
		"pushfl\n\t"
		"popl %0"
#endif
		: "=r" (eflags) :: "memory");

	return eflags;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static inline void set_eflags(unsigned long eflags)
{
<<<<<<< HEAD
#ifdef __x86_64__
	__builtin_ia32_writeeflags_u64(eflags);
#else
	__builtin_ia32_writeeflags_u32(eflags);
#endif
=======
	asm volatile (
#ifdef __x86_64__
		"subq $128, %%rsp\n\t"
		"pushq %0\n\t"
		"popfq\n\t"
		"addq $128, %%rsp"
#else
		"pushl %0\n\t"
		"popfl"
#endif
		:: "r" (eflags) : "flags", "memory");
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

#endif /* __SELFTESTS_X86_HELPERS_H */
