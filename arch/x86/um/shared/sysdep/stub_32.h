/*
 * Copyright (C) 2004 Jeff Dike (jdike@addtoit.com)
 * Licensed under the GPL
 */

#ifndef __SYSDEP_STUB_H
#define __SYSDEP_STUB_H

#include <asm/ptrace.h>
<<<<<<< HEAD
#include <generated/asm-offsets.h>

=======

#define STUB_SYSCALL_RET EAX
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#define STUB_MMAP_NR __NR_mmap2
#define MMAP_OFFSET(o) ((o) >> UM_KERN_PAGE_SHIFT)

static inline long stub_syscall0(long syscall)
{
	long ret;

	__asm__ volatile ("int $0x80" : "=a" (ret) : "0" (syscall));

	return ret;
}

static inline long stub_syscall1(long syscall, long arg1)
{
	long ret;

	__asm__ volatile ("int $0x80" : "=a" (ret) : "0" (syscall), "b" (arg1));

	return ret;
}

static inline long stub_syscall2(long syscall, long arg1, long arg2)
{
	long ret;

	__asm__ volatile ("int $0x80" : "=a" (ret) : "0" (syscall), "b" (arg1),
			"c" (arg2));

	return ret;
}

static inline long stub_syscall3(long syscall, long arg1, long arg2, long arg3)
{
	long ret;

	__asm__ volatile ("int $0x80" : "=a" (ret) : "0" (syscall), "b" (arg1),
			"c" (arg2), "d" (arg3));

	return ret;
}

static inline long stub_syscall4(long syscall, long arg1, long arg2, long arg3,
				 long arg4)
{
	long ret;

	__asm__ volatile ("int $0x80" : "=a" (ret) : "0" (syscall), "b" (arg1),
			"c" (arg2), "d" (arg3), "S" (arg4));

	return ret;
}

static inline long stub_syscall5(long syscall, long arg1, long arg2, long arg3,
				 long arg4, long arg5)
{
	long ret;

	__asm__ volatile ("int $0x80" : "=a" (ret) : "0" (syscall), "b" (arg1),
			"c" (arg2), "d" (arg3), "S" (arg4), "D" (arg5));

	return ret;
}

static inline void trap_myself(void)
{
	__asm("int3");
}

<<<<<<< HEAD
static void inline remap_stack_and_trap(void)
{
	__asm__ volatile (
		"movl %%esp,%%ebx ;"
		"andl %0,%%ebx ;"
		"movl %1,%%eax ;"
		"movl %%ebx,%%edi ; addl %2,%%edi ; movl (%%edi),%%edi ;"
		"movl %%ebx,%%ebp ; addl %3,%%ebp ; movl (%%ebp),%%ebp ;"
		"int $0x80 ;"
		"addl %4,%%ebx ; movl %%eax, (%%ebx) ;"
		"int $3"
		: :
		"g" (~(UM_KERN_PAGE_SIZE - 1)),
		"g" (STUB_MMAP_NR),
		"g" (UML_STUB_FIELD_FD),
		"g" (UML_STUB_FIELD_OFFSET),
		"g" (UML_STUB_FIELD_CHILD_ERR),
		"c" (UM_KERN_PAGE_SIZE),
		"d" (PROT_READ | PROT_WRITE),
		"S" (MAP_FIXED | MAP_SHARED)
		:
		"memory");
=======
static inline void remap_stack(int fd, unsigned long offset)
{
	__asm__ volatile ("movl %%eax,%%ebp ; movl %0,%%eax ; int $0x80 ;"
			  "movl %7, %%ebx ; movl %%eax, (%%ebx)"
			  : : "g" (STUB_MMAP_NR), "b" (STUB_DATA),
			    "c" (UM_KERN_PAGE_SIZE),
			    "d" (PROT_READ | PROT_WRITE),
			    "S" (MAP_FIXED | MAP_SHARED), "D" (fd),
			    "a" (offset),
			    "i" (&((struct stub_data *) STUB_DATA)->err)
			  : "memory");
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

#endif
