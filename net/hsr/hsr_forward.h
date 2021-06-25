/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * include file for HSR and PRP.
 */

#ifndef __HSR_FORWARD_H
#define __HSR_FORWARD_H

#include <linux/netdevice.h>
#include "hsr_main.h"

void hsr_forward_skb(struct sk_buff *skb, struct hsr_port *port);
struct sk_buff *prp_create_tagged_frame(struct hsr_frame_info *frame,
					struct hsr_port *port);
struct sk_buff *hsr_create_tagged_frame(struct hsr_frame_info *frame,
					struct hsr_port *port);
struct sk_buff *hsr_get_untagged_frame(struct hsr_frame_info *frame,
				       struct hsr_port *port);
struct sk_buff *prp_get_untagged_frame(struct hsr_frame_info *frame,
				       struct hsr_port *port);
bool prp_drop_frame(struct hsr_frame_info *frame, struct hsr_port *port);
<<<<<<< HEAD
bool hsr_drop_frame(struct hsr_frame_info *frame, struct hsr_port *port);
int prp_fill_frame_info(__be16 proto, struct sk_buff *skb,
			struct hsr_frame_info *frame);
int hsr_fill_frame_info(__be16 proto, struct sk_buff *skb,
			struct hsr_frame_info *frame);
=======
void prp_fill_frame_info(__be16 proto, struct sk_buff *skb,
			 struct hsr_frame_info *frame);
void hsr_fill_frame_info(__be16 proto, struct sk_buff *skb,
			 struct hsr_frame_info *frame);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif /* __HSR_FORWARD_H */
