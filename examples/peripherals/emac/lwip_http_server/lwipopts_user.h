

#ifndef LWIP_HDR_LWIPOPTS_H__
#define LWIP_HDR_LWIPOPTS_H__

#define LWIP_NETIF_API 1

/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#define NO_SYS 0

/* ---------- Memory options ---------- */
/* MEM_ALIGNMENT: should be set to the alignment of the CPU for which
   lwIP is compiled. 4 byte alignment -> define MEM_ALIGNMENT to 4, 2
   byte alignment -> define MEM_ALIGNMENT to 2. */
#define MEM_ALIGNMENT 4

/* MEM_SIZE: the size of the heap memory. If the application will send
a lot of data that needs to be copied, this should be set high. */
#define MEM_SIZE (15 * 1024)

/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
#define MEMP_NUM_PBUF 10
/* MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
   per active UDP "connection". */
#define MEMP_NUM_UDP_PCB 6
/* MEMP_NUM_TCP_PCB: the number of simulatenously active TCP
   connections. */
#define MEMP_NUM_TCP_PCB 10
/* MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP
   connections. */
#define MEMP_NUM_TCP_PCB_LISTEN 5
/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */
#define MEMP_NUM_SYS_TIMEOUT 10

/* ---------- IPv4 options ---------- */
#define LWIP_IPV4 1

/* ---------- TCP options ---------- */
#define LWIP_TCP 1
#define TCP_TTL  255

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ 0

/* TCP Maximum segment size. */
#define TCP_MSS (1500 - 40) /* TCP_MSS = (Ethernet MTU - IP header size - TCP header size) */

/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF (4 * TCP_MSS)

/*  TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
  as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work. */

#define TCP_SND_QUEUELEN (2 * TCP_SND_BUF / TCP_MSS)

/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
#define MEMP_NUM_TCP_SEG TCP_SND_QUEUELEN

/* TCP receive window. */
#define TCP_WND (2 * TCP_MSS)

/* ---------- Pbuf options ---------- */
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool.
   @ note: used to allocate Tx pbufs only
   mix pbuf size is (TCP_WND / TCP_MSS)  */
#define PBUF_POOL_SIZE (TCP_WND / TCP_MSS)

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE 1524

/* LWIP_SUPPORT_CUSTOM_PBUF == 1: to pass directly MAC Rx buffers to the stack
   no copy is needed */
#define LWIP_SUPPORT_CUSTOM_PBUF 1

/* ---------- ICMP options ---------- */
#define LWIP_ICMP 1

/* ---------- DHCP options ---------- */
#define LWIP_DHCP 1

/* ---------- UDP options ---------- */
#define LWIP_UDP 1
#define UDP_TTL  255

/* ---------- Statistics options ---------- */
#define LWIP_STATS 0

#define LWIP_TIMEVAL_PRIVATE      0 // use sys/time.h for struct timeval

#define LWIP_ERRNO_STDINCLUDE     1
// #define LWIP_SOCKET_SET_ERRNO     1
extern int *__errno(void);
#define errno                         (*__errno())

/* ---------- link callback options ---------- */
/* LWIP_NETIF_LINK_CALLBACK==1: Support a callback function from an interface
 * whenever the link changes (i.e., link down)
 */
#define LWIP_NETIF_LINK_CALLBACK 1

/*
   --------------------------------------
   ---------- Checksum options ----------
   --------------------------------------
*/
/* LWIP_CHECKSUM_ON_COPY==1: Calculate checksum when copying data from application buffers to pbufs. */
#define LWIP_CHECKSUM_ON_COPY 0

#ifdef CHECKSUM_BY_HARDWARE
/* CHECKSUM_GEN_IP==0: Generate checksums by hardware for outgoing IP packets.*/
#define CHECKSUM_GEN_IP 0
/* CHECKSUM_GEN_UDP==0: Generate checksums by hardware for outgoing UDP packets.*/
#define CHECKSUM_GEN_UDP 0
/* CHECKSUM_GEN_TCP==0: Generate checksums by hardware for outgoing TCP packets.*/
#define CHECKSUM_GEN_TCP 0
/* CHECKSUM_CHECK_IP==0: Check checksums by hardware for incoming IP packets.*/
#define CHECKSUM_CHECK_IP 0
/* CHECKSUM_CHECK_UDP==0: Check checksums by hardware for incoming UDP packets.*/
#define CHECKSUM_CHECK_UDP 0
/* CHECKSUM_CHECK_TCP==0: Check checksums by hardware for incoming TCP packets.*/
#define CHECKSUM_CHECK_TCP 0
/* CHECKSUM_CHECK_ICMP==0: Check checksums by hardware for incoming ICMP packets.*/
#define CHECKSUM_GEN_ICMP 0
#else
/* CHECKSUM_GEN_IP==1: Generate checksums in software for outgoing IP packets.*/
#define CHECKSUM_GEN_IP     1
/* CHECKSUM_GEN_UDP==1: Generate checksums in software for outgoing UDP packets.*/
#define CHECKSUM_GEN_UDP    1
/* CHECKSUM_GEN_TCP==1: Generate checksums in software for outgoing TCP packets.*/
#define CHECKSUM_GEN_TCP    1
/* CHECKSUM_CHECK_IP==1: Check checksums in software for incoming IP packets.*/
#define CHECKSUM_CHECK_IP   1
/* CHECKSUM_CHECK_UDP==1: Check checksums in software for incoming UDP packets.*/
#define CHECKSUM_CHECK_UDP  1
/* CHECKSUM_CHECK_TCP==1: Check checksums in software for incoming TCP packets.*/
#define CHECKSUM_CHECK_TCP  1
/* CHECKSUM_CHECK_ICMP==1: Check checksums by hardware for incoming ICMP packets.*/
#define CHECKSUM_GEN_ICMP   1
#define CHECKSUM_CHECK_ICMP 1
#endif

/*
   ----------------------------------------------
   ---------- Sequential layer options ----------
   ----------------------------------------------
*/
/**
 * LWIP_NETCONN==1: Enable Netconn API (require to use api_lib.c)
 */
#define LWIP_NETCONN 1

/*
   ------------------------------------
   ---------- Socket options ----------
   ------------------------------------
*/
/**
 * LWIP_SOCKET==1: Enable Socket API (require to use sockets.c)
 */
#define LWIP_SOCKET 1

/* ---------------- httpd options --------------- */
#define HTTPD_USE_CUSTOM_FSDATA 1

// /** Set this to 1 to support CGI (old style).*/
// #define LWIP_HTTPD_CGI 1

// /** Set this to 1 to support SSI (Server-Side-Includes)*/
// #define LWIP_HTTPD_SSI 0

// /** Set this to 1 to support HTTP POST */
// #define LWIP_HTTPD_SUPPORT_POST 0

// /** Set this to 0 to not send the SSI tag (default is on, so the tag will
//  * be sent in the HTML page */
// #define LWIP_HTTPD_SSI_INCLUDE_TAG 0

// /** This is the size of a static buffer used when URIs end with '/'.
//  * In this buffer, the directory requested is concatenated with all the
//  * configured default file names.
//  * Set to 0 to disable checking default filenames on non-root directories.
//  */
// #define LWIP_HTTPD_MAX_REQUEST_URI_LEN 256

// /** The server port for HTTPD to use */
// #define HTTPD_SERVER_PORT LWIP_IANA_PORT_HTTP
#define HTTPD_FSDATA_FILE "web_demo/fsdata_custom.c"

/*
   ----------------------------------------
   ---------- Lwip Debug options ----------
   ----------------------------------------
*/
#define LWIP_DEBUG       LWIP_DBG_OFF
#define ETHARP_DEBUG     LWIP_DBG_OFF
#define ICMP_DEBUG       LWIP_DBG_OFF
#define TCPIP_DEBUG      LWIP_DBG_OFF
#define TCP_DEBUG        LWIP_DBG_OFF
#define TCP_OUTPUT_DEBUG LWIP_DBG_OFF
#define UDP_DEBUG        LWIP_DBG_OFF
#define SOCKET_DEBUG     LWIP_DBG_OFF
#define API_LIB_DEBUG    LWIP_DBG_OFF
#define HTTPD_DEBUG      LWIP_DBG_OFF
#define PBUF_DEBUG       LWIP_DBG_OFF
#define IP_DEBUG         LWIP_DBG_OFF

/*
   ---------------------------------
   ---------- OS options ----------
   ---------------------------------
*/

#define osPriorityIdle        0 //< priority: idle (lowest)
#define osPriorityLow         1 //< priority: low
#define osPriorityBelowNormal 2 //< priority: below normal
#define osPriorityNormal      3 //< priority: normal (default)
#define osPriorityAboveNormal 4 //< priority: above normal
#define osPriorityHigh        5 //< priority: high
#define osPriorityRealtime    6 //< priority: realtime (highest)

#define TCPIP_THREAD_NAME         "TCP/IP"
#define TCPIP_THREAD_STACKSIZE    1024
#define TCPIP_MBOX_SIZE           50
#define DEFAULT_UDP_RECVMBOX_SIZE 100
#define DEFAULT_TCP_RECVMBOX_SIZE 100
#define DEFAULT_ACCEPTMBOX_SIZE   100
#define DEFAULT_THREAD_STACKSIZE  512
#define TCPIP_THREAD_PRIO         osPriorityHigh

#endif /* LWIP_HDR_LWIPOPTS_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
