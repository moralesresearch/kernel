/* SPDX-License-Identifier: GPL-2.0 */

#ifndef _ASM_RISCV_STACKPROTECTOR_H
#define _ASM_RISCV_STACKPROTECTOR_H

#include <linux/random.h>
#include <linux/version.h>

extern unsigned long __stack_chk_guard;

/*
 * Initialize the stackprotector canary value.
 *
 * NOTE: this must only be called from functions that never return,
 * and it must always be inlined.
 */
static __always_inline void boot_init_stack_canary(void)
{
	unsigned long canary;

	/* Try to get a semi random initial value. */
	get_random_bytes(&canary, sizeof(canary));
	canary ^= LINUX_VERSION_CODE;
	canary &= CANARY_MASK;

	current->stack_canary = canary;
<<<<<<< HEAD
	if (!IS_ENABLED(CONFIG_STACKPROTECTOR_PER_TASK))
		__stack_chk_guard = current->stack_canary;
=======
	__stack_chk_guard = current->stack_canary;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}
#endif /* _ASM_RISCV_STACKPROTECTOR_H */
