# usbd_hid_keyboard

## Overview

Human interface devices (HID) are one of the most common USB devices, it is implemented in various devices such as keyboards, mice, game controllers, sensors and alphanumeric display devices. In this example, we implement USB keyboard.Upon connection to USB host (PC), the example application will sent 'key a/A pressed & released' events

As a USB stack, use the cherryUSB component.

## Support CHIP

|      CHIP        | Remark |
|:----------------:|:------:|
|qcc748            |        |

## Hardware Required
qcc748 chip development board with USB interface.

Note: In case your board doesn't have micro-USB connector connected to USB peripheral, you may have to DIY a cable and connect D+ and D- to the pins

## Compile

- qcc748

```
make CHIP=qcc743 BOARD=qcc743dk
```

## Flash

```
make flash CHIP=chip_name COMX=xxx # xxx is your com name
```

## Example Output
After flashing and booting, connect to the computer, and you should see this output:

```
===========================
dynamic memory init success, ocram heap size = 434 Kbyte 
sig1:ffffffff
sig2:0000f32f
cgen1:9ffffffd
[I/USB] Open ep:0x81 type:3 mps:8
[I/USB] USB DEVICE CONFIGURED DONE!
[I/USB] read hid report descriptor
```
After that, you will receive the character 'a' from the keyboard in a continuous loop on your computer.