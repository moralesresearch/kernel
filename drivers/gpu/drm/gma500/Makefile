# SPDX-License-Identifier: GPL-2.0
#
#	KMS driver for the GMA500
#

gma500_gfx-y += \
	  accel_2d.o \
	  backlight.o \
<<<<<<< HEAD
	  blitter.o \
	  cdv_device.o \
	  cdv_intel_crt.o \
	  cdv_intel_display.o \
	  cdv_intel_dp.o \
	  cdv_intel_hdmi.o \
	  cdv_intel_lvds.o \
	  framebuffer.o \
	  gem.o \
	  gma_device.o \
	  gma_display.o \
	  gtt.o \
	  intel_bios.o \
	  intel_gmbus.o \
	  intel_i2c.o \
	  mid_bios.o \
	  mmu.o \
	  power.o \
	  psb_device.o \
	  psb_drv.o \
=======
	  framebuffer.o \
	  gem.o \
	  gtt.o \
	  intel_bios.o \
	  intel_i2c.o \
	  intel_gmbus.o \
	  mmu.o \
	  blitter.o \
	  power.o \
	  psb_drv.o \
	  gma_display.o \
	  gma_device.o \
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	  psb_intel_display.o \
	  psb_intel_lvds.o \
	  psb_intel_modes.o \
	  psb_intel_sdvo.o \
	  psb_lid.o \
<<<<<<< HEAD
	  psb_irq.o

gma500_gfx-$(CONFIG_ACPI) +=  opregion.o \

=======
	  psb_irq.o \
	  psb_device.o \
	  mid_bios.o

gma500_gfx-$(CONFIG_ACPI) +=  opregion.o \

gma500_gfx-$(CONFIG_DRM_GMA3600) +=  cdv_device.o \
	  cdv_intel_crt.o \
	  cdv_intel_display.o \
	  cdv_intel_hdmi.o \
	  cdv_intel_lvds.o \
	  cdv_intel_dp.o

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
gma500_gfx-$(CONFIG_DRM_GMA600) += oaktrail_device.o \
	  oaktrail_crtc.o \
	  oaktrail_lvds.o \
	  oaktrail_lvds_i2c.o \
	  oaktrail_hdmi.o \
	  oaktrail_hdmi_i2c.o

<<<<<<< HEAD
=======
gma500_gfx-$(CONFIG_DRM_MEDFIELD) += mdfld_device.o \
	  mdfld_output.o \
	  mdfld_intel_display.o \
	  mdfld_dsi_output.o \
	  mdfld_dsi_dpi.o \
	  mdfld_dsi_pkg_sender.o \
	  mdfld_tpo_vid.o \
	  mdfld_tmd_vid.o \
	  tc35876x-dsi-lvds.o

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
obj-$(CONFIG_DRM_GMA500) += gma500_gfx.o
