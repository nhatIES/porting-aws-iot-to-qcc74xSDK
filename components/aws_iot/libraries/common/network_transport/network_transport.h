/*
 * QCC74x SDK Network Transport Interface
 * Common transport layer for AWS IoT coreMQTT and coreHTTP
 */

#ifndef NETWORK_TRANSPORT_H
#define NETWORK_TRANSPORT_H

#include <FreeRTOS.h>
#include "transport_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Establish a TLS connection.
 *
 * @param[in] pxNetworkContext Network context for the connection.
 *
 * @return pdPASS on success, pdFAIL on failure.
 */
BaseType_t xTlsConnect( NetworkContext_t * pxNetworkContext );

/**
 * @brief Disconnect from TLS connection.
 *
 * @param[in] pxNetworkContext Network context for the connection.
 *
 * @return pdPASS on success, pdFAIL on failure.
 */
BaseType_t xTlsDisconnect( NetworkContext_t * pxNetworkContext );

/**
 * @brief Disconnect from TLS connection (void return).
 *
 * @param[in] pxNetworkContext Network context for the connection.
 */
void vTlsDisconnect( NetworkContext_t * pxNetworkContext );

/**
 * @brief Send data over TLS connection.
 *
 * @param[in] pxNetworkContext Network context for the connection.
 * @param[in] pvData Data to send.
 * @param[in] uxDataLen Length of data to send.
 *
 * @return Number of bytes sent on success, negative value on failure.
 */
int32_t lTlsTransportSend( NetworkContext_t * pxNetworkContext,
                          const void * pvData,
                          size_t uxDataLen );

/**
 * @brief Receive data over TLS connection.
 *
 * @param[in] pxNetworkContext Network context for the connection.
 * @param[out] pvData Buffer to receive data.
 * @param[in] uxDataLen Maximum length of data to receive.
 *
 * @return Number of bytes received on success, negative value on failure.
 */
int32_t lTlsTransportRecv( NetworkContext_t * pxNetworkContext,
                          void * pvData,
                          size_t uxDataLen );

/* Legacy ESP-style function names for compatibility */

/**
 * @brief Send data over ESP TLS connection (legacy compatibility).
 */
int32_t TlsTransportSend( NetworkContext_t * pxNetworkContext,
                            const void * pvData,
                            size_t uxDataLen );

/**
 * @brief Receive data over ESP TLS connection (legacy compatibility).
 */
int32_t espTlsTransportRecv( NetworkContext_t * pxNetworkContext,
                            void * pvData,
                            size_t uxDataLen );

#ifdef __cplusplus
}
#endif

#endif /* NETWORK_TRANSPORT_H */ 