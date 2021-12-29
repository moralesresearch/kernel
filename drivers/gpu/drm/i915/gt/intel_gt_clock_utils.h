/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2020 Intel Corporation
 */

#ifndef __INTEL_GT_CLOCK_UTILS_H__
#define __INTEL_GT_CLOCK_UTILS_H__

#include <linux/types.h>

struct intel_gt;

void intel_gt_init_clock_frequency(struct intel_gt *gt);

#if IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM)
void intel_gt_check_clock_frequency(const struct intel_gt *gt);
#else
static inline void intel_gt_check_clock_frequency(const struct intel_gt *gt) {}
#endif

<<<<<<< HEAD
u64 intel_gt_clock_interval_to_ns(const struct intel_gt *gt, u64 count);
u64 intel_gt_pm_interval_to_ns(const struct intel_gt *gt, u64 count);

u64 intel_gt_ns_to_clock_interval(const struct intel_gt *gt, u64 ns);
u64 intel_gt_ns_to_pm_interval(const struct intel_gt *gt, u64 ns);
=======
u32 intel_gt_clock_interval_to_ns(const struct intel_gt *gt, u32 count);
u32 intel_gt_pm_interval_to_ns(const struct intel_gt *gt, u32 count);

u32 intel_gt_ns_to_clock_interval(const struct intel_gt *gt, u32 ns);
u32 intel_gt_ns_to_pm_interval(const struct intel_gt *gt, u32 ns);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#endif /* __INTEL_GT_CLOCK_UTILS_H__ */
