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
    int errno = -ENOMEM;Q
     
    LedCtrl *pDev = kmalloc(sizeof(LedCtrl), GFP_KERNEL);
    if(!pDev) {
        DMESG_ERR("Out of memory.\n");
        goto L_Error;
    }
    memset(pDev, 0, sizeof(*pDev)) ;
    kref_init(&pDev->kref); // 参照カウンタを初期化
    pDev->pDev = usb_get_dev(interface_to_usbdev(ip)); // USBデバイスがあるか
    pDev->ip = ip;

    UsbHostInterface *pHostIf = ip->cur_altsetting;
    // 0番目のエンドポイントを得る．このチューナはBulk-Inのep0が1つしかない（当然，control endpointもlsusbで表示されないが存在はしている）
    UsbEndpointDescriptor *ep = &pHostIf->endpoint[0].desc;
    pDev->bulkInEndpointAddr = ep->bEndpointAddress; // エンドポイントのアドレス

    usb_set_intfdata(ip, pDev);

        errno = usb_register_dev(ip, &class); // USBデバイスを登録
    if(errno) {
        DMESG_ERR("Not able to get minor for this device.\n");
        usb_set_intfdata(ip, NULL);
        goto L_Error;
    }
    dev_info(&ip->dev, "[+] LedCtrl: Attached=%d", ip->minor);
        return 0;
        
    L_Error: // エラー
    if(pDev) kref_put(&pDev->kref, Delete);
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
}

module_init(anqi_init);
module_exit(anqi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("an.qi");
MODULE_DESCRIPTION("test_module");
MODULE_VERSION("V1.0");

