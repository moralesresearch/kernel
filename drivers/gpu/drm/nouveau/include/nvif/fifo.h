#ifndef __NVIF_FIFO_H__
#define __NVIF_FIFO_H__
#include <nvif/device.h>

<<<<<<< HEAD
/* Returns mask of runlists that support a NV_DEVICE_INFO_RUNLIST_ENGINES_* type. */
=======
/* Returns mask of runlists that support a NV_DEVICE_INFO_ENGINE_* type. */
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
u64 nvif_fifo_runlist(struct nvif_device *, u64 engine);

/* CE-supporting runlists (excluding GRCE, if others exist). */
static inline u64
nvif_fifo_runlist_ce(struct nvif_device *device)
{
<<<<<<< HEAD
	u64 runmgr = nvif_fifo_runlist(device, NV_DEVICE_HOST_RUNLIST_ENGINES_GR);
	u64 runmce = nvif_fifo_runlist(device, NV_DEVICE_HOST_RUNLIST_ENGINES_CE);
=======
	u64 runmgr = nvif_fifo_runlist(device, NV_DEVICE_INFO_ENGINE_GR);
	u64 runmce = nvif_fifo_runlist(device, NV_DEVICE_INFO_ENGINE_CE);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	if (runmce && !(runmce &= ~runmgr))
		runmce = runmgr;
	return runmce;
}
#endif
