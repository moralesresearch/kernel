/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIPS_SPRAM_H
#define _MIPS_SPRAM_H

#if defined(CONFIG_MIPS_SPRAM)
extern __init void spram_config(void);
#else
<<<<<<< HEAD
static inline void spram_config(void) { }
=======
<<<<<<< HEAD
static inline void spram_config(void) { }
=======
static inline void spram_config(void) { };
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif /* CONFIG_MIPS_SPRAM */

#endif /* _MIPS_SPRAM_H */
