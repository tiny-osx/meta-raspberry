SUMMARY = "Generic firware USB loading tool for RaspberryPi"
SECTION = "console/utils"
HOMEPAGE = "https://github.com/raspberrypi/usbboot"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=e3fc50a88d0a364313df4b21ef20c29e"

# SRCREV = "dce11e8d491051430d4ece572fea03448586a708"
SRCREV = "cd6896cbafabad02fef44c815579a91dccd8e04e"
SRC_URI = "gitsm://github.com/raspberrypi/usbboot.git;protocol=https;branch=master"

inherit pkgconfig deploy native

S = "${WORKDIR}/git"

DEPENDS:append = " libusb1-native"

do_install[network] = "1"
do_install(){
  install -m 755 ${S}/rpiboot ${D}
  install -m 644 ${S}/msd/bootcode.bin ${D}
  install -m 644 ${S}/msd/bootcode4.bin ${D}
  install -m 644 ${S}/msd/start.elf ${D}
  install -m 644 ${S}/msd/start4.elf ${D}
}

do_deploy(){
    install -d ${DEPLOYDIR}/usbboot/
    cp -r ${D}/* ${DEPLOYDIR}/usbboot/
}
addtask do_deploy before do_package after do_install