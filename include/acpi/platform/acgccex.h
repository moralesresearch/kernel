/* SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acgccex.h - Extra GCC specific defines, etc.
 *
<<<<<<< HEAD
 * Copyright (C) 2000 - 2021, Intel Corp.
=======
 * Copyright (C) 2000 - 2020, Intel Corp.
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
 *
 *****************************************************************************/

#ifndef __ACGCCEX_H__
#define __ACGCCEX_H__

/*
 * Some versions of gcc implement strchr() with a buggy macro. So,
 * undef it here. Prevents error messages of this form (usually from the
 * file getopt.c):
 *
 * error: logical '&&' with non-zero constant will always evaluate as true
 */
#ifdef strchr
#undef strchr
#endif

#endif				/* __ACGCCEX_H__ */
