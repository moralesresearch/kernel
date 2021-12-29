// SPDX-License-Identifier: GPL-2.0
/* Copyright (c) 2019 Carlos Neira cneirabustos@gmail.com */

#include <linux/bpf.h>
#include <stdint.h>
#include <bpf/bpf_helpers.h>

<<<<<<< HEAD
__u64 user_pid = 0;
__u64 user_tgid = 0;
__u64 dev = 0;
__u64 ino = 0;

SEC("tracepoint/syscalls/sys_enter_nanosleep")
int handler(const void *ctx)
{
	struct bpf_pidns_info nsdata;

	if (bpf_get_ns_current_pid_tgid(dev, ino, &nsdata, sizeof(struct bpf_pidns_info)))
		return 0;

	user_pid = nsdata.pid;
	user_tgid = nsdata.tgid;
=======
static volatile struct {
	__u64 dev;
	__u64 ino;
	__u64 pid_tgid;
	__u64 user_pid_tgid;
} res;

SEC("raw_tracepoint/sys_enter")
int trace(void *ctx)
{
	__u64  ns_pid_tgid, expected_pid;
	struct bpf_pidns_info nsdata;
	__u32 key = 0;

	if (bpf_get_ns_current_pid_tgid(res.dev, res.ino, &nsdata,
		   sizeof(struct bpf_pidns_info)))
		return 0;

	ns_pid_tgid = (__u64)nsdata.tgid << 32 | nsdata.pid;
	expected_pid = res.user_pid_tgid;

	if (expected_pid != ns_pid_tgid)
		return 0;

	res.pid_tgid = ns_pid_tgid;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return 0;
}

char _license[] SEC("license") = "GPL";
