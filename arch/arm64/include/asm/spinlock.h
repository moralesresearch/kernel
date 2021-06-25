/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#ifndef __ASM_SPINLOCK_H
#define __ASM_SPINLOCK_H

<<<<<<< HEAD
#include <asm/qspinlock.h>
#include <asm/qrwlock.h>
=======
#include <asm/qrwlock.h>
#include <asm/qspinlock.h>
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

/* See include/linux/spinlock.h */
#define smp_mb__after_spinlock()	smp_mb()

/*
 * Changing this will break osq_lock() thanks to the call inside
 * smp_cond_load_relaxed().
 *
 * See:
 * https://lore.kernel.org/lkml/20200110100612.GC2827@hirez.programming.kicks-ass.net
 */
#define vcpu_is_preempted vcpu_is_preempted
static inline bool vcpu_is_preempted(int cpu)
{
	return false;
}

#endif /* __ASM_SPINLOCK_H */
