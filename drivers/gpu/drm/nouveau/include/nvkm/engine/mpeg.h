/* SPDX-License-Identifier: MIT */
#ifndef __NVKM_MPEG_H__
#define __NVKM_MPEG_H__
#include <core/engine.h>
<<<<<<< HEAD
int nv31_mpeg_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_engine **);
int nv40_mpeg_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_engine **);
int nv44_mpeg_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_engine **);
int nv50_mpeg_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_engine **);
int g84_mpeg_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_engine **);
=======
int nv31_mpeg_new(struct nvkm_device *, int index, struct nvkm_engine **);
int nv40_mpeg_new(struct nvkm_device *, int index, struct nvkm_engine **);
int nv44_mpeg_new(struct nvkm_device *, int index, struct nvkm_engine **);
int nv50_mpeg_new(struct nvkm_device *, int index, struct nvkm_engine **);
int g84_mpeg_new(struct nvkm_device *, int index, struct nvkm_engine **);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif
