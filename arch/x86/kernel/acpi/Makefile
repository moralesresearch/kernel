# SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
=======
OBJECT_FILES_NON_STANDARD_wakeup_$(BITS).o := y
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

obj-$(CONFIG_ACPI)		+= boot.o
obj-$(CONFIG_ACPI_SLEEP)	+= sleep.o wakeup_$(BITS).o
obj-$(CONFIG_ACPI_APEI)		+= apei.o
obj-$(CONFIG_ACPI_CPPC_LIB)	+= cppc_msr.o

ifneq ($(CONFIG_ACPI_PROCESSOR),)
obj-y				+= cstate.o
endif

