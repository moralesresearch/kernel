# SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
ifeq (, $(findstring -W,$(KCFLAGS)))
=======
ifeq (, $(findstring -W,$(EXTRA_CFLAGS)))
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	ccflags-y += -Werror
endif

tilcdc-y := \
	tilcdc_plane.o \
	tilcdc_crtc.o \
	tilcdc_panel.o \
	tilcdc_external.o \
	tilcdc_drv.o

obj-$(CONFIG_DRM_TILCDC)	+= tilcdc.o
