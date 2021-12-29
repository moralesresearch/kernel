/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __BRCMSTB_SOC_H
#define __BRCMSTB_SOC_H

<<<<<<< HEAD
#include <linux/kconfig.h>

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static inline u32 BRCM_ID(u32 reg)
{
	return reg >> 28 ? reg >> 16 : reg >> 8;
}

static inline u32 BRCM_REV(u32 reg)
{
	return reg & 0xff;
}

<<<<<<< HEAD
#if IS_ENABLED(CONFIG_SOC_BRCMSTB)

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
/*
 * Helper functions for getting family or product id from the
 * SoC driver.
 */
u32 brcmstb_get_family_id(void);
u32 brcmstb_get_product_id(void);

<<<<<<< HEAD
#else
static inline u32 brcmstb_get_family_id(void)
{
	return 0;
}

static inline u32 brcmstb_get_product_id(void)
{
	return 0;
}
#endif

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif /* __BRCMSTB_SOC_H */
