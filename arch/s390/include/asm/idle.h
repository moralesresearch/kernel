/* SPDX-License-Identifier: GPL-2.0 */
/*
 *  Copyright IBM Corp. 2014
 *
 *  Author: Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef _S390_IDLE_H
#define _S390_IDLE_H

#include <linux/types.h>
#include <linux/device.h>
#include <linux/seqlock.h>

struct s390_idle_data {
	seqcount_t seqcount;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	unsigned long idle_count;
	unsigned long idle_time;
	unsigned long clock_idle_enter;
	unsigned long clock_idle_exit;
	unsigned long timer_idle_enter;
	unsigned long timer_idle_exit;
	unsigned long mt_cycles_enter[8];
<<<<<<< HEAD
=======
=======
	unsigned long long idle_count;
	unsigned long long idle_time;
	unsigned long long clock_idle_enter;
	unsigned long long clock_idle_exit;
	unsigned long long timer_idle_enter;
	unsigned long long timer_idle_exit;
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

extern struct device_attribute dev_attr_idle_count;
extern struct device_attribute dev_attr_idle_time_us;

<<<<<<< HEAD
void psw_idle(struct s390_idle_data *data, unsigned long psw_mask);
void psw_idle_exit(void);
=======
<<<<<<< HEAD
void psw_idle(struct s390_idle_data *data, unsigned long psw_mask);
void psw_idle_exit(void);
=======
void psw_idle(struct s390_idle_data *, unsigned long);
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#endif /* _S390_IDLE_H */
