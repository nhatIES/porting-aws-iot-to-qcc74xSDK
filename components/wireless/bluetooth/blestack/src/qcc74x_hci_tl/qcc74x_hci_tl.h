#ifndef __QCC74x_HCI_WRAPPER_H__
#define __QCC74x_HCI_WRAPPER_H__

#include "buf.h"

#define HCI_TYPE_CMD_PKT 0x01
#define HCI_TYPE_ACL_PKT 0x02

int qcc74x_hci_init(char *port);
int qcc74x_hci_send(struct net_buf *buf);
void qcc74x_hci_reset(void);
#endif
