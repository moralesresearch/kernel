// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Author: Kumar Gala <galak@kernel.crashing.org>
 *
 * Copyright 2009 Freescale Semiconductor Inc.
 */

#include <linux/stddef.h>
#include <linux/kernel.h>
#include <linux/smp.h>
#include <linux/threads.h>
#include <linux/hardirq.h>

#include <asm/dbell.h>
<<<<<<< HEAD
#include <asm/interrupt.h>
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#include <asm/irq_regs.h>
#include <asm/kvm_ppc.h>
#include <asm/trace.h>

#ifdef CONFIG_SMP

<<<<<<< HEAD
DEFINE_INTERRUPT_HANDLER_ASYNC(doorbell_exception)
{
	struct pt_regs *old_regs = set_irq_regs(regs);

=======
void doorbell_exception(struct pt_regs *regs)
{
	struct pt_regs *old_regs = set_irq_regs(regs);

	irq_enter();
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	trace_doorbell_entry(regs);

	ppc_msgsync();

	may_hard_irq_enable();

	kvmppc_clear_host_ipi(smp_processor_id());
	__this_cpu_inc(irq_stat.doorbell_irqs);

	smp_ipi_demux_relaxed(); /* already performed the barrier */

	trace_doorbell_exit(regs);
<<<<<<< HEAD

	set_irq_regs(old_regs);
}
#else /* CONFIG_SMP */
DEFINE_INTERRUPT_HANDLER_ASYNC(doorbell_exception)
=======
	irq_exit();
	set_irq_regs(old_regs);
}
#else /* CONFIG_SMP */
void doorbell_exception(struct pt_regs *regs)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	printk(KERN_WARNING "Received doorbell on non-smp system\n");
}
#endif /* CONFIG_SMP */
<<<<<<< HEAD
=======

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
