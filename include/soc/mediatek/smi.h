/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Yong Wu <yong.wu@mediatek.com>
 */
#ifndef MTK_IOMMU_SMI_H
#define MTK_IOMMU_SMI_H

#include <linux/bitops.h>
#include <linux/device.h>

<<<<<<< HEAD
#if IS_ENABLED(CONFIG_MTK_SMI)
=======
#ifdef CONFIG_MTK_SMI

#define MTK_LARB_NR_MAX		16
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#define MTK_SMI_MMU_EN(port)	BIT(port)

struct mtk_smi_larb_iommu {
	struct device *dev;
	unsigned int   mmu;
<<<<<<< HEAD
	unsigned char  bank[32];
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

/*
 * mtk_smi_larb_get: Enable the power domain and clocks for this local arbiter.
 *                   It also initialize some basic setting(like iommu).
 * mtk_smi_larb_put: Disable the power domain and clocks for this local arbiter.
 * Both should be called in non-atomic context.
 *
 * Returns 0 if successful, negative on failure.
 */
int mtk_smi_larb_get(struct device *larbdev);
void mtk_smi_larb_put(struct device *larbdev);

#else

static inline int mtk_smi_larb_get(struct device *larbdev)
{
	return 0;
}

static inline void mtk_smi_larb_put(struct device *larbdev) { }

#endif

#endif
