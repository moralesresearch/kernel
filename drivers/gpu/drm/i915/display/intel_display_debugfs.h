/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2020 Intel Corporation
 */

#ifndef __INTEL_DISPLAY_DEBUGFS_H__
#define __INTEL_DISPLAY_DEBUGFS_H__

struct drm_connector;
<<<<<<< HEAD
struct drm_crtc;
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
struct drm_i915_private;

#ifdef CONFIG_DEBUG_FS
void intel_display_debugfs_register(struct drm_i915_private *i915);
int intel_connector_debugfs_add(struct drm_connector *connector);
<<<<<<< HEAD
int intel_crtc_debugfs_add(struct drm_crtc *crtc);
#else
static inline void intel_display_debugfs_register(struct drm_i915_private *i915) {}
static inline int intel_connector_debugfs_add(struct drm_connector *connector) { return 0; }
static inline int intel_crtc_debugfs_add(struct drm_crtc *crtc) { return 0; }
=======
#else
static inline void intel_display_debugfs_register(struct drm_i915_private *i915) {}
static inline int intel_connector_debugfs_add(struct drm_connector *connector) { return 0; }
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif

#endif /* __INTEL_DISPLAY_DEBUGFS_H__ */
