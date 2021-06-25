/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright © 2019 Intel Corporation
 */

#ifndef __I915_GEM_PM_H__
#define __I915_GEM_PM_H__

#include <linux/types.h>

struct drm_i915_private;
struct work_struct;

void i915_gem_resume(struct drm_i915_private *i915);

void i915_gem_idle_work_handler(struct work_struct *work);

void i915_gem_suspend(struct drm_i915_private *i915);
void i915_gem_suspend_late(struct drm_i915_private *i915);

<<<<<<< HEAD
int i915_gem_freeze(struct drm_i915_private *i915);
int i915_gem_freeze_late(struct drm_i915_private *i915);

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif /* __I915_GEM_PM_H__ */
