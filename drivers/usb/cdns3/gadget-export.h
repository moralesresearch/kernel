/* SPDX-License-Identifier: GPL-2.0 */
/*
<<<<<<< HEAD
 * Cadence USBSS and USBSSP DRD Driver - Gadget Export APIs.
=======
 * Cadence USBSS DRD Driver - Gadget Export APIs.
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
 *
 * Copyright (C) 2017 NXP
 * Copyright (C) 2017-2018 NXP
 *
 * Authors: Peter Chen <peter.chen@nxp.com>
 */
#ifndef __LINUX_CDNS3_GADGET_EXPORT
#define __LINUX_CDNS3_GADGET_EXPORT

<<<<<<< HEAD
#if IS_ENABLED(CONFIG_USB_CDNSP_GADGET)

int cdnsp_gadget_init(struct cdns *cdns);
#else

static inline int cdnsp_gadget_init(struct cdns *cdns)
=======
#ifdef CONFIG_USB_CDNS3_GADGET

int cdns3_gadget_init(struct cdns3 *cdns);
#else

static inline int cdns3_gadget_init(struct cdns3 *cdns)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	return -ENXIO;
}

<<<<<<< HEAD
#endif /* CONFIG_USB_CDNSP_GADGET */

#if IS_ENABLED(CONFIG_USB_CDNS3_GADGET)

int cdns3_gadget_init(struct cdns *cdns);
#else

static inline int cdns3_gadget_init(struct cdns *cdns)
{
	return -ENXIO;
}

#endif /* CONFIG_USB_CDNS3_GADGET */
=======
#endif
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#endif /* __LINUX_CDNS3_GADGET_EXPORT */
