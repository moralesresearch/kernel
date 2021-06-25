/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright © 2019 Intel Corporation
 */

#include "gem/i915_gem_pm.h"
#include "gt/intel_gt.h"
#include "gt/intel_gt_pm.h"
#include "gt/intel_gt_requests.h"

#include "i915_drv.h"

<<<<<<< HEAD
#if defined(CONFIG_X86)
#include <asm/smp.h>
#else
#define wbinvd_on_all_cpus() \
	pr_warn(DRIVER_NAME ": Missing cache flush in %s\n", __func__)
#endif

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
void i915_gem_suspend(struct drm_i915_private *i915)
{
	GEM_TRACE("%s\n", dev_name(i915->drm.dev));

	intel_wakeref_auto(&i915->ggtt.userfault_wakeref, 0);
	flush_workqueue(i915->wq);

	/*
	 * We have to flush all the executing contexts to main memory so
	 * that they can saved in the hibernation image. To ensure the last
	 * context image is coherent, we have to switch away from it. That
	 * leaves the i915->kernel_context still active when
	 * we actually suspend, and its image in memory may not match the GPU
	 * state. Fortunately, the kernel_context is disposable and we do
	 * not rely on its state.
	 */
	intel_gt_suspend_prepare(&i915->gt);

	i915_gem_drain_freed_objects(i915);
}

<<<<<<< HEAD
=======
static struct drm_i915_gem_object *first_mm_object(struct list_head *list)
{
	return list_first_entry_or_null(list,
					struct drm_i915_gem_object,
					mm.link);
}

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
void i915_gem_suspend_late(struct drm_i915_private *i915)
{
	struct drm_i915_gem_object *obj;
	struct list_head *phases[] = {
		&i915->mm.shrink_list,
		&i915->mm.purge_list,
		NULL
	}, **phase;
	unsigned long flags;
<<<<<<< HEAD
	bool flush = false;
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	/*
	 * Neither the BIOS, ourselves or any other kernel
	 * expects the system to be in execlists mode on startup,
	 * so we need to reset the GPU back to legacy mode. And the only
	 * known way to disable logical contexts is through a GPU reset.
	 *
	 * So in order to leave the system in a known default configuration,
	 * always reset the GPU upon unload and suspend. Afterwards we then
	 * clean up the GEM state tracking, flushing off the requests and
	 * leaving the system in a known idle state.
	 *
	 * Note that is of the upmost importance that the GPU is idle and
	 * all stray writes are flushed *before* we dismantle the backing
	 * storage for the pinned objects.
	 *
	 * However, since we are uncertain that resetting the GPU on older
	 * machines is a good idea, we don't - just in case it leaves the
	 * machine in an unusable condition.
	 */

	intel_gt_suspend_late(&i915->gt);

	spin_lock_irqsave(&i915->mm.obj_lock, flags);
	for (phase = phases; *phase; phase++) {
<<<<<<< HEAD
		list_for_each_entry(obj, *phase, mm.link) {
			if (!(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ))
				flush |= (obj->read_domains & I915_GEM_DOMAIN_CPU) == 0;
			__start_cpu_write(obj); /* presume auto-hibernate */
		}
	}
	spin_unlock_irqrestore(&i915->mm.obj_lock, flags);
	if (flush)
		wbinvd_on_all_cpus();
}

int i915_gem_freeze(struct drm_i915_private *i915)
{
	/* Discard all purgeable objects, let userspace recover those as
	 * required after resuming.
	 */
	i915_gem_shrink_all(i915);

	return 0;
}

int i915_gem_freeze_late(struct drm_i915_private *i915)
{
	struct drm_i915_gem_object *obj;
	intel_wakeref_t wakeref;

	/*
	 * Called just before we write the hibernation image.
	 *
	 * We need to update the domain tracking to reflect that the CPU
	 * will be accessing all the pages to create and restore from the
	 * hibernation, and so upon restoration those pages will be in the
	 * CPU domain.
	 *
	 * To make sure the hibernation image contains the latest state,
	 * we update that state just before writing out the image.
	 *
	 * To try and reduce the hibernation image, we manually shrink
	 * the objects as well, see i915_gem_freeze()
	 */

	with_intel_runtime_pm(&i915->runtime_pm, wakeref)
		i915_gem_shrink(i915, -1UL, NULL, ~0);
	i915_gem_drain_freed_objects(i915);

	wbinvd_on_all_cpus();
	list_for_each_entry(obj, &i915->mm.shrink_list, mm.link)
		__start_cpu_write(obj);

	return 0;
=======
		LIST_HEAD(keep);

		while ((obj = first_mm_object(*phase))) {
			list_move_tail(&obj->mm.link, &keep);

			/* Beware the background _i915_gem_free_objects */
			if (!kref_get_unless_zero(&obj->base.refcount))
				continue;

			spin_unlock_irqrestore(&i915->mm.obj_lock, flags);

			i915_gem_object_lock(obj, NULL);
			drm_WARN_ON(&i915->drm,
			    i915_gem_object_set_to_gtt_domain(obj, false));
			i915_gem_object_unlock(obj);
			i915_gem_object_put(obj);

			spin_lock_irqsave(&i915->mm.obj_lock, flags);
		}

		list_splice_tail(&keep, *phase);
	}
	spin_unlock_irqrestore(&i915->mm.obj_lock, flags);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

void i915_gem_resume(struct drm_i915_private *i915)
{
	GEM_TRACE("%s\n", dev_name(i915->drm.dev));

	/*
	 * As we didn't flush the kernel context before suspend, we cannot
	 * guarantee that the context image is complete. So let's just reset
	 * it and start again.
	 */
	intel_gt_resume(&i915->gt);
}
