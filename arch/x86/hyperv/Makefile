# SPDX-License-Identifier: GPL-2.0-only
<<<<<<< HEAD
obj-y			:= hv_init.o mmu.o nested.o irqdomain.o
obj-$(CONFIG_X86_64)	+= hv_apic.o hv_proc.o
=======
obj-y			:= hv_init.o mmu.o nested.o
obj-$(CONFIG_X86_64)	+= hv_apic.o
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

ifdef CONFIG_X86_64
obj-$(CONFIG_PARAVIRT_SPINLOCKS)	+= hv_spinlock.o
endif
