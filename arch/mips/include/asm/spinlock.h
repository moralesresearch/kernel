/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1999, 2000, 06 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#ifndef _ASM_SPINLOCK_H
#define _ASM_SPINLOCK_H

#include <asm/processor.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include <asm/qrwlock.h>
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#include <asm-generic/qspinlock_types.h>

#define	queued_spin_unlock queued_spin_unlock
/**
 * queued_spin_unlock - release a queued spinlock
 * @lock : Pointer to queued spinlock structure
 */
static inline void queued_spin_unlock(struct qspinlock *lock)
{
	/* This could be optimised with ARCH_HAS_MMIOWB */
	mmiowb();
	smp_store_release(&lock->locked, 0);
}

#include <asm/qspinlock.h>
<<<<<<< HEAD
#include <asm/qrwlock.h>
=======
<<<<<<< HEAD
#include <asm/qrwlock.h>
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#endif /* _ASM_SPINLOCK_H */
