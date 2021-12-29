# SPDX-License-Identifier: GPL-2.0

KASAN_SANITIZE_mmu.o := n

ifdef CONFIG_KASAN
CFLAGS_mmu.o  		+= -DDISABLE_BRANCH_PROFILING
endif

<<<<<<< HEAD
obj-y += mmu.o mmu_context.o
obj-$(CONFIG_PPC_BOOK3S_603) += nohash_low.o
obj-$(CONFIG_PPC_BOOK3S_604) += hash_low.o tlb.o
=======
obj-y += mmu.o hash_low.o mmu_context.o tlb.o nohash_low.o
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
