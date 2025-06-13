# lwip_tcp

## Overview

This test case verifies the basic TCP communication of the EMAC.

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
    - A router and a computer(linux) connected to that router.

- Extra Software on PC
    - telnet

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
dynamic memory init success, ocram heap size = 400 Kbyte 
sig1:ffffffff
sig2:0000f32f
cgen1:9ffffffd
EMAC lwip tcp test case !
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
wait DHCP get ip...
wait DHCP get ip...
```

Then, connect the E-PHY module to the router using an Ethernet cable. You will see the following output:

```
[W][LWIP_EMAC] Lwip Eth Emac LinkUp !!!
[I][LWIP_EMAC] eth_phy speed: 100M_FULL_DUPLEX
[I][LWIP_EMAC] State: Looking for DHCP server ...
 IP:10.28.30.178
 MASK: 255.255.255.0
 Gateway: 10.28.30.1
wait DHCP get ip...
wait DHCP get ip...
[I][LWIP_EMAC] IP address assigned by a DHCP server: 10.28.30.178
TCP Server create socket
Create server success, server ip & listen port:10.28.30.178:3365
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

On the PC, run the command **telnet <device_IP> 3365** to connect to the TCP service on the device. Any data you send will be echoed back, you will see the following output:

```
$ telnet 10.28.30.178 3365
Trying 10.28.30.178...
Connected to 10.28.30.178.
Escape character is '^]'.

hello, world!
hello, world!
```
