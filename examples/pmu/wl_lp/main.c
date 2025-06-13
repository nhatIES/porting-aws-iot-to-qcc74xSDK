#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "mem.h"

#include <lwip/tcpip.h>
#include <lwip/sockets.h>
#include <lwip/netdb.h>

#include "export/qcc74x_fw_api.h"
#include "wifi_mgmr_ext.h"
#include "wifi_mgmr.h"

#include "qcc74x_irq.h"
#include "qcc74x_mtimer.h"
#include "board.h"
#include "qcc74x_lp.h"
#include "qcc743_pm.h"
#include "qcc74x_uart.h"
#include "qcc74x_gpio.h"
#include "qcc74x_clock.h"
#include "qcc743_glb.h"
#include "qcc743_glb_gpio.h"
#include "qcc743_hbn.h"
#include "qcc74x_rtc.h"

#include "rfparam_adapter.h"

#include "board.h"
#include "board_rf.h"
#include "shell.h"
#include "qcc74x_mtd.h"
#include "easyflash.h"
#include "app_clock_manager.h"

#define DBG_TAG "MAIN"
#include "log.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define WIFI_STACK_SIZE  (1536)
#define TASK_PRIORITY_FW (16)

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct qcc74x_device_s *uart0;

static TaskHandle_t wifi_fw_task;

static wifi_conf_t conf = {
    .country_code = "US",
};

extern void shell_init_with_task(struct qcc74x_device_s *shell);

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Functions
 ****************************************************************************/

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
    /* If the buffers to be provided to the Idle task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[1024];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = 1024;
}

int wifi_start_firmware_task(void)
{
    LOG_I("Starting wifi ...\r\n");

    /* enable wifi clock */

    GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_IP_WIFI_PHY | GLB_AHB_CLOCK_IP_WIFI_MAC_PHY | GLB_AHB_CLOCK_IP_WIFI_PLATFORM);
    GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_WIFI);

    /* set ble controller EM Size */

    GLB_Set_EM_Sel(GLB_WRAM160KB_EM0KB);

    if (0 != rfparam_init(0, NULL, 0)) {
        LOG_I("PHY RF init failed!\r\n");
        return 0;
    }

    LOG_I("PHY RF init success!\r\n");

    /* Enable wifi irq */

    extern void interrupt0_handler(void);
    qcc74x_irq_attach(WIFI_IRQn, (irq_callback)interrupt0_handler, NULL);
    qcc74x_irq_enable(WIFI_IRQn);

    xTaskCreate(wifi_main, (char *)"fw", WIFI_STACK_SIZE, NULL, TASK_PRIORITY_FW, &wifi_fw_task);

    return 0;
}

/**********************************************************
  * wifi event handler
 ***********************************************************/
void wifi_event_handler(uint32_t code)
{
    switch (code) {
        case CODE_WIFI_ON_INIT_DONE: {
            LOG_I("[APP] [EVT] %s, CODE_WIFI_ON_INIT_DONE\r\n", __func__);
            wifi_mgmr_init(&conf);
        } break;
        case CODE_WIFI_ON_MGMR_DONE: {
            LOG_I("[APP] [EVT] %s, CODE_WIFI_ON_MGMR_DONE\r\n", __func__);
        } break;
        case CODE_WIFI_ON_SCAN_DONE: {
            LOG_I("[APP] [EVT] %s, CODE_WIFI_ON_SCAN_DONE\r\n", __func__);
            wifi_mgmr_sta_scanlist();
        } break;
        case CODE_WIFI_ON_CONNECTED: {
            LOG_I("[APP] [EVT] %s, CODE_WIFI_ON_CONNECTED\r\n", __func__);
            void mm_sec_keydump();
            mm_sec_keydump();
        } break;
        case CODE_WIFI_ON_GOT_IP: {
            LOG_I("[APP] [EVT] %s, CODE_WIFI_ON_GOT_IP\r\n", __func__);
            LOG_I("[SYS] Memory left is %d Bytes\r\n", kfree_size());
        } break;
        case CODE_WIFI_ON_DISCONNECT: {
            LOG_I("[APP] [EVT] %s, CODE_WIFI_ON_DISCONNECT\r\n", __func__);
        } break;
        case CODE_WIFI_ON_AP_STARTED: {
            LOG_I("[APP] [EVT] %s, CODE_WIFI_ON_AP_STARTED\r\n", __func__);
        } break;
        case CODE_WIFI_ON_AP_STOPPED: {
            LOG_I("[APP] [EVT] %s, CODE_WIFI_ON_AP_STOPPED\r\n", __func__);
        } break;
        case CODE_WIFI_ON_AP_STA_ADD: {
            LOG_I("[APP] [EVT] [AP] [ADD] %lld\r\n", xTaskGetTickCount());
        } break;
        case CODE_WIFI_ON_AP_STA_DEL: {
            LOG_I("[APP] [EVT] [AP] [DEL] %lld\r\n", xTaskGetTickCount());
        } break;
        default: {
            LOG_I("[APP] [EVT] Unknown code %u \r\n", code);
        }
    }
}

/**********************************************************
    lp enter callback func
 **********************************************************/
static int lp_enter(void *arg)
{
    return 0;
}

/***********************************************************
    shell 
 ***********************************************************/
extern void uart_shell_isr();
extern struct qcc74x_device_s *uart_shell;
extern void vPortSetupTimerInterrupt(void);
static int lp_exit(void *arg)
{
    /* recovery system_clock_init\peripheral_clock_init\console_init*/
    board_recovery();

    GLB_Set_EM_Sel(GLB_WRAM160KB_EM0KB);

    board_rf_ctl(BRD_CTL_RF_RESET_DEFAULT, 0);

    vPortSetupTimerInterrupt();

    qcc74x_uart_rxint_mask(uart_shell, false);
    qcc74x_irq_attach(uart_shell->irq_num, uart_shell_isr, NULL);
    qcc74x_irq_enable(uart_shell->irq_num);

    return 0;
}

#ifdef CONFIG_SHELL
int cmd_wifi_lp(int argc, char **argv)
{
    int ret = 0;
    printf("enter wireless low power!\r\n");

    qcc74x_lp_init();
    // qcc74x_lp_fw_init();
    qcc74x_lp_sys_callback_register(lp_enter, NULL, lp_exit, NULL);

    while (1) {
        // lp_exit(0);
        ret = qcc74x_lp_fw_enter(&lpfw_cfg);
        if (ret < 0) {
            printf("[E]qcc74x_lpfw_enter Fail,ErrId:%d\r\n", ret);
        } else {
            printf("qcc74x_lpfw_enter Success\r\n");
        }
        arch_delay_ms(1000);
    }

    return 0;
}

extern int enable_tickless;
extern qcc74x_lp_fw_cfg_t lpfw_cfg;

static void cmd_tickless(int argc, char **argv)
{
#if 0
    uint32_t tmpVal;
    /* Set RTC compare mode, and enable rtc */
    tmpVal = QCC74x_RD_REG(HBN_BASE, HBN_CTL);
    tmpVal = tmpVal & 0xfffffff1;
    QCC74x_WR_REG(HBN_BASE, HBN_CTL, tmpVal | 0x00000003);
#endif

    if ((argc > 1) && (argv[1] != NULL)) {
        printf("%s\r\n", argv[1]);
        lpfw_cfg.dtim_origin = atoi(argv[1]);
    } else {
        lpfw_cfg.dtim_origin = 10;
    }

    qcc74x_lp_fw_bcn_loss_cfg_dtim_default(lpfw_cfg.dtim_origin);
    printf("sta_ps %ld\r\n", wifi_mgmr_sta_ps_enter());
    enable_tickless = 1;
}

static int test_tcp_keepalive(int argc, char **argv)
{
    int sockfd;
    // uint8_t *recv_buffer;
    struct sockaddr_in dest, my_addr;
    char buffer[51];
    uint32_t pck_cnt = 0;
    uint32_t pck_total = 0;

    /* Create a socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error in socket\r\n");
        return -1;
    }

    /*---Initialize server address/port struct---*/
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(50001);

    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(50001);
    inet_aton(argv[1], &dest.sin_addr);

    if (argc == 4) {
        pck_cnt = atoi(argv[3]);
        printf("keep alive pck:%ld\r\n");
    }

    printf("tcp server ip: %s\r\n", argv[1]);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) != 0) {
        printf("Error in bind\r\n");
        close(sockfd);
        return -1;
    }

    /*---Connect to server---*/
    if (connect(sockfd, (struct sockaddr *)&dest, sizeof(dest)) != 0) {
        printf("Error in connect\r\n");
        close(sockfd);
        return -1;
    }

    printf("Connect tcp server success.\r\n");

    /*---Get "Hello?"---*/
    memset(buffer, 'A', sizeof(buffer) - 1);

#ifdef LP_APP
    if (argc > 2) {
        cmd_tickless(0, NULL);
    }
#endif

    int ret = 0;

    while (1) {
        pck_total++;
        snprintf(buffer, sizeof(buffer), "SEQ = %ld  ", pck_total);

        buffer[sizeof(buffer) - 2] = '\n';
        ret = write(sockfd, buffer, sizeof(buffer) - 1);
        if (ret != sizeof(buffer) - 1) {
            printf("write error: %d\n", ret);
            break;
        }
        printf("**********************************\n");
        printf("SEQ:%ld WRITE SUCCESS %d\n", pck_total, ret);

        if (pck_cnt && (pck_total >= pck_cnt)) {
            qcc74x_pm_event_bit_set(PSM_EVENT_APP);
            break;
        }
#if 0
        ret = read(sockfd, buffer, sizeof(buffer)-1);
        buffer[sizeof(buffer) -1] = 0;
        printf("read ret: %d, %s\r\n", ret, buffer);
#endif
        vTaskDelay(pdMS_TO_TICKS(30 * 1000));
    }

    close(sockfd);
    return 0;
}

static void cmd_hbn_test(int argc, char **argv)
{
    if (argc <= 5) {
        qcc74x_lp_hbn_fw_cfg_t hbn_test_cfg = {
            .hbn_sleep_cnt = 32768 * 5,
            .hbn_level = 0,
        };
        qcc74x_lp_hbn_enter(&hbn_test_cfg);
    } else {
        if ((argv[1] != NULL) && (argv[2] != NULL) && (argv[3] != NULL)) {
            printf("wdt_pin %d\r\n", atoi(argv[1]));
            printf("max_continue_times %d\r\n", atoi(argv[3]));
            qcc74x_lp_hbn_init(1, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
        }

        if ((argv[4] != NULL) && (argv[5] != NULL)) {
            printf("hbn sleep %ds\r\n", atoi(argv[4]));
            printf("hbn_level %d\r\n", atoi(argv[5]));
            vTaskDelay(1);
            qcc74x_lp_hbn_fw_cfg_t hbn_test_cfg = {
                .hbn_sleep_cnt = 32768 * atoi(argv[4]),
                .hbn_level = atoi(argv[5]),
            };
            qcc74x_lp_hbn_enter(&hbn_test_cfg);
        }
    }
}

static void cmd_hbn_time(int argc, char **argv)
{
    if (argc != 2) {
        printf("arg error, please input :hbn_time [time_sec]\r\n");
        return;
    }
    qcc74x_lp_hbn_fw_cfg_t hbn_test_cfg = {
        .hbn_sleep_cnt = 32768 * atoi(argv[1]), // s
        .hbn_level = 0,
    };

    qcc74x_lp_hbn_init(0,0,0,0);
    qcc74x_lp_hbn_enter(&hbn_test_cfg);
}

static void cmd_io_dbg(int argc, char **argv)
{
    if (argc != 2) {
        printf("cmd_io_dbg err\r\n");
        return;
    }

    if (atoi(argv[1]) <= 34) {
        iot2lp_para->debug_io = atoi(argv[1]);
    } else {
        iot2lp_para->debug_io = 0xFF;
    }
}


void app_arp_send(void)
{
    if (!wifi_mgmr_sta_state_get()) {
        return;
    }

    if (ip4_addr_isany_val(*netif_ip4_addr(netif_default))) {
        printf("IP address not assigned. ARP announcement skipped.\n");
        return;
    }

    LOCK_TCPIP_CORE();
    do {
        ip_addr_t src_ip = netif_default->ip_addr;
        ip_addr_t dest_ip;
        ip_addr_copy(dest_ip, src_ip);
        err_t result = etharp_request(netif_default, &dest_ip);

        if (result != ERR_OK) {
            printf("Failed to send ARP request. Error: %d\n", result);
        }
    } while (0);
    UNLOCK_TCPIP_CORE();
}

TimerHandle_t xArpTimer = NULL;
static void arp_send(TimerHandle_t xTimer) {

    app_arp_send();
}

int app_pm_create_arp_announce_timer(uint32_t seconds)
{
    if (xArpTimer) {
        return -1;
    }

    app_arp_send();

    xArpTimer = xTimerCreate("traffic probe",  pdMS_TO_TICKS(seconds * 1000), pdTRUE, (void*)0, arp_send);
    xTimerStart(xArpTimer, 0);

    return 0;
}

int app_pm_delete_arp_announce_timer(void)
{
    if (xArpTimer) {
        xTimerStop(xArpTimer, 0);
        xTimerDelete(xArpTimer, portMAX_DELAY);
        xArpTimer = NULL;
        printf("Delete arp timer.\r\n");
    } else {
        printf("Arp timer has not been create.\r\n");
    }

    return 0;
}

static void cmd_create_arp_timer(int argc, char **argv)
{
    if (argc != 2) {
        printf("Need param\r\n");
        return;
    }

    printf("set arp interval :%d s\r\n",atoi(argv[1]));
    app_pm_create_arp_announce_timer(atoi(argv[1]));

    return;
}

static void cmd_delete_arp_timer(int argc, char **argv)
{
    app_pm_delete_arp_announce_timer();
    return;
}

static void cmd_set_clock_source(int argc, char **argv)
{
    uint8_t source;

    // Check argument count
    if (argc != 2) {
        printf("Usage: set_clock_source <source>\r\n");
        printf("  1: Internal RC oscillator\r\n");
        printf("  2: External passive crystal\r\n");
        printf("  3: External active crystal\r\n");
        return;
    }

    // Parse source value from argument
    source = (uint8_t)atoi(argv[1]);

    // Validate source value
    if (source < 1 || source > 3) {
        printf("Error: Invalid clock source value. Must be 1, 2, or 3.\r\n");
        return;
    }

    // Call the API function to set clock source
    int ret = app_set_clock_source(source);
    if (ret == 0) {
        printf("Clock source updated to %d. System will restart...\r\n", source);
        // The system should reboot automatically after this
    } else {
        printf("Failed to set clock source, error code: %d\r\n", ret);
    }
}

static void cmd_get_clock_source(int argc, char **argv)
{
    uint8_t source;
    int ret;

    // Call the API function to get current clock source
    ret = app_get_clock_source(&source);

    if (ret == 0) {
        printf("Current clock source: %d (", source);

        // Print descriptive name of the clock source
        switch (source) {
            case 1:
                printf("Internal RC oscillator");
                break;
            case 2:
                printf("External passive crystal");
                break;
            case 3:
                printf("External active crystal");
                break;
            default:
                printf("Unknown");
                break;
        }
        printf(")\r\n");
    } else {
        printf("Failed to get clock source, error code: %d\r\n", ret);
        printf("Using default source: Internal RC oscillator\r\n");
    }
}

// Export the commands to shell
SHELL_CMD_EXPORT_ALIAS(cmd_set_clock_source, set_clock_source, Set system clock source (1:RC, 2:Passive XTAL, 3:Active XTAL));
SHELL_CMD_EXPORT_ALIAS(cmd_get_clock_source, get_clock_source, Get current system clock source);
SHELL_CMD_EXPORT_ALIAS(cmd_tickless, tickless, cmd tickless);
SHELL_CMD_EXPORT_ALIAS(cmd_wifi_lp, wifi_lp_test, wifi low power test);
SHELL_CMD_EXPORT_ALIAS(test_tcp_keepalive, lpfw_tcp_keepalive, tcp keepalive test);
SHELL_CMD_EXPORT_ALIAS(cmd_hbn_test, hbn_test, hbn test);
SHELL_CMD_EXPORT_ALIAS(cmd_hbn_time, hbn_time, hbn_time [sec]);
SHELL_CMD_EXPORT_ALIAS(cmd_io_dbg, io_debug, cmd io_debug);
SHELL_CMD_EXPORT_ALIAS(cmd_create_arp_timer, create_arp_timer, cmd create arp timer);
SHELL_CMD_EXPORT_ALIAS(cmd_delete_arp_timer, delete_arp_timer, cmd delete arp timer);

#endif

/**********************************************************
    proc_hellow_entry task func
 **********************************************************/
#if 0
static void proc_hellow_entry(void *pvParameters)
{
    vTaskDelay(500);

    while (1) {
        printf("%s: RISC-V rv64imafc\r\n", __func__);

#ifdef LP_APP
        qcc74x_lp_info_t lp_info;
        /* get lp info */
        qcc74x_lp_info_get(&lp_info);
        /* clear lp info */
        qcc74x_lp_info_clear();

        printf("\r\nVirtual time: %llu us\r\n", qcc74x_lp_get_virtual_us());
        printf("LowPower info dump:\r\n");
        printf("LPFW try recv bcn: %d, loss %d\r\n", lp_info.lpfw_recv_cnt, lp_info.lpfw_loss_cnt);
        printf("Total time %lldms\r\n", lp_info.time_total_us / 1000);
        printf("PDS sleep: %lldms\r\n", lp_info.sleep_pds_us / 1000);
        printf("LPFW active: %lldms\r\n", lp_info.active_lpfw_us / 1000);
        printf("APP active: %lldms\r\n", lp_info.active_app_us / 1000);

        uint64_t current = (lp_info.sleep_pds_us * 40 + lp_info.active_lpfw_us * 40000 + lp_info.active_app_us * 65000) / lp_info.time_total_us;
        printf("Predict current: %llduA\r\n", current);
#endif

        vTaskDelay(10000);
    }
    vTaskDelete(NULL);
}
#endif

void tcpip_init_done(void *arg)
{
}

int main(void)
{
    uint8_t soc_v, rt_v, aon_v;

    board_init();

    uart0 = qcc74x_device_get_by_name("uart0");
    shell_init_with_task(uart0);

    tcpip_init(tcpip_init_done, NULL);
    wifi_start_firmware_task();

    hal_pm_ldo11_cfg(PM_PDS_LDO_LEVEL_SOC_DEFAULT, PM_PDS_LDO_LEVEL_RT_DEFAULT, PM_PDS_LDO_LEVEL_AON_DEFAULT);
    hal_pm_ldo11_cfg_get(&soc_v, &rt_v, &aon_v);
    printf("SOC:%d RT:%d AON:%d\r\n", soc_v, rt_v, aon_v);

    HBN_Enable_RTC_Counter();
    pm_rc32k_auto_cal_init();

    qcc74x_mtd_init();
    easyflash_init();

#ifdef LP_APP
#if defined(CFG_QCC74x_WIFI_PS_ENABLE) || defined(CFG_WIFI_PDS_RESUME)
    qcc74x_lp_init();
#endif
    qcc74x_lp_sys_callback_register(lp_enter, NULL, lp_exit, NULL);
#endif

    app_clock_init();

#if 0
    printf("[OS] Starting proc_hellow_entry task...\r\n");
    xTaskCreate(proc_hellow_entry, (char*)"hellow", 512, NULL, 10, NULL);
#endif

    vTaskStartScheduler();

    while (1) {
    }
}
