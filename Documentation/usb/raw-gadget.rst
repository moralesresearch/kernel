==============
USB Raw Gadget
==============

<<<<<<< HEAD
USB Raw Gadget is a gadget driver that gives userspace low-level control over
the gadget's communication process.

Like any other gadget driver, Raw Gadget implements USB devices via the
USB gadget API. Unlike most gadget drivers, Raw Gadget does not implement
any concrete USB functions itself but requires userspace to do that.

Raw Gadget is currently a strictly debugging feature and should not be used
in production. Use GadgetFS instead.

Enabled with CONFIG_USB_RAW_GADGET.
=======
USB Raw Gadget is a kernel module that provides a userspace interface for
the USB Gadget subsystem. Essentially it allows to emulate USB devices
from userspace. Enabled with CONFIG_USB_RAW_GADGET. Raw Gadget is
currently a strictly debugging feature and shouldn't be used in
production, use GadgetFS instead.
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

Comparison to GadgetFS
~~~~~~~~~~~~~~~~~~~~~~

<<<<<<< HEAD
Raw Gadget is similar to GadgetFS but provides more direct access to the
USB gadget layer for userspace. The key differences are:

1. Raw Gadget passes every USB request to userspace to get a response, while
   GadgetFS responds to some USB requests internally based on the provided
   descriptors. Note that the UDC driver might respond to some requests on
   its own and never forward them to the gadget layer.

2. Raw Gadget allows providing arbitrary data as responses to USB requests,
   while GadgetFS performs sanity checks on the provided USB descriptors.
   This makes Raw Gadget suitable for fuzzing by providing malformed data as
   responses to USB requests.

3. Raw Gadget provides a way to select a UDC device/driver to bind to,
   while GadgetFS currently binds to the first available UDC. This allows
   having multiple Raw Gadget instances bound to different UDCs.

4. Raw Gadget explicitly exposes information about endpoints addresses and
   capabilities. This allows the user to write UDC-agnostic gadgets.

5. Raw Gadget has an ioctl-based interface instead of a filesystem-based
   one.
=======
Raw Gadget is similar to GadgetFS, but provides a more low-level and
direct access to the USB Gadget layer for the userspace. The key
differences are:

1. Every USB request is passed to the userspace to get a response, while
   GadgetFS responds to some USB requests internally based on the provided
   descriptors. However note, that the UDC driver might respond to some
   requests on its own and never forward them to the Gadget layer.

2. GadgetFS performs some sanity checks on the provided USB descriptors,
   while Raw Gadget allows you to provide arbitrary data as responses to
   USB requests.

3. Raw Gadget provides a way to select a UDC device/driver to bind to,
   while GadgetFS currently binds to the first available UDC.

4. Raw Gadget explicitly exposes information about endpoints addresses and
   capabilities allowing a user to write UDC-agnostic gadgets.

5. Raw Gadget has ioctl-based interface instead of a filesystem-based one.
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

Userspace interface
~~~~~~~~~~~~~~~~~~~

<<<<<<< HEAD
The user can interact with Raw Gadget by opening ``/dev/raw-gadget`` and
issuing ioctl calls; see the comments in include/uapi/linux/usb/raw_gadget.h
for details. Multiple Raw Gadget instances (bound to different UDCs) can be
used at the same time.

A typical usage scenario of Raw Gadget:

1. Create a Raw Gadget instance by opening ``/dev/raw-gadget``.
2. Initialize the instance via ``USB_RAW_IOCTL_INIT``.
3. Launch the instance with ``USB_RAW_IOCTL_RUN``.
4. In a loop issue ``USB_RAW_IOCTL_EVENT_FETCH`` to receive events from
   Raw Gadget and react to those depending on what kind of USB gadget must
   be implemented.

Note that some UDC drivers have fixed addresses assigned to endpoints, and
therefore arbitrary endpoint addresses cannot be used in the descriptors.
Nevertheless, Raw Gadget provides a UDC-agnostic way to write USB gadgets.
Once ``USB_RAW_EVENT_CONNECT`` is received via ``USB_RAW_IOCTL_EVENT_FETCH``,
``USB_RAW_IOCTL_EPS_INFO`` can be used to find out information about the
endpoints that the UDC driver has. Based on that, userspace must choose UDC
endpoints for the gadget and assign addresses in the endpoint descriptors
correspondingly.

Raw Gadget usage examples and a test suite:
=======
To create a Raw Gadget instance open /dev/raw-gadget. Multiple raw-gadget
instances (bound to different UDCs) can be used at the same time. The
interaction with the opened file happens through the ioctl() calls, see
comments in include/uapi/linux/usb/raw_gadget.h for details.

The typical usage of Raw Gadget looks like:

1. Open Raw Gadget instance via /dev/raw-gadget.
2. Initialize the instance via USB_RAW_IOCTL_INIT.
3. Launch the instance with USB_RAW_IOCTL_RUN.
4. In a loop issue USB_RAW_IOCTL_EVENT_FETCH calls to receive events from
   Raw Gadget and react to those depending on what kind of USB device
   needs to be emulated.

Note, that some UDC drivers have fixed addresses assigned to endpoints, and
therefore arbitrary endpoint addresses can't be used in the descriptors.
Nevertheles, Raw Gadget provides a UDC-agnostic way to write USB gadgets.
Once a USB_RAW_EVENT_CONNECT event is received via USB_RAW_IOCTL_EVENT_FETCH,
the USB_RAW_IOCTL_EPS_INFO ioctl can be used to find out information about
endpoints that the UDC driver has. Based on that information, the user must
chose UDC endpoints that will be used for the gadget being emulated, and
properly assign addresses in endpoint descriptors.

You can find usage examples (along with a test suite) here:
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

https://github.com/xairy/raw-gadget

Internal details
~~~~~~~~~~~~~~~~

<<<<<<< HEAD
Every Raw Gadget endpoint read/write ioctl submits a USB request and waits
until its completion. This is done deliberately to assist with coverage-guided
fuzzing by having a single syscall fully process a single USB request. This
feature must be kept in the implementation.
=======
Currently every endpoint read/write ioctl submits a USB request and waits until
its completion. This is the desired mode for coverage-guided fuzzing (as we'd
like all USB request processing happen during the lifetime of a syscall),
and must be kept in the implementation. (This might be slow for real world
applications, thus the O_NONBLOCK improvement suggestion below.)
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

Potential future improvements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

<<<<<<< HEAD
- Report more events (suspend, resume, etc.) through
  ``USB_RAW_IOCTL_EVENT_FETCH``.

- Support ``O_NONBLOCK`` I/O. This would be another mode of operation, where
  Raw Gadget would not wait until the completion of each USB request.

- Support USB 3 features (accept SS endpoint companion descriptor when
  enabling endpoints; allow providing ``stream_id`` for bulk transfers).

- Support ISO transfer features (expose ``frame_number`` for completed
  requests).
=======
- Report more events (suspend, resume, etc.) through USB_RAW_IOCTL_EVENT_FETCH.

- Support O_NONBLOCK I/O.

- Support USB 3 features (accept SS endpoint companion descriptor when
  enabling endpoints; allow providing stream_id for bulk transfers).

- Support ISO transfer features (expose frame_number for completed requests).
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
