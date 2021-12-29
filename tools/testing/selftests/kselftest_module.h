/* SPDX-License-Identifier: GPL-2.0+ */
#ifndef __KSELFTEST_MODULE_H
#define __KSELFTEST_MODULE_H

#include <linux/module.h>

/*
 * Test framework for writing test modules to be loaded by kselftest.
 * See Documentation/dev-tools/kselftest.rst for an example test module.
 */

#define KSTM_MODULE_GLOBALS()			\
static unsigned int total_tests __initdata;	\
<<<<<<< HEAD
static unsigned int failed_tests __initdata;	\
static unsigned int skipped_tests __initdata
=======
static unsigned int failed_tests __initdata
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#define KSTM_CHECK_ZERO(x) do {						\
	total_tests++;							\
	if (x) {							\
		pr_warn("TC failed at %s:%d\n", __func__, __LINE__);	\
		failed_tests++;						\
	}								\
} while (0)

<<<<<<< HEAD
static inline int kstm_report(unsigned int total_tests, unsigned int failed_tests,
			      unsigned int skipped_tests)
{
	if (failed_tests == 0) {
		if (skipped_tests) {
			pr_info("skipped %u tests\n", skipped_tests);
			pr_info("remaining %u tests passed\n", total_tests);
		} else
			pr_info("all %u tests passed\n", total_tests);
	} else
=======
static inline int kstm_report(unsigned int total_tests, unsigned int failed_tests)
{
	if (failed_tests == 0)
		pr_info("all %u tests passed\n", total_tests);
	else
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		pr_warn("failed %u out of %u tests\n", failed_tests, total_tests);

	return failed_tests ? -EINVAL : 0;
}

#define KSTM_MODULE_LOADERS(__module)			\
static int __init __module##_init(void)			\
{							\
	pr_info("loaded.\n");				\
	selftest();					\
<<<<<<< HEAD
	return kstm_report(total_tests, failed_tests, skipped_tests);	\
=======
	return kstm_report(total_tests, failed_tests);	\
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}							\
static void __exit __module##_exit(void)		\
{							\
	pr_info("unloaded.\n");				\
}							\
module_init(__module##_init);				\
module_exit(__module##_exit)

#endif	/* __KSELFTEST_MODULE_H */
