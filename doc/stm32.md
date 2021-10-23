
# STM32 Board setup

## Prerequisite list

You will need the following components:

 - An `arm-none-eabi` compatible cross compiler.
 - OPTIONAL for flashing: The ST-Link Tools.
 - OPTIONAL for debug probes: J-Link Tooling.

Each STM32 file should then have a make file that enables building. 
See specific firmware documentation.

## Distro-specific setup

### Ubuntu

```
sudo apt install gcc-arm-none-eabi
sudo apt install stlink-tools
```

[J-Link DEB][jlink]

### Fedora

```
sudo dnf install arm-none-eabi-gcc-cs
sudo dnf install stlink
```

[J-Link RPMs][jlink]


   [jlink]: https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack
