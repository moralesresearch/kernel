/* SPDX-License-Identifier: MIT */
#ifndef __NVKM_MSPDEC_H__
#define __NVKM_MSPDEC_H__
#include <engine/falcon.h>
<<<<<<< HEAD
int g98_mspdec_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_engine **);
int gt215_mspdec_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_engine **);
int gf100_mspdec_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_engine **);
int gk104_mspdec_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_engine **);
=======
int g98_mspdec_new(struct nvkm_device *, int, struct nvkm_engine **);
int gt215_mspdec_new(struct nvkm_device *, int, struct nvkm_engine **);
int gf100_mspdec_new(struct nvkm_device *, int, struct nvkm_engine **);
int gk104_mspdec_new(struct nvkm_device *, int, struct nvkm_engine **);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif
