# lwip_iperf

## Overview

This test case uses iperf to measure Ethernet speed.

## Support CHIP

|      CHIP        | Remark |
|:----------------:|:------:|
| qcc744           |        |

## How to use example

### Hardware Required

- Boards
    - qcc744dk

- Device
    - A standard E-PHY module with an RMII interface that complies with the IEEE 802.3/802.3u specifications, e.g: IP101G,LAN8720.
    - A router and a computer connected to that router.

- Extra Software on PC
    - iperf2

### Hardware Connection

#### QCC744

The RMII pin configuration is fixed and as follows:

| GPIO   | RMII Signal | Description        |
| ------ | ----------- | ------------------ |
| GPIO25 | REF_CLK_IN  | 50 MHz reference clock input |
| GPIO26 | TX_0        | EMAC_TXD0          |
| GPIO27 | TX_1        | EMAC_TXD1          |
| GPIO28 | RX_0        | EMAC_RXD0          |
| GPIO29 | RX_1        | EMAC_RXD1          |
| GPIO31 | TX_EN       | EMAC_TX_EN         |
| GPIO32 | RX_DV       | EMAC_RX_DV         |
| GPIO33 | MDIO_CLK    | MDIO clock line    |
| GPIO34 | MDIO_IO     | MDIO data line     |

**Note:**
Since the default configuration sets REF_CLK to input mode, the E-PHY module must output a 50 MHz REF_CLK signal.

## Compile

- qcc744

```
make CHIP=qcc743 BOARD=qcc744dk
```

## Flash

```
make flash CHIP=chip_name COMX=xxx # xxx is your com name
```

## Example Output

After the flashing you should see this output:

```
===========================
dynamic memory init success, ocram heap size = 343 Kbyte 
sig1:ffffffff
sig2:0000f32f
cgen1:9ffffffd
EMAC lwip iperf test case !
[I][MAIN] Create app_start task.
[I][MAIN] Start Scheduler.
[I][MAIN] app_start_task Run...
qcc74x />[I][MAIN] Shell Ready...
[I][MAIN] lwip statck init
[I][MAIN] netif config
[I][EPHY] eth phy scan success, phy_addr: 1, phy_id: 0x02430C54
[W][EPHY] drv_match falied, use General driver
[I][LWIP_EMAC] [OS] Starting emac rx task...
[I][MAIN] app_start_task Delete...
[I][MAIN] lwip_status_update_task Run...

```

Then, connect the E-PHY module to the router using an Ethernet cable. You will see the following output:

```
[W][LWIP_EMAC] Lwip Eth Emac LinkUp !!!
[I][LWIP_EMAC] eth_phy speed: 100M_FULL_DUPLEX
[I][LWIP_EMAC] State: Looking for DHCP server ...
 IP:10.28.30.178
 MASK: 255.255.255.0
 Gateway: 10.28.30.1
[I][LWIP_EMAC] IP address assigned by a DHCP server: 10.28.30.178
```

Please make a note of the IP address from the output, as it will be used later.

You can use the command **lwip_emac_info** to retrieve relevant information about the EMAC. The output is as follows:

```
qcc74x />lwip_emac_info
[I][LWIP_EMAC] TX: success cnt:76, error cnt:0, total size:40215Byte
[I][LWIP_EMAC]     push_cnt:76, tx_db available:64, tx_bd_ptr:12
[I][LWIP_EMAC] RX: success cnt:31827, error cnt:0, total size:6597894Byte
[I][LWIP_EMAC]     push_cnt:31837, rx_db available:54, rx_bd_ptr:19, busy cnt:0
```

### TCP-RX test: 
Execute the command **iperf -s -i 1** on the device. Then, on your computer, run the command **iperf -c <device_IP> -i 1 -t 5**. 

You will see the following output on the device side:
```
qcc74x />iperf -s -i 1
[iperf] Socket created
------------------------------------------------------------
Server listening on TCP port 5001
------------------------------------------------------------
[iperf] accept: 10.28.30.94,44943
[ ID] Interval       Transfer     Bandwidth
[  0]  0.0- 1.0 sec  5.69 MByte  45.52 Mbits/sec
[  0]  1.0- 2.0 sec  3.86 MByte  30.88 Mbits/sec
[  0]  2.0- 3.0 sec  5.78 MByte  46.24 Mbits/sec
[  0]  3.0- 4.0 sec  5.70 MByte  45.60 Mbits/sec
[  0]  4.0- 5.0 sec  5.05 MByte  40.43 Mbits/sec
[iperf] TCP Socket server is closed.
iperf exit
```

PC-side output:
```
$ iperf -c 10.28.30.178 -i 1 -t 5
------------------------------------------------------------
Client connecting to 10.28.30.178, TCP port 5001
TCP window size: 85.0 KByte (default)
------------------------------------------------------------
[  1] local 10.28.30.94 port 44943 connected with 10.28.30.178 port 5001
[ ID] Interval       Transfer     Bandwidth
[  1] 0.0000-1.0000 sec  5.38 MBytes  45.1 Mbits/sec
[  1] 1.0000-2.0000 sec  3.50 MBytes  29.4 Mbits/sec
[  1] 2.0000-3.0000 sec  5.38 MBytes  45.1 Mbits/sec
[  1] 3.0000-4.0000 sec  5.25 MBytes  44.0 Mbits/sec
[  1] 4.0000-5.0000 sec  5.25 MBytes  44.0 Mbits/sec
[  1] 0.0000-5.0458 sec  24.9 MBytes  41.4 Mbits/sec
```

### TCP-TX test: 
Execute the command **iperf -s -i 1** on the PC, then execute the command **iperf -c <PC_IP> -i 1 -t 5** on the device.
device-side output:
```
qcc74x />iperf -c 10.28.30.94 -i 1 -t 5
------------------------------------------------------------
Client connecting to 10.28.30.94, TCP port 5001
------------------------------------------------------------
[iperf] Successfully connected
[ ID] Interval       Transfer     Bandwidth
[  0]  0.0- 1.0 sec  5.05 MByte  40.40 Mbits/sec
[  0]  1.0- 2.0 sec  5.12 MByte  40.99 Mbits/sec
[  0]  2.0- 3.0 sec  5.21 MByte  41.68 Mbits/sec
[  0]  3.0- 4.0 sec  5.19 MByte  41.48 Mbits/sec
[  0]  4.0- 5.0 sec  5.19 MByte  41.48 Mbits/sec
[  0]  0.0- 5.0 sec  25.76 MByte  41.21 Mbits/sec
[iperf] TCP Socket client is closed.
iperf exit
```

PC-side output:
```
$ iperf -s -i 1
------------------------------------------------------------
Server listening on TCP port 5001
TCP window size:  128 KByte (default)
------------------------------------------------------------
[  1] local 10.28.30.94 port 5001 connected with 10.28.30.178 port 49154
[ ID] Interval       Transfer     Bandwidth
[  1] 0.0000-1.0000 sec  4.60 MBytes  38.6 Mbits/sec
[  1] 1.0000-2.0000 sec  4.73 MBytes  39.7 Mbits/sec
[  1] 2.0000-3.0000 sec  4.82 MBytes  40.4 Mbits/sec
[  1] 3.0000-4.0000 sec  4.78 MBytes  40.1 Mbits/sec
[  1] 4.0000-5.0000 sec  4.81 MBytes  40.3 Mbits/sec
[  1] 0.0000-5.1780 sec  24.6 MBytes  39.8 Mbits/sec
```
