#include "qcc74x_mtimer.h"

#include "usbh_core.h"
#include "usbh_cdc_acm.h"
#include "usbh_hid.h"
#include "usbh_msc.h"
#include "usbh_video.h"
#include "usbh_audio.h"

#define TEST_USBH_CDC_ACM   1
#define TEST_USBH_HID       1
#define TEST_USBH_MSC       1
#define TEST_USBH_MSC_FATFS 1
#define TEST_USBH_CDC_ECM   1
#define TEST_USBH_RNDIS     0

#if TEST_USBH_CDC_ACM

#define ACM_TEST_SIZE (2 * 1024)

volatile uint32_t in_size = 0, in_offset = 0, out_size = 0;

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t cdc_acm_in_buffer[ACM_TEST_SIZE];  /* <16K */
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t cdc_acm_out_buffer[ACM_TEST_SIZE - 1]; /* <16K */

void usbh_cdc_acm_out_callback(void *arg, int nbytes)
{
    //struct usbh_cdc_acm *cdc_acm_class = (struct usbh_cdc_acm *)arg;
    // USB_LOG_RAW("acm_out nbytes:%d\r\n", nbytes);
    out_size += nbytes;
}

void usbh_cdc_acm_in_callback(void *arg, int nbytes)
{
    //struct usbh_cdc_acm *cdc_acm_class = (struct usbh_cdc_acm *)arg;
    // USB_LOG_RAW("acm_in nbytes:%d\r\n", nbytes);
    in_size += nbytes;
    in_offset += nbytes;
}

static void usbh_cdc_acm_thread(void *argument)
{
    int ret;
    struct usbh_cdc_acm *cdc_acm_class;

    // clang-format off
find_class:
    // clang-format on
    while ((cdc_acm_class = (struct usbh_cdc_acm *)usbh_find_class_instance("/dev/ttyACM0")) == NULL) {
        goto delete;
    }

    for (int i = 0; i < sizeof(cdc_acm_out_buffer); i++) {
        cdc_acm_out_buffer[i] = (uint8_t)i;
    }

    out_size = 0;
    in_size = 0;

    /* clean input buff */
    // usbh_bulk_urb_fill(&cdc_acm_class->bulkin_urb, cdc_acm_class->hport, cdc_acm_class->bulkin, cdc_acm_in_buffer, sizeof(cdc_acm_in_buffer), 100, usbh_cdc_acm_in_callback, cdc_acm_class);
    // usbh_submit_urb(&cdc_acm_class->bulkin_urb);

    uint32_t time_node = qcc74x_mtimer_get_time_ms();

    for (int i = 0; i < 1000; i++) {
        // USB_LOG_RAW("test cnt: %d\r\n", i);

        usbh_bulk_urb_fill(&cdc_acm_class->bulkout_urb, cdc_acm_class->hport, cdc_acm_class->bulkout, cdc_acm_out_buffer, sizeof(cdc_acm_out_buffer), 3000, usbh_cdc_acm_out_callback, cdc_acm_class);
        ret = usbh_submit_urb(&cdc_acm_class->bulkout_urb);
        if (ret < 0) {
            USB_LOG_RAW("bulk out error,ret:%d\r\n", ret);
            goto delete;
        }

        for (in_offset = 0; in_offset < sizeof(cdc_acm_out_buffer);) {
            usbh_bulk_urb_fill(&cdc_acm_class->bulkin_urb, cdc_acm_class->hport, cdc_acm_class->bulkin, &cdc_acm_in_buffer[in_offset], (sizeof(cdc_acm_in_buffer) - in_offset), 3000, usbh_cdc_acm_in_callback, cdc_acm_class);
            ret = usbh_submit_urb(&cdc_acm_class->bulkin_urb);
            if (ret < 0) {
                USB_LOG_RAW("bulk in error,ret:%d\r\n", ret);
                goto delete;
            }
        }

        /* data check */
        // for (int i = 0; i < sizeof(cdc_acm_in_buffer) / 4; i++) {
        //     if (((uint32_t *)cdc_acm_in_buffer)[i] != ((uint32_t *)cdc_acm_out_buffer)[i]) {
        //         USB_LOG_RAW("data error, i:%d, data:0x%08X->0x%08X\r\n", i, ((uint32_t *)cdc_acm_out_buffer)[i], ((uint32_t *)cdc_acm_in_buffer)[i]);
        //     }
        // }
    }

    time_node = qcc74x_mtimer_get_time_ms() - time_node;
    USB_LOG_RAW("time:%dms, in_size:%d, out_size:%d, speed:%dByte/s\r\n", time_node, in_size, out_size, (in_size + out_size) * 1000 / time_node);

    // clang-format off
delete: 
    usb_osal_thread_delete(NULL);
    // clang-format on
}
#endif

#if TEST_USBH_HID
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t hid_buffer[128];

void usbh_hid_callback(void *arg, int nbytes)
{
    struct usbh_hid *hid_class = (struct usbh_hid *)arg;

    if (nbytes > 0) {
        for (size_t i = 0; i < nbytes; i++) {
            USB_LOG_RAW("0x%02x ", hid_buffer[i]);
        }
        USB_LOG_RAW("nbytes:%d\r\n", nbytes);
        usbh_submit_urb(&hid_class->intin_urb);
    }
}

static void usbh_hid_thread(void *argument)
{
    int ret;
    struct usbh_hid *hid_class;

    // clang-format off
find_class:
    // clang-format on
    while ((hid_class = (struct usbh_hid *)usbh_find_class_instance("/dev/input0")) == NULL) {
        goto delete;
    }

    usbh_int_urb_fill(&hid_class->intin_urb, hid_class->hport, hid_class->intin, hid_buffer, hid_class->intin->wMaxPacketSize, 0, usbh_hid_callback, hid_class);
    ret = usbh_submit_urb(&hid_class->intin_urb);
    if (ret < 0) {
        goto find_class;
    }
    // clang-format off
delete: 
    usb_osal_thread_delete(NULL);
    // clang-format on
}
#endif

#if TEST_USBH_MSC

#if TEST_USBH_MSC_FATFS
#include "ff.h"
USB_NOCACHE_RAM_SECTION FATFS fs;
USB_NOCACHE_RAM_SECTION FIL fnew;

char test_data[] =
    "I've been reading books of old \r\n\
    The legends and the myths \r\n\
    Achilles and his gold \r\n\
    Hercules and his gifts \r\n\
    Spiderman's control \r\n\
    And Batman with his fists\r\n\
    And clearly I don't see myself upon that list\r\n\
    But she said, where'd you wanna go?\r\n\
    How much you wanna risk?\r\n\
    I'm not looking for somebody\r\n\
    With some superhuman gifts\r\n\
    Some superhero\r\n\
    Some fairytale bliss\r\n\
    Just something I can turn to\r\n\
    Somebody I can kiss\r\n\
    I want something just like this\r\n\r\n";

USB_NOCACHE_RAM_SECTION BYTE RW_Buffer[32 * 1024] = { 0 };
USB_NOCACHE_RAM_SECTION BYTE Check_Buffer[sizeof(RW_Buffer)] = { 0 };

void fatfs_write_read_test()
{
    FRESULT ret;
    UINT fnum;

    uint32_t time_node, i, j;

    /* full test data to buff */
    for (uint32_t cnt = 0; cnt < (sizeof(RW_Buffer) / sizeof(test_data)); cnt++) {
        memcpy(&RW_Buffer[cnt * sizeof(test_data)], test_data, sizeof(test_data));
        memcpy(&Check_Buffer[cnt * sizeof(test_data)], test_data, sizeof(test_data));
    }

    /* write test */
    USB_LOG_RAW("\r\n");
    USB_LOG_INFO("******************** be about to write test... **********************\r\n");
    ret = f_open(&fnew, "/usb/test_file.txt", FA_CREATE_ALWAYS | FA_WRITE);
    if (ret == FR_OK) {
        time_node = (uint32_t)qcc74x_mtimer_get_time_ms();
        /*write into file*/
        // ret = f_write(&fnew, RW_Buffer, 1024, &fnum);
        for (i = 0; i < 1024; i++) {
            ret = f_write(&fnew, RW_Buffer, sizeof(RW_Buffer), &fnum);
            if (ret) {
                break;
            }
        }

        /* close file */
        ret |= f_close(&fnew);
        /* get time */
        time_node = (uint32_t)qcc74x_mtimer_get_time_ms() - time_node;

        if (ret == FR_OK) {
            USB_LOG_INFO("Write Test Succeed! \r\n");
            USB_LOG_INFO("Single data size:%d Byte, Write the number:%d, Total size:%d KB\r\n", sizeof(RW_Buffer), i, sizeof(RW_Buffer) * i >> 10);
            USB_LOG_INFO("Time:%dms, Write Speed:%d KB/s \r\n", time_node, ((sizeof(RW_Buffer) * i) >> 10) * 1000 / time_node);
        } else {
            USB_LOG_ERR("Fail to write files(%d) num:%d\n", ret, i);
            return;
        }
    } else {
        USB_LOG_ERR("Fail to open or create files: %d.\r\n", ret);
        return;
    }

    /* read test */
    USB_LOG_RAW("\r\n");
    USB_LOG_INFO("******************** be about to read test... **********************\r\n");
    ret = f_open(&fnew, "/usb/test_file.txt", FA_OPEN_EXISTING | FA_READ);
    if (ret == FR_OK) {
        time_node = (uint32_t)qcc74x_mtimer_get_time_ms();

        // ret = f_read(&fnew, RW_Buffer, 1024, &fnum);
        for (i = 0; i < 1024; i++) {
            ret = f_read(&fnew, RW_Buffer, sizeof(RW_Buffer), &fnum);
            if (ret) {
                break;
            }
        }
        /* close file */
        ret |= f_close(&fnew);
        /* get time */
        time_node = (uint32_t)qcc74x_mtimer_get_time_ms() - time_node;

        if (ret == FR_OK) {
            USB_LOG_INFO("Read Test Succeed! \r\n");
            USB_LOG_INFO("Single data size:%dByte, Read the number:%d, Total size:%d KB\r\n", sizeof(RW_Buffer), i, sizeof(RW_Buffer) * i >> 10);
            USB_LOG_INFO("Time:%dms, Read Speed:%d KB/s \r\n", time_node, ((sizeof(RW_Buffer) * i) >> 10) * 1000 / time_node);
        } else {
            USB_LOG_ERR("Fail to read file: (%d), num:%d\n", ret, i);
            return;
        }
    } else {
        USB_LOG_ERR("Fail to open files.\r\n");
        return;
    }

    /* check data */
    USB_LOG_RAW("\r\n");
    USB_LOG_INFO("******************** be about to check test... **********************\r\n");
    ret = f_open(&fnew, "/usb/test_file.txt", FA_OPEN_EXISTING | FA_READ);
    if (ret == FR_OK) {
        // ret = f_read(&fnew, RW_Buffer, 1024, &fnum);
        for (i = 0; i < 1024; i++) {
            memset(RW_Buffer, 0x55, sizeof(RW_Buffer));
            ret = f_read(&fnew, RW_Buffer, sizeof(RW_Buffer), &fnum);
            if (ret) {
                break;
            }
            for (j = 0; j < sizeof(RW_Buffer); j++) {
                if (RW_Buffer[j] != Check_Buffer[j]) {
                    break;
                }
            }
            if (j < sizeof(RW_Buffer)) {
                break;
            }
        }
        /* close file */
        ret |= f_close(&fnew);

        if (ret == FR_OK) {
            if (i < 1024 || j < sizeof(RW_Buffer)) {
                USB_LOG_INFO("Check Test Error! \r\n");
                USB_LOG_INFO("Data Error!  Num:%d/1024, Byte:%d/%d", i, j, sizeof(RW_Buffer));
            } else {
                USB_LOG_INFO("Check Test Succeed! \r\n");
                USB_LOG_INFO("All Data Is Good! \r\n");
            }

        } else {
            USB_LOG_ERR("Fail to read file: (%d), num:%d\n", ret, i);
            return;
        }
    } else {
        USB_LOG_ERR("Fail to open files.\r\n");
        return;
    }
}

#endif

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t partition_table[512];

static void usbh_msc_thread(void *argument)
{
    int ret;
    struct usbh_msc *msc_class;

    // clang-format off
find_class:
    // clang-format on
    while ((msc_class = (struct usbh_msc *)usbh_find_class_instance("/dev/sda")) == NULL) {
        goto delete;
    }

#if 1
    /* get the partition table */
    ret = usbh_msc_scsi_read10(msc_class, 0, partition_table, 1);
    if (ret < 0) {
        USB_LOG_RAW("scsi_read10 error,ret:%d\r\n", ret);
        goto find_class;
    }
    // for (uint32_t i = 0; i < 512; i++) {
    //     if (i % 16 == 0) {
    //         USB_LOG_RAW("\r\n");
    //     }
    //     USB_LOG_RAW("%02x ", partition_table[i]);
    // }
    // USB_LOG_RAW("\r\n");
#endif

#if TEST_USBH_MSC_FATFS
    extern void fatfs_usbh_driver_register(void);
    fatfs_usbh_driver_register();

    ret = f_mount(&fs, "/usb", 1);
    if (FR_OK != ret) {
        USB_LOG_RAW("mount fail, res: %d\r\n", ret);
        goto delete;
    }

    fatfs_write_read_test();

    f_mount(NULL, "/usb", 1);
#endif
    // clang-format off
delete: 
    usb_osal_thread_delete(NULL);
    // clang-format on
}
#endif

#if 0
void usbh_videostreaming_parse_mjpeg(struct usbh_urb *urb, struct usbh_videostreaming *stream)
{
    struct usbh_iso_frame_packet *iso_packet;
    uint32_t num_of_iso_packets;
    uint8_t data_offset;
    uint32_t data_len;
    uint8_t header_len = 0;

    num_of_iso_packets = urb->num_of_iso_packets;
    iso_packet = urb->iso_packet;

    for (uint32_t i = 0; i < num_of_iso_packets; i++) {
        /*
            uint8_t frameIdentifier : 1U;
            uint8_t endOfFrame      : 1U;
            uint8_t presentationTimeStamp    : 1U;
            uint8_t sourceClockReference : 1U;
            uint8_t reserved             : 1U;
            uint8_t stillImage           : 1U;
            uint8_t errorBit             : 1U;
            uint8_t endOfHeader          : 1U;
        */
        if (iso_packet[i].actual_length == 0) { /* skip no data */
            continue;
        }

        header_len = iso_packet[i].transfer_buffer[0];

        if ((header_len > 12) || (header_len == 0)) { /* do not be illegal */
            while (1) {
            }
        }
        if (iso_packet[i].transfer_buffer[1] & (1 << 6)) { /* error bit, re-receive */
            stream->bufoffset = 0;
            continue;
        }

        if ((stream->bufoffset == 0) && ((iso_packet[i].transfer_buffer[header_len] != 0xff) || (iso_packet[i].transfer_buffer[header_len + 1] != 0xd8))) {
            stream->bufoffset = 0;
            continue;
        }

        data_offset = header_len;
        data_len = iso_packet[i].actual_length - header_len;

        /** do something here */

        stream->bufoffset += data_len;

        if (iso_packet[i].transfer_buffer[1] & (1 << 1)) {
            if ((iso_packet[i].transfer_buffer[iso_packet[i].actual_length - 2] != 0xff) || (iso_packet[i].transfer_buffer[iso_packet[i].actual_length - 1] != 0xd9)) {
                stream->bufoffset = 0;
                continue;
            }

            /** do something here */

            if (stream->video_one_frame_callback) {
                stream->video_one_frame_callback(stream);
            }
            stream->bufoffset = 0;
        }
    }
    /** do something here */
}

void usbh_videostreaming_parse_yuyv2(struct usbh_urb *urb, struct usbh_videostreaming *stream)
{
    struct usbh_iso_frame_packet *iso_packet;
    uint32_t num_of_iso_packets;
    uint8_t data_offset;
    uint32_t data_len;
    uint8_t header_len = 0;

    num_of_iso_packets = urb->num_of_iso_packets;
    iso_packet = urb->iso_packet;

    for (uint32_t i = 0; i < num_of_iso_packets; i++) {
        /*
            uint8_t frameIdentifier : 1U;
            uint8_t endOfFrame      : 1U;
            uint8_t presentationTimeStamp    : 1U;
            uint8_t sourceClockReference : 1U;
            uint8_t reserved             : 1U;
            uint8_t stillImage           : 1U;
            uint8_t errorBit             : 1U;
            uint8_t endOfHeader          : 1U;
        */

        if (iso_packet[i].actual_length == 0) { /* skip no data */
            continue;
        }

        header_len = iso_packet[i].transfer_buffer[0];

        if ((header_len > 12) || (header_len == 0)) { /* do not be illegal */
            while (1) {
            }
        }
        if (iso_packet[i].transfer_buffer[1] & (1 << 6)) { /* error bit, re-receive */
            stream->bufoffset = 0;
            continue;
        }

        data_offset = header_len;
        data_len = iso_packet[i].actual_length - header_len;

        /** do something here */

        stream->bufoffset += data_len;

        if (iso_packet[i].transfer_buffer[1] & (1 << 1)) {
            /** do something here */

            if (stream->video_one_frame_callback && (stream->bufoffset == stream->buflen)) {
                stream->video_one_frame_callback(stream);
            }
            stream->bufoffset = 0;
        }
    }

    /** do something here */
}
#endif

#if TEST_USBH_CDC_ECM || TEST_USBH_RNDIS
#include "netif/etharp.h"
#include "lwip/netif.h"
#include "lwip/pbuf.h"
#include "lwip/tcpip.h"
#if LWIP_DHCP
#include "lwip/dhcp.h"
#include "lwip/prot/dhcp.h"
#endif

#ifdef __RTTHREAD__

#ifndef RT_USING_TIMER_SOFT
#error must enable RT_USING_TIMER_SOFT to support timer callback in thread
#endif

#include <rtthread.h>
#include <rtdevice.h>
#include <netif/ethernetif.h>
#include <netdev.h>

#else
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"

TimerHandle_t dhcp_handle1;
TimerHandle_t dhcp_handle2;

static void dhcp_timeout(TimerHandle_t xTimer)
{
    struct netif *netif = (struct netif *)pvTimerGetTimerID(xTimer);
    struct dhcp *dhcp;

    if (netif_is_up(netif)) {
        dhcp = netif_dhcp_data(netif);

        if (dhcp && (dhcp->state == DHCP_STATE_BOUND)) {
            USB_LOG_INFO("IPv4 Address     : %s\r\n", ipaddr_ntoa(&netif->ip_addr));
            USB_LOG_INFO("IPv4 Subnet mask : %s\r\n", ipaddr_ntoa(&netif->netmask));
            USB_LOG_INFO("IPv4 Gateway     : %s\r\n\r\n", ipaddr_ntoa(&netif->gw));

            xTimerStop(xTimer, 0);
        }
    }
}
#endif
#endif

#if TEST_USBH_CDC_ECM
#include "usbh_cdc_ecm.h"

struct netif g_cdc_ecm_netif;

#ifdef __RTTHREAD__
static struct eth_device cdc_ecm_dev;

static rt_err_t rt_usbh_cdc_ecm_control(rt_device_t dev, int cmd, void *args)
{
    struct usbh_cdc_ecm *cdc_ecm_class = (struct usbh_cdc_ecm *)dev->user_data;

    switch (cmd) {
        case NIOCTL_GADDR:

            /* get mac address */
            if (args)
                rt_memcpy(args, cdc_ecm_class->mac, 6);
            else
                return -RT_ERROR;

            break;

        default:
            break;
    }

    return RT_EOK;
}

static rt_err_t rt_usbh_cdc_ecm_eth_tx(rt_device_t dev, struct pbuf *p)
{
    return usbh_cdc_ecm_linkoutput(NULL, p);
}
#endif

static err_t usbh_cdc_ecm_if_init(struct netif *netif)
{
    LWIP_ASSERT("netif != NULL", (netif != NULL));

    netif->mtu = 1500;
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP | NETIF_FLAG_UP;
    netif->state = NULL;
    netif->name[0] = 'E';
    netif->name[1] = 'X';
    netif->output = etharp_output;
    netif->linkoutput = usbh_cdc_ecm_linkoutput;
    return ERR_OK;
}

void usbh_cdc_ecm_run(struct usbh_cdc_ecm *cdc_ecm_class)
{
#ifdef __RTTHREAD__
    struct netdev *netdev;

    memset(&cdc_ecm_dev, 0, sizeof(struct eth_device));

    cdc_ecm_dev.parent.control = rt_usbh_cdc_ecm_control;
    cdc_ecm_dev.eth_rx = NULL;
    cdc_ecm_dev.eth_tx = rt_usbh_cdc_ecm_eth_tx;
    cdc_ecm_dev.parent.user_data = cdc_ecm_class;

    eth_device_init(&cdc_ecm_dev, "u0");
    eth_device_linkchange(&cdc_ecm_dev, RT_TRUE);

    usb_osal_thread_create("usbh_cdc_ecm_rx", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_cdc_ecm_rx_thread, cdc_ecm_dev.netif);
#else
    struct netif *netif = &g_cdc_ecm_netif;

    netif->hwaddr_len = 6;
    memcpy(netif->hwaddr, cdc_ecm_class->mac, 6);

    IP4_ADDR(&cdc_ecm_class->ipaddr, 0, 0, 0, 0);
    IP4_ADDR(&cdc_ecm_class->netmask, 0, 0, 0, 0);
    IP4_ADDR(&cdc_ecm_class->gateway, 0, 0, 0, 0);

    netif = netif_add(netif, &cdc_ecm_class->ipaddr, &cdc_ecm_class->netmask, &cdc_ecm_class->gateway, NULL, usbh_cdc_ecm_if_init, tcpip_input);
    netif_set_default(netif);
    while (!netif_is_up(netif)) {
    }

    dhcp_handle1 = xTimerCreate((const char *)"dhcp1", (TickType_t)200, (UBaseType_t)pdTRUE, (void *const)netif, (TimerCallbackFunction_t)dhcp_timeout);
    if (dhcp_handle1 == NULL) {
        USB_LOG_ERR("timer creation failed! \r\n");
        while (1) {
        }
    }

    usb_osal_thread_create("usbh_cdc_ecm_rx", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_cdc_ecm_rx_thread, netif);
#if LWIP_DHCP
    dhcp_start(netif);
    xTimerStart(dhcp_handle1, 0);
#endif
#endif
}

void usbh_cdc_ecm_stop(struct usbh_cdc_ecm *cdc_ecm_class)
{
#ifdef __RTTHREAD__
    eth_device_deinit(&cdc_ecm_dev);
#else
    struct netif *netif = &g_cdc_ecm_netif;
#if LWIP_DHCP
    dhcp_stop(netif);
    dhcp_cleanup(netif);
#endif
    netif_set_down(netif);
    netif_remove(netif);
#endif
}
#endif

#if TEST_USBH_RNDIS
#include "usbh_rndis.h"

struct netif g_rndis_netif;

#ifdef __RTTHREAD__

static struct eth_device rndis_dev;

static rt_timer_t keep_timer = RT_NULL;

static void rndis_dev_keepalive_timeout(void *parameter)
{
    struct usbh_rndis *rndis_class = (struct usbh_rndis *)parameter;
    usbh_rndis_keepalive(rndis_class);
}

static void timer_init(struct usbh_rndis *rndis_class)
{
    keep_timer = rt_timer_create("keep",
                                 rndis_dev_keepalive_timeout,
                                 rndis_class,
                                 5000,
                                 RT_TIMER_FLAG_PERIODIC |
                                     RT_TIMER_FLAG_SOFT_TIMER);

    rt_timer_start(keep_timer);
}

static rt_err_t rt_usbh_rndis_control(rt_device_t dev, int cmd, void *args)
{
    struct usbh_rndis *rndis_class = (struct usbh_rndis *)dev->user_data;

    switch (cmd) {
        case NIOCTL_GADDR:

            /* get mac address */
            if (args)
                rt_memcpy(args, rndis_class->mac, 6);
            else
                return -RT_ERROR;

            break;

        default:
            break;
    }

    return RT_EOK;
}

static rt_err_t rt_usbh_rndis_eth_tx(rt_device_t dev, struct pbuf *p)
{
    return usbh_rndis_linkoutput(NULL, p);
}

#else
TimerHandle_t timer_handle;

static void rndis_dev_keepalive_timeout(TimerHandle_t xTimer)
{
    struct usbh_rndis *rndis_class = (struct usbh_rndis *)pvTimerGetTimerID(xTimer);
    usbh_rndis_keepalive(rndis_class);
}

void timer_init(struct usbh_rndis *rndis_class)
{
    timer_handle = xTimerCreate((const char *)NULL, (TickType_t)5000, (UBaseType_t)pdTRUE, (void *const)rndis_class, (TimerCallbackFunction_t)rndis_dev_keepalive_timeout);
    if (NULL != timer_handle) {
        xTimerStart(timer_handle, 0);
    } else {
        USB_LOG_ERR("timer creation failed! \r\n");
        for (;;) {
            ;
        }
    }
}
#endif

static err_t usbh_rndis_if_init(struct netif *netif)
{
    LWIP_ASSERT("netif != NULL", (netif != NULL));

    netif->mtu = 1500;
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP | NETIF_FLAG_UP;
    netif->state = NULL;
    netif->name[0] = 'E';
    netif->name[1] = 'X';
    netif->output = etharp_output;
    netif->linkoutput = usbh_rndis_linkoutput;
    return ERR_OK;
}

void usbh_rndis_run(struct usbh_rndis *rndis_class)
{
#ifdef __RTTHREAD__
    struct netdev *netdev;

    memset(&rndis_dev, 0, sizeof(struct eth_device));

    rndis_dev.parent.control = rt_usbh_rndis_control;
    rndis_dev.eth_rx = NULL;
    rndis_dev.eth_tx = rt_usbh_rndis_eth_tx;
    rndis_dev.parent.user_data = rndis_class;

    eth_device_init(&rndis_dev, "u1");
    eth_device_linkchange(&rndis_dev, RT_TRUE);

    usb_osal_thread_create("usbh_rndis_rx", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_rndis_rx_thread, rndis_dev.netif);
    timer_init(rndis_class);
#else
    struct netif *netif = &g_rndis_netif;

    netif->hwaddr_len = 6;
    memcpy(netif->hwaddr, rndis_class->mac, 6);

    IP4_ADDR(&rndis_class->ipaddr, 0, 0, 0, 0);
    IP4_ADDR(&rndis_class->netmask, 0, 0, 0, 0);
    IP4_ADDR(&rndis_class->gateway, 0, 0, 0, 0);

    netif = netif_add(netif, &rndis_class->ipaddr, &rndis_class->netmask, &rndis_class->gateway, NULL, usbh_rndis_if_init, tcpip_input);
    netif_set_default(netif);
    while (!netif_is_up(netif)) {
    }

    dhcp_handle2 = xTimerCreate((const char *)"dhcp2", (TickType_t)200, (UBaseType_t)pdTRUE, (void *const)netif, (TimerCallbackFunction_t)dhcp_timeout);
    if (dhcp_handle2 == NULL) {
        USB_LOG_ERR("timer creation failed! \r\n");
        while (1) {
        }
    }

    usb_osal_thread_create("usbh_rndis_rx", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_rndis_rx_thread, netif);
    timer_init(rndis_class);

#if LWIP_DHCP
    dhcp_start(netif);
    xTimerStart(dhcp_handle2, 0);
#endif
#endif
}

void usbh_rndis_stop(struct usbh_rndis *rndis_class)
{
#ifdef __RTTHREAD__
    eth_device_deinit(&rndis_dev);
    rt_timer_stop(keep_timer);
    rt_timer_delete(keep_timer);
#else
    struct netif *netif = &g_rndis_netif;
#if LWIP_DHCP
    dhcp_stop(netif);
    dhcp_cleanup(netif);
#endif
    netif_set_down(netif);
    netif_remove(netif);
    xTimerStop(timer_handle, 0);
    xTimerDelete(timer_handle, 0);
#endif
}
#endif

void usbh_cdc_acm_run(struct usbh_cdc_acm *cdc_acm_class)
{
#if TEST_USBH_CDC_ACM
    usb_osal_thread_create("usbh_cdc", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_cdc_acm_thread, NULL);
#endif
}

void usbh_cdc_acm_stop(struct usbh_cdc_acm *cdc_acm_class)
{
}

void usbh_hid_run(struct usbh_hid *hid_class)
{
#if TEST_USBH_HID
    usb_osal_thread_create("usbh_hid", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_hid_thread, NULL);
#endif
}

void usbh_hid_stop(struct usbh_hid *hid_class)
{
}

#ifndef __RTTHREAD__
void usbh_msc_run(struct usbh_msc *msc_class)
{
#if TEST_USBH_MSC
    usb_osal_thread_create("usbh_msc", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_msc_thread, NULL);
#endif
}

void usbh_msc_stop(struct usbh_msc *msc_class)
{
}
#endif

#if TEST_USBH_CDC_ECM || TEST_USBH_RNDIS
const uint8_t message[] = {
    0x55, 0x53, 0x42, 0x43, 0x12, 0x34, 0x56, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11,
    0x06, 0x20, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
struct usbh_msc_modeswitch_config config = {
    .name = "huawei",
    .vid = 0x12d1,
    .pid = 0x1f01,
    .message_content = message
};
#endif

void usbh_class_test(void)
{
#ifdef __RTTHREAD__
    /* do nothing */
#else
#if TEST_USBH_CDC_ECM || TEST_USBH_RNDIS
    usbh_msc_modeswitch_enable(&config);
    /* Initialize the LwIP stack */
    tcpip_init(NULL, NULL);
#endif
#endif
}