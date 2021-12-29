# SPDX-License-Identifier: GPL-2.0-only

CFLAGS_init.o := -mcmodel=medany
ifdef CONFIG_FTRACE
<<<<<<< HEAD
CFLAGS_REMOVE_init.o = $(CC_FLAGS_FTRACE)
CFLAGS_REMOVE_cacheflush.o = $(CC_FLAGS_FTRACE)
=======
CFLAGS_REMOVE_init.o = -pg
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
endif

KCOV_INSTRUMENT_init.o := n

obj-y += init.o
obj-y += extable.o
obj-$(CONFIG_MMU) += fault.o pageattr.o
obj-y += cacheflush.o
obj-y += context.o

ifeq ($(CONFIG_MMU),y)
obj-$(CONFIG_SMP) += tlbflush.o
endif
obj-$(CONFIG_HUGETLB_PAGE) += hugetlbpage.o
obj-$(CONFIG_PTDUMP_CORE) += ptdump.o
obj-$(CONFIG_KASAN)   += kasan_init.o

ifdef CONFIG_KASAN
KASAN_SANITIZE_kasan_init.o := n
KASAN_SANITIZE_init.o := n
endif

obj-$(CONFIG_DEBUG_VIRTUAL) += physaddr.o
