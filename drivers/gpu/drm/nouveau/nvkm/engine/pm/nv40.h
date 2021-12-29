/* SPDX-License-Identifier: MIT */
#ifndef __NVKM_PM_NV40_H__
#define __NVKM_PM_NV40_H__
#define nv40_pm(p) container_of((p), struct nv40_pm, base)
#include "priv.h"

struct nv40_pm {
	struct nvkm_pm base;
	u32 sequence;
};

<<<<<<< HEAD
int nv40_pm_new_(const struct nvkm_specdom *, struct nvkm_device *, enum nvkm_subdev_type, int,
		 struct nvkm_pm **);
=======
int nv40_pm_new_(const struct nvkm_specdom *, struct nvkm_device *,
		 int index, struct nvkm_pm **);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
extern const struct nvkm_funcdom nv40_perfctr_func;
#endif
