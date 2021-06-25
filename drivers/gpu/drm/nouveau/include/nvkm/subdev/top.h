/* SPDX-License-Identifier: MIT */
#ifndef __NVKM_TOP_H__
#define __NVKM_TOP_H__
#include <core/subdev.h>

struct nvkm_top {
	const struct nvkm_top_func *func;
	struct nvkm_subdev subdev;
	struct list_head device;
};

<<<<<<< HEAD
struct nvkm_top_device {
	enum nvkm_subdev_type type;
	int inst;
	u32 addr;
	int fault;
	int engine;
	int runlist;
	int reset;
	int intr;
	struct list_head head;
};

u32 nvkm_top_addr(struct nvkm_device *, enum nvkm_subdev_type, int);
u32 nvkm_top_reset(struct nvkm_device *, enum nvkm_subdev_type, int);
u32 nvkm_top_intr_mask(struct nvkm_device *, enum nvkm_subdev_type, int);
int nvkm_top_fault_id(struct nvkm_device *, enum nvkm_subdev_type, int);
struct nvkm_subdev *nvkm_top_fault(struct nvkm_device *, int fault);

int gk104_top_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_top **);
int ga100_top_new(struct nvkm_device *, enum nvkm_subdev_type, int inst, struct nvkm_top **);
=======
u32 nvkm_top_addr(struct nvkm_device *, enum nvkm_devidx);
u32 nvkm_top_reset(struct nvkm_device *, enum nvkm_devidx);
u32 nvkm_top_intr(struct nvkm_device *, u32 intr, u64 *subdevs);
u32 nvkm_top_intr_mask(struct nvkm_device *, enum nvkm_devidx);
int nvkm_top_fault_id(struct nvkm_device *, enum nvkm_devidx);
enum nvkm_devidx nvkm_top_fault(struct nvkm_device *, int fault);
enum nvkm_devidx nvkm_top_engine(struct nvkm_device *, int, int *runl, int *engn);

int gk104_top_new(struct nvkm_device *, int, struct nvkm_top **);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif
