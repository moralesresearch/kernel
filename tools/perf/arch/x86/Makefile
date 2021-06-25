# SPDX-License-Identifier: GPL-2.0
ifndef NO_DWARF
PERF_HAVE_DWARF_REGS := 1
endif
HAVE_KVM_STAT_SUPPORT := 1
PERF_HAVE_ARCH_REGS_QUERY_REGISTER_OFFSET := 1
PERF_HAVE_JITDUMP := 1

###
# Syscall table generation
#

<<<<<<< HEAD
generated := $(OUTPUT)arch/x86/include/generated
out       := $(generated)/asm
header    := $(out)/syscalls_64.c
sys       := $(srctree)/tools/perf/arch/x86/entry/syscalls
systbl    := $(sys)/syscalltbl.sh
=======
out    := $(OUTPUT)arch/x86/include/generated/asm
header := $(out)/syscalls_64.c
sys    := $(srctree)/tools/perf/arch/x86/entry/syscalls
systbl := $(sys)/syscalltbl.sh
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

# Create output directory if not already present
_dummy := $(shell [ -d '$(out)' ] || mkdir -p '$(out)')

$(header): $(sys)/syscall_64.tbl $(systbl)
	$(Q)$(SHELL) '$(systbl)' $(sys)/syscall_64.tbl 'x86_64' > $@

clean::
<<<<<<< HEAD
	$(call QUIET_CLEAN, x86) $(RM) -r $(header) $(generated)
=======
	$(call QUIET_CLEAN, x86) $(RM) $(header)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

archheaders: $(header)
