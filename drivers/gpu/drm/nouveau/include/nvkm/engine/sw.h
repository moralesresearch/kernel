/* SPDX-License-Identifier: MIT */
#ifndef __NVKM_SW_H__
#define __NVKM_SW_H__
#include <core/engine.h>

struct nvkm_sw {
	const struct nvkm_sw_func *func;
	struct nvkm_engine engine;

	struct list_head chan;
};

bool nvkm_sw_mthd(struct nvkm_sw *sw, int chid, int subc, u32 mthd, u32 data);

<<<<<<< HEAD
int nv04_sw_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_sw **);
int nv10_sw_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_sw **);
int nv50_sw_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_sw **);
int gf100_sw_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_sw **);
=======
int nv04_sw_new(struct nvkm_device *, int, struct nvkm_sw **);
int nv10_sw_new(struct nvkm_device *, int, struct nvkm_sw **);
int nv50_sw_new(struct nvkm_device *, int, struct nvkm_sw **);
int gf100_sw_new(struct nvkm_device *, int, struct nvkm_sw **);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif
