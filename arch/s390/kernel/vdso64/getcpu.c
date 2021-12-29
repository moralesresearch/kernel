// SPDX-License-Identifier: GPL-2.0
/* Copyright IBM Corp. 2020 */

#include <linux/compiler.h>
#include <linux/getcpu.h>
#include <asm/timex.h>
#include "vdso.h"

int __s390_vdso_getcpu(unsigned *cpu, unsigned *node, struct getcpu_cache *unused)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	union tod_clock clk;

	/* CPU number is stored in the programmable field of the TOD clock */
	store_tod_clock_ext(&clk);
	if (cpu)
		*cpu = clk.pf;
<<<<<<< HEAD
=======
=======
	__u16 todval[8];

	/* CPU number is stored in the programmable field of the TOD clock */
	get_tod_clock_ext((char *)todval);
	if (cpu)
		*cpu = todval[7];
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	/* NUMA node is always zero */
	if (node)
		*node = 0;
	return 0;
}
