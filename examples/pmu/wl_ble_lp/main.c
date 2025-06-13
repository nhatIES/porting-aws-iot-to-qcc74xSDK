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

#include "bluetooth.h"
#include "conn.h"
#include "conn_internal.h"
#include "btble_lib_api.h"
#include "qcc743_glb.h"
#include "hci_driver.h"
#include "hci_core.h"

//#include "qcc74x_mtd.h"
//#include "easyflash.h"

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

TaskHandle_t wifi_fw_task;
static TaskHandle_t app_start_handle;
struct bt_conn *bleapp_default_conn;

static wifi_conf_t conf = {
    .country_code = "US",
};

static void ble_connected(struct bt_conn *conn, u8_t err)
{
    if(err || conn->type != BT_CONN_TYPE_LE)
    {
        return;
    }
    if (!bleapp_default_conn) {
        bleapp_default_conn = conn;
    }
}

static void ble_disconnected(struct bt_conn *conn, u8_t reason)
{
    int ret;
    if(conn->type != BT_CONN_TYPE_LE)
    {
        return;
    }
    if (bleapp_default_conn == conn) {
        bleapp_default_conn = NULL;
    }
    printf("%s",__func__);
}
static void ble_conn_param_updated(struct bt_conn *conn, u16_t interval,
			     u16_t latency, u16_t timeout)
{
    if(conn == bleapp_default_conn)
    {
        printf("%s: int 0x%04x lat %d to %d \r\n", __func__, interval, latency, timeout);
    }
}
static struct bt_conn_cb ble_conn_callbacks = {
    .connected  =   ble_connected,
    .disconnected   =   ble_disconnected,
    .le_param_updated = ble_conn_param_updated,
};

void bt_enable_cb(int err)
{
    if (!err) {
        bt_addr_le_t bt_addr;
        bt_get_local_public_address(&bt_addr);
        printf("BD_ADDR:(MSB)%02x:%02x:%02x:%02x:%02x:%02x(LSB) \r\n",
                bt_addr.a.val[5], bt_addr.a.val[4], bt_addr.a.val[3], bt_addr.a.val[2], bt_addr.a.val[1], bt_addr.a.val[0]);
        bt_conn_cb_register(&ble_conn_callbacks);
        //ble_cli_register();
    }
}

static void app_start_task(void *pvParameters)
{
    btble_controller_init(configMAX_PRIORITIES - 1);
    hci_driver_init();
    bt_enable(bt_enable_cb);

    vTaskDelete(NULL);
}

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

    //GLB_Set_EM_Sel(GLB_WRAM160KB_EM0KB);

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

static void set_cpu_bclk_80M_and_gate_clk(void)
{
    uint32_t tmpVal = 0;

    GLB_Set_MCU_System_CLK_Div(0, 3);
    CPU_Set_MTimer_CLK(ENABLE, QCC74x_MTIMER_SOURCE_CLOCK_MCU_CLK, Clock_System_Clock_Get(QCC74x_SYSTEM_CLOCK_MCU_CLK) / 1000000 - 1);

    /* clk gate,except DMA&CPU&UART0&SF&EMI&WIFI&EFUSE */
    tmpVal = 0;
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_M_CPU, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_M_DMA, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_M_SEC, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_M_SDU, 1);
    QCC74x_WR_REG(GLB_BASE, GLB_CGEN_CFG0,tmpVal);

    tmpVal = 0;
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_S1_EF_CTRL, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_S1_SF_CTRL, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_S1_DMA, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_S1A_UART0, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_S1A_UART1, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_S1_SEC_ENG, 1);
    QCC74x_WR_REG(GLB_BASE, GLB_CGEN_CFG1,tmpVal);

    tmpVal = 0;
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_S2_WIFI, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_S1_EXT_EMI_MISC, 1);
    tmpVal = QCC74x_SET_REG_BITS_VAL(tmpVal, GLB_CGEN_S1_EXT_PIO, 1);

    QCC74x_WR_REG(GLB_BASE, GLB_CGEN_CFG2, tmpVal);
}

GLB_GPIO_Type pinList[4] = {
    GLB_GPIO_PIN_0,
    GLB_GPIO_PIN_1,
    GLB_GPIO_PIN_2,
    GLB_GPIO_PIN_3,
};

static int lp_exit(void *arg)
{
    set_cpu_bclk_80M_and_gate_clk();

    /* recovery system_clock_init\peripheral_clock_init\console_init*/
    board_recovery();

    //GLB_Set_EM_Sel(GLB_WRAM160KB_EM0KB);
    //qcc74x_sys_em_config();

    //board_rf_ctl(BRD_CTL_RF_RESET_DEFAULT, 0);

    vPortSetupTimerInterrupt();

    qcc74x_uart_rxint_mask(uart_shell, false);
    qcc74x_irq_attach(uart_shell->irq_num, uart_shell_isr, NULL);
    qcc74x_irq_enable(uart_shell->irq_num);

    //GLB_GPIO_Func_Init(GPIO_FUN_JTAG, pinList, 4);

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
        printf("Clock source updated to %d.\r\n", source);
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

SHELL_CMD_EXPORT_ALIAS(cmd_tickless, tickless, cmd tickless);
SHELL_CMD_EXPORT_ALIAS(cmd_wifi_lp, wifi_lp_test, wifi low power test);
SHELL_CMD_EXPORT_ALIAS(test_tcp_keepalive, lpfw_tcp_keepalive, tcp keepalive test);
SHELL_CMD_EXPORT_ALIAS(cmd_hbn_test, hbn_test, hbn test);
SHELL_CMD_EXPORT_ALIAS(cmd_io_dbg, io_debug, cmd io_debug);
SHELL_CMD_EXPORT_ALIAS(cmd_set_clock_source, set_clock_source, Set system clock source (1:RC, 2:Passive XTAL, 3:Active XTAL));
SHELL_CMD_EXPORT_ALIAS(cmd_get_clock_source, get_clock_source, Get current system clock source);
#endif

/**********************************************************
    proc_hellow_entry task func
 **********************************************************/
#if 0
static void proc_hellow_entry(void *pvParameters)
{
    vTaskDelay(500);

    while (1) {
        printf("task run.\r\n");
        vTaskDelay(5000);
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
    app_set_clock_source(CLOCK_SOURCE_PASSIVE);
    app_clock_init();

    if (0 != rfparam_init(0, NULL, 0)) {
        printf("PHY RF init failed!\r\n");
        return 0;
    }

#if 0
    printf("[OS] Starting proc_hellow_entry task...\r\n");
    xTaskCreate(proc_hellow_entry, (char*)"hellow", 512, NULL, 10, NULL);
#endif

    xTaskCreate(app_start_task, (char *)"app_start", 1024, NULL, 15, &app_start_handle);

    vTaskStartScheduler();

    while (1) {
    }
}
