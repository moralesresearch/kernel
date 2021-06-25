/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#ifndef CFSERL_H_
#define CFSERL_H_
#include <net/caif/caif_layer.h>

struct cflayer *cfserl_create(int instance, bool use_stx);
<<<<<<< HEAD
void cfserl_release(struct cflayer *layer);
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif
