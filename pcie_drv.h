#define DEV_DRIVER_NAME    "FST PCIE"
#define DEV_DID                   (u16)0x0046
#define DEV_VID                   (u16)0x1679

static int dev_probe(struct pci_dev *dev, const struct pci_device_id *id) __init;
static void dev_remove(struct pci_dev *dev) __exit;
