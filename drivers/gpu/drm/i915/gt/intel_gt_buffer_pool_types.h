/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright © 2014-2018 Intel Corporation
 */

#ifndef INTEL_GT_BUFFER_POOL_TYPES_H
#define INTEL_GT_BUFFER_POOL_TYPES_H

#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/workqueue.h>

<<<<<<< HEAD
#include "gem/i915_gem_object_types.h"
#include "i915_active_types.h"

=======
#include "i915_active_types.h"

struct drm_i915_gem_object;

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
struct intel_gt_buffer_pool {
	spinlock_t lock;
	struct list_head cache_list[4];
	struct delayed_work work;
};

struct intel_gt_buffer_pool_node {
	struct i915_active active;
	struct drm_i915_gem_object *obj;
	struct list_head link;
	union {
		struct intel_gt_buffer_pool *pool;
		struct intel_gt_buffer_pool_node *free;
		struct rcu_head rcu;
	};
	unsigned long age;
<<<<<<< HEAD
	enum i915_map_type type;
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

#endif /* INTEL_GT_BUFFER_POOL_TYPES_H */
