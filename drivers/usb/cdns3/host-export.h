/* SPDX-License-Identifier: GPL-2.0 */
/*
<<<<<<< HEAD
 * Cadence USBSS and USBSSP DRD Driver - Host Export APIs
=======
 * Cadence USBSS DRD Driver - Host Export APIs
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
 *
 * Copyright (C) 2017-2018 NXP
 *
 * Authors: Peter Chen <peter.chen@nxp.com>
 */
#ifndef __LINUX_CDNS3_HOST_EXPORT
#define __LINUX_CDNS3_HOST_EXPORT

<<<<<<< HEAD
#if IS_ENABLED(CONFIG_USB_CDNS_HOST)

int cdns_host_init(struct cdns *cdns);

#else

static inline int cdns_host_init(struct cdns *cdns)
=======
struct usb_hcd;
#ifdef CONFIG_USB_CDNS3_HOST

int cdns3_host_init(struct cdns3 *cdns);
int xhci_cdns3_suspend_quirk(struct usb_hcd *hcd);

#else

static inline int cdns3_host_init(struct cdns3 *cdns)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
{
	return -ENXIO;
}

<<<<<<< HEAD
static inline void cdns_host_exit(struct cdns *cdns) { }

#endif /* USB_CDNS_HOST */
=======
static inline void cdns3_host_exit(struct cdns3 *cdns) { }
static inline int xhci_cdns3_suspend_quirk(struct usb_hcd *hcd)
{
	return 0;
}

#endif /* CONFIG_USB_CDNS3_HOST */
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

#endif /* __LINUX_CDNS3_HOST_EXPORT */
