DESCRIPTION = "Closed source binary files to help boot all raspberry pi devices."
LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://LICENCE.broadcom;md5=c403841ff2837657b2ed8e5bb474ac8d"

inherit deploy nopackages

FIRMWARE_BRANCH = "stable" 
PROVIDES += "virtual/bootloader"

COMPATIBLE_MACHINE = "^rpi$"
INHIBIT_DEFAULT_DEPS = "1"

BB_STRICT_CHECKSUM = "0"
WARN_QA:remove = "src-uri-bad buildpaths"

# SRC_URI  = "file://firmware-${FIRMWARE_BRANCH}.tar.gz"
SRC_URI  = "https://github.com/raspberrypi/firmware/archive/refs/heads/${FIRMWARE_BRANCH}.tar.gz"
SRC_URI += "file://cmdline.txt"
SRC_URI += "file://config.txt"

S = "${WORKDIR}/firmware-${FIRMWARE_BRANCH}/boot"

do_deploy() {
    install -d ${DEPLOYDIR}/boot
    install -m 0644 ${S}/bootcode.bin ${S}/start4.elf ${S}/fixup4.dat ${DEPLOYDIR}/boot
    install -m 0644 ${S}/LICENCE.broadcom ${DEPLOYDIR}/boot
    install -m 0644 ${WORKDIR}/config.txt ${WORKDIR}/cmdline.txt ${DEPLOYDIR}/boot   
}

do_deploy:append() {
    if grep -q -E '^.{80}.$' ${DEPLOYDIR}/boot/config.txt; then
        bbwarn "config.txt contains lines longer than 80 characters, this is not supported"
    fi
}

addtask deploy before do_build after do_install
do_deploy[dirs] += "${DEPLOYDIR}/boot"

PACKAGE_ARCH = "${MACHINE_ARCH}"