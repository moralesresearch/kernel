/* SPDX-License-Identifier: GPL-2.0 */
<<<<<<< HEAD
/* Copyright (C) B.A.T.M.A.N. contributors:
=======
/* Copyright (C) 2012-2020  B.A.T.M.A.N. contributors:
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
 *
 * Edo Monticelli, Antonio Quartulli
 */

#ifndef _NET_BATMAN_ADV_TP_METER_H_
#define _NET_BATMAN_ADV_TP_METER_H_

#include "main.h"

#include <linux/skbuff.h>
#include <linux/types.h>

void batadv_tp_meter_init(void);
void batadv_tp_start(struct batadv_priv *bat_priv, const u8 *dst,
		     u32 test_length, u32 *cookie);
void batadv_tp_stop(struct batadv_priv *bat_priv, const u8 *dst,
		    u8 return_value);
void batadv_tp_meter_recv(struct batadv_priv *bat_priv, struct sk_buff *skb);

#endif /* _NET_BATMAN_ADV_TP_METER_H_ */
