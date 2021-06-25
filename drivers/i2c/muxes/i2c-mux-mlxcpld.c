<<<<<<< HEAD
// SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0
/*
 * Mellanox i2c mux driver
 *
 * Copyright (C) 2016-2020 Mellanox Technologies
=======
/*
 * drivers/i2c/muxes/i2c-mux-mlxcpld.c
 * Copyright (c) 2016 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2016 Michael Shych <michaels@mellanox.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
 */

#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/i2c-mux.h>
#include <linux/io.h>
#include <linux/init.h>
#include <linux/module.h>
<<<<<<< HEAD
#include <linux/platform_data/mlxcpld.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

/* mlxcpld_mux - mux control structure:
 * @last_val - last selected register value or -1 if mux deselected
 * @client - I2C device client
 * @pdata: platform data
 */
struct mlxcpld_mux {
	int last_val;
	struct i2c_client *client;
	struct mlxcpld_mux_plat_data pdata;
=======
#include <linux/platform_data/x86/mlxcpld.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

#define CPLD_MUX_MAX_NCHANS	8

/* mlxcpld_mux - mux control structure:
 * @last_chan - last register value
 * @client - I2C device client
 */
struct mlxcpld_mux {
	u8 last_chan;
	struct i2c_client *client;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
};

/* MUX logic description.
 * Driver can support different mux control logic, according to CPLD
 * implementation.
 *
 * Connectivity schema.
 *
 * i2c-mlxcpld                                 Digital               Analog
 * driver
 * *--------*                                 * -> mux1 (virt bus2) -> mux -> |
 * | I2CLPC | i2c physical                    * -> mux2 (virt bus3) -> mux -> |
 * | bridge | bus 1                 *---------*                               |
 * | logic  |---------------------> * mux reg *                               |
 * | in CPLD|                       *---------*                               |
 * *--------*   i2c-mux-mlxpcld          ^    * -> muxn (virt busn) -> mux -> |
 *     |        driver                   |                                    |
 *     |        *---------------*        |                              Devices
 *     |        * CPLD (i2c bus)* select |
 *     |        * registers for *--------*
 *     |        * mux selection * deselect
 *     |        *---------------*
 *     |                 |
 * <-------->     <----------->
 * i2c cntrl      Board cntrl reg
 * reg space      space (mux select,
 *                IO, LED, WD, info)
 *
 */

<<<<<<< HEAD
=======
static const struct i2c_device_id mlxcpld_mux_id[] = {
	{ "mlxcpld_mux_module", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, mlxcpld_mux_id);

>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
/* Write to mux register. Don't use i2c_transfer() and i2c_smbus_xfer()
 * for this as they will try to lock adapter a second time.
 */
static int mlxcpld_mux_reg_write(struct i2c_adapter *adap,
<<<<<<< HEAD
				 struct mlxcpld_mux *mux, u32 val)
{
	struct i2c_client *client = mux->client;
	union i2c_smbus_data data;
	struct i2c_msg msg;
	u8 buf[3];

	switch (mux->pdata.reg_size) {
	case 1:
		data.byte = val;
		return __i2c_smbus_xfer(adap, client->addr, client->flags,
					I2C_SMBUS_WRITE, mux->pdata.sel_reg_addr,
					I2C_SMBUS_BYTE_DATA, &data);
	case 2:
		buf[0] = mux->pdata.sel_reg_addr >> 8;
		buf[1] = mux->pdata.sel_reg_addr;
		buf[2] = val;
		msg.addr = client->addr;
		msg.buf = buf;
		msg.len = mux->pdata.reg_size + 1;
		msg.flags = 0;
		return __i2c_transfer(adap, &msg, 1);
	default:
		return -EINVAL;
	}
=======
				 struct i2c_client *client, u8 val)
{
	struct mlxcpld_mux_plat_data *pdata = dev_get_platdata(&client->dev);
	union i2c_smbus_data data = { .byte = val };

	return __i2c_smbus_xfer(adap, client->addr, client->flags,
				I2C_SMBUS_WRITE, pdata->sel_reg_addr,
				I2C_SMBUS_BYTE_DATA, &data);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}

static int mlxcpld_mux_select_chan(struct i2c_mux_core *muxc, u32 chan)
{
<<<<<<< HEAD
	struct mlxcpld_mux *mux = i2c_mux_priv(muxc);
	u32 regval = chan;
	int err = 0;

	if (mux->pdata.reg_size == 1)
		regval += 1;

	/* Only select the channel if its different from the last channel */
	if (mux->last_val != regval) {
		err = mlxcpld_mux_reg_write(muxc->parent, mux, regval);
		mux->last_val = err < 0 ? -1 : regval;
=======
	struct mlxcpld_mux *data = i2c_mux_priv(muxc);
	struct i2c_client *client = data->client;
	u8 regval = chan + 1;
	int err = 0;

	/* Only select the channel if its different from the last channel */
	if (data->last_chan != regval) {
		err = mlxcpld_mux_reg_write(muxc->parent, client, regval);
		data->last_chan = err < 0 ? 0 : regval;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	}

	return err;
}

static int mlxcpld_mux_deselect(struct i2c_mux_core *muxc, u32 chan)
{
<<<<<<< HEAD
	struct mlxcpld_mux *mux = i2c_mux_priv(muxc);

	/* Deselect active channel */
	mux->last_val = -1;

	return mlxcpld_mux_reg_write(muxc->parent, mux, 0);
}

/* Probe/reomove functions */
static int mlxcpld_mux_probe(struct platform_device *pdev)
{
	struct mlxcpld_mux_plat_data *pdata = dev_get_platdata(&pdev->dev);
	struct i2c_client *client = to_i2c_client(pdev->dev.parent);
	struct i2c_mux_core *muxc;
	struct mlxcpld_mux *data;
	int num, err;
	u32 func;
=======
	struct mlxcpld_mux *data = i2c_mux_priv(muxc);
	struct i2c_client *client = data->client;

	/* Deselect active channel */
	data->last_chan = 0;

	return mlxcpld_mux_reg_write(muxc->parent, client, data->last_chan);
}

/* Probe/reomove functions */
static int mlxcpld_mux_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct i2c_adapter *adap = client->adapter;
	struct mlxcpld_mux_plat_data *pdata = dev_get_platdata(&client->dev);
	struct i2c_mux_core *muxc;
	int num, force;
	struct mlxcpld_mux *data;
	int err;
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	if (!pdata)
		return -EINVAL;

<<<<<<< HEAD
	switch (pdata->reg_size) {
	case 1:
		func = I2C_FUNC_SMBUS_WRITE_BYTE_DATA;
		break;
	case 2:
		func = I2C_FUNC_I2C;
		break;
	default:
		return -EINVAL;
	}

	if (!i2c_check_functionality(client->adapter, func))
		return -ENODEV;

	muxc = i2c_mux_alloc(client->adapter, &pdev->dev, pdata->num_adaps,
=======
	if (!i2c_check_functionality(adap, I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		return -ENODEV;

	muxc = i2c_mux_alloc(adap, &client->dev, CPLD_MUX_MAX_NCHANS,
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			     sizeof(*data), 0, mlxcpld_mux_select_chan,
			     mlxcpld_mux_deselect);
	if (!muxc)
		return -ENOMEM;

<<<<<<< HEAD
	platform_set_drvdata(pdev, muxc);
	data = i2c_mux_priv(muxc);
	data->client = client;
	memcpy(&data->pdata, pdata, sizeof(*pdata));
	data->last_val = -1; /* force the first selection */

	/* Create an adapter for each channel. */
	for (num = 0; num < pdata->num_adaps; num++) {
		err = i2c_mux_add_adapter(muxc, 0, pdata->chan_ids[num], 0);
=======
	data = i2c_mux_priv(muxc);
	i2c_set_clientdata(client, muxc);
	data->client = client;
	data->last_chan = 0; /* force the first selection */

	/* Create an adapter for each channel. */
	for (num = 0; num < CPLD_MUX_MAX_NCHANS; num++) {
		if (num >= pdata->num_adaps)
			/* discard unconfigured channels */
			break;

		force = pdata->adap_ids[num];

		err = i2c_mux_add_adapter(muxc, force, num, 0);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		if (err)
			goto virt_reg_failed;
	}

<<<<<<< HEAD
	/* Notify caller when all channels' adapters are created. */
	if (pdata->completion_notify)
		pdata->completion_notify(pdata->handle, muxc->parent, muxc->adapter);

=======
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	return 0;

virt_reg_failed:
	i2c_mux_del_adapters(muxc);
	return err;
}

<<<<<<< HEAD
static int mlxcpld_mux_remove(struct platform_device *pdev)
{
	struct i2c_mux_core *muxc = platform_get_drvdata(pdev);
=======
static int mlxcpld_mux_remove(struct i2c_client *client)
{
	struct i2c_mux_core *muxc = i2c_get_clientdata(client);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	i2c_mux_del_adapters(muxc);
	return 0;
}

<<<<<<< HEAD
static struct platform_driver mlxcpld_mux_driver = {
	.driver = {
		.name = "i2c-mux-mlxcpld",
	},
	.probe = mlxcpld_mux_probe,
	.remove = mlxcpld_mux_remove,
};

module_platform_driver(mlxcpld_mux_driver);
=======
static struct i2c_driver mlxcpld_mux_driver = {
	.driver		= {
		.name	= "mlxcpld-mux",
	},
	.probe		= mlxcpld_mux_probe,
	.remove		= mlxcpld_mux_remove,
	.id_table	= mlxcpld_mux_id,
};

module_i2c_driver(mlxcpld_mux_driver);
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

MODULE_AUTHOR("Michael Shych (michaels@mellanox.com)");
MODULE_DESCRIPTION("Mellanox I2C-CPLD-MUX driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("platform:i2c-mux-mlxcpld");
