SUMMARY = "Generic firware USB loading tool for RaspberryPi"
SECTION = "console/utils"
HOMEPAGE = "https://github.com/raspberrypi/usbboot"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=e3fc50a88d0a364313df4b21ef20c29e"

SRCREV = "cd6896cbafabad02fef44c815579a91dccd8e04e"
SRC_URI = "gitsm://github.com/raspberrypi/usbboot.git;protocol=https;branch=master"

inherit native

S = "${WORKDIR}/git"

DEPENDS += "libusb1-native"

do_install[network] = "1"

do_install(){
  install -d ${D}${bindir}
  install -m 755 ${S}/rpiboot ${D}${bindir}
  install -m 644 ${S}/msd/bootcode.bin ${D}${bindir}
  install -m 644 ${S}/msd/bootcode4.bin ${D}${bindir}
  install -m 644 ${S}/msd/start.elf ${D}${bindir}
  install -m 644 ${S}/msd/start4.elf ${D}${bindir}
}