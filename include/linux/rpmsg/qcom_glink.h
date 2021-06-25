/* SPDX-License-Identifier: GPL-2.0 */

#ifndef _LINUX_RPMSG_QCOM_GLINK_H
#define _LINUX_RPMSG_QCOM_GLINK_H

#include <linux/device.h>

struct qcom_glink;

<<<<<<< HEAD
#if IS_ENABLED(CONFIG_RPMSG_QCOM_GLINK)
void qcom_glink_ssr_notify(const char *ssr_name);
#else
static inline void qcom_glink_ssr_notify(const char *ssr_name) {}
#endif

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#if IS_ENABLED(CONFIG_RPMSG_QCOM_GLINK_SMEM)

struct qcom_glink *qcom_glink_smem_register(struct device *parent,
					    struct device_node *node);
void qcom_glink_smem_unregister(struct qcom_glink *glink);
<<<<<<< HEAD
=======
void qcom_glink_ssr_notify(const char *ssr_name);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#else

static inline struct qcom_glink *
qcom_glink_smem_register(struct device *parent,
			 struct device_node *node)
{
	return NULL;
}

static inline void qcom_glink_smem_unregister(struct qcom_glink *glink) {}
<<<<<<< HEAD
=======
static inline void qcom_glink_ssr_notify(const char *ssr_name) {}
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif

#endif
