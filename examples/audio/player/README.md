# Full-featured Player [中文](README_zh.md)

**Note**: As of the last update of this document, the coexistence of WiFi and Bluetooth on qcc743 has not been ported yet. Therefore, playing Bluetooth music while playing WiFi music may lead to unknown exceptions, and vice versa. Please stay tuned for future updates.

## Supported CHIPs

|      CHIP        | Remark |
|:----------------:|:------:|
|qcc743/qcc744       |        |

## Compilation

- For qcc743/qcc744

```
make
```

## Flashing
make flash CHIP=qcc743 COMX=/dev/ttyACM0

## Running

### 1. Play Local File System Audio

```
qxx74x />smta play file:///romfs/music.mp3
```

### 2. Play Online Music

##### 2.1 Connect to WiFi

```
qxx74x />wifi_sta_connect <ssid> <password>
```

##### 2.2 Play HTTP Music

The URL link should be accessible and supports HTTPS.

```
qxx74x />smta play http://iot-du-home-test.bj.bcebos.com/test/bp_32k_mono_32kbps_03m53s.mp3
```

##### 2.3 Stop Player

```
qxx74x />smta stop
```

### 3. Play Bluetooth Music

##### 3.1 Enable Bluetooth Broadcast

```
qxx74x />smta a2dp 1
```

##### 3.2 Connect and Play Music from a Mobile Device
Open Bluetooth on your mobile device, search for and connect to a device named something like qcc74xMSP[XX:XX:XX], and you can play music via Bluetooth.

##### 3.3 Turn Off Bluetooth Broadcast

```
qxx74x />smta a2dp 0
```

### 4. Network Recording

tydb network recording is a tool for transferring audio data over a local network based on WebSocket. The development board sends locally recorded data over the network to a PC in the local network, where you can view the audio data. The tydb tool is located in the examples/audio/player/tools/tydb directory. Ensure that your board is connected to the network and in the same local network as your PC, with mutual pingability.
##### 4.1 Server Side

```
tydb.exe record web 0.0.0.0:8090 ./
```

##### 4.2 Device Side

To initiate audio recording transmission from the device side, `<dest_ip>` represents the IP address of the target PC:

* Single-channel audio recording (Supported on qcc743/4 platforms):

```bash
qxx74x />record start ws://<dest_ip>:8090 16k_16bit_1ch.pcm 1
```

* To stop the recording:

```bash
qxx74x />record stop
```

