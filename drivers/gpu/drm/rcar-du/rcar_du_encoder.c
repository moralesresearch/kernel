// SPDX-License-Identifier: GPL-2.0+
/*
 * rcar_du_encoder.c  --  R-Car Display Unit Encoder
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinchart (laurent.pinchart@ideasonboard.com)
 */

#include <linux/export.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#include <linux/slab.h>

#include <drm/drm_bridge.h>
#include <drm/drm_crtc.h>
#include <drm/drm_managed.h>
#include <drm/drm_modeset_helper_vtables.h>
#include <drm/drm_panel.h>
<<<<<<< HEAD
=======
=======

#include <drm/drm_bridge.h>
#include <drm/drm_crtc.h>
#include <drm/drm_modeset_helper_vtables.h>
#include <drm/drm_panel.h>
#include <drm/drm_simple_kms_helper.h>
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#include "rcar_du_drv.h"
#include "rcar_du_encoder.h"
#include "rcar_du_kms.h"
#include "rcar_lvds.h"

/* -----------------------------------------------------------------------------
 * Encoder
 */

static unsigned int rcar_du_encoder_count_ports(struct device_node *node)
{
	struct device_node *ports;
	struct device_node *port;
	unsigned int num_ports = 0;

	ports = of_get_child_by_name(node, "ports");
	if (!ports)
		ports = of_node_get(node);

	for_each_child_of_node(ports, port) {
		if (of_node_name_eq(port, "port"))
			num_ports++;
	}

	of_node_put(ports);

	return num_ports;
}

<<<<<<< HEAD
static const struct drm_encoder_funcs rcar_du_encoder_funcs = {
};

=======
<<<<<<< HEAD
static const struct drm_encoder_funcs rcar_du_encoder_funcs = {
};

=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
int rcar_du_encoder_init(struct rcar_du_device *rcdu,
			 enum rcar_du_output output,
			 struct device_node *enc_node)
{
	struct rcar_du_encoder *renc;
<<<<<<< HEAD
	struct drm_bridge *bridge;
=======
<<<<<<< HEAD
	struct drm_bridge *bridge;
=======
	struct drm_encoder *encoder;
	struct drm_bridge *bridge;
	int ret;

	renc = devm_kzalloc(rcdu->dev, sizeof(*renc), GFP_KERNEL);
	if (renc == NULL)
		return -ENOMEM;

	renc->output = output;
	encoder = rcar_encoder_to_drm_encoder(renc);

	dev_dbg(rcdu->dev, "initializing encoder %pOF for output %u\n",
		enc_node, output);
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	/*
	 * Locate the DRM bridge from the DT node. For the DPAD outputs, if the
	 * DT node has a single port, assume that it describes a panel and
	 * create a panel bridge.
	 */
	if ((output == RCAR_DU_OUTPUT_DPAD0 ||
	     output == RCAR_DU_OUTPUT_DPAD1) &&
	    rcar_du_encoder_count_ports(enc_node) == 1) {
		struct drm_panel *panel = of_drm_find_panel(enc_node);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		if (IS_ERR(panel))
			return PTR_ERR(panel);

		bridge = devm_drm_panel_bridge_add_typed(rcdu->dev, panel,
							 DRM_MODE_CONNECTOR_DPI);
		if (IS_ERR(bridge))
			return PTR_ERR(bridge);
	} else {
		bridge = of_drm_find_bridge(enc_node);
		if (!bridge)
			return -EPROBE_DEFER;
<<<<<<< HEAD
=======
=======
		if (IS_ERR(panel)) {
			ret = PTR_ERR(panel);
			goto done;
		}

		bridge = devm_drm_panel_bridge_add_typed(rcdu->dev, panel,
							 DRM_MODE_CONNECTOR_DPI);
		if (IS_ERR(bridge)) {
			ret = PTR_ERR(bridge);
			goto done;
		}
	} else {
		bridge = of_drm_find_bridge(enc_node);
		if (!bridge) {
			ret = -EPROBE_DEFER;
			goto done;
		}
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

		if (output == RCAR_DU_OUTPUT_LVDS0 ||
		    output == RCAR_DU_OUTPUT_LVDS1)
			rcdu->lvds[output - RCAR_DU_OUTPUT_LVDS0] = bridge;
	}

	/*
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	 * Create and initialize the encoder. On Gen3 skip the LVDS1 output if
	 * the LVDS1 encoder is used as a companion for LVDS0 in dual-link
	 * mode.
	 */
	if (rcdu->info->gen >= 3 && output == RCAR_DU_OUTPUT_LVDS1) {
		if (rcar_lvds_dual_link(bridge))
			return -ENOLINK;
	}

	dev_dbg(rcdu->dev, "initializing encoder %pOF for output %u\n",
		enc_node, output);

	renc = drmm_encoder_alloc(&rcdu->ddev, struct rcar_du_encoder, base,
				  &rcar_du_encoder_funcs, DRM_MODE_ENCODER_NONE,
				  NULL);
	if (!renc)
		return -ENOMEM;

	renc->output = output;
<<<<<<< HEAD
=======
=======
	 * On Gen3 skip the LVDS1 output if the LVDS1 encoder is used as a
	 * companion for LVDS0 in dual-link mode.
	 */
	if (rcdu->info->gen >= 3 && output == RCAR_DU_OUTPUT_LVDS1) {
		if (rcar_lvds_dual_link(bridge)) {
			ret = -ENOLINK;
			goto done;
		}
	}

	ret = drm_simple_encoder_init(rcdu->ddev, encoder,
				      DRM_MODE_ENCODER_NONE);
	if (ret < 0)
		goto done;
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	/*
	 * Attach the bridge to the encoder. The bridge will create the
	 * connector.
	 */
<<<<<<< HEAD
	return drm_bridge_attach(&renc->base, bridge, NULL, 0);
=======
<<<<<<< HEAD
	return drm_bridge_attach(&renc->base, bridge, NULL, 0);
=======
	ret = drm_bridge_attach(encoder, bridge, NULL, 0);
	if (ret) {
		drm_encoder_cleanup(encoder);
		return ret;
	}

done:
	if (ret < 0) {
		if (encoder->name)
			encoder->funcs->destroy(encoder);
		devm_kfree(rcdu->dev, renc);
	}

	return ret;
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
}
