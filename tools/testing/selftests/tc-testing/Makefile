# SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
include ../../../scripts/Makefile.include
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

top_srcdir = $(abspath ../../../..)
APIDIR := $(top_scrdir)/include/uapi
TEST_GEN_FILES = action.o

KSFT_KHDR_INSTALL := 1
include ../lib.mk

<<<<<<< HEAD
=======
CLANG ?= clang
LLC   ?= llc
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
PROBE := $(shell $(LLC) -march=bpf -mcpu=probe -filetype=null /dev/null 2>&1)

ifeq ($(PROBE),)
  CPU ?= probe
else
  CPU ?= generic
endif

CLANG_SYS_INCLUDES := $(shell $(CLANG) -v -E - </dev/null 2>&1 \
	| sed -n '/<...> search starts here:/,/End of search list./{ s| \(/.*\)|-idirafter \1|p }')

CLANG_FLAGS = -I. -I$(APIDIR) \
	      $(CLANG_SYS_INCLUDES) \
	      -Wno-compare-distinct-pointer-types

$(OUTPUT)/%.o: %.c
	$(CLANG) $(CLANG_FLAGS) \
		 -O2 -target bpf -emit-llvm -c $< -o - |      \
	$(LLC) -march=bpf -mcpu=$(CPU) $(LLC_FLAGS) -filetype=obj -o $@

TEST_PROGS += ./tdc.sh
TEST_FILES := tdc*.py Tdc*.py plugins plugin-lib tc-tests
