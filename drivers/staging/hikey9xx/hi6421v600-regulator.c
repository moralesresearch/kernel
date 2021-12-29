// SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
//
// Device driver for regulators in Hisi IC
//
// Copyright (c) 2013 Linaro Ltd.
// Copyright (c) 2011 Hisilicon.
// Copyright (c) 2020-2021 Huawei Technologies Co., Ltd
//
// Guodong Xu <guodong.xu@linaro.org>

#include <linux/delay.h>
#include <linux/mfd/hi6421-spmi-pmic.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/regulator/driver.h>
#include <linux/spmi.h>

struct hi6421_spmi_reg_info {
	struct regulator_desc	desc;
	struct hi6421_spmi_pmic *pmic;
	u8			eco_mode_mask;
	u32			eco_uA;

	/* Serialize regulator enable logic */
	struct mutex enable_mutex;
};

static const unsigned int ldo3_voltages[] = {
	1500000, 1550000, 1600000, 1650000,
	1700000, 1725000, 1750000, 1775000,
	1800000, 1825000, 1850000, 1875000,
	1900000, 1925000, 1950000, 2000000
};

static const unsigned int ldo4_voltages[] = {
	1725000, 1750000, 1775000, 1800000,
	1825000, 1850000, 1875000, 1900000
};

static const unsigned int ldo9_voltages[] = {
	1750000, 1800000, 1825000, 2800000,
	2850000, 2950000, 3000000, 3300000
};

static const unsigned int ldo15_voltages[] = {
	1800000, 1850000, 2400000, 2600000,
	2700000, 2850000, 2950000, 3000000
};

static const unsigned int ldo17_voltages[] = {
	2500000, 2600000, 2700000, 2800000,
	3000000, 3100000, 3200000, 3300000
};

static const unsigned int ldo34_voltages[] = {
	2600000, 2700000, 2800000, 2900000,
	3000000, 3100000, 3200000, 3300000
};

/**
 * HI6421V600_LDO() - specify a LDO power line
 * @_id: LDO id name string
 * @vtable: voltage table
 * @ereg: enable register
 * @emask: enable mask
 * @vreg: voltage select register
 * @odelay: off/on delay time in uS
 * @etime: enable time in uS
 * @ecomask: eco mode mask
 * @ecoamp: eco mode load uppler limit in uA
 */
#define HI6421V600_LDO(_id, vtable, ereg, emask, vreg,			       \
		       odelay, etime, ecomask, ecoamp)			       \
	[HI6421V600_##_id] = {						       \
		.desc = {						       \
			.name		= #_id,				       \
			.of_match        = of_match_ptr(#_id),		       \
			.regulators_node = of_match_ptr("regulators"),	       \
			.ops		= &hi6421_spmi_ldo_rops,	       \
			.type		= REGULATOR_VOLTAGE,		       \
			.id		= HI6421V600_##_id,		       \
			.owner		= THIS_MODULE,			       \
			.volt_table	= vtable,			       \
			.n_voltages	= ARRAY_SIZE(vtable),		       \
			.vsel_mask	= ARRAY_SIZE(vtable) - 1,	       \
			.vsel_reg	= vreg,				       \
			.enable_reg	= ereg,				       \
			.enable_mask	= emask,			       \
			.enable_time	= etime,			       \
			.ramp_delay	= etime,			       \
			.off_on_delay	= odelay,			       \
		},							       \
		.eco_mode_mask		= ecomask,			       \
		.eco_uA			= ecoamp,			       \
	}

static int hi6421_spmi_regulator_enable(struct regulator_dev *rdev)
{
	struct hi6421_spmi_reg_info *sreg = rdev_get_drvdata(rdev);
	struct hi6421_spmi_pmic *pmic = sreg->pmic;
	int ret;

	/* cannot enable more than one regulator at one time */
	mutex_lock(&sreg->enable_mutex);

	ret = regmap_update_bits(pmic->regmap, rdev->desc->enable_reg,
				 rdev->desc->enable_mask,
				 rdev->desc->enable_mask);

	/* Avoid powering up multiple devices at the same time */
	usleep_range(rdev->desc->off_on_delay, rdev->desc->off_on_delay + 60);

	mutex_unlock(&sreg->enable_mutex);

	return ret;
=======
/*
 * Device driver for regulators in Hisi IC
 *
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2011 Hisilicon.
 *
 * Guodong Xu <guodong.xu@linaro.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/delay.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/mfd/hi6421-spmi-pmic.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/of_regulator.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/spmi.h>
#include <linux/time.h>
#include <linux/uaccess.h>

#define rdev_dbg(rdev, fmt, arg...)	\
		 pr_debug("%s: %s: " fmt, (rdev)->desc->name, __func__, ##arg)

struct hi6421v600_regulator {
	struct regulator_desc rdesc;
	struct hi6421_spmi_pmic *pmic;
	u32 eco_mode_mask, eco_uA;
};

static DEFINE_MUTEX(enable_mutex);

/*
 * helper function to ensure when it returns it is at least 'delay_us'
 * microseconds after 'since'.
 */

static int hi6421_spmi_regulator_is_enabled(struct regulator_dev *rdev)
{
	struct hi6421v600_regulator *sreg = rdev_get_drvdata(rdev);
	struct hi6421_spmi_pmic *pmic = sreg->pmic;
	u32 reg_val;

	reg_val = hi6421_spmi_pmic_read(pmic, rdev->desc->enable_reg);

	rdev_dbg(rdev,
		 "enable_reg=0x%x, val= 0x%x, enable_state=%d\n",
		 rdev->desc->enable_reg,
		 reg_val, (reg_val & rdev->desc->enable_mask));

	return ((reg_val & rdev->desc->enable_mask) != 0);
}

static int hi6421_spmi_regulator_enable(struct regulator_dev *rdev)
{
	struct hi6421v600_regulator *sreg = rdev_get_drvdata(rdev);
	struct hi6421_spmi_pmic *pmic = sreg->pmic;

	/* cannot enable more than one regulator at one time */
	mutex_lock(&enable_mutex);
	usleep_range(HISI_REGS_ENA_PROTECT_TIME,
		     HISI_REGS_ENA_PROTECT_TIME + 1000);

	/* set enable register */
	rdev_dbg(rdev,
		 "off_on_delay=%d us, enable_reg=0x%x, enable_mask=0x%x\n",
		 rdev->desc->off_on_delay, rdev->desc->enable_reg,
		 rdev->desc->enable_mask);

	hi6421_spmi_pmic_rmw(pmic, rdev->desc->enable_reg,
			     rdev->desc->enable_mask,
			     rdev->desc->enable_mask);

	mutex_unlock(&enable_mutex);

	return 0;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static int hi6421_spmi_regulator_disable(struct regulator_dev *rdev)
{
<<<<<<< HEAD
	struct hi6421_spmi_reg_info *sreg = rdev_get_drvdata(rdev);
	struct hi6421_spmi_pmic *pmic = sreg->pmic;

	return regmap_update_bits(pmic->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask, 0);
=======
	struct hi6421v600_regulator *sreg = rdev_get_drvdata(rdev);
	struct hi6421_spmi_pmic *pmic = sreg->pmic;

	/* set enable register to 0 */
	rdev_dbg(rdev, "enable_reg=0x%x, enable_mask=0x%x\n",
		 rdev->desc->enable_reg, rdev->desc->enable_mask);

	hi6421_spmi_pmic_rmw(pmic, rdev->desc->enable_reg,
			     rdev->desc->enable_mask, 0);

	return 0;
}

static int hi6421_spmi_regulator_get_voltage_sel(struct regulator_dev *rdev)
{
	struct hi6421v600_regulator *sreg = rdev_get_drvdata(rdev);
	struct hi6421_spmi_pmic *pmic = sreg->pmic;
	u32 reg_val, selector;

	/* get voltage selector */
	reg_val = hi6421_spmi_pmic_read(pmic, rdev->desc->vsel_reg);

	selector = (reg_val & rdev->desc->vsel_mask) >>	(ffs(rdev->desc->vsel_mask) - 1);

	rdev_dbg(rdev,
		 "vsel_reg=0x%x, value=0x%x, entry=0x%x, voltage=%d mV\n",
		 rdev->desc->vsel_reg, reg_val, selector,
		rdev->desc->ops->list_voltage(rdev, selector) / 1000);

	return selector;
}

static int hi6421_spmi_regulator_set_voltage_sel(struct regulator_dev *rdev,
						 unsigned int selector)
{
	struct hi6421v600_regulator *sreg = rdev_get_drvdata(rdev);
	struct hi6421_spmi_pmic *pmic = sreg->pmic;
	u32 reg_val;

	if (unlikely(selector >= rdev->desc->n_voltages))
		return -EINVAL;

	reg_val = selector << (ffs(rdev->desc->vsel_mask) - 1);

	/* set voltage selector */
	rdev_dbg(rdev,
		 "vsel_reg=0x%x, mask=0x%x, value=0x%x, voltage=%d mV\n",
		 rdev->desc->vsel_reg, rdev->desc->vsel_mask, reg_val,
		 rdev->desc->ops->list_voltage(rdev, selector) / 1000);

	hi6421_spmi_pmic_rmw(pmic, rdev->desc->vsel_reg,
			     rdev->desc->vsel_mask, reg_val);

	return 0;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static unsigned int hi6421_spmi_regulator_get_mode(struct regulator_dev *rdev)
{
<<<<<<< HEAD
	struct hi6421_spmi_reg_info *sreg = rdev_get_drvdata(rdev);
	struct hi6421_spmi_pmic *pmic = sreg->pmic;
	u32 reg_val;

	regmap_read(pmic->regmap, rdev->desc->enable_reg, &reg_val);

	if (reg_val & sreg->eco_mode_mask)
		return REGULATOR_MODE_IDLE;

	return REGULATOR_MODE_NORMAL;
=======
	struct hi6421v600_regulator *sreg = rdev_get_drvdata(rdev);
	struct hi6421_spmi_pmic *pmic = sreg->pmic;
	unsigned int mode;
	u32 reg_val;

	reg_val = hi6421_spmi_pmic_read(pmic, rdev->desc->enable_reg);

	if (reg_val & sreg->eco_mode_mask)
		mode = REGULATOR_MODE_IDLE;
	else
		mode = REGULATOR_MODE_NORMAL;

	rdev_dbg(rdev,
		 "enable_reg=0x%x, eco_mode_mask=0x%x, reg_val=0x%x, %s mode\n",
		 rdev->desc->enable_reg, sreg->eco_mode_mask, reg_val,
		 mode == REGULATOR_MODE_IDLE ? "idle" : "normal");

	return mode;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static int hi6421_spmi_regulator_set_mode(struct regulator_dev *rdev,
					  unsigned int mode)
{
<<<<<<< HEAD
	struct hi6421_spmi_reg_info *sreg = rdev_get_drvdata(rdev);
=======
	struct hi6421v600_regulator *sreg = rdev_get_drvdata(rdev);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	struct hi6421_spmi_pmic *pmic = sreg->pmic;
	u32 val;

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		val = 0;
		break;
	case REGULATOR_MODE_IDLE:
		val = sreg->eco_mode_mask << (ffs(sreg->eco_mode_mask) - 1);
		break;
	default:
		return -EINVAL;
	}

<<<<<<< HEAD
	return regmap_update_bits(pmic->regmap, rdev->desc->enable_reg,
				  sreg->eco_mode_mask, val);
=======
	/* set mode */
	rdev_dbg(rdev, "enable_reg=0x%x, eco_mode_mask=0x%x, value=0x%x\n",
		 rdev->desc->enable_reg, sreg->eco_mode_mask, val);

	hi6421_spmi_pmic_rmw(pmic, rdev->desc->enable_reg,
			     sreg->eco_mode_mask, val);

	return 0;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static unsigned int
hi6421_spmi_regulator_get_optimum_mode(struct regulator_dev *rdev,
				       int input_uV, int output_uV,
				       int load_uA)
{
<<<<<<< HEAD
	struct hi6421_spmi_reg_info *sreg = rdev_get_drvdata(rdev);

	if (!sreg->eco_uA || ((unsigned int)load_uA > sreg->eco_uA))
=======
	struct hi6421v600_regulator *sreg = rdev_get_drvdata(rdev);

	if (load_uA || ((unsigned int)load_uA > sreg->eco_uA))
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		return REGULATOR_MODE_NORMAL;

	return REGULATOR_MODE_IDLE;
}

<<<<<<< HEAD
static const struct regulator_ops hi6421_spmi_ldo_rops = {
	.is_enabled = regulator_is_enabled_regmap,
=======
static int hi6421_spmi_dt_parse(struct platform_device *pdev,
				struct hi6421v600_regulator *sreg,
			 struct regulator_desc *rdesc)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	unsigned int *v_table;
	int ret;

	ret = of_property_read_u32(np, "reg", &rdesc->enable_reg);
	if (ret) {
		dev_err(dev, "missing reg property\n");
		return ret;
	}

	ret = of_property_read_u32(np, "vsel-reg", &rdesc->vsel_reg);
	if (ret) {
		dev_err(dev, "missing vsel-reg property\n");
		return ret;
	}

	ret = of_property_read_u32(np, "enable-mask", &rdesc->enable_mask);
	if (ret) {
		dev_err(dev, "missing enable-mask property\n");
		return ret;
	}

	/*
	 * Not all regulators work on idle mode
	 */
	ret = of_property_read_u32(np, "idle-mode-mask", &sreg->eco_mode_mask);
	if (ret) {
		dev_dbg(dev, "LDO doesn't support economy mode.\n");
		sreg->eco_mode_mask = 0;
		sreg->eco_uA = 0;
	} else {
		ret = of_property_read_u32(np, "eco-microamp", &sreg->eco_uA);
		if (ret) {
			dev_err(dev, "missing eco-microamp property\n");
			return ret;
		}
	}

	/* parse .off-on-delay */
	ret = of_property_read_u32(np, "off-on-delay-us",
				   &rdesc->off_on_delay);
	if (ret) {
		dev_err(dev, "missing off-on-delay-us property\n");
		return ret;
	}

	/* parse .enable_time */
	ret = of_property_read_u32(np, "startup-delay-us",
				   &rdesc->enable_time);
	if (ret) {
		dev_err(dev, "missing startup-delay-us property\n");
		return ret;
	}

	/* FIXME: are there a better value for this? */
	rdesc->ramp_delay = rdesc->enable_time;

	/* parse volt_table */

	rdesc->n_voltages = of_property_count_u32_elems(np, "voltage-table");

	v_table = devm_kzalloc(dev, sizeof(unsigned int) * rdesc->n_voltages,
			       GFP_KERNEL);
	if (unlikely(!v_table))
		return  -ENOMEM;
	rdesc->volt_table = v_table;

	ret = of_property_read_u32_array(np, "voltage-table",
					 v_table, rdesc->n_voltages);
	if (ret) {
		dev_err(dev, "missing voltage-table property\n");
		return ret;
	}

	/*
	 * Instead of explicitly requiring a mask for the voltage selector,
	 * as they all start from bit zero (at least on the known LDOs),
	 * just use the number of voltages at the voltage table, getting the
	 * minimal mask that would pick everything.
	 */
	rdesc->vsel_mask = (1 << (fls(rdesc->n_voltages) - 1)) - 1;

	dev_dbg(dev, "voltage selector settings: reg: 0x%x, mask: 0x%x\n",
		rdesc->vsel_reg, rdesc->vsel_mask);

	return 0;
}

static const struct regulator_ops hi6421_spmi_ldo_rops = {
	.is_enabled = hi6421_spmi_regulator_is_enabled,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	.enable = hi6421_spmi_regulator_enable,
	.disable = hi6421_spmi_regulator_disable,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_iterate,
<<<<<<< HEAD
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
=======
	.get_voltage_sel = hi6421_spmi_regulator_get_voltage_sel,
	.set_voltage_sel = hi6421_spmi_regulator_set_voltage_sel,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	.get_mode = hi6421_spmi_regulator_get_mode,
	.set_mode = hi6421_spmi_regulator_set_mode,
	.get_optimum_mode = hi6421_spmi_regulator_get_optimum_mode,
};

<<<<<<< HEAD
/* HI6421v600 regulators with known registers */
enum hi6421_spmi_regulator_id {
	HI6421V600_LDO3,
	HI6421V600_LDO4,
	HI6421V600_LDO9,
	HI6421V600_LDO15,
	HI6421V600_LDO16,
	HI6421V600_LDO17,
	HI6421V600_LDO33,
	HI6421V600_LDO34,
};

static struct hi6421_spmi_reg_info regulator_info[] = {
	HI6421V600_LDO(LDO3, ldo3_voltages,
		       0x16, 0x01, 0x51,
		       20000, 120,
		       0, 0),
	HI6421V600_LDO(LDO4, ldo4_voltages,
		       0x17, 0x01, 0x52,
		       20000, 120,
		       0x10, 10000),
	HI6421V600_LDO(LDO9, ldo9_voltages,
		       0x1c, 0x01, 0x57,
		       20000, 360,
		       0x10, 10000),
	HI6421V600_LDO(LDO15, ldo15_voltages,
		       0x21, 0x01, 0x5c,
		       20000, 360,
		       0x10, 10000),
	HI6421V600_LDO(LDO16, ldo15_voltages,
		       0x22, 0x01, 0x5d,
		       20000, 360,
		       0x10, 10000),
	HI6421V600_LDO(LDO17, ldo17_voltages,
		       0x23, 0x01, 0x5e,
		       20000, 120,
		       0x10, 10000),
	HI6421V600_LDO(LDO33, ldo17_voltages,
		       0x32, 0x01, 0x6d,
		       20000, 120,
		       0, 0),
	HI6421V600_LDO(LDO34, ldo34_voltages,
		       0x33, 0x01, 0x6e,
		       20000, 120,
		       0, 0),
};
=======
static int hi6421_spmi_regulator_probe_ldo(struct platform_device *pdev,
					   struct device_node *np,
					   struct hi6421_spmi_pmic *pmic)
{
	struct regulation_constraints *constraint;
	struct regulator_init_data *initdata;
	struct regulator_config config = { };
	struct hi6421v600_regulator *sreg;
	struct device *dev = &pdev->dev;
	struct regulator_desc *rdesc;
	struct regulator_dev *rdev;
	const char *supplyname;
	int ret;

	initdata = of_get_regulator_init_data(dev, np, NULL);
	if (!initdata) {
		dev_err(dev, "failed to get regulator data\n");
		return -EINVAL;
	}

	sreg = devm_kzalloc(dev, sizeof(*sreg), GFP_KERNEL);
	if (!sreg)
		return -ENOMEM;

	sreg->pmic = pmic;
	rdesc = &sreg->rdesc;

	rdesc->name = initdata->constraints.name;
	rdesc->ops = &hi6421_spmi_ldo_rops;
	rdesc->type = REGULATOR_VOLTAGE;
	rdesc->min_uV = initdata->constraints.min_uV;

	supplyname = of_get_property(np, "supply_name", NULL);
	if (supplyname)
		initdata->supply_regulator = supplyname;

	/* parse device tree data for regulator specific */
	ret = hi6421_spmi_dt_parse(pdev, sreg, rdesc);
	if (ret)
		return ret;

	/* hisi regulator supports two modes */
	constraint = &initdata->constraints;

	constraint->valid_modes_mask = REGULATOR_MODE_NORMAL;
	if (sreg->eco_mode_mask) {
		constraint->valid_modes_mask |= REGULATOR_MODE_IDLE;
		constraint->valid_ops_mask |= REGULATOR_CHANGE_MODE;
	}

	config.dev = &pdev->dev;
	config.init_data = initdata;
	config.driver_data = sreg;
	config.of_node = pdev->dev.of_node;

	/* register regulator */
	rdev = regulator_register(rdesc, &config);
	if (IS_ERR(rdev)) {
		dev_err(dev, "failed to register %s\n",
			rdesc->name);
		return PTR_ERR(rdev);
	}

	rdev_dbg(rdev, "valid_modes_mask: 0x%x, valid_ops_mask: 0x%x\n",
		 constraint->valid_modes_mask, constraint->valid_ops_mask);

	dev_set_drvdata(dev, rdev);

	return 0;
}
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

static int hi6421_spmi_regulator_probe(struct platform_device *pdev)
{
	struct device *pmic_dev = pdev->dev.parent;
<<<<<<< HEAD
	struct regulator_config config = { };
	struct hi6421_spmi_reg_info *sreg;
	struct hi6421_spmi_reg_info *info;
	struct device *dev = &pdev->dev;
	struct hi6421_spmi_pmic *pmic;
	struct regulator_dev *rdev;
	int i;
=======
	struct device_node *np = pmic_dev->of_node;
	struct device_node *regulators, *child;
	struct platform_device *new_pdev;
	struct hi6421_spmi_pmic *pmic;
	int ret;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	/*
	 * This driver is meant to be called by hi6421-spmi-core,
	 * which should first set drvdata. If this doesn't happen, hit
	 * a warn on and return.
	 */
	pmic = dev_get_drvdata(pmic_dev);
	if (WARN_ON(!pmic))
		return -ENODEV;

<<<<<<< HEAD
	sreg = devm_kzalloc(dev, sizeof(*sreg), GFP_KERNEL);
	if (!sreg)
		return -ENOMEM;

	sreg->pmic = pmic;
	mutex_init(&sreg->enable_mutex);

	for (i = 0; i < ARRAY_SIZE(regulator_info); i++) {
		info = &regulator_info[i];

		config.dev = pdev->dev.parent;
		config.driver_data = sreg;
		config.regmap = pmic->regmap;

		rdev = devm_regulator_register(dev, &info->desc, &config);
		if (IS_ERR(rdev)) {
			dev_err(dev, "failed to register %s\n",
				info->desc.name);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}

static const struct platform_device_id hi6421_spmi_regulator_table[] = {
	{ .name = "hi6421v600-regulator" },
	{},
};
MODULE_DEVICE_TABLE(platform, hi6421_spmi_regulator_table);

static struct platform_driver hi6421_spmi_regulator_driver = {
	.id_table = hi6421_spmi_regulator_table,
	.driver = {
		.name = "hi6421v600-regulator",
	},
	.probe	= hi6421_spmi_regulator_probe,
};
module_platform_driver(hi6421_spmi_regulator_driver);

MODULE_DESCRIPTION("Hi6421v600 SPMI regulator driver");
=======
	regulators = of_get_child_by_name(np, "regulators");
	if (!regulators) {
		dev_err(&pdev->dev, "regulator node not found\n");
		return -ENODEV;
	}

	/*
	 * Parse all LDO regulator nodes
	 */
	for_each_child_of_node(regulators, child) {
		dev_dbg(&pdev->dev, "adding child %pOF\n", child);

		new_pdev = platform_device_alloc(child->name, -1);
		new_pdev->dev.parent = pmic_dev;
		new_pdev->dev.of_node = of_node_get(child);

		ret = platform_device_add(new_pdev);
		if (ret < 0) {
			platform_device_put(new_pdev);
			continue;
		}

		ret = hi6421_spmi_regulator_probe_ldo(new_pdev, child, pmic);
		if (ret < 0)
			platform_device_put(new_pdev);
	}

	of_node_put(regulators);

	return 0;
}

static int hi6421_spmi_regulator_remove(struct platform_device *pdev)
{
	struct regulator_dev *rdev = dev_get_drvdata(&pdev->dev);
	struct hi6421v600_regulator *sreg = rdev_get_drvdata(rdev);

	regulator_unregister(rdev);

	if (rdev->desc->volt_table)
		devm_kfree(&pdev->dev, (unsigned int *)rdev->desc->volt_table);

	kfree(sreg);

	return 0;
}

static const struct platform_device_id hi6421v600_regulator_table[] = {
	{ .name = "hi6421v600-regulator" },
	{},
};
MODULE_DEVICE_TABLE(platform, hi6421v600_regulator_table);

static struct platform_driver hi6421v600_regulator_driver = {
	.id_table = hi6421v600_regulator_table,
	.driver = {
		.name	= "hi6421v600-regulator",
	},
	.probe	= hi6421_spmi_regulator_probe,
	.remove	= hi6421_spmi_regulator_remove,
};
module_platform_driver(hi6421v600_regulator_driver);

MODULE_DESCRIPTION("Hi6421v600 regulator driver");
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
MODULE_LICENSE("GPL v2");

