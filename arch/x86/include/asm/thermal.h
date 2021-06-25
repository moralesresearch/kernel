/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_THERMAL_H
#define _ASM_X86_THERMAL_H

#ifdef CONFIG_X86_THERMAL_VECTOR
<<<<<<< HEAD
void therm_lvt_init(void);
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
void intel_init_thermal(struct cpuinfo_x86 *c);
bool x86_thermal_enabled(void);
void intel_thermal_interrupt(void);
#else
<<<<<<< HEAD
static inline void therm_lvt_init(void)				{ }
static inline void intel_init_thermal(struct cpuinfo_x86 *c)	{ }
=======
static inline void intel_init_thermal(struct cpuinfo_x86 *c) { }
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif

#endif /* _ASM_X86_THERMAL_H */
