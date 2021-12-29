# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the drm device driver.  This driver provides support for the
# Direct Rendering Infrastructure (DRI)
#

<<<<<<< HEAD
=======
obj-y += dss/
obj-y += displays/

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
omapdrm-y := omap_drv.o \
	omap_irq.o \
	omap_debugfs.o \
	omap_crtc.o \
	omap_plane.o \
	omap_encoder.o \
<<<<<<< HEAD
=======
	omap_connector.o \
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	omap_fb.o \
	omap_gem.o \
	omap_gem_dmabuf.o \
	omap_dmm_tiler.o \
	tcm-sita.o

omapdrm-$(CONFIG_DRM_FBDEV_EMULATION) += omap_fbdev.o

<<<<<<< HEAD
omapdrm-y += dss/base.o dss/output.o dss/dss.o dss/dispc.o \
		dss/dispc_coefs.o dss/pll.o dss/video-pll.o
omapdrm-$(CONFIG_OMAP2_DSS_DPI) += dss/dpi.o
omapdrm-$(CONFIG_OMAP2_DSS_VENC) += dss/venc.o
omapdrm-$(CONFIG_OMAP2_DSS_SDI) += dss/sdi.o
omapdrm-$(CONFIG_OMAP2_DSS_DSI) += dss/dsi.o
omapdrm-$(CONFIG_OMAP2_DSS_HDMI_COMMON) += dss/hdmi_common.o dss/hdmi_wp.o \
		dss/hdmi_pll.o dss/hdmi_phy.o
omapdrm-$(CONFIG_OMAP4_DSS_HDMI) += dss/hdmi4.o dss/hdmi4_core.o
omapdrm-$(CONFIG_OMAP4_DSS_HDMI_CEC) += dss/hdmi4_cec.o
omapdrm-$(CONFIG_OMAP5_DSS_HDMI) += dss/hdmi5.o dss/hdmi5_core.o
ccflags-$(CONFIG_OMAP2_DSS_DEBUG) += -DDEBUG

obj-$(CONFIG_DRM_OMAP) += omapdrm.o
=======
obj-$(CONFIG_DRM_OMAP)	+= omapdrm.o
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
