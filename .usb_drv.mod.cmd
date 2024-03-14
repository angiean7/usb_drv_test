cmd_/home/inuineko/anqi/usb_drv_test/usb_drv.mod := printf '%s\n'   usb_drv.o | awk '!x[$$0]++ { print("/home/inuineko/anqi/usb_drv_test/"$$0) }' > /home/inuineko/anqi/usb_drv_test/usb_drv.mod
