#ifndef _PKG_PROTOCOL_H_
#define _PKG_PROTOCOL_H_

#define PKG_DATA_FRAME 0x7878
#define PKG_CMD_FRAME 0xef01

struct pkg_protocol {
  uint16_t type;
  uint16_t length;
  uint8_t payload[0];
};

struct pkg_cmd_connect_ap {
  uint16_t ssid_len;
  uint8_t ssid[32];
  uint8_t ssid_tail[1];
  uint8_t passphr[64];
  uint8_t psk_tail[1];
} __attribute__((packed));

struct pkg_protocol_cmd {
  uint16_t cmd;
  uint16_t msg_id;
  uint8_t payload[0];
} __attribute__((packed));

#endif
