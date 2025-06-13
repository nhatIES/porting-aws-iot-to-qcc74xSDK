/*
 * AWS IoT MQTT Demo for QCC74x SDK
 * 
 * This is a simplified version of the AWS IoT MQTT demo
 * adapted for QCC74x SDK with FreeRTOS
 */

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* QCC74x SDK includes */
#include <FreeRTOS.h>
#include "task.h"
#include "log.h"
#include "qcc74x_mtimer.h"

/* Include Demo Config */
#include "demo_config.h"

/* MQTT API headers. */
#include "core_mqtt.h"

/* Network transport implementation. */
#include "network_transport.h"

/* Clock for timer. */
#include "clock.h"

/* Demo configurations */
#define MQTT_DEMO_TASK_STACK_SIZE    (4096)
#define MQTT_DEMO_TASK_PRIORITY      (16)

#define MQTT_EXAMPLE_TOPIC           "qcc74x/demo/topic"
#define MQTT_EXAMPLE_MESSAGE         "Hello from QCC74x AWS IoT Demo!"

/* Static buffer for MQTT operations */
static uint8_t mqttBuffer[1024];

/* Network context */
static NetworkContext_t networkContext;

/* MQTT context */
static MQTTContext_t mqttContext;

/**
 * @brief Simple time function for MQTT library
 */
static uint32_t getTimeMs(void)
{
    return qcc74x_mtimer_get_time_ms();
}

/**
 * @brief MQTT event callback
 */
static void mqttEventCallback(MQTTContext_t *pContext,
                             MQTTPacketInfo_t *pPacketInfo,
                             MQTTDeserializedInfo_t *pDeserializedInfo)
{
    (void)pContext;
    
    if (pPacketInfo->type == MQTT_PACKET_TYPE_PUBLISH) {
        MQTTPublishInfo_t *pPublishInfo = pDeserializedInfo->pPublishInfo;
        
        LOG_I("Received MQTT publish:");
        LOG_I("  Topic: %.*s", pPublishInfo->topicNameLength, pPublishInfo->pTopicName);
        LOG_I("  Message: %.*s", pPublishInfo->payloadLength, (char*)pPublishInfo->pPayload);
    }
}

/**
 * @brief Initialize MQTT context
 */
static int initializeMqtt(void)
{
    MQTTStatus_t mqttStatus;
    TransportInterface_t transport = {0};
    MQTTFixedBuffer_t networkBuffer = {0};
    
    /* Setup transport interface */
    transport.pNetworkContext = &networkContext;
    transport.send = TlsTransportSend;
    transport.recv = espTlsTransportRecv;
    
    /* Setup network buffer */
    networkBuffer.pBuffer = mqttBuffer;
    networkBuffer.size = sizeof(mqttBuffer);
    
    /* Initialize MQTT context */
    mqttStatus = MQTT_Init(&mqttContext,
                          &transport,
                          getTimeMs,
                          mqttEventCallback,
                          &networkBuffer);
    
    if (mqttStatus != MQTTSuccess) {
        LOG_E("Failed to initialize MQTT context: %d", mqttStatus);
        return -1;
    }
    
    LOG_I("MQTT context initialized successfully");
    return 0;
}

/**
 * @brief Connect to AWS IoT MQTT broker
 */
static int connectToAwsIot(void)
{
    MQTTStatus_t mqttStatus;
    MQTTConnectInfo_t connectInfo = {0};
    bool sessionPresent = false;
    
    /* Setup network context */
    networkContext.pcHostname = AWS_IOT_ENDPOINT;
    networkContext.xPort = AWS_MQTT_PORT;
    // TODO: Set up certificates for production use
    networkContext.pcServerRootCA = NULL;  // Set your root CA
    networkContext.pcClientCert = NULL;    // Set your client cert
    networkContext.pcClientKey = NULL;     // Set your client key
    networkContext.pcServerRootCASize = 0;
    networkContext.pcClientCertSize = 0;
    networkContext.pcClientKeySize = 0;
    networkContext.use_secure_element = false;
    networkContext.disableSni = pdFALSE;
    networkContext.pAlpnProtos = NULL;
    
    /* Setup connection parameters */
    connectInfo.cleanSession = true;
    connectInfo.pClientIdentifier = "qcc74x-demo-client";
    connectInfo.clientIdentifierLength = strlen("qcc74x-demo-client");
    connectInfo.keepAliveSeconds = 60;
    
#ifdef CLIENT_USERNAME
    connectInfo.pUserName = CLIENT_USERNAME;
    connectInfo.userNameLength = strlen(CLIENT_USERNAME);
    connectInfo.pPassword = CLIENT_PASSWORD;
    connectInfo.passwordLength = strlen(CLIENT_PASSWORD);
#endif
    
    LOG_I("Connecting to AWS IoT...");
    LOG_I("Endpoint: %s", AWS_IOT_ENDPOINT);
    LOG_I("Port: %d", AWS_MQTT_PORT);
    LOG_I("Client ID: %s", connectInfo.pClientIdentifier);
    
    /* First establish TLS connection */
    if (xTlsConnect(&networkContext) != TLS_TRANSPORT_SUCCESS) {
        LOG_E("Failed to establish TLS connection");
        return -1;
    }
    
    /* Send MQTT CONNECT packet */
    mqttStatus = MQTT_Connect(&mqttContext, &connectInfo, NULL, 1000, &sessionPresent);
    
    if (mqttStatus != MQTTSuccess) {
        LOG_E("Failed to connect to MQTT broker: %d", mqttStatus);
        return -1;
    }
    
    LOG_I("Connected to AWS IoT MQTT broker successfully");
    LOG_I("Session present: %s", sessionPresent ? "true" : "false");
    
    return 0;
}

/**
 * @brief Subscribe to a topic
 */
static int subscribeToTopic(void)
{
    MQTTStatus_t mqttStatus;
    MQTTSubscribeInfo_t subscribeInfo = {0};
    
    subscribeInfo.qos = MQTTQoS1;
    subscribeInfo.pTopicFilter = MQTT_EXAMPLE_TOPIC;
    subscribeInfo.topicFilterLength = strlen(MQTT_EXAMPLE_TOPIC);
    
    LOG_I("Subscribing to topic: %s", MQTT_EXAMPLE_TOPIC);
    
    mqttStatus = MQTT_Subscribe(&mqttContext, &subscribeInfo, 1, 1000);
    
    if (mqttStatus != MQTTSuccess) {
        LOG_E("Failed to subscribe to topic: %d", mqttStatus);
        return -1;
    }
    
    LOG_I("Subscribed to topic successfully");
    return 0;
}

/**
 * @brief Publish a message to a topic
 */
static int publishMessage(void)
{
    MQTTStatus_t mqttStatus;
    MQTTPublishInfo_t publishInfo = {0};
    
    publishInfo.qos = MQTTQoS1;
    publishInfo.retain = false;
    publishInfo.pTopicName = MQTT_EXAMPLE_TOPIC;
    publishInfo.topicNameLength = strlen(MQTT_EXAMPLE_TOPIC);
    publishInfo.pPayload = MQTT_EXAMPLE_MESSAGE;
    publishInfo.payloadLength = strlen(MQTT_EXAMPLE_MESSAGE);
    
    LOG_I("Publishing message to topic: %s", MQTT_EXAMPLE_TOPIC);
    LOG_I("Message: %s", MQTT_EXAMPLE_MESSAGE);
    
    mqttStatus = MQTT_Publish(&mqttContext, &publishInfo, 1000);
    
    if (mqttStatus != MQTTSuccess) {
        LOG_E("Failed to publish message: %d", mqttStatus);
        return -1;
    }
    
    LOG_I("Message published successfully");
    return 0;
}

/**
 * @brief MQTT demo task
 */
static void mqttDemoTask(void *pvParameters)
{
    (void)pvParameters;
    
    LOG_I("AWS IoT MQTT Demo started");
    
    /* Initialize MQTT */
    if (initializeMqtt() != 0) {
        LOG_E("Failed to initialize MQTT");
        goto exit;
    }
    
    /* Connect to AWS IoT */
    if (connectToAwsIot() != 0) {
        LOG_E("Failed to connect to AWS IoT");
        goto exit;
    }
    
    /* Subscribe to topic */
    if (subscribeToTopic() != 0) {
        LOG_E("Failed to subscribe to topic");
        goto exit;
    }
    
    /* Main loop */
    for (int i = 0; i < 10; i++) {
        /* Publish message */
        if (publishMessage() != 0) {
            LOG_E("Failed to publish message");
            break;
        }
        
        /* Process MQTT events */
        MQTT_ProcessLoop(&mqttContext);
        
        /* Wait before next publish */
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
    
    /* Disconnect */
    LOG_I("Disconnecting from AWS IoT...");
    MQTT_Disconnect(&mqttContext);
    xTlsDisconnect(&networkContext);
    
exit:
    LOG_I("AWS IoT MQTT Demo finished");
    vTaskDelete(NULL);
}

/**
 * @brief Application main entry point
 */
int main(void)
{
    BaseType_t xReturned;
    
    LOG_I("QCC74x AWS IoT MQTT Demo");
    
    /* Create MQTT demo task */
    xReturned = xTaskCreate(mqttDemoTask,
                           "mqtt_demo",
                           MQTT_DEMO_TASK_STACK_SIZE,
                           NULL,
                           MQTT_DEMO_TASK_PRIORITY,
                           NULL);
    
    if (xReturned != pdPASS) {
        LOG_E("Failed to create MQTT demo task");
        return -1;
    }
    
    /* Start FreeRTOS scheduler */
    vTaskStartScheduler();
    
    /* Should never reach here */
    return 0;
} 