DESCRIPTION = "Closed source binary files to help boot all raspberry pi devices."
LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://LICENCE.broadcom;md5=c403841ff2837657b2ed8e5bb474ac8d"

inherit deploy nopackages

# FIRMWARE_BRANCH = "stable" 
PROVIDES += "virtual/bootloader"

COMPATIBLE_MACHINE = "^rpi$"
INHIBIT_DEFAULT_DEPS = "1"

# BB_STRICT_CHECKSUM = "0"
# WARN_QA:remove = "src-uri-bad buildpaths"

SRCREV = "3590de0c181d433af368a95f15bc480bdaff8b47"
SRC_URI[sha256sum] = "a116479e4e8e3bae354860d00321e5df5010cdbe10a3db9e59c81858a0aec84d"
SRC_URI = "https://codeload.github.com/raspberrypi/firmware/tar.gz/${SRCREV};downloadfilename=${BPN}-${PV}.tar.gz"
# SRC_URI  = "file://firmware-${FIRMWARE_BRANCH}.tar.gz"
# SRC_URI  = "https://github.com/raspberrypi/firmware/archive/refs/heads/${FIRMWARE_BRANCH}.tar.gz"
SRC_URI += "file://cmdline.txt"
SRC_URI += "file://config.txt"

S = "${WORKDIR}/firmware-${SRCREV}/boot"
# S = "${WORKDIR}/firmware-${FIRMWARE_BRANCH}/boot"

do_deploy() {
    install -d ${DEPLOYDIR}/boot
    install -m 0644 ${S}/LICENCE.broadcom ${DEPLOYDIR}/boot
    install -m 0644 ${WORKDIR}/config.txt ${WORKDIR}/cmdline.txt ${DEPLOYDIR}/boot   
}

do_deploy:append() {
    if grep -q -E '^.{80}.$' ${DEPLOYDIR}/boot/config.txt; then
        bbwarn "config.txt contains lines longer than 80 characters, this is not supported"
    fi
}

do_deploy:append:raspberrypi0-2w() {
    install -m 0644 ${S}/bootcode.bin ${DEPLOYDIR}/boot
    install -m 0644 ${S}/start.elf ${S}/fixup.dat ${DEPLOYDIR}/boot
    install -m 0644 ${S}/start_x.elf ${S}/fixup_x.dat ${DEPLOYDIR}/boot
    install -m 0644 ${S}/start_cd.elf ${S}/fixup_cd.dat ${DEPLOYDIR}/boot
    install -m 0644 ${S}/start_db.elf ${S}/fixup_db.dat ${DEPLOYDIR}/boot
}

do_deploy:append:raspberrypi3() {
    install -m 0644 ${S}/bootcode.bin ${DEPLOYDIR}/boot
    install -m 0644 ${S}/start.elf ${S}/fixup.dat ${DEPLOYDIR}/boot
    install -m 0644 ${S}/start_x.elf ${S}/fixup_x.dat ${DEPLOYDIR}/boot
    install -m 0644 ${S}/start_cd.elf ${S}/fixup_cd.dat ${DEPLOYDIR}/boot
    install -m 0644 ${S}/start_db.elf ${S}/fixup_db.dat ${DEPLOYDIR}/boot
}

do_deploy:append:raspberrypi4() {
    install -m 0644 ${S}/start4.elf ${S}/fixup4.dat ${DEPLOYDIR}/boot
    install -m 0644 ${S}/start4x.elf ${S}/fixup4x.dat ${DEPLOYDIR}/boot
    install -m 0644 ${S}/start4cd.elf ${S}/fixup4cd.dat ${DEPLOYDIR}/boot
    install -m 0644 ${S}/start4db.elf ${S}/fixup4db.dat ${DEPLOYDIR}/boot
}

addtask deploy before do_build after do_install
do_deploy[dirs] += "${DEPLOYDIR}/boot"

PACKAGE_ARCH = "${MACHINE_ARCH}"