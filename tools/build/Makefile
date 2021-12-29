# SPDX-License-Identifier: GPL-2.0
ifeq ($(srctree),)
srctree := $(patsubst %/,%,$(dir $(CURDIR)))
srctree := $(patsubst %/,%,$(dir $(srctree)))
endif

include $(srctree)/tools//scripts/Makefile.include

define allow-override
  $(if $(or $(findstring environment,$(origin $(1))),\
            $(findstring command line,$(origin $(1)))),,\
    $(eval $(1) = $(2)))
endef

$(call allow-override,CC,$(CROSS_COMPILE)gcc)
$(call allow-override,LD,$(CROSS_COMPILE)ld)

export HOSTCC HOSTLD HOSTAR

ifeq ($(V),1)
  Q =
else
  Q = @
endif

export Q srctree CC LD

MAKEFLAGS := --no-print-directory
build     := -f $(srctree)/tools/build/Makefile.build dir=. obj

all: $(OUTPUT)fixdep

<<<<<<< HEAD
# Make sure there's anything to clean,
# feature contains check for existing OUTPUT
TMP_O := $(if $(OUTPUT),$(OUTPUT)/feature,./)

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
clean:
	$(call QUIET_CLEAN, fixdep)
	$(Q)find $(if $(OUTPUT),$(OUTPUT),.) -name '*.o' -delete -o -name '\.*.cmd' -delete -o -name '\.*.d' -delete
	$(Q)rm -f $(OUTPUT)fixdep
	$(call QUIET_CLEAN, feature-detect)
<<<<<<< HEAD
ifneq ($(wildcard $(TMP_O)),)
	$(Q)$(MAKE) -C feature OUTPUT=$(TMP_O) clean >/dev/null
endif
=======
	$(Q)$(MAKE) -C feature/ clean >/dev/null
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

$(OUTPUT)fixdep-in.o: FORCE
	$(Q)$(MAKE) $(build)=fixdep

$(OUTPUT)fixdep: $(OUTPUT)fixdep-in.o
	$(QUIET_LINK)$(HOSTCC) $(KBUILD_HOSTLDFLAGS) -o $@ $<

FORCE:

.PHONY: FORCE
