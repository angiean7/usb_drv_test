#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/usb.h>
#include "usb_drv.h"


static struct usb_device_id usb_ids[] = {
{ USB_DEVICE(DEV_VID, DEV_DID) },
{ 0 }
};

static int __init usb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    int errno = -ENOMEM;
     
    struct usb_device *pDev = interface_to_usbdev(interface);
    if(!pDev) {
        printk(KERN_ERR DEV_DRIVER_NAME ": USB driver registration failed\n");
    }

    return errno;
}

static void __exit usb_remove(struct usb_interface *interface) 
{
    return;
}
static struct usb_driver dev_ops = {
    .name = DEV_DRIVER_NAME,
    .id_table = usb_ids,
    .probe = usb_probe,
    .disconnect  = usb_remove,
};

static int anqi_init(void)
{
    int rc = 0;
    printk(KERN_INFO"Hello World enter 20240314\n");

    rc = usb_register_driver(&dev_ops, THIS_MODULE, DEV_DRIVER_NAME);
    if (rc) {
        printk(KERN_ERR DEV_DRIVER_NAME ": USB driver registration failed\n");
        goto exit;
    }

exit:
    return rc;
}

static void anqi_exit(void)
{
    printk(KERN_INFO"Hello World exit 20240314\n ");
    usb_deregister(&dev_ops);
}

module_init(anqi_init);
module_exit(anqi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("an.qi");
MODULE_DESCRIPTION("test_module");
MODULE_VERSION("V1.0");

