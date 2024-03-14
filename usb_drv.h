#define DEV_DRIVER_NAME    "FST USB DRV"
#define DEV_DID                   (u16)0x0046
#define DEV_VID                   (u16)0x1679

static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id) __init;
static void usb_remove(struct usb_interface *interface) __exit;
