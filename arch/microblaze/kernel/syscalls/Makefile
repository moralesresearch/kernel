# SPDX-License-Identifier: GPL-2.0
kapi := arch/$(SRCARCH)/include/generated/asm
uapi := arch/$(SRCARCH)/include/generated/uapi/asm

_dummy := $(shell [ -d '$(uapi)' ] || mkdir -p '$(uapi)')	\
	  $(shell [ -d '$(kapi)' ] || mkdir -p '$(kapi)')

<<<<<<< HEAD
syscall := $(src)/syscall.tbl
=======
syscall := $(srctree)/$(src)/syscall.tbl
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
syshdr := $(srctree)/$(src)/syscallhdr.sh
systbl := $(srctree)/$(src)/syscalltbl.sh

quiet_cmd_syshdr = SYSHDR  $@
      cmd_syshdr = $(CONFIG_SHELL) '$(syshdr)' '$<' '$@'	\
		   '$(syshdr_abis_$(basetarget))'		\
		   '$(syshdr_pfx_$(basetarget))'		\
		   '$(syshdr_offset_$(basetarget))'

quiet_cmd_systbl = SYSTBL  $@
      cmd_systbl = $(CONFIG_SHELL) '$(systbl)' '$<' '$@'	\
		   '$(systbl_abis_$(basetarget))'		\
		   '$(systbl_abi_$(basetarget))'		\
		   '$(systbl_offset_$(basetarget))'

<<<<<<< HEAD
$(uapi)/unistd_32.h: $(syscall) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(kapi)/syscall_table.h: $(syscall) $(systbl) FORCE
=======
$(uapi)/unistd_32.h: $(syscall) $(syshdr)
	$(call if_changed,syshdr)

$(kapi)/syscall_table.h: $(syscall) $(systbl)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	$(call if_changed,systbl)

uapisyshdr-y		+= unistd_32.h
kapisyshdr-y		+= syscall_table.h

<<<<<<< HEAD
uapisyshdr-y	:= $(addprefix $(uapi)/, $(uapisyshdr-y))
kapisyshdr-y	:= $(addprefix $(kapi)/, $(kapisyshdr-y))
targets		+= $(addprefix ../../../../, $(uapisyshdr-y) $(kapisyshdr-y))

PHONY += all
all: $(uapisyshdr-y) $(kapisyshdr-y)
=======
targets	+= $(uapisyshdr-y) $(kapisyshdr-y)

PHONY += all
all: $(addprefix $(uapi)/,$(uapisyshdr-y))
all: $(addprefix $(kapi)/,$(kapisyshdr-y))
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	@:
