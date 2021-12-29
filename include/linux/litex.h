/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Common LiteX header providing
 * helper functions for accessing CSRs.
 *
<<<<<<< HEAD
=======
 * Implementation of the functions is provided by
 * the LiteX SoC Controller driver.
 *
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
 * Copyright (C) 2019-2020 Antmicro <www.antmicro.com>
 */

#ifndef _LINUX_LITEX_H
#define _LINUX_LITEX_H

#include <linux/io.h>
<<<<<<< HEAD

/* LiteX SoCs support 8- or 32-bit CSR Bus data width (i.e., subreg. size) */
#if defined(CONFIG_LITEX_SUBREG_SIZE) && \
	(CONFIG_LITEX_SUBREG_SIZE == 1 || CONFIG_LITEX_SUBREG_SIZE == 4)
#define LITEX_SUBREG_SIZE      CONFIG_LITEX_SUBREG_SIZE
#else
#error LiteX subregister size (LITEX_SUBREG_SIZE) must be 4 or 1!
#endif
#define LITEX_SUBREG_SIZE_BIT	 (LITEX_SUBREG_SIZE * 8)

/* LiteX subregisters of any width are always aligned on a 4-byte boundary */
#define LITEX_SUBREG_ALIGN	  0x4

static inline void _write_litex_subregister(u32 val, void __iomem *addr)
{
	writel((u32 __force)cpu_to_le32(val), addr);
}

static inline u32 _read_litex_subregister(void __iomem *addr)
{
	return le32_to_cpu((__le32 __force)readl(addr));
}

/*
 * LiteX SoC Generator, depending on the configuration, can split a single
 * logical CSR (Control&Status Register) into a series of consecutive physical
 * registers.
 *
 * For example, in the configuration with 8-bit CSR Bus, a 32-bit aligned,
 * 32-bit wide logical CSR will be laid out as four 32-bit physical
 * subregisters, each one containing one byte of meaningful data.
 *
 * For details see: https://github.com/enjoy-digital/litex/wiki/CSR-Bus
 */

/* number of LiteX subregisters needed to store a register of given reg_size */
#define _litex_num_subregs(reg_size) \
	(((reg_size) - 1) / LITEX_SUBREG_SIZE + 1)

/*
 * since the number of 4-byte aligned subregisters required to store a single
 * LiteX CSR (MMIO) register varies with LITEX_SUBREG_SIZE, the offset of the
 * next adjacent LiteX CSR register w.r.t. the offset of the current one also
 * depends on how many subregisters the latter is spread across
 */
#define _next_reg_off(off, size) \
	((off) + _litex_num_subregs(size) * LITEX_SUBREG_ALIGN)

/*
 * The purpose of `_litex_[set|get]_reg()` is to implement the logic of
 * writing to/reading from the LiteX CSR in a single place that can be then
 * reused by all LiteX drivers via the `litex_[write|read][8|16|32|64]()`
 * accessors for the appropriate data width.
 * NOTE: direct use of `_litex_[set|get]_reg()` by LiteX drivers is strongly
 * discouraged, as they perform no error checking on the requested data width!
 */

/**
 * _litex_set_reg() - Writes a value to the LiteX CSR (Control&Status Register)
 * @reg: Address of the CSR
 * @reg_size: The width of the CSR expressed in the number of bytes
 * @val: Value to be written to the CSR
 *
 * This function splits a single (possibly multi-byte) LiteX CSR write into
 * a series of subregister writes with a proper offset.
 * NOTE: caller is responsible for ensuring (0 < reg_size <= sizeof(u64)).
 */
static inline void _litex_set_reg(void __iomem *reg, size_t reg_size, u64 val)
{
	u8 shift = _litex_num_subregs(reg_size) * LITEX_SUBREG_SIZE_BIT;

	while (shift > 0) {
		shift -= LITEX_SUBREG_SIZE_BIT;
		_write_litex_subregister(val >> shift, reg);
		reg += LITEX_SUBREG_ALIGN;
	}
}

/**
 * _litex_get_reg() - Reads a value of the LiteX CSR (Control&Status Register)
 * @reg: Address of the CSR
 * @reg_size: The width of the CSR expressed in the number of bytes
 *
 * Return: Value read from the CSR
 *
 * This function generates a series of subregister reads with a proper offset
 * and joins their results into a single (possibly multi-byte) LiteX CSR value.
 * NOTE: caller is responsible for ensuring (0 < reg_size <= sizeof(u64)).
 */
static inline u64 _litex_get_reg(void __iomem *reg, size_t reg_size)
{
	u64 r;
	u8 i;

	r = _read_litex_subregister(reg);
	for (i = 1; i < _litex_num_subregs(reg_size); i++) {
		r <<= LITEX_SUBREG_SIZE_BIT;
		reg += LITEX_SUBREG_ALIGN;
		r |= _read_litex_subregister(reg);
	}
	return r;
}

static inline void litex_write8(void __iomem *reg, u8 val)
{
	_litex_set_reg(reg, sizeof(u8), val);
=======
#include <linux/types.h>
#include <linux/compiler_types.h>

/*
 * The parameters below are true for LiteX SoCs configured for 8-bit CSR Bus,
 * 32-bit aligned.
 *
 * Supporting other configurations will require extending the logic in this
 * header and in the LiteX SoC controller driver.
 */
#define LITEX_REG_SIZE	  0x4
#define LITEX_SUBREG_SIZE	0x1
#define LITEX_SUBREG_SIZE_BIT	 (LITEX_SUBREG_SIZE * 8)

#define WRITE_LITEX_SUBREGISTER(val, base_offset, subreg_id) \
	writel((u32 __force)cpu_to_le32(val), base_offset + (LITEX_REG_SIZE * subreg_id))

#define READ_LITEX_SUBREGISTER(base_offset, subreg_id) \
	le32_to_cpu((__le32 __force)readl(base_offset + (LITEX_REG_SIZE * subreg_id)))

void litex_set_reg(void __iomem *reg, unsigned long reg_sz, unsigned long val);

unsigned long litex_get_reg(void __iomem *reg, unsigned long reg_sz);

static inline void litex_write8(void __iomem *reg, u8 val)
{
	WRITE_LITEX_SUBREGISTER(val, reg, 0);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static inline void litex_write16(void __iomem *reg, u16 val)
{
<<<<<<< HEAD
	_litex_set_reg(reg, sizeof(u16), val);
=======
	WRITE_LITEX_SUBREGISTER(val >> 8, reg, 0);
	WRITE_LITEX_SUBREGISTER(val, reg, 1);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static inline void litex_write32(void __iomem *reg, u32 val)
{
<<<<<<< HEAD
	_litex_set_reg(reg, sizeof(u32), val);
=======
	WRITE_LITEX_SUBREGISTER(val >> 24, reg, 0);
	WRITE_LITEX_SUBREGISTER(val >> 16, reg, 1);
	WRITE_LITEX_SUBREGISTER(val >> 8, reg, 2);
	WRITE_LITEX_SUBREGISTER(val, reg, 3);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static inline void litex_write64(void __iomem *reg, u64 val)
{
<<<<<<< HEAD
	_litex_set_reg(reg, sizeof(u64), val);
=======
	WRITE_LITEX_SUBREGISTER(val >> 56, reg, 0);
	WRITE_LITEX_SUBREGISTER(val >> 48, reg, 1);
	WRITE_LITEX_SUBREGISTER(val >> 40, reg, 2);
	WRITE_LITEX_SUBREGISTER(val >> 32, reg, 3);
	WRITE_LITEX_SUBREGISTER(val >> 24, reg, 4);
	WRITE_LITEX_SUBREGISTER(val >> 16, reg, 5);
	WRITE_LITEX_SUBREGISTER(val >> 8, reg, 6);
	WRITE_LITEX_SUBREGISTER(val, reg, 7);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static inline u8 litex_read8(void __iomem *reg)
{
<<<<<<< HEAD
	return _litex_get_reg(reg, sizeof(u8));
=======
	return READ_LITEX_SUBREGISTER(reg, 0);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static inline u16 litex_read16(void __iomem *reg)
{
<<<<<<< HEAD
	return _litex_get_reg(reg, sizeof(u16));
=======
	return (READ_LITEX_SUBREGISTER(reg, 0) << 8)
		| (READ_LITEX_SUBREGISTER(reg, 1));
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static inline u32 litex_read32(void __iomem *reg)
{
<<<<<<< HEAD
	return _litex_get_reg(reg, sizeof(u32));
=======
	return (READ_LITEX_SUBREGISTER(reg, 0) << 24)
		| (READ_LITEX_SUBREGISTER(reg, 1) << 16)
		| (READ_LITEX_SUBREGISTER(reg, 2) << 8)
		| (READ_LITEX_SUBREGISTER(reg, 3));
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static inline u64 litex_read64(void __iomem *reg)
{
<<<<<<< HEAD
	return _litex_get_reg(reg, sizeof(u64));
=======
	return ((u64)READ_LITEX_SUBREGISTER(reg, 0) << 56)
		| ((u64)READ_LITEX_SUBREGISTER(reg, 1) << 48)
		| ((u64)READ_LITEX_SUBREGISTER(reg, 2) << 40)
		| ((u64)READ_LITEX_SUBREGISTER(reg, 3) << 32)
		| ((u64)READ_LITEX_SUBREGISTER(reg, 4) << 24)
		| ((u64)READ_LITEX_SUBREGISTER(reg, 5) << 16)
		| ((u64)READ_LITEX_SUBREGISTER(reg, 6) << 8)
		| ((u64)READ_LITEX_SUBREGISTER(reg, 7));
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

#endif /* _LINUX_LITEX_H */
