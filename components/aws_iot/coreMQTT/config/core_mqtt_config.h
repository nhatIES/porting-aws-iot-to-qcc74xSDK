#ifndef COREMQTT_CONFIG_H
#define COREMQTT_CONFIG_H

/**************************************************/
/******* DO NOT CHANGE the following order ********/
/**************************************************/

#include "logging_levels.h"

/* Logging configuration for the MQTT library. */
#ifndef LIBRARY_LOG_NAME
    #define LIBRARY_LOG_NAME    "MQTT"
#endif

#ifndef LIBRARY_LOG_LEVEL
    #define LIBRARY_LOG_LEVEL    LOG_INFO
#endif

#include "logging_stack.h"

/************ End of logging configuration ****************/

/* coreMQTT configurations - using reasonable defaults for QCC74x SDK */
#ifndef MQTT_STATE_ARRAY_MAX_COUNT
#define MQTT_STATE_ARRAY_MAX_COUNT 10U
#endif

#ifndef MQTT_MAX_CONNACK_RECEIVE_RETRY_COUNT
#define MQTT_MAX_CONNACK_RECEIVE_RETRY_COUNT 5U
#endif

#ifndef MQTT_PINGRESP_TIMEOUT_MS
#define MQTT_PINGRESP_TIMEOUT_MS 5000U
#endif

#ifndef MQTT_RECV_POLLING_TIMEOUT_MS
#define MQTT_RECV_POLLING_TIMEOUT_MS 1000U
#endif

#ifndef MQTT_SEND_TIMEOUT_MS
#define MQTT_SEND_TIMEOUT_MS 20000U
#endif

/* coreMQTT-Agent configurations */
#ifndef MQTT_AGENT_MAX_OUTSTANDING_ACKS
#define MQTT_AGENT_MAX_OUTSTANDING_ACKS 20U
#endif

#ifndef MQTT_AGENT_MAX_EVENT_QUEUE_WAIT_TIME
#define MQTT_AGENT_MAX_EVENT_QUEUE_WAIT_TIME 1000U
#endif

#endif /* COREMQTT_CONFIG_H */