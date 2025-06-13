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
#include "shell.h"

extern int enable_tickless;
void timerCallback(TimerHandle_t xTimer)
{
    enable_tickless = 0;
    xTimerDelete(xTimer, portMAX_DELAY);

    //if (wifi_mgmr_sta_state_get()) {
    //    wifi_mgmr_sta_ps_exit();
    //}
}

void createAndStartTimer(const char* timerName, TickType_t timerPeriod)
{
    TimerHandle_t timer = xTimerCreate(timerName,
                                       timerPeriod,
                                       pdTRUE,
                                       0,
                                       timerCallback
                                    );

    if (timer == NULL)
    {
        printf("Failed to create timer.\n");
        return;
    }

    if (xTimerStart(timer, 0) != pdPASS)
    {
        printf("Failed to start timer.\n");
        return;
    }
}

void app_pm_enter_pds15(uint32_t timeouts_ms)
{
    if (timeouts_ms) {
        TickType_t timerPeriod = pdMS_TO_TICKS(timeouts_ms);

        char timerName[32];
        snprintf(timerName, sizeof(timerName), "PwrTimer_%u", (unsigned int)timerPeriod);

        createAndStartTimer(timerName, timerPeriod);
        timeouts_ms = 0;
    }
}

int cmd_wakeup_timer(int argc, char **argv)
{
    uint32_t timeouts_ms;

    if ((argc > 1) && (argv[1] != NULL)) {
        printf("%s\r\n", argv[1]);
        timeouts_ms = atoi(argv[1]);
    } else {
        printf("Need timeouts.\r\n");
        return -1;
    }

    app_pm_enter_pds15(timeouts_ms);

    return 0;
}




#define BUFFER_SIZE 1024

typedef struct {
    char server_ip[16];
    uint16_t server_port;
} server_info_t;

void tcp_client_task(void *pvParameters)
{
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int bytes_received;
    server_info_t *server_info = (server_info_t *) pvParameters;

    printf("create tcp client task.\r\n");

    // 创建 socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Failed to create socket, errno: %d\n", errno);
        vPortFree(server_info);
        vTaskDelete(NULL);
        return;
    }

    // 设置服务器地址
    printf("set server address.\r\n");
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_info->server_port);
    if (inet_aton(server_info->server_ip, &server_addr.sin_addr) == 0) {
        printf("Invalid server IP address\n");
        close(sock);
        vPortFree(server_info);
        vTaskDelete(NULL);
        return;
    }

    // 连接到服务器
    printf("start connect server.\r\n");
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Failed to connect to server, errno: %d\n", errno);
        close(sock);
        vPortFree(server_info);
        vTaskDelete(NULL);
        return;
    }

    printf("Connected to server %s:%d\n", server_info->server_ip, server_info->server_port);

    while (1) {
        // 接收服务器发送的数据
        bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received < 0) {
            printf("Failed to receive data, errno: %d\n", errno);
            break;
        } else if (bytes_received == 0) {
            printf("Server closed connection\n");
            break;
        }

        // 处理接收到的数据
        buffer[bytes_received] = '\0';
        printf("Received from server: %s\n", buffer);
    }

    close(sock);
    vPortFree(server_info);
    printf("Socket closed, task exiting\n");
    vTaskDelete(NULL);
}

void start_tcp_client_task(const char *ip, uint16_t port)
{
    printf("start_tcp_client_task.\r\n");
    server_info_t *server_info = (server_info_t *)pvPortMalloc(sizeof(server_info_t));
    if (server_info == NULL) {
        printf("Failed to allocate memory for server_info\n");
        return;
    }

    printf("copy ip.\r\n");

    strncpy(server_info->server_ip, ip, sizeof(server_info->server_ip) - 1);
    server_info->server_ip[sizeof(server_info->server_ip) - 1] = '\0';  // 确保字符串以 NULL 结尾
    server_info->server_port = port;

    printf("start create.\r\n");
    if (xTaskCreate(tcp_client_task, "tcp_client_task", 2048, server_info, 15, NULL) != pdPASS) {
        printf("Failed to create task\n");
        vPortFree(server_info);
    }
}

static void cmd_tcp_client(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: %s <ip> <port>\n", argv[0], atoi(argv[2]));
        return;
    }
    start_tcp_client_task(argv[1], (uint16_t)atoi(argv[2]));
}

SHELL_CMD_EXPORT_ALIAS(cmd_tcp_client, tcp_client, cmd tcp client);
SHELL_CMD_EXPORT_ALIAS(cmd_wakeup_timer, wakeup_timer, wakeup timer);
