# SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
=======
OBJECT_FILES_NON_STANDARD_hibernate_asm_$(BITS).o := y
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

# __restore_processor_state() restores %gs after S3 resume and so should not
# itself be stack-protected
CFLAGS_cpu.o	:= -fno-stack-protector

<<<<<<< HEAD
# Clang may incorrectly inline functions with stack protector enabled into
# __restore_processor_state(): https://bugs.llvm.org/show_bug.cgi?id=47479
CFLAGS_REMOVE_cpu.o := $(CC_FLAGS_LTO)

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
obj-$(CONFIG_PM_SLEEP)		+= cpu.o
obj-$(CONFIG_HIBERNATION)	+= hibernate_$(BITS).o hibernate_asm_$(BITS).o hibernate.o
