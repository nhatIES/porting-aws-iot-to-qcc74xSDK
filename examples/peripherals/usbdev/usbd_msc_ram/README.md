# usbd_cdc_acm

## Overview

Mass Storage Devices are one of the most common USB devices.  It use Mass Storage Class (MSC) that allow access to their internal data storage.  This example contains code to make ESP based device recognizable by USB-hosts as a USB Mass Storage Device.  It either allows the embedded application i.e. example to access the partition or Host PC accesses the partition over USB MSC.  They can't be allowed to access the partition at the same time.

This example program uses RAM as the storage medium to demonstrate the usage of USB-MSC. Power-off or reset will result in data loss.

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
After the flashing you should see this output:

```
===========================
dynamic memory init success, ocram heap size = 305 Kbyte 
sig1:ffffffff
sig2:0000f32f
cgen1:9ffffffd
[I/USB] Open ep:0x02 type:2 mps:512
[I/USB] Open ep:0x81 type:2 mps:512
[I/USB] USB DEVICE CONFIGURED DONE!
```

Then you can find this storage device on your computer and use it, but please note that data will be lost after power off or reset.