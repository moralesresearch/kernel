/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ARCH_X86_EVENTS_PROBE_H__
#define __ARCH_X86_EVENTS_PROBE_H__
#include <linux/sysfs.h>

struct perf_msr {
<<<<<<< HEAD
	u64			msr;
	struct attribute_group	*grp;
	bool			(*test)(int idx, void *data);
	bool			no_check;
	u64			mask;
=======
	u64			  msr;
	struct attribute_group	 *grp;
	bool			(*test)(int idx, void *data);
	bool			  no_check;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

unsigned long
perf_msr_probe(struct perf_msr *msr, int cnt, bool no_zero, void *data);

#define __PMU_EVENT_GROUP(_name)			\
static struct attribute *attrs_##_name[] = {		\
	&attr_##_name.attr.attr,			\
	NULL,						\
}

#define PMU_EVENT_GROUP(_grp, _name)			\
__PMU_EVENT_GROUP(_name);				\
static struct attribute_group group_##_name = {		\
	.name  = #_grp,					\
	.attrs = attrs_##_name,				\
}

#endif /* __ARCH_X86_EVENTS_PROBE_H__ */
