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
KBUILD_DEFCONFIG:raspberrypi3-aplus ?= "bcm2711_defconfig"
KBUILD_DEFCONFIG:raspberrypi0-2w ?= "bcm2711_defconfig"

KERNEL_VERSION_SANITY_SKIP="1"
KERNEL_DTC_FLAGS += "-@ -H epapr"

RASPBERRYPI_KERNEL_PACKAGE_NAME = "kernel-v7"
RDEPENDS:${KERNEL_PACKAGE_NAME}:raspberrypi-armv7:append = " ${RASPBERRYPI_KERNEL_PACKAGE_NAME}"
RDEPENDS:${KERNEL_PACKAGE_NAME}-base:raspberrypi-armv7:append = " ${RASPBERRYPI_KERNEL_PACKAGE_NAME}-base"
RDEPENDS:${KERNEL_PACKAGE_NAME}-image:raspberrypi-armv7:append = " ${RASPBERRYPI_KERNEL_PACKAGE_NAME}-image"
RDEPENDS:${KERNEL_PACKAGE_NAME}-dev:raspberrypi-armv7:append = " ${RASPBERRYPI_KERNEL_PACKAGE_NAME}-dev"
RDEPENDS:${KERNEL_PACKAGE_NAME}-vmlinux:raspberrypi-armv7:append = " ${RASPBERRYPI_KERNEL_PACKAGE_NAME}-vmlinux"
RDEPENDS:${KERNEL_PACKAGE_NAME}-modules:raspberrypi-armv7:append = " ${RASPBERRYPI_KERNEL_PACKAGE_NAME}-modules"
RDEPENDS:${KERNEL_PACKAGE_NAME}-dbg:raspberrypi-armv7:append = " ${RASPBERRYPI_KERNEL_PACKAGE_NAME}-dbg"

SRC_URI  = "git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=${LINUX_KMETA_BRANCH};destsuffix=kernel-meta"
SRC_URI += "git://github.com/raspberrypi/linux.git;name=machine;branch=${LINUX_BRANCH};protocol=https"
SRC_URI += "file://vc4graphics-enable.cfg"
SRC_URI += "file://powersave-enable.cfg"

SRC_URI:append:raspberrypi4 = " \
    file://rpi4-nvmem-enable.cfg \
"