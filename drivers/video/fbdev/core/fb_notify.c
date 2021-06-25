/*
 *  linux/drivers/video/fb_notify.c
 *
 *  Copyright (C) 2006 Antonino Daplas <adaplas@pol.net>
 *
 *	2001 - Documented with DocBook
 *	- Brad Douglas <brad@neruo.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the main directory of this archive
 * for more details.
 */
#include <linux/fb.h>
#include <linux/notifier.h>
#include <linux/export.h>

static BLOCKING_NOTIFIER_HEAD(fb_notifier_list);

/**
 *	fb_register_client - register a client notifier
 *	@nb: notifier block to callback on events
<<<<<<< HEAD
 *
 *	Return: 0 on success, negative error code on failure.
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
 */
int fb_register_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&fb_notifier_list, nb);
}
EXPORT_SYMBOL(fb_register_client);

/**
 *	fb_unregister_client - unregister a client notifier
 *	@nb: notifier block to callback on events
<<<<<<< HEAD
 *
 *	Return: 0 on success, negative error code on failure.
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
 */
int fb_unregister_client(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&fb_notifier_list, nb);
}
EXPORT_SYMBOL(fb_unregister_client);

/**
 * fb_notifier_call_chain - notify clients of fb_events
<<<<<<< HEAD
 * @val: value passed to callback
 * @v: pointer passed to callback
 *
 * Return: The return value of the last notifier function
=======
 *
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
 */
int fb_notifier_call_chain(unsigned long val, void *v)
{
	return blocking_notifier_call_chain(&fb_notifier_list, val, v);
}
EXPORT_SYMBOL_GPL(fb_notifier_call_chain);
