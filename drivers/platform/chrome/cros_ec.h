/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * ChromeOS Embedded Controller core interface.
 *
 * Copyright (C) 2020 Google LLC
 */

#ifndef __CROS_EC_H
#define __CROS_EC_H

<<<<<<< HEAD
#include <linux/interrupt.h>

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
int cros_ec_register(struct cros_ec_device *ec_dev);
int cros_ec_unregister(struct cros_ec_device *ec_dev);

int cros_ec_suspend(struct cros_ec_device *ec_dev);
int cros_ec_resume(struct cros_ec_device *ec_dev);

<<<<<<< HEAD
irqreturn_t cros_ec_irq_thread(int irq, void *data);
=======
bool cros_ec_handle_event(struct cros_ec_device *ec_dev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#endif /* __CROS_EC_H */
