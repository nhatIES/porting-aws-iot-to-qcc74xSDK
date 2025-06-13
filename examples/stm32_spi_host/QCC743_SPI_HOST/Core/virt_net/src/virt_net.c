#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include <lwip/api.h>
#include <lwip/opt.h>
#include <lwip/def.h>
#include <lwip/mem.h>
#include <lwip/pbuf.h>
#include <lwip/tcpip.h>
#include <lwip/dns.h>
#include <lwip/etharp.h>

#include "virt_net.h"

static void __timer_callback(TimerHandle_t handle)
{
	struct virt_net *obj = (struct virt_net *)pvTimerGetTimerID(handle);
    //printf("dhcp timeout\r\n");
    //TODO: Notify the device of WiFi disconnection?
    if (obj->ctrl) {
    	obj->ctrl(obj, VIRT_NET_CTRL_DISCONNECT_AP);
    }
}

int virt_net_get_mac(virt_net_t obj, uint8_t mac[6])
{
  assert(obj != NULL);
  assert(mac != NULL);

  memcpy(mac, obj->mac, sizeof(mac));
  return 0;
}

int virt_net_get_netmode(virt_net_t obj, int *netmode)
{
	struct virt_net *obj_t = (struct virt_net *)obj;
    assert(obj != NULL);

    *netmode = obj_t->netmode;
    return 0;
}

int virt_net_dhcp_start(virt_net_t obj, uint32_t timeout)
{
  struct virt_net *wobj = (struct virt_net *)obj;

  if (obj == NULL) {
	  return -1;
  }
  if (wobj->dhcp_timer) {
	  return 0;
  }

  netifapi_netif_set_up((struct netif *)&wobj->netif);
  netifapi_dhcp_release((struct netif *)&wobj->netif);
  netifapi_dhcp_start((struct netif *)&wobj->netif);

  wobj->dhcp_timer = xTimerCreate("dhcp", timeout, pdFALSE, (void *)wobj, __timer_callback);
  if (wobj->dhcp_timer) {
	  xTimerStart(wobj->dhcp_timer, 0);
  }
  return 0;
}

int virt_net_dhcp_done(virt_net_t obj)
{
	struct virt_net *wobj = (struct virt_net *)obj;

	if (wobj->dhcp_timer) {
		xTimerStop(wobj->dhcp_timer, 0);
		xTimerDelete(wobj->dhcp_timer, 0);
		wobj->dhcp_timer = NULL;
	}
	//netifapi_dhcp_stop((struct netif *)&wobj->netif);
	return 0;
}

int virt_net_get_ip(virt_net_t obj, uint32_t *ip, uint32_t *mask, uint32_t *gw)
{
    struct netif *nif = (struct netif *)&obj->netif;

    if (!nif) {
        return -1;
    }

    if (ip)
        *ip = netif_ip4_addr(nif)->addr;
    if (mask)
        *mask = netif_ip4_netmask(nif)->addr;
    if (gw)
        *gw = netif_ip4_gw(nif)->addr;

    return 0;
}

int virt_net_initial(virt_net_t obj)
{
  struct virt_net *wobj = (struct virt_net *)obj;

  assert(obj != NULL);

  wobj->dhcp_timer = NULL;

  return obj->init(obj);
}

