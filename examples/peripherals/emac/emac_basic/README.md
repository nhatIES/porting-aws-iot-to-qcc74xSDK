# emac_basic

## Overview

This test case verifies the basic packet transmission and reception functionality of the EMAC by conducting a loopback test of ARP packets through the connected external E-PHY chip.

## Support CHIP

|      CHIP        | Remark |
|:----------------:|:------:|
|qcc743/qcc744     |        |

## How to use example

### Hardware Required

- Boards
    - qcc743dk
    - qcc744dk

- Device
    - A standard E-PHY module with an RMII interface that complies with the IEEE 802.3/802.3u specifications, e.g: IP101G,LAN8720.

### Hardware Connection

#### QCC743/QCC744

There are two sets of RMII pin configurations. The default configuration is as follows:

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

- qcc743/qcc744

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
dynamic memory init success, ocram heap size = 430 Kbyte 
sig1:ffffffff
sig2:0000f32f
cgen1:9ffffffd
[I][MAIN] EMAC ARP Packet test!
[I][EPHY] eth phy scan success, phy_addr: 1, phy_id: 0x02430C54
[W][EPHY] drv_match falied, use General driver
[I][MAIN] eth_phy speed: 100M_FULL_DUPLEX
[I][MAIN] eth_phy loopback mode
[I][MAIN] eth_phy init done

[I][MAIN] TX: Speed: 74Mbps, valid_data_speed: 49Mbps
[I][MAIN]     success cnt:292520, error cnt:0, total size:12285840Byte
[I][MAIN]     push_cnt:292520, tx_db available:0
[I][MAIN] RX: Speed: 74Mbps, valid_data_speed: 74Mbps
[I][MAIN]     success cnt:292519, error cnt:0, total size:18721216Byte
[I][MAIN]     push_cnt:292519, rx_db available:1, busy cnt:1

[I][MAIN] TX: Speed: 73Mbps, valid_data_speed: 48Mbps
[I][MAIN]     success cnt:580536, error cnt:0, total size:24382512Byte
[I][MAIN]     push_cnt:580536, tx_db available:0
[I][MAIN] RX: Speed: 73Mbps, valid_data_speed: 73Mbps
[I][MAIN]     success cnt:580535, error cnt:0, total size:37154240Byte
[I][MAIN]     push_cnt:580535, rx_db available:0, busy cnt:1

```
