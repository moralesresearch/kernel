// SPDX-License-Identifier: GPL-2.0-only
/*
<<<<<<< HEAD
 * soc-acpi-intel-ehl-match.c - tables and support for EHL ACPI enumeration.
=======
 * soc-apci-intel-ehl-match.c - tables and support for EHL ACPI enumeration.
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
 *
 * Copyright (c) 2019, Intel Corporation.
 *
 */

#include <sound/soc-acpi.h>
#include <sound/soc-acpi-intel-match.h>
#include "../skylake/skl.h"

struct snd_soc_acpi_mach snd_soc_acpi_intel_ehl_machines[] = {
	{
		.id = "10EC5660",
		.drv_name = "ehl_rt5660",
		.sof_fw_filename = "sof-ehl.ri",
		.sof_tplg_filename = "sof-ehl-rt5660.tplg",
	},
	{},
};
EXPORT_SYMBOL_GPL(snd_soc_acpi_intel_ehl_machines);
<<<<<<< HEAD
=======

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel Common ACPI Match module");
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
