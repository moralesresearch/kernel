/* SPDX-License-Identifier: GPL-2.0 */
#ifndef RAS_H
#define RAS_H

<<<<<<< HEAD
#include <asm/interrupt.h>

DECLARE_INTERRUPT_HANDLER(cbe_system_error_exception);
DECLARE_INTERRUPT_HANDLER(cbe_maintenance_exception);
DECLARE_INTERRUPT_HANDLER(cbe_thermal_exception);

=======
extern void cbe_system_error_exception(struct pt_regs *regs);
extern void cbe_maintenance_exception(struct pt_regs *regs);
extern void cbe_thermal_exception(struct pt_regs *regs);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
extern void cbe_ras_init(void);

#endif /* RAS_H */
