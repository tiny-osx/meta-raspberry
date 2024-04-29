DESCRIPTION = "Linux Kernel for Raspberry Pi"
SECTION = "kernel"
LICENSE = "GPL-2.0-only"

inherit kernel siteinfo
require recipes-kernel/linux/linux-yocto.inc

COMPATIBLE_MACHINE = "^rpi$"
LINUX_VERSION_EXTENSION = ""

EXTRA_IMAGEDEPENDS += "firmware-rpi"

PE = "1"
PV = "${LINUX_VERSION}+git${SRCPV}"

KCONFIG_MODE="--alldefconfig"
KBUILD_DEFCONFIG:raspberrypi5 ?= "bcm2712_defconfig"
KBUILD_DEFCONFIG:raspberrypi4 ?= "bcm2711_defconfig"
KBUILD_DEFCONFIG:raspberrypi0-2w ?= "bcmrpi3_defconfig"

KERNEL_VERSION_SANITY_SKIP="1"
KERNEL_DTC_FLAGS += "-@ -H epapr"

SRC_URI  = "git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=${LINUX_KMETA_BRANCH};destsuffix=kernel-meta"
SRC_URI += "git://github.com/raspberrypi/linux.git;name=machine;branch=${LINUX_BRANCH};protocol=https"
SRC_URI += "file://vc4graphics-enable.cfg"
SRC_URI += "file://powersave-enable.cfg"
SRC_URI += "file://usbether-enable.cfg"
# SRC_URI += "file://legacy-ptys-enable.cfg"

SRC_URI:append:raspberrypi4 = " \
    file://rpi4-nvmem-enable.cfg \
"















 
# addtask deploy before do_package after do_install
# do_deploy[dirs] += "${KERNEL_IMAGEDEST}/firmware"

# FILES:${KERNEL_PACKAGE_NAME}-image = "/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}.gz"
# ARCH = "sh"
# KERNEL_OUTPUT = "arch/${ARCH}/boot/${KERNEL_IMAGETYPE}"

# DEPLOYDEP = ""
# do_deploy[depends] += "${DEPLOYDEP}"