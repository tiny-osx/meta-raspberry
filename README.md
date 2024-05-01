# Yocto/OE meta layer for TinyOS

This layer provides BSP support for the [Raspberry Pi](https://www.raspberrypi.com/) containing custom recipes, classes, configuration, etc. Layer relies on OpenEmbedded/Yocto build system and depends on:

```
[OECORE]
URI: git://git.yoctoproject.org/poky
layers: meta
branch: same dedicated branch as meta-raspberry

[OECORE]
URI: git://git.openembedded.org/meta-openembedded
layers: meta
branch: same dedicated branch as meta-raspberry
```

## Licenses

An image is made of many components and it’s hard to describe the full details of all the licenses that are in use. When building the system from sources with OpenEmbedded, you are responsible for understanding the licenses used by each package.