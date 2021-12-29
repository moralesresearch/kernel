/* SPDX-License-Identifier: MIT */
#ifndef __NVKM_MSPPP_PRIV_H__
#define __NVKM_MSPPP_PRIV_H__
#include <engine/msppp.h>

<<<<<<< HEAD
int nvkm_msppp_new_(const struct nvkm_falcon_func *, struct nvkm_device *, enum nvkm_subdev_type,
		    int, struct nvkm_engine **);
=======
int nvkm_msppp_new_(const struct nvkm_falcon_func *, struct nvkm_device *,
		    int index, struct nvkm_engine **);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

void g98_msppp_init(struct nvkm_falcon *);
#endif
