#ifndef QCC_TLS_TRANSPORT_H
#define QCC_TLS_TRANSPORT_H

#include "FreeRTOS.h"
#include "semphr.h"
#include "transport_interface.h"
#include "mbedtls/ssl.h"
#include "mbedtls/net_sockets.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/x509_crt.h"
#include "mbedtls/pk.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief TLS Transport status codes for QCC74x platform
 */
typedef enum TlsTransportStatus
{
    TLS_TRANSPORT_SUCCESS = 0,              /**< Function successfully completed. */
    TLS_TRANSPORT_INVALID_PARAMETER = -2,   /**< At least one parameter was invalid. */
    TLS_TRANSPORT_INSUFFICIENT_MEMORY = -3, /**< Insufficient memory required to establish connection. */
    TLS_TRANSPORT_INVALID_CREDENTIALS = -4, /**< Provided credentials were invalid. */
    TLS_TRANSPORT_HANDSHAKE_FAILED = -5,    /**< Performing TLS handshake with server failed. */
    TLS_TRANSPORT_INTERNAL_ERROR = -6,      /**< A call to a system API resulted in an internal error. */
    TLS_TRANSPORT_CONNECT_FAILURE = -7,     /**< Initial connection to the server failed. */
    TLS_TRANSPORT_DISCONNECT_FAILURE = -8   /**< Failed to disconnect from server. */
} TlsTransportStatus_t;

/**
 * @brief TLS connection context for QCC74x with enhanced reliability
 * 
 * This structure contains all the necessary mbedTLS contexts for secure
 * communication with proper resource management and error handling.
 */
typedef struct TlsContext
{
    mbedtls_ssl_context ssl;              /**< mbedTLS SSL context. */
    mbedtls_ssl_config conf;              /**< mbedTLS SSL configuration. */
    mbedtls_net_context server_fd;        /**< mbedTLS network context. */
    mbedtls_entropy_context entropy;      /**< mbedTLS entropy context. */
    mbedtls_ctr_drbg_context ctr_drbg;    /**< mbedTLS CTR DRBG context. */
    mbedtls_x509_crt cacert;              /**< CA certificate. */
    mbedtls_x509_crt clicert;             /**< Client certificate. */
    mbedtls_pk_context pkey;              /**< Private key. */
} TlsContext_t;

/**
 * @brief Structure to configure timeouts for individual TLS operations in milliseconds resolution.
 * 
 * Note that it uses FreeRTOS software timer internally and hence minimum resolution is the tick duration.
 * These timeouts can be specified before any receive or send operation. Timeout of 0 will act as a non-blocking mode.
 *
 * Production defaults:
 * - Connection timeout: 4 seconds
 * - Send timeout: 10 seconds  
 * - Receive timeout: 2 seconds
 */
typedef struct Timeouts
{
    uint16_t connectionTimeoutMs;    /**< Connection establishment timeout in milliseconds */
    uint16_t sendTimeoutMs;          /**< Send operation timeout in milliseconds */
    uint16_t recvTimeoutMs;          /**< Receive operation timeout in milliseconds */
} Timeouts_t;

/**
 * @brief Network context structure for QCC74x TLS transport
 * 
 * Enhanced with validation, proper error handling, and production-ready features.
 */
struct NetworkContext
{
    SemaphoreHandle_t xTlsContextSemaphore;  /**< Semaphore for thread-safe access to TLS context */
    TlsContext_t* pxTlsContext;              /**< Pointer to TLS context structure */
    const char *pcHostname;                  /**< Server host name (must not be NULL) */
    int xPort;                              /**< Server port in host-order */
    
    /* Certificate and key data with validation */
    const char *pcServerRootCA;             /**< Trusted server root certificate bytes (PEM format) */
    uint32_t pcServerRootCASize;            /**< Number of trusted server root certificate bytes */
    const char *pcClientCert;               /**< Client certificate bytes (PEM format, optional) */
    uint32_t pcClientCertSize;              /**< Number of client certificate bytes */
    const char *pcClientKey;                /**< Client certificate's private key bytes (PEM format, optional) */
    uint32_t pcClientKeySize;               /**< Number of client certificate's private key bytes */

    /**
     * @brief To use ALPN, set this to a NULL-terminated list of supported
     * protocols in decreasing order of preference.
     *
     * See [this link]
     * (https://aws.amazon.com/blogs/iot/mqtt-with-tls-client-authentication-on-port-443-why-it-is-useful-and-how-it-works/)
     * for more information.
     */
    const char ** pAlpnProtos;

    /**
     * @brief Disable server name indication (SNI) for a TLS session.
     * 
     * Set to pdTRUE to disable SNI, pdFALSE to enable (recommended for AWS IoT).
     */
    BaseType_t disableSni;
};

/**
 * @brief Establish a TLS connection with the specified endpoint.
 * 
 * Enhanced with certificate validation, improved error handling, and timeout management.
 *
 * @param[in,out] pxNetworkContext Pointer to a network context to contain the
 * initialized socket handle.
 *
 * @return #TLS_TRANSPORT_SUCCESS on success;
 *         #TLS_TRANSPORT_INVALID_PARAMETER, #TLS_TRANSPORT_INSUFFICIENT_MEMORY,
 *         #TLS_TRANSPORT_INVALID_CREDENTIALS, #TLS_TRANSPORT_HANDSHAKE_FAILED,
 *         #TLS_TRANSPORT_INTERNAL_ERROR, or #TLS_TRANSPORT_CONNECT_FAILURE on failure.
 */
TlsTransportStatus_t xTlsConnect(NetworkContext_t* pxNetworkContext );

/**
 * @brief Gracefully disconnect the TLS connection.
 * 
 * Enhanced with proper close notification and error handling.
 *
 * @param[in,out] pxNetworkContext Pointer to a network context to contain the
 * initialized socket handle.
 *
 * @return #TLS_TRANSPORT_SUCCESS on success; #TLS_TRANSPORT_INVALID_PARAMETER or
 *         #TLS_TRANSPORT_DISCONNECT_FAILURE on failure.
 */
TlsTransportStatus_t xTlsDisconnect( NetworkContext_t* pxNetworkContext );

/**
 * @brief Sends data over an established TLS connection.
 * 
 * Enhanced with improved timeout handling, attempt limiting, and better error reporting.
 *
 * @param[in] pxNetworkContext The network context containing the socket handle.
 * @param[in] pvData The data to send over the connection.
 * @param[in] uxDataLen Length of the data.
 *
 * @return Number of bytes (> 0) sent on success;
 *         0 on timeout or if no data was sent;
 *         negative value on error.
 */
int32_t qccTlsTransportSend( NetworkContext_t* pxNetworkContext,
    const void* pvData, size_t uxDataLen );

/**
 * @brief Receives data from an established TLS connection.
 * 
 * Enhanced with proper timeout handling, attempt limiting, and graceful connection closure detection.
 *
 * @param[in] pxNetworkContext The network context containing the socket handle.
 * @param[out] pvData Buffer to receive the data into.
 * @param[in] uxDataLen Length of the data buffer.
 *
 * @return Number of bytes (> 0) received on success;
 *         0 on timeout or if no data available;
 *         negative value on error or connection closed.
 */
int32_t qccTlsTransportRecv( NetworkContext_t* pxNetworkContext,
    void* pvData, size_t uxDataLen );

/**
 * @brief Set the connection timeout for TLS operations.
 * 
 * @param[in] connectionTimeoutMs Connection timeout in milliseconds.
 */
void vTlsSetConnectTimeout( uint16_t connectionTimeoutMs );

/**
 * @brief Set the send timeout for TLS send operations.
 * 
 * @param[in] sendTimeoutMs Send timeout in milliseconds.
 */
void vTlsSetSendTimeout( uint16_t sendTimeoutMs );

/**
 * @brief Set the receive timeout for TLS receive operations.
 * 
 * @param[in] recvTimeoutMs Receive timeout in milliseconds.
 */
void vTlsSetRecvTimeout( uint16_t recvTimeoutMs );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* QCC_TLS_TRANSPORT_H */ 