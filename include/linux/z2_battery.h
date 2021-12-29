/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_Z2_BATTERY_H
#define _LINUX_Z2_BATTERY_H

struct z2_battery_info {
	int	 batt_I2C_bus;
	int	 batt_I2C_addr;
	int	 batt_I2C_reg;
<<<<<<< HEAD
=======
	int	 charge_gpio;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	int	 min_voltage;
	int	 max_voltage;
	int	 batt_div;
	int	 batt_mult;
	int	 batt_tech;
	char	*batt_name;
};

#endif
