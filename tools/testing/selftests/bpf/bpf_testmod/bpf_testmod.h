/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (c) 2020 Facebook */
#ifndef _BPF_TESTMOD_H
#define _BPF_TESTMOD_H

#include <linux/types.h>

struct bpf_testmod_test_read_ctx {
	char *buf;
	loff_t off;
	size_t len;
};

<<<<<<< HEAD
struct bpf_testmod_test_write_ctx {
	char *buf;
	loff_t off;
	size_t len;
};

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif /* _BPF_TESTMOD_H */
