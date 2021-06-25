/* SPDX-License-Identifier: MIT */
#ifndef __NVKM_NVDEC_H__
#define __NVKM_NVDEC_H__
#define nvkm_nvdec(p) container_of((p), struct nvkm_nvdec, engine)
#include <core/engine.h>
#include <core/falcon.h>

struct nvkm_nvdec {
	const struct nvkm_nvdec_func *func;
	struct nvkm_engine engine;
	struct nvkm_falcon falcon;
};

<<<<<<< HEAD
int gm107_nvdec_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_nvdec **);
=======
int gm107_nvdec_new(struct nvkm_device *, int, struct nvkm_nvdec **);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif
