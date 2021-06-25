
/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __PERF_API_PROBE_H
#define __PERF_API_PROBE_H

#include <stdbool.h>

bool perf_can_aux_sample(void);
bool perf_can_comm_exec(void);
bool perf_can_record_cpu_wide(void);
bool perf_can_record_switch_events(void);
bool perf_can_record_text_poke_events(void);
bool perf_can_sample_identifier(void);
<<<<<<< HEAD
bool perf_can_record_build_id(void);
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#endif // __PERF_API_PROBE_H
