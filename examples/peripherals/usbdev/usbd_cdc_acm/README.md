# usbd_cdc_acm

## Overview

This example shows how to set up the chip to work as a USB serial device.

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
dynamic memory init success, ocram heap size = 426 Kbyte 
sig1:ffffffff
sig2:0000f32f
cgen1:9ffffffd
[I/USB] Open ep:0x83 type:3 mps:64
[I/USB] Open ep:0x02 type:2 mps:512
[I/USB] Open ep:0x81 type:2 mps:512
[I/USB] USB DEVICE CONFIGURED DONE!
```

Connect to the serial port (e.g. on Linux, it should be /dev/ttyACM0) by any terminal application (e.g. picocom /dev/ttyACM0). Now you can send data strings to the device, the device will echo back the same data string.

Using ./tests/speed_test.py can test the speed of the TX-RX loopback, but it is not very accurate. The results may vary on different computers and systems. The ideal value is around 18MB/s.

```
$ python3 tests/speed_test_.py /dev/ttyACM0

Total data size: 32768000 bytes
Elapsed time: 1.92 seconds
Transfer speed: 17100478.08 bytes/second
```
