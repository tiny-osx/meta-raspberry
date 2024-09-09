#@TYPE: Machine
#@NAME: Generic Raspberry Pi
#@DESCRIPTION: Machine configuration for generic Raspberry Pi

SOC_FAMILY = "rpi"
include conf/machine/include/soc-family.inc

PREFERRED_VERSION_linux-rpi ??= "6.6.%"
PREFERRED_PROVIDER_virtual/kernel ??= "linux-rpi"
PREFERRED_PROVIDER_virtual/firmware ??= "firmware-rpi"

KERNEL_IMAGETYPE = "Image"
EXTRA_IMAGEDEPENDS += "firmware-rpi"

WKS_FILE ?= "raspberrypi.wks"
IMAGE_FSTYPES  ?= "tar.gz wic.gz wic.bmap"

MACHINE_FEATURES = " \
    wifi \
    usbhost \
    usbgadget \
    bluetooth \
"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " \
    kernel-modules \
    udev-rules-rpi \
"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS +=" \
    kernel-module-i2c-dev \
    kernel-module-i2c-bcm2708 \
"

KERNEL_DEVICETREE_OVERLAYS ?= " \
    overlays/overlay_map.dtb \
    overlays/disable-bt.dtbo \
    overlays/disable-wifi.dtbo \
    overlays/dwc2.dtbo \
    overlays/gpio-ir.dtbo \
    overlays/gpio-ir-tx.dtbo \
    overlays/gpio-key.dtbo \
    overlays/gpio-poweroff.dtbo \
    overlays/gpio-shutdown.dtbo \
    overlays/i2c-gpio.dtbo \
    overlays/i2c-rtc.dtbo \
    overlays/imx219.dtbo \
    overlays/imx477.dtbo \
    overlays/imx708.dtbo \
    overlays/miniuart-bt.dtbo \
    overlays/pps-gpio.dtbo \
    overlays/rpi-ft5406.dtbo \
    overlays/rpi-poe.dtbo \
    overlays/vc4-kms-v3d.dtbo \
    overlays/vc4-kms-v3d-pi4.dtbo \
    overlays/vc4-kms-dsi-7inch.dtbo \
    overlays/vc4-kms-dsi-waveshare-panel.dtbo \
"

KERNEL_DEVICETREE ?= " \
    ${KERNEL_DEVICETREE_OVERLAYS} \
"

KERNEL_MODULE_AUTOLOAD += " \
    i2c-dev \
    i2c-bcm2708 \
    libcomposite \
"

WKS_FILE_DEPENDS ?= " \
    virtual/bootloader \
    e2fsprogs-native \
    bmaptool-native \
    rpiboot-native \
"

USE_VT="0"

def make_dtb_boot_files(d):

    alldtbs = d.getVar('KERNEL_DEVICETREE')

    if not alldtbs:
        return ''

    def transform(dtb):
        base = os.path.basename(dtb)
        if dtb.endswith('dtbo') or base == 'overlay_map.dtb':
            return '{};{}'.format(base, dtb)
        elif dtb.endswith('dtb'):
            return base

    return ' '.join([transform(dtb) for dtb in alldtbs.split(' ') if dtb])

IMAGE_BOOT_FILES ?= " \
    boot/* \
    ${@make_dtb_boot_files(d)} \
    ${KERNEL_IMAGETYPE};${KERNEL_IMAGE} \
"

do_image_wic[depends] += " \
    virtual/kernel:do_deploy \
    virtual/bootloader:do_deploy \
"

do_image_wic[recrdeps] = "do_build"

# RDEPENDS:${KERNEL_PACKAGE_NAME}-base = ""

# KERNEL_PACKAGE_NAME = "kernel-v8"

# MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " \
#     kernel-modules \
#     kernel-module-u-ether \
#     kernel-module-u-serial \
#     kernel-module-usb-f-rndis \
#     kernel-module-usb-f-ecm \
#     kernel-module-usb-f-acm \
#     udev-rules-rpi \
# "

# SERIAL_CONSOLES = "115200;ttyGS0 115200;ttyS0 115200;ttyS1 115200;ttyAMA0 115200;ttyAMA10"
# SERIAL_CONSOLES_CHECK = "${SERIAL_CONSOLES}"

# SERIAL_CONSOLES = "115200;ttyGS0"
# SERIAL_CONSOLE:append:raspberrypi0-2w = "115200;ttyS0"
# SERIAL_CONSOLE:append:raspberrypi3 = "115200;ttyS0"
# SERIAL_CONSOLE:append:raspberrypi4 = "115200;ttyS0"
# SERIAL_CONSOLE:append:raspberrypi5 = "115200;ttyAMA10"

# KERNEL_CONSOLE:intel-corei7-64 = "ttyUSB0"

# SERIAL_CONSOLES = "115200;ttyGS0 115200;ttyS0 115200;ttyS1 115200;ttyAMA0 115200;ttyAMA10"
# SERIAL_CONSOLES_CHECK = "${SERIAL_CONSOLES}"
# SERIAL_CONSOLES =+ "115200;ttyGS0"

# WKS_FILE_DEPENDS ?= " \
#     virtual/bootloader \
#     usbboot-native \
#     e2fsprogs-native \
#     bmap-tools-native \
# "

# MACHINE_FEATURES = " \
#     touchscreen \
#     usbgadget \
#     keyboard \
#     bluetooth \
#     screen \
#     wifi \  
#     sdio \
#     vfat \
#     ext2 \
#     alsa \
# "
