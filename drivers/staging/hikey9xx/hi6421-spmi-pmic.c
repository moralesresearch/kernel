// SPDX-License-Identifier: GPL-2.0
/*
 * Device driver for regulators in HISI PMIC IC
 *
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2011 Hisilicon.
<<<<<<< HEAD
 * Copyright (c) 2020-2021 Huawei Technologies Co., Ltd
 */

#include <linux/bitops.h>
#include <linux/interrupt.h>
=======
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/delay.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/io.h>
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#include <linux/irq.h>
#include <linux/mfd/core.h>
#include <linux/mfd/hi6421-spmi-pmic.h>
#include <linux/module.h>
<<<<<<< HEAD
#include <linux/of_gpio.h>
=======
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/of_irq.h>
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/spmi.h>

<<<<<<< HEAD
enum hi6421_spmi_pmic_irq_list {
	OTMP = 0,
	VBUS_CONNECT,
	VBUS_DISCONNECT,
	ALARMON_R,
	HOLD_6S,
	HOLD_1S,
	POWERKEY_UP,
	POWERKEY_DOWN,
	OCP_SCP_R,
	COUL_R,
	SIM0_HPD_R,
	SIM0_HPD_F,
	SIM1_HPD_R,
	SIM1_HPD_F,
	PMIC_IRQ_LIST_MAX,
};
=======
/* 8-bit register offset in PMIC */
#define HISI_MASK_STATE			0xff
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#define HISI_IRQ_ARRAY			2
#define HISI_IRQ_NUM			(HISI_IRQ_ARRAY * 8)

<<<<<<< HEAD
#define HISI_IRQ_KEY_NUM		0

#define HISI_BITS			8
#define HISI_IRQ_KEY_VALUE		(BIT(POWERKEY_DOWN) | BIT(POWERKEY_UP))
#define HISI_MASK			GENMASK(HISI_BITS - 1, 0)

/*
 * The IRQs are mapped as:
 *
 * 	======================  =============   ============	=====
 *	IRQ			MASK REGISTER 	IRQ REGISTER	BIT
 * 	======================  =============   ============	=====
 *	OTMP			0x0202		0x212		bit 0
 *	VBUS_CONNECT		0x0202		0x212		bit 1
 *	VBUS_DISCONNECT		0x0202		0x212		bit 2
 *	ALARMON_R		0x0202		0x212		bit 3
 *	HOLD_6S			0x0202		0x212		bit 4
 *	HOLD_1S			0x0202		0x212		bit 5
 *	POWERKEY_UP		0x0202		0x212		bit 6
 *	POWERKEY_DOWN		0x0202		0x212		bit 7
 *
 *	OCP_SCP_R		0x0203		0x213		bit 0
 *	COUL_R			0x0203		0x213		bit 1
 *	SIM0_HPD_R		0x0203		0x213		bit 2
 *	SIM0_HPD_F		0x0203		0x213		bit 3
 *	SIM1_HPD_R		0x0203		0x213		bit 4
 *	SIM1_HPD_F		0x0203		0x213		bit 5
 * 	======================  =============   ============	=====
 */
#define SOC_PMIC_IRQ_MASK_0_ADDR	0x0202
#define SOC_PMIC_IRQ0_ADDR		0x0212

#define IRQ_MASK_REGISTER(irq_data)	(SOC_PMIC_IRQ_MASK_0_ADDR + \
					 (irqd_to_hwirq(irq_data) >> 3))
#define IRQ_MASK_BIT(irq_data)		BIT(irqd_to_hwirq(irq_data) & 0x07)
=======
#define SOC_PMIC_IRQ_MASK_0_ADDR	0x0202
#define SOC_PMIC_IRQ0_ADDR		0x0212

#define HISI_IRQ_KEY_NUM		0
#define HISI_IRQ_KEY_VALUE		0xc0
#define HISI_IRQ_KEY_DOWN		7
#define HISI_IRQ_KEY_UP			6

#define HISI_MASK_FIELD			0xFF
#define HISI_BITS			8

/*define the first group interrupt register number*/
#define HISI_PMIC_FIRST_GROUP_INT_NUM	2
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

static const struct mfd_cell hi6421v600_devs[] = {
	{ .name = "hi6421v600-regulator", },
};

<<<<<<< HEAD
static irqreturn_t hi6421_spmi_irq_handler(int irq, void *priv)
{
	struct hi6421_spmi_pmic *ddata = (struct hi6421_spmi_pmic *)priv;
	unsigned long pending;
	unsigned int in;
	int i, offset;

	for (i = 0; i < HISI_IRQ_ARRAY; i++) {
		regmap_read(ddata->regmap, SOC_PMIC_IRQ0_ADDR + i, &in);
		pending = HISI_MASK & in;
		regmap_write(ddata->regmap, SOC_PMIC_IRQ0_ADDR + i, pending);

		if (i == HISI_IRQ_KEY_NUM &&
		    (pending & HISI_IRQ_KEY_VALUE) == HISI_IRQ_KEY_VALUE) {
			generic_handle_irq(ddata->irqs[POWERKEY_DOWN]);
			generic_handle_irq(ddata->irqs[POWERKEY_UP]);
			pending &= (~HISI_IRQ_KEY_VALUE);
		}

		if (!pending)
			continue;

		for_each_set_bit(offset, &pending, HISI_BITS)
			generic_handle_irq(ddata->irqs[offset + i * HISI_BITS]);
=======
/*
 * The PMIC register is only 8-bit.
 * Hisilicon SoC use hardware to map PMIC register into SoC mapping.
 * At here, we are accessing SoC register with 32-bit.
 */
int hi6421_spmi_pmic_read(struct hi6421_spmi_pmic *pmic, int reg)
{
	struct spmi_device *pdev;
	u8 read_value = 0;
	u32 ret;

	pdev = to_spmi_device(pmic->dev);
	if (!pdev) {
		pr_err("%s: pdev get failed!\n", __func__);
		return -ENODEV;
	}

	ret = spmi_ext_register_readl(pdev, reg, &read_value, 1);
	if (ret) {
		pr_err("%s: spmi_ext_register_readl failed!\n", __func__);
		return ret;
	}
	return read_value;
}
EXPORT_SYMBOL(hi6421_spmi_pmic_read);

int hi6421_spmi_pmic_write(struct hi6421_spmi_pmic *pmic, int reg, u32 val)
{
	struct spmi_device *pdev;
	u32 ret;

	pdev = to_spmi_device(pmic->dev);
	if (!pdev) {
		pr_err("%s: pdev get failed!\n", __func__);
		return -ENODEV;
	}

	ret = spmi_ext_register_writel(pdev, reg, (unsigned char *)&val, 1);
	if (ret)
		pr_err("%s: spmi_ext_register_writel failed!\n", __func__);

	return ret;
}
EXPORT_SYMBOL(hi6421_spmi_pmic_write);

int hi6421_spmi_pmic_rmw(struct hi6421_spmi_pmic *pmic, int reg,
			 u32 mask, u32 bits)
{
	unsigned long flags;
	u32 data;
	int ret;

	spin_lock_irqsave(&pmic->lock, flags);
	data = hi6421_spmi_pmic_read(pmic, reg) & ~mask;
	data |= mask & bits;
	ret = hi6421_spmi_pmic_write(pmic, reg, data);
	spin_unlock_irqrestore(&pmic->lock, flags);

	return ret;
}
EXPORT_SYMBOL(hi6421_spmi_pmic_rmw);

static irqreturn_t hi6421_spmi_irq_handler(int irq, void *data)
{
	struct hi6421_spmi_pmic *pmic = (struct hi6421_spmi_pmic *)data;
	unsigned long pending;
	int i, offset;

	for (i = 0; i < HISI_IRQ_ARRAY; i++) {
		pending = hi6421_spmi_pmic_read(pmic, (i + SOC_PMIC_IRQ0_ADDR));
		pending &= HISI_MASK_FIELD;
		if (pending != 0)
			pr_debug("pending[%d]=0x%lx\n\r", i, pending);

		hi6421_spmi_pmic_write(pmic, (i + SOC_PMIC_IRQ0_ADDR), pending);

		/* solve powerkey order */
		if ((i == HISI_IRQ_KEY_NUM) &&
		    ((pending & HISI_IRQ_KEY_VALUE) == HISI_IRQ_KEY_VALUE)) {
			generic_handle_irq(pmic->irqs[HISI_IRQ_KEY_DOWN]);
			generic_handle_irq(pmic->irqs[HISI_IRQ_KEY_UP]);
			pending &= (~HISI_IRQ_KEY_VALUE);
		}

		if (pending) {
			for_each_set_bit(offset, &pending, HISI_BITS)
				generic_handle_irq(pmic->irqs[offset + i * HISI_BITS]);
		}
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	}

	return IRQ_HANDLED;
}

static void hi6421_spmi_irq_mask(struct irq_data *d)
{
<<<<<<< HEAD
	struct hi6421_spmi_pmic *ddata = irq_data_get_irq_chip_data(d);
	unsigned long flags;
	unsigned int data;
	u32 offset;

	offset = IRQ_MASK_REGISTER(d);

	spin_lock_irqsave(&ddata->lock, flags);

	regmap_read(ddata->regmap, offset, &data);
	data |= IRQ_MASK_BIT(d);
	regmap_write(ddata->regmap, offset, data);

	spin_unlock_irqrestore(&ddata->lock, flags);
=======
	struct hi6421_spmi_pmic *pmic = irq_data_get_irq_chip_data(d);
	u32 data, offset;
	unsigned long flags;

	offset = (irqd_to_hwirq(d) >> 3);
	offset += SOC_PMIC_IRQ_MASK_0_ADDR;

	spin_lock_irqsave(&pmic->lock, flags);
	data = hi6421_spmi_pmic_read(pmic, offset);
	data |= (1 << (irqd_to_hwirq(d) & 0x07));
	hi6421_spmi_pmic_write(pmic, offset, data);
	spin_unlock_irqrestore(&pmic->lock, flags);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static void hi6421_spmi_irq_unmask(struct irq_data *d)
{
<<<<<<< HEAD
	struct hi6421_spmi_pmic *ddata = irq_data_get_irq_chip_data(d);
=======
	struct hi6421_spmi_pmic *pmic = irq_data_get_irq_chip_data(d);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	u32 data, offset;
	unsigned long flags;

	offset = (irqd_to_hwirq(d) >> 3);
	offset += SOC_PMIC_IRQ_MASK_0_ADDR;

<<<<<<< HEAD
	spin_lock_irqsave(&ddata->lock, flags);

	regmap_read(ddata->regmap, offset, &data);
	data &= ~(1 << (irqd_to_hwirq(d) & 0x07));
	regmap_write(ddata->regmap, offset, data);

	spin_unlock_irqrestore(&ddata->lock, flags);
=======
	spin_lock_irqsave(&pmic->lock, flags);
	data = hi6421_spmi_pmic_read(pmic, offset);
	data &= ~(1 << (irqd_to_hwirq(d) & 0x07));
	hi6421_spmi_pmic_write(pmic, offset, data);
	spin_unlock_irqrestore(&pmic->lock, flags);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static struct irq_chip hi6421_spmi_pmu_irqchip = {
	.name		= "hisi-irq",
	.irq_mask	= hi6421_spmi_irq_mask,
	.irq_unmask	= hi6421_spmi_irq_unmask,
	.irq_disable	= hi6421_spmi_irq_mask,
	.irq_enable	= hi6421_spmi_irq_unmask,
};

static int hi6421_spmi_irq_map(struct irq_domain *d, unsigned int virq,
			       irq_hw_number_t hw)
{
<<<<<<< HEAD
	struct hi6421_spmi_pmic *ddata = d->host_data;

	irq_set_chip_and_handler_name(virq, &hi6421_spmi_pmu_irqchip,
				      handle_simple_irq, "hisi");
	irq_set_chip_data(virq, ddata);
=======
	struct hi6421_spmi_pmic *pmic = d->host_data;

	irq_set_chip_and_handler_name(virq, &hi6421_spmi_pmu_irqchip,
				      handle_simple_irq, "hisi");
	irq_set_chip_data(virq, pmic);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	irq_set_irq_type(virq, IRQ_TYPE_NONE);

	return 0;
}

static const struct irq_domain_ops hi6421_spmi_domain_ops = {
	.map	= hi6421_spmi_irq_map,
	.xlate	= irq_domain_xlate_twocell,
};

<<<<<<< HEAD
static void hi6421_spmi_pmic_irq_init(struct hi6421_spmi_pmic *ddata)
{
	int i;
	unsigned int pending;

	for (i = 0; i < HISI_IRQ_ARRAY; i++)
		regmap_write(ddata->regmap, SOC_PMIC_IRQ_MASK_0_ADDR + i,
			     HISI_MASK);

	for (i = 0; i < HISI_IRQ_ARRAY; i++) {
		regmap_read(ddata->regmap, SOC_PMIC_IRQ0_ADDR + i, &pending);
		regmap_write(ddata->regmap, SOC_PMIC_IRQ0_ADDR + i,
			     HISI_MASK);
	}
}

static const struct regmap_config regmap_config = {
	.reg_bits		= 16,
	.val_bits		= HISI_BITS,
	.max_register		= 0xffff,
	.fast_io		= true
};

=======
static void hi6421_spmi_pmic_irq_prc(struct hi6421_spmi_pmic *pmic)
{
	int i, pending;

	for (i = 0 ; i < HISI_IRQ_ARRAY; i++)
		hi6421_spmi_pmic_write(pmic, SOC_PMIC_IRQ_MASK_0_ADDR + i,
				       HISI_MASK_STATE);

	for (i = 0 ; i < HISI_IRQ_ARRAY; i++) {
		pending = hi6421_spmi_pmic_read(pmic, SOC_PMIC_IRQ0_ADDR + i);

		pr_debug("PMU IRQ address value:irq[0x%x] = 0x%x\n",
			 SOC_PMIC_IRQ0_ADDR + i, pending);
		hi6421_spmi_pmic_write(pmic, SOC_PMIC_IRQ0_ADDR + i,
				       HISI_MASK_STATE);
	}
}

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
static int hi6421_spmi_pmic_probe(struct spmi_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
<<<<<<< HEAD
	struct hi6421_spmi_pmic *ddata;
	unsigned int virq;
	int ret, i;

	ddata = devm_kzalloc(dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	ddata->regmap = devm_regmap_init_spmi_ext(pdev, &regmap_config);
	if (IS_ERR(ddata->regmap))
		return PTR_ERR(ddata->regmap);

	spin_lock_init(&ddata->lock);

	ddata->dev = dev;

	ddata->gpio = of_get_gpio(np, 0);
	if (ddata->gpio < 0)
		return ddata->gpio;

	if (!gpio_is_valid(ddata->gpio))
		return -EINVAL;

	ret = devm_gpio_request_one(dev, ddata->gpio, GPIOF_IN, "pmic");
	if (ret < 0) {
		dev_err(dev, "Failed to request gpio%d\n", ddata->gpio);
		return ret;
	}

	ddata->irq = gpio_to_irq(ddata->gpio);

	hi6421_spmi_pmic_irq_init(ddata);

	ddata->irqs = devm_kzalloc(dev, HISI_IRQ_NUM * sizeof(int), GFP_KERNEL);
	if (!ddata->irqs)
		return -ENOMEM;

	ddata->domain = irq_domain_add_simple(np, HISI_IRQ_NUM, 0,
					      &hi6421_spmi_domain_ops, ddata);
	if (!ddata->domain) {
		dev_err(dev, "Failed to create IRQ domain\n");
		return -ENODEV;
	}

	for (i = 0; i < HISI_IRQ_NUM; i++) {
		virq = irq_create_mapping(ddata->domain, i);
		if (!virq) {
			dev_err(dev, "Failed to map H/W IRQ\n");
			return -ENOSPC;
		}
		ddata->irqs[i] = virq;
	}

	ret = request_threaded_irq(ddata->irq, hi6421_spmi_irq_handler, NULL,
				   IRQF_TRIGGER_LOW | IRQF_SHARED | IRQF_NO_SUSPEND,
				   "pmic", ddata);
	if (ret < 0) {
		dev_err(dev, "Failed to start IRQ handling thread: error %d\n",
			ret);
		return ret;
	}

	dev_set_drvdata(&pdev->dev, ddata);

	ret = devm_mfd_add_devices(&pdev->dev, PLATFORM_DEVID_NONE,
				   hi6421v600_devs, ARRAY_SIZE(hi6421v600_devs),
				   NULL, 0, NULL);
	if (ret < 0)
		dev_err(dev, "Failed to add child devices: %d\n", ret);
=======
	struct hi6421_spmi_pmic *pmic;
	unsigned int virq;
	int ret, i;

	pmic = devm_kzalloc(dev, sizeof(*pmic), GFP_KERNEL);
	if (!pmic)
		return -ENOMEM;

	spin_lock_init(&pmic->lock);

	pmic->dev = dev;

	pmic->gpio = of_get_gpio(np, 0);
	if (pmic->gpio < 0)
		return pmic->gpio;

	if (!gpio_is_valid(pmic->gpio))
		return -EINVAL;

	ret = devm_gpio_request_one(dev, pmic->gpio, GPIOF_IN, "pmic");
	if (ret < 0) {
		dev_err(dev, "failed to request gpio%d\n", pmic->gpio);
		return ret;
	}

	pmic->irq = gpio_to_irq(pmic->gpio);

	hi6421_spmi_pmic_irq_prc(pmic);

	pmic->irqs = devm_kzalloc(dev, HISI_IRQ_NUM * sizeof(int), GFP_KERNEL);
	if (!pmic->irqs) {
		ret = -ENOMEM;
		goto irq_malloc;
	}

	pmic->domain = irq_domain_add_simple(np, HISI_IRQ_NUM, 0,
					     &hi6421_spmi_domain_ops, pmic);
	if (!pmic->domain) {
		dev_err(dev, "failed irq domain add simple!\n");
		ret = -ENODEV;
		goto irq_malloc;
	}

	for (i = 0; i < HISI_IRQ_NUM; i++) {
		virq = irq_create_mapping(pmic->domain, i);
		if (!virq) {
			dev_err(dev, "Failed mapping hwirq\n");
			ret = -ENOSPC;
			goto irq_malloc;
		}
		pmic->irqs[i] = virq;
		dev_dbg(dev, "%s: pmic->irqs[%d] = %d\n",
			__func__, i, pmic->irqs[i]);
	}

	ret = request_threaded_irq(pmic->irq, hi6421_spmi_irq_handler, NULL,
				   IRQF_TRIGGER_LOW | IRQF_SHARED | IRQF_NO_SUSPEND,
				   "pmic", pmic);
	if (ret < 0) {
		dev_err(dev, "could not claim pmic IRQ: error %d\n", ret);
		goto irq_malloc;
	}

	dev_set_drvdata(&pdev->dev, pmic);

	/*
	 * The logic below will rely that the pmic is already stored at
	 * drvdata.
	 */
	dev_dbg(&pdev->dev, "SPMI-PMIC: adding children for %pOF\n",
		pdev->dev.of_node);
	ret = devm_mfd_add_devices(&pdev->dev, PLATFORM_DEVID_NONE,
				   hi6421v600_devs, ARRAY_SIZE(hi6421v600_devs),
				   NULL, 0, NULL);
	if (!ret)
		return 0;

	dev_err(dev, "Failed to add child devices: %d\n", ret);

irq_malloc:
	free_irq(pmic->irq, pmic);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return ret;
}

static void hi6421_spmi_pmic_remove(struct spmi_device *pdev)
{
<<<<<<< HEAD
	struct hi6421_spmi_pmic *ddata = dev_get_drvdata(&pdev->dev);

	free_irq(ddata->irq, ddata);
=======
	struct hi6421_spmi_pmic *pmic = dev_get_drvdata(&pdev->dev);

	free_irq(pmic->irq, pmic);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static const struct of_device_id pmic_spmi_id_table[] = {
	{ .compatible = "hisilicon,hi6421-spmi" },
	{ }
};
MODULE_DEVICE_TABLE(of, pmic_spmi_id_table);

static struct spmi_driver hi6421_spmi_pmic_driver = {
	.driver = {
		.name	= "hi6421-spmi-pmic",
		.of_match_table = pmic_spmi_id_table,
	},
	.probe	= hi6421_spmi_pmic_probe,
	.remove	= hi6421_spmi_pmic_remove,
};
module_spmi_driver(hi6421_spmi_pmic_driver);

MODULE_DESCRIPTION("HiSilicon Hi6421v600 SPMI PMIC driver");
MODULE_LICENSE("GPL v2");
