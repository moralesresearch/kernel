/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright 2017 Icenowy Zheng <icenowy@aosc.xyz>
 */

#ifndef _CCU_SUN50I_H6_R_H
#define _CCU_SUN50I_H6_R_H

#include <dt-bindings/clock/sun50i-h6-r-ccu.h>
#include <dt-bindings/reset/sun50i-h6-r-ccu.h>

/* AHB/APB bus clocks are not exported except APB1 for R_PIO */
#define CLK_R_AHB	1

#define CLK_R_APB2	3

<<<<<<< HEAD
#define CLK_NUMBER	(CLK_R_APB2_RSB + 1)
=======
#define CLK_NUMBER	(CLK_W1 + 1)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#endif /* _CCU_SUN50I_H6_R_H */
