// SPDX-License-Identifier: GPL-2.0
#include <linux/stringify.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs.h"

<<<<<<< HEAD
struct cgroupfs_cache_entry {
	char	subsys[32];
	char	mountpoint[PATH_MAX];
};

/* just cache last used one */
static struct cgroupfs_cache_entry cached;

int cgroupfs_find_mountpoint(char *buf, size_t maxlen, const char *subsys)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	char *p, *path;
	char mountpoint[PATH_MAX];

	if (!strcmp(cached.subsys, subsys)) {
		if (strlen(cached.mountpoint) < maxlen) {
			strcpy(buf, cached.mountpoint);
			return 0;
		}
		return -1;
	}
=======
int cgroupfs_find_mountpoint(char *buf, size_t maxlen, const char *subsys)
{
	FILE *fp;
	char mountpoint[PATH_MAX + 1], tokens[PATH_MAX + 1], type[PATH_MAX + 1];
	char path_v1[PATH_MAX + 1], path_v2[PATH_MAX + 2], *path;
	char *token, *saved_ptr = NULL;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	fp = fopen("/proc/mounts", "r");
	if (!fp)
		return -1;

	/*
	 * in order to handle split hierarchy, we need to scan /proc/mounts
	 * and inspect every cgroupfs mount point to find one that has
<<<<<<< HEAD
	 * the given subsystem.  If we found v1, just use it.  If not we can
	 * use v2 path as a fallback.
	 */
	mountpoint[0] = '\0';

	/*
	 * The /proc/mounts has the follow format:
	 *
	 *   <devname> <mount point> <fs type> <options> ...
	 *
	 */
	while (getline(&line, &len, fp) != -1) {
		/* skip devname */
		p = strchr(line, ' ');
		if (p == NULL)
			continue;

		/* save the mount point */
		path = ++p;
		p = strchr(p, ' ');
		if (p == NULL)
			continue;

		*p++ = '\0';

		/* check filesystem type */
		if (strncmp(p, "cgroup", 6))
			continue;

		if (p[6] == '2') {
			/* save cgroup v2 path */
			strcpy(mountpoint, path);
			continue;
		}

		/* now we have cgroup v1, check the options for subsystem */
		p += 7;

		p = strstr(p, subsys);
		if (p == NULL)
			continue;

		/* sanity check: it should be separated by a space or a comma */
		if (!strchr(" ,", p[-1]) || !strchr(" ,", p[strlen(subsys)]))
			continue;

		strcpy(mountpoint, path);
		break;
	}
	free(line);
	fclose(fp);

	strncpy(cached.subsys, subsys, sizeof(cached.subsys) - 1);
	strcpy(cached.mountpoint, mountpoint);

	if (mountpoint[0] && strlen(mountpoint) < maxlen) {
		strcpy(buf, mountpoint);
=======
	 * perf_event subsystem
	 */
	path_v1[0] = '\0';
	path_v2[0] = '\0';

	while (fscanf(fp, "%*s %"__stringify(PATH_MAX)"s %"__stringify(PATH_MAX)"s %"
				__stringify(PATH_MAX)"s %*d %*d\n",
				mountpoint, type, tokens) == 3) {

		if (!path_v1[0] && !strcmp(type, "cgroup")) {

			token = strtok_r(tokens, ",", &saved_ptr);

			while (token != NULL) {
				if (subsys && !strcmp(token, subsys)) {
					strcpy(path_v1, mountpoint);
					break;
				}
				token = strtok_r(NULL, ",", &saved_ptr);
			}
		}

		if (!path_v2[0] && !strcmp(type, "cgroup2"))
			strcpy(path_v2, mountpoint);

		if (path_v1[0] && path_v2[0])
			break;
	}
	fclose(fp);

	if (path_v1[0])
		path = path_v1;
	else if (path_v2[0])
		path = path_v2;
	else
		return -1;

	if (strlen(path) < maxlen) {
		strcpy(buf, path);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		return 0;
	}
	return -1;
}
