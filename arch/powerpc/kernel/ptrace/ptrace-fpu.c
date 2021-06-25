// SPDX-License-Identifier: GPL-2.0-or-later

#include <linux/regset.h>

#include <asm/switch_to.h>

#include "ptrace-decl.h"

int ptrace_get_fpr(struct task_struct *child, int index, unsigned long *data)
{
<<<<<<< HEAD
#ifdef CONFIG_PPC_FPU_REGS
	unsigned int fpidx = index - PT_FPR0;
#endif
=======
	unsigned int fpidx = index - PT_FPR0;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	if (index > PT_FPSCR)
		return -EIO;

<<<<<<< HEAD
#ifdef CONFIG_PPC_FPU_REGS
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	flush_fp_to_thread(child);
	if (fpidx < (PT_FPSCR - PT_FPR0))
		memcpy(data, &child->thread.TS_FPR(fpidx), sizeof(long));
	else
		*data = child->thread.fp_state.fpscr;
<<<<<<< HEAD
#else
	*data = 0;
#endif
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return 0;
}

int ptrace_put_fpr(struct task_struct *child, int index, unsigned long data)
{
<<<<<<< HEAD
#ifdef CONFIG_PPC_FPU_REGS
	unsigned int fpidx = index - PT_FPR0;
#endif
=======
	unsigned int fpidx = index - PT_FPR0;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	if (index > PT_FPSCR)
		return -EIO;

<<<<<<< HEAD
#ifdef CONFIG_PPC_FPU_REGS
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	flush_fp_to_thread(child);
	if (fpidx < (PT_FPSCR - PT_FPR0))
		memcpy(&child->thread.TS_FPR(fpidx), &data, sizeof(long));
	else
		child->thread.fp_state.fpscr = data;
<<<<<<< HEAD
#endif
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return 0;
}

