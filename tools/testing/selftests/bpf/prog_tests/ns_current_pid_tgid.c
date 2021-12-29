// SPDX-License-Identifier: GPL-2.0
/* Copyright (c) 2020 Carlos Neira cneirabustos@gmail.com */
<<<<<<< HEAD

#define _GNU_SOURCE
#include <test_progs.h>
#include "test_ns_current_pid_tgid.skel.h"
=======
#include <test_progs.h>
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
<<<<<<< HEAD
#include <sched.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/fcntl.h>

#define STACK_SIZE (1024 * 1024)
static char child_stack[STACK_SIZE];

static int test_current_pid_tgid(void *args)
{
	struct test_ns_current_pid_tgid__bss  *bss;
	struct test_ns_current_pid_tgid *skel;
	int err = -1, duration = 0;
	pid_t tgid, pid;
	struct stat st;

	skel = test_ns_current_pid_tgid__open_and_load();
	if (CHECK(!skel, "skel_open_load", "failed to load skeleton\n"))
		goto cleanup;

	pid = syscall(SYS_gettid);
	tgid = getpid();

	err = stat("/proc/self/ns/pid", &st);
	if (CHECK(err, "stat", "failed /proc/self/ns/pid: %d\n", err))
		goto cleanup;

	bss = skel->bss;
	bss->dev = st.st_dev;
	bss->ino = st.st_ino;
	bss->user_pid = 0;
	bss->user_tgid = 0;

	err = test_ns_current_pid_tgid__attach(skel);
	if (CHECK(err, "skel_attach", "skeleton attach failed: %d\n", err))
		goto cleanup;

	/* trigger tracepoint */
	usleep(1);
	ASSERT_EQ(bss->user_pid, pid, "pid");
	ASSERT_EQ(bss->user_tgid, tgid, "tgid");
	err = 0;

cleanup:
	 test_ns_current_pid_tgid__destroy(skel);

	return err;
}

static void test_ns_current_pid_tgid_new_ns(void)
{
	int wstatus, duration = 0;
	pid_t cpid;

	/* Create a process in a new namespace, this process
	 * will be the init process of this new namespace hence will be pid 1.
	 */
	cpid = clone(test_current_pid_tgid, child_stack + STACK_SIZE,
		     CLONE_NEWPID | SIGCHLD, NULL);

	if (CHECK(cpid == -1, "clone", strerror(errno)))
		return;

	if (CHECK(waitpid(cpid, &wstatus, 0) == -1, "waitpid", strerror(errno)))
		return;

	if (CHECK(WEXITSTATUS(wstatus) != 0, "newns_pidtgid", "failed"))
		return;
}

void test_ns_current_pid_tgid(void)
{
	if (test__start_subtest("ns_current_pid_tgid_root_ns"))
		test_current_pid_tgid(NULL);
	if (test__start_subtest("ns_current_pid_tgid_new_ns"))
		test_ns_current_pid_tgid_new_ns();
=======

struct bss {
	__u64 dev;
	__u64 ino;
	__u64 pid_tgid;
	__u64 user_pid_tgid;
};

void test_ns_current_pid_tgid(void)
{
	const char *probe_name = "raw_tracepoint/sys_enter";
	const char *file = "test_ns_current_pid_tgid.o";
	int err, key = 0, duration = 0;
	struct bpf_link *link = NULL;
	struct bpf_program *prog;
	struct bpf_map *bss_map;
	struct bpf_object *obj;
	struct bss bss;
	struct stat st;
	__u64 id;

	obj = bpf_object__open_file(file, NULL);
	if (CHECK(IS_ERR(obj), "obj_open", "err %ld\n", PTR_ERR(obj)))
		return;

	err = bpf_object__load(obj);
	if (CHECK(err, "obj_load", "err %d errno %d\n", err, errno))
		goto cleanup;

	bss_map = bpf_object__find_map_by_name(obj, "test_ns_.bss");
	if (CHECK(!bss_map, "find_bss_map", "failed\n"))
		goto cleanup;

	prog = bpf_object__find_program_by_title(obj, probe_name);
	if (CHECK(!prog, "find_prog", "prog '%s' not found\n",
		  probe_name))
		goto cleanup;

	memset(&bss, 0, sizeof(bss));
	pid_t tid = syscall(SYS_gettid);
	pid_t pid = getpid();

	id = (__u64) tid << 32 | pid;
	bss.user_pid_tgid = id;

	if (CHECK_FAIL(stat("/proc/self/ns/pid", &st))) {
		perror("Failed to stat /proc/self/ns/pid");
		goto cleanup;
	}

	bss.dev = st.st_dev;
	bss.ino = st.st_ino;

	err = bpf_map_update_elem(bpf_map__fd(bss_map), &key, &bss, 0);
	if (CHECK(err, "setting_bss", "failed to set bss : %d\n", err))
		goto cleanup;

	link = bpf_program__attach_raw_tracepoint(prog, "sys_enter");
	if (CHECK(IS_ERR(link), "attach_raw_tp", "err %ld\n",
		  PTR_ERR(link))) {
		link = NULL;
		goto cleanup;
	}

	/* trigger some syscalls */
	usleep(1);

	err = bpf_map_lookup_elem(bpf_map__fd(bss_map), &key, &bss);
	if (CHECK(err, "set_bss", "failed to get bss : %d\n", err))
		goto cleanup;

	if (CHECK(id != bss.pid_tgid, "Compare user pid/tgid vs. bpf pid/tgid",
		  "User pid/tgid %llu BPF pid/tgid %llu\n", id, bss.pid_tgid))
		goto cleanup;
cleanup:
	bpf_link__destroy(link);
	bpf_object__close(obj);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}
