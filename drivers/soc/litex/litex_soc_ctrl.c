// SPDX-License-Identifier: GPL-2.0
/*
 * LiteX SoC Controller Driver
 *
 * Copyright (C) 2020 Antmicro <www.antmicro.com>
 *
 */

#include <linux/litex.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/printk.h>
#include <linux/module.h>
<<<<<<< HEAD
#include <linux/io.h>
#include <linux/reboot.h>

/* reset register located at the base address */
#define RESET_REG_OFF           0x00
#define RESET_REG_VALUE         0x00000001
=======
#include <linux/errno.h>
#include <linux/io.h>

/*
 * LiteX SoC Generator, depending on the configuration, can split a single
 * logical CSR (Control&Status Register) into a series of consecutive physical
 * registers.
 *
 * For example, in the configuration with 8-bit CSR Bus, 32-bit aligned (the
 * default one for 32-bit CPUs) a 32-bit logical CSR will be generated as four
 * 32-bit physical registers, each one containing one byte of meaningful data.
 *
 * For details see: https://github.com/enjoy-digital/litex/wiki/CSR-Bus
 *
 * The purpose of `litex_set_reg`/`litex_get_reg` is to implement the logic
 * of writing to/reading from the LiteX CSR in a single place that can be
 * then reused by all LiteX drivers.
 */

/**
 * litex_set_reg() - Writes the value to the LiteX CSR (Control&Status Register)
 * @reg: Address of the CSR
 * @reg_size: The width of the CSR expressed in the number of bytes
 * @val: Value to be written to the CSR
 *
 * In the currently supported LiteX configuration (8-bit CSR Bus, 32-bit aligned),
 * a 32-bit LiteX CSR is generated as 4 consecutive 32-bit physical registers,
 * each one containing one byte of meaningful data.
 *
 * This function splits a single possibly multi-byte write into a series of
 * single-byte writes with a proper offset.
 */
void litex_set_reg(void __iomem *reg, unsigned long reg_size,
		    unsigned long val)
{
	unsigned long shifted_data, shift, i;

	for (i = 0; i < reg_size; ++i) {
		shift = ((reg_size - i - 1) * LITEX_SUBREG_SIZE_BIT);
		shifted_data = val >> shift;

		WRITE_LITEX_SUBREGISTER(shifted_data, reg, i);
	}
}
EXPORT_SYMBOL_GPL(litex_set_reg);

/**
 * litex_get_reg() - Reads the value of the LiteX CSR (Control&Status Register)
 * @reg: Address of the CSR
 * @reg_size: The width of the CSR expressed in the number of bytes
 *
 * Return: Value read from the CSR
 *
 * In the currently supported LiteX configuration (8-bit CSR Bus, 32-bit aligned),
 * a 32-bit LiteX CSR is generated as 4 consecutive 32-bit physical registers,
 * each one containing one byte of meaningful data.
 *
 * This function generates a series of single-byte reads with a proper offset
 * and joins their results into a single multi-byte value.
 */
unsigned long litex_get_reg(void __iomem *reg, unsigned long reg_size)
{
	unsigned long shifted_data, shift, i;
	unsigned long result = 0;

	for (i = 0; i < reg_size; ++i) {
		shifted_data = READ_LITEX_SUBREGISTER(reg, i);

		shift = ((reg_size - i - 1) * LITEX_SUBREG_SIZE_BIT);
		result |= (shifted_data << shift);
	}

	return result;
}
EXPORT_SYMBOL_GPL(litex_get_reg);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#define SCRATCH_REG_OFF         0x04
#define SCRATCH_REG_VALUE       0x12345678
#define SCRATCH_TEST_VALUE      0xdeadbeef

/*
 * Check LiteX CSR read/write access
 *
 * This function reads and writes a scratch register in order to verify if CSR
 * access works.
 *
 * In case any problems are detected, the driver should panic.
 *
 * Access to the LiteX CSR is, by design, done in CPU native endianness.
 * The driver should not dynamically configure access functions when
 * the endianness mismatch is detected. Such situation indicates problems in
 * the soft SoC design and should be solved at the LiteX generator level,
 * not in the software.
 */
static int litex_check_csr_access(void __iomem *reg_addr)
{
	unsigned long reg;

	reg = litex_read32(reg_addr + SCRATCH_REG_OFF);

	if (reg != SCRATCH_REG_VALUE) {
		panic("Scratch register read error - the system is probably broken! Expected: 0x%x but got: 0x%lx",
			SCRATCH_REG_VALUE, reg);
		return -EINVAL;
	}

	litex_write32(reg_addr + SCRATCH_REG_OFF, SCRATCH_TEST_VALUE);
	reg = litex_read32(reg_addr + SCRATCH_REG_OFF);

	if (reg != SCRATCH_TEST_VALUE) {
		panic("Scratch register write error - the system is probably broken! Expected: 0x%x but got: 0x%lx",
			SCRATCH_TEST_VALUE, reg);
		return -EINVAL;
	}

	/* restore original value of the SCRATCH register */
	litex_write32(reg_addr + SCRATCH_REG_OFF, SCRATCH_REG_VALUE);

<<<<<<< HEAD
	pr_info("LiteX SoC Controller driver initialized: subreg:%d, align:%d",
		LITEX_SUBREG_SIZE, LITEX_SUBREG_ALIGN);
=======
	pr_info("LiteX SoC Controller driver initialized");
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	return 0;
}

struct litex_soc_ctrl_device {
	void __iomem *base;
<<<<<<< HEAD
	struct notifier_block reset_nb;
};

static int litex_reset_handler(struct notifier_block *this, unsigned long mode,
			       void *cmd)
{
	struct litex_soc_ctrl_device *soc_ctrl_dev =
		container_of(this, struct litex_soc_ctrl_device, reset_nb);

	litex_write32(soc_ctrl_dev->base + RESET_REG_OFF, RESET_REG_VALUE);
	return NOTIFY_DONE;
}

=======
};

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#ifdef CONFIG_OF
static const struct of_device_id litex_soc_ctrl_of_match[] = {
	{.compatible = "litex,soc-controller"},
	{},
};
MODULE_DEVICE_TABLE(of, litex_soc_ctrl_of_match);
#endif /* CONFIG_OF */

static int litex_soc_ctrl_probe(struct platform_device *pdev)
{
	struct litex_soc_ctrl_device *soc_ctrl_dev;
<<<<<<< HEAD
	int error;
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	soc_ctrl_dev = devm_kzalloc(&pdev->dev, sizeof(*soc_ctrl_dev), GFP_KERNEL);
	if (!soc_ctrl_dev)
		return -ENOMEM;

	soc_ctrl_dev->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(soc_ctrl_dev->base))
		return PTR_ERR(soc_ctrl_dev->base);

<<<<<<< HEAD
	error = litex_check_csr_access(soc_ctrl_dev->base);
	if (error)
		return error;

	platform_set_drvdata(pdev, soc_ctrl_dev);

	soc_ctrl_dev->reset_nb.notifier_call = litex_reset_handler;
	soc_ctrl_dev->reset_nb.priority = 128;
	error = register_restart_handler(&soc_ctrl_dev->reset_nb);
	if (error) {
		dev_warn(&pdev->dev, "cannot register restart handler: %d\n",
			 error);
	}

	return 0;
}

static int litex_soc_ctrl_remove(struct platform_device *pdev)
{
	struct litex_soc_ctrl_device *soc_ctrl_dev = platform_get_drvdata(pdev);

	unregister_restart_handler(&soc_ctrl_dev->reset_nb);
	return 0;
=======
	return litex_check_csr_access(soc_ctrl_dev->base);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static struct platform_driver litex_soc_ctrl_driver = {
	.driver = {
		.name = "litex-soc-controller",
		.of_match_table = of_match_ptr(litex_soc_ctrl_of_match)
	},
	.probe = litex_soc_ctrl_probe,
<<<<<<< HEAD
	.remove = litex_soc_ctrl_remove,
=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

module_platform_driver(litex_soc_ctrl_driver);
MODULE_DESCRIPTION("LiteX SoC Controller driver");
MODULE_AUTHOR("Antmicro <www.antmicro.com>");
MODULE_LICENSE("GPL v2");
