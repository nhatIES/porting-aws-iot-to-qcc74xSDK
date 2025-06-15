#include "FreeRTOS.h"
#include "task.h" 
#include "semphr.h"
#include <string.h>
#include <stdio.h>
#include "network_transport.h"

/* mbedTLS includes */
#include "mbedtls/ssl.h"
#include "mbedtls/net_sockets.h"
#include "mbedtls/entropy.h" 
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/x509_crt.h"
#include "mbedtls/pk.h"
#include "mbedtls/error.h"
#include "mbedtls/debug.h"

/* LWIP includes for socket options */
#include "lwip/sockets.h"
#include "lwip/netdb.h"

#define TAG "network_transport"
#define DEBUG_LEVEL 1
#define MAX_CERT_SIZE (8192)  /* Maximum certificate size in bytes */
#define SOCKET_RECV_TIMEOUT_MS (2000)  /* Socket receive timeout */
#define SOCKET_SEND_TIMEOUT_MS (5000)  /* Socket send timeout */

Timeouts_t timeouts = { .connectionTimeoutMs = 4000, .sendTimeoutMs = 10000, .recvTimeoutMs = 2000 };

static void my_debug(void *ctx, int level, const char *file, int line, const char *str)
{
    (void) ctx;
    (void) level;
    printf("%s:%04d: %s", file, line, str);
}

/**
 * @brief Setup socket timeouts for reliable networking
 */
static int setupSocketTimeouts(mbedtls_net_context *net_ctx, uint32_t timeoutMs)
{
    if (net_ctx == NULL || net_ctx->fd < 0) {
        return -1;
    }

    struct timeval timeout;
    timeout.tv_sec = timeoutMs / 1000;
    timeout.tv_usec = (timeoutMs % 1000) * 1000;
    
    if (setsockopt(net_ctx->fd, SOL_SOCKET, SO_RCVTIMEO, 
                   &timeout, sizeof(timeout)) < 0) {
        printf("Failed to set socket receive timeout\n");
        return -1;
    }
    
    if (setsockopt(net_ctx->fd, SOL_SOCKET, SO_SNDTIMEO,
                   &timeout, sizeof(timeout)) < 0) {
        printf("Failed to set socket send timeout\n");
        return -1;
    }
    
    return 0;
}

/**
 * @brief Validate certificate data before parsing
 */
static TlsTransportStatus_t validateCertificateData(const char* certData, uint32_t certSize, const char* certType)
{
    if (certData == NULL) {
        printf("Certificate data is NULL for %s\n", certType);
        return TLS_TRANSPORT_INVALID_CREDENTIALS;
    }
    
    if (certSize == 0) {
        printf("Certificate size is 0 for %s\n", certType);
        return TLS_TRANSPORT_INVALID_CREDENTIALS;
    }
    
    if (certSize > MAX_CERT_SIZE) {
        printf("Certificate size %u exceeds maximum %d for %s\n", certSize, MAX_CERT_SIZE, certType);
        return TLS_TRANSPORT_INVALID_CREDENTIALS;
    }
    
    /* Basic PEM format validation */
    if (strstr(certData, "-----BEGIN") == NULL || strstr(certData, "-----END") == NULL) {
        printf("Certificate does not appear to be in PEM format for %s\n", certType);
        return TLS_TRANSPORT_INVALID_CREDENTIALS;
    }
    
    return TLS_TRANSPORT_SUCCESS;
}

static TlsTransportStatus_t initializeTlsContext(TlsContext_t* pxTlsContext)
{
    int ret = 0;
    
    if (pxTlsContext == NULL) {
        return TLS_TRANSPORT_INVALID_PARAMETER;
    }
    
    /* Initialize the RNG and the session data */
    mbedtls_ssl_init(&pxTlsContext->ssl);
    mbedtls_ssl_config_init(&pxTlsContext->conf);
    mbedtls_net_init(&pxTlsContext->server_fd);
    mbedtls_entropy_init(&pxTlsContext->entropy);
    mbedtls_ctr_drbg_init(&pxTlsContext->ctr_drbg);
    mbedtls_x509_crt_init(&pxTlsContext->cacert);
    mbedtls_x509_crt_init(&pxTlsContext->clicert);
    mbedtls_pk_init(&pxTlsContext->pkey);

    /* Seed the RNG */
    if ((ret = mbedtls_ctr_drbg_seed(&pxTlsContext->ctr_drbg, mbedtls_entropy_func, 
                                     &pxTlsContext->entropy, NULL, 0)) != 0)
    {
        printf("mbedtls_ctr_drbg_seed returned -0x%04x\n", (unsigned int)(-ret));
        return TLS_TRANSPORT_INTERNAL_ERROR;
    }

    return TLS_TRANSPORT_SUCCESS;
}

static void cleanupTlsContext(TlsContext_t* pxTlsContext)
{
    if (pxTlsContext == NULL) {
        return;
    }
    
    mbedtls_ssl_free(&pxTlsContext->ssl);
    mbedtls_ssl_config_free(&pxTlsContext->conf);
    mbedtls_net_free(&pxTlsContext->server_fd);
    mbedtls_entropy_free(&pxTlsContext->entropy);
    mbedtls_ctr_drbg_free(&pxTlsContext->ctr_drbg);
    mbedtls_x509_crt_free(&pxTlsContext->cacert);
    mbedtls_x509_crt_free(&pxTlsContext->clicert);
    mbedtls_pk_free(&pxTlsContext->pkey);
}

void vTlsSetConnectTimeout( uint16_t connectionTimeoutMs )
{
    timeouts.connectionTimeoutMs = connectionTimeoutMs;
}

void vTlsSetSendTimeout( uint16_t sendTimeoutMs )
{
    timeouts.sendTimeoutMs = sendTimeoutMs;
}

void vTlsSetRecvTimeout( uint16_t recvTimeoutMs )
{
    timeouts.recvTimeoutMs = recvTimeoutMs;
}

TlsTransportStatus_t xTlsConnect(NetworkContext_t* pxNetworkContext)
{
    TlsTransportStatus_t xResult = TLS_TRANSPORT_CONNECT_FAILURE;
    int ret = 0;
    char port_str[6];
    TlsContext_t* pxTlsContext = NULL;

    if (pxNetworkContext == NULL)
    {
        printf("NetworkContext is NULL\n");
        return TLS_TRANSPORT_INVALID_PARAMETER;
    }

    if (pxNetworkContext->pcHostname == NULL)
    {
        printf("Hostname is NULL\n");
        return TLS_TRANSPORT_INVALID_PARAMETER;
    }

    /* Validate certificates before proceeding */
    if (pxNetworkContext->pcServerRootCA != NULL)
    {
        xResult = validateCertificateData(pxNetworkContext->pcServerRootCA, 
                                          pxNetworkContext->pcServerRootCASize, 
                                          "Root CA");
        if (xResult != TLS_TRANSPORT_SUCCESS)
        {
            return xResult;
        }
    }

    if (pxNetworkContext->pcClientCert != NULL)
    {
        xResult = validateCertificateData(pxNetworkContext->pcClientCert,
                                          pxNetworkContext->pcClientCertSize,
                                          "Client Certificate");
        if (xResult != TLS_TRANSPORT_SUCCESS)
        {
            return xResult;
        }
    }

    /* Allocate TLS context */
    pxTlsContext = pvPortMalloc(sizeof(TlsContext_t));
    if (pxTlsContext == NULL)
    {
        printf("Failed to allocate TLS context\n");
        return TLS_TRANSPORT_INSUFFICIENT_MEMORY;
    }

    if (xSemaphoreTake(pxNetworkContext->xTlsContextSemaphore, pdMS_TO_TICKS(timeouts.connectionTimeoutMs)) == pdTRUE)
    {
        pxNetworkContext->pxTlsContext = pxTlsContext;

        /* Initialize TLS context */
        if (initializeTlsContext(pxTlsContext) != TLS_TRANSPORT_SUCCESS)
        {
            printf("Failed to initialize TLS context\n");
            xResult = TLS_TRANSPORT_INTERNAL_ERROR;
            goto cleanup;
        }

        /* Convert port to string */
        snprintf(port_str, sizeof(port_str), "%d", pxNetworkContext->xPort);

        /* Start the connection */
        printf("Connecting to %s:%s\n", pxNetworkContext->pcHostname, port_str);
        if ((ret = mbedtls_net_connect(&pxTlsContext->server_fd, 
                                       pxNetworkContext->pcHostname,
                                       port_str, MBEDTLS_NET_PROTO_TCP)) != 0)
        {
            printf("mbedtls_net_connect returned -0x%04x\n", (unsigned int)(-ret));
            xResult = TLS_TRANSPORT_CONNECT_FAILURE;
            goto cleanup;
        }

        /* Setup socket timeouts for reliable operation */
        if (setupSocketTimeouts(&pxTlsContext->server_fd, SOCKET_RECV_TIMEOUT_MS) != 0)
        {
            printf("Warning: Failed to setup socket timeouts\n");
            /* Continue as this is not critical */
        }

        /* Set socket to non-blocking mode - this is now more robust */
        if ((ret = mbedtls_net_set_nonblock(&pxTlsContext->server_fd)) != 0)
        {
            printf("mbedtls_net_set_nonblock returned -0x%04x\n", (unsigned int)(-ret));
            /* For production, we need reliable non-blocking behavior */
            xResult = TLS_TRANSPORT_INTERNAL_ERROR;
            goto cleanup;
        }

        /* Setup SSL */
        if ((ret = mbedtls_ssl_config_defaults(&pxTlsContext->conf,
                                               MBEDTLS_SSL_IS_CLIENT,
                                               MBEDTLS_SSL_TRANSPORT_STREAM,
                                               MBEDTLS_SSL_PRESET_DEFAULT)) != 0)
        {
            printf("mbedtls_ssl_config_defaults returned -0x%04x\n", (unsigned int)(-ret));
            xResult = TLS_TRANSPORT_INTERNAL_ERROR;
            goto cleanup;
        }

        /* Set authentication mode */
        mbedtls_ssl_conf_authmode(&pxTlsContext->conf, MBEDTLS_SSL_VERIFY_REQUIRED);
        mbedtls_ssl_conf_ca_chain(&pxTlsContext->conf, &pxTlsContext->cacert, NULL);
        mbedtls_ssl_conf_rng(&pxTlsContext->conf, mbedtls_ctr_drbg_random, &pxTlsContext->ctr_drbg);
        mbedtls_ssl_conf_dbg(&pxTlsContext->conf, my_debug, NULL);

        /* Load CA certificate */
        if (pxNetworkContext->pcServerRootCA != NULL)
        {
            ret = mbedtls_x509_crt_parse(&pxTlsContext->cacert,
                                         (const unsigned char *)pxNetworkContext->pcServerRootCA,
                                         pxNetworkContext->pcServerRootCASize);
            if (ret < 0)
            {
                printf("mbedtls_x509_crt_parse ca returned -0x%04x\n", (unsigned int)(-ret));
                xResult = TLS_TRANSPORT_INVALID_CREDENTIALS;
                goto cleanup;
            }
            printf("Loaded CA certificate (%d bytes)\n", pxNetworkContext->pcServerRootCASize);
        }

        /* Load client certificate and private key */
        if (pxNetworkContext->pcClientCert != NULL && pxNetworkContext->pcClientKey != NULL)
        {
            /* Validate client key as well */
            xResult = validateCertificateData(pxNetworkContext->pcClientKey,
                                              pxNetworkContext->pcClientKeySize,
                                              "Client Private Key");
            if (xResult != TLS_TRANSPORT_SUCCESS)
            {
                goto cleanup;
            }

            ret = mbedtls_x509_crt_parse(&pxTlsContext->clicert,
                                         (const unsigned char *)pxNetworkContext->pcClientCert,
                                         pxNetworkContext->pcClientCertSize);
            if (ret != 0)
            {
                printf("mbedtls_x509_crt_parse client cert returned -0x%04x\n", (unsigned int)(-ret));
                xResult = TLS_TRANSPORT_INVALID_CREDENTIALS;
                goto cleanup;
            }

            ret = mbedtls_pk_parse_key(&pxTlsContext->pkey,
                                       (const unsigned char *)pxNetworkContext->pcClientKey,
                                       pxNetworkContext->pcClientKeySize,
                                       NULL, 0);
            if (ret != 0)
            {
                printf("mbedtls_pk_parse_key returned -0x%04x\n", (unsigned int)(-ret));
                xResult = TLS_TRANSPORT_INVALID_CREDENTIALS;
                goto cleanup;
            }

            if ((ret = mbedtls_ssl_conf_own_cert(&pxTlsContext->conf,
                                                 &pxTlsContext->clicert,
                                                 &pxTlsContext->pkey)) != 0)
            {
                printf("mbedtls_ssl_conf_own_cert returned -0x%04x\n", (unsigned int)(-ret));
                xResult = TLS_TRANSPORT_INVALID_CREDENTIALS;
                goto cleanup;
            }
            printf("Loaded client certificate and private key\n");
        }

        /* Setup SSL context */
        if ((ret = mbedtls_ssl_setup(&pxTlsContext->ssl, &pxTlsContext->conf)) != 0)
        {
            printf("mbedtls_ssl_setup returned -0x%04x\n", (unsigned int)(-ret));
            xResult = TLS_TRANSPORT_INTERNAL_ERROR;
            goto cleanup;
        }

        /* Set hostname for SNI */
        if (!pxNetworkContext->disableSni)
        {
            if ((ret = mbedtls_ssl_set_hostname(&pxTlsContext->ssl,
                                                pxNetworkContext->pcHostname)) != 0)
            {
                printf("mbedtls_ssl_set_hostname returned -0x%04x\n", (unsigned int)(-ret));
                xResult = TLS_TRANSPORT_INTERNAL_ERROR;
                goto cleanup;
            }
        }

        /* Set ALPN protocols */
        if (pxNetworkContext->pAlpnProtos != NULL)
        {
            if ((ret = mbedtls_ssl_conf_alpn_protocols(&pxTlsContext->conf,
                                                       pxNetworkContext->pAlpnProtos)) != 0)
            {
                printf("mbedtls_ssl_conf_alpn_protocols returned -0x%04x\n", (unsigned int)(-ret));
                xResult = TLS_TRANSPORT_INTERNAL_ERROR;
                goto cleanup;
            }
            printf("ALPN protocols configured\n");
        }

        mbedtls_ssl_set_bio(&pxTlsContext->ssl, &pxTlsContext->server_fd,
                            mbedtls_net_send, mbedtls_net_recv, NULL);

        /* Perform the SSL/TLS handshake with improved timeout handling */
        printf("Starting TLS handshake...\n");
        TickType_t startTime = xTaskGetTickCount();
        uint32_t handshakeAttempts = 0;
        const uint32_t maxHandshakeAttempts = 100; /* Prevent infinite loop */
        
        while ((ret = mbedtls_ssl_handshake(&pxTlsContext->ssl)) != 0)
        {
            if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
            {
                printf("mbedtls_ssl_handshake returned -0x%04x\n", (unsigned int)(-ret));
                xResult = TLS_TRANSPORT_HANDSHAKE_FAILED;
                goto cleanup;
            }
            
            /* Check for timeout */
            TickType_t elapsedTime = xTaskGetTickCount() - startTime;
            if (elapsedTime > pdMS_TO_TICKS(timeouts.connectionTimeoutMs))
            {
                printf("TLS handshake timeout after %u ms\n", (unsigned int)(elapsedTime * portTICK_PERIOD_MS));
                xResult = TLS_TRANSPORT_HANDSHAKE_FAILED;
                goto cleanup;
            }
            
            /* Prevent infinite handshake attempts */
            if (++handshakeAttempts > maxHandshakeAttempts)
            {
                printf("TLS handshake max attempts exceeded\n");
                xResult = TLS_TRANSPORT_HANDSHAKE_FAILED;
                goto cleanup;
            }
            
            /* Small delay to prevent busy loop and allow other tasks to run */
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        /* Verify the server certificate */
        uint32_t flags = mbedtls_ssl_get_verify_result(&pxTlsContext->ssl);
        if (flags != 0)
        {
            printf("Server certificate verification failed with flags: 0x%08x\n", (unsigned int)flags);
            xResult = TLS_TRANSPORT_HANDSHAKE_FAILED;
            goto cleanup;
        }

        printf("TLS handshake completed successfully\n");
        xResult = TLS_TRANSPORT_SUCCESS;

cleanup:
        if (xResult != TLS_TRANSPORT_SUCCESS && pxTlsContext != NULL)
        {
            cleanupTlsContext(pxTlsContext);
            vPortFree(pxTlsContext);
            pxNetworkContext->pxTlsContext = NULL;
        }
        xSemaphoreGive(pxNetworkContext->xTlsContextSemaphore);
    }
    else
    {
        printf("Failed to acquire TLS context semaphore\n");
        vPortFree(pxTlsContext);
        xResult = TLS_TRANSPORT_CONNECT_FAILURE;
    }

    return xResult;
}

TlsTransportStatus_t xTlsDisconnect(NetworkContext_t* pxNetworkContext)
{
    TlsTransportStatus_t xResult = TLS_TRANSPORT_SUCCESS;

    if (pxNetworkContext == NULL)
    {
        return TLS_TRANSPORT_INVALID_PARAMETER;
    }

    if (xSemaphoreTake(pxNetworkContext->xTlsContextSemaphore, pdMS_TO_TICKS(timeouts.connectionTimeoutMs)) == pdTRUE)
    {
        if (pxNetworkContext->pxTlsContext == NULL)
        {
            xResult = TLS_TRANSPORT_SUCCESS;
        }
        else
        {
            TlsContext_t* pxTlsContext = pxNetworkContext->pxTlsContext;
            
            /* Send close notify to peer */
            int ret = mbedtls_ssl_close_notify(&pxTlsContext->ssl);
            if (ret != 0)
            {
                printf("mbedtls_ssl_close_notify returned -0x%04x\n", (unsigned int)(-ret));
                /* Continue with cleanup even if close_notify fails */
            }
            
            /* Cleanup TLS context */
            cleanupTlsContext(pxTlsContext);
            vPortFree(pxTlsContext);
            pxNetworkContext->pxTlsContext = NULL;
            
            printf("TLS connection disconnected\n");
        }
        xSemaphoreGive(pxNetworkContext->xTlsContextSemaphore);
    }
    else
    {
        printf("Failed to acquire semaphore for disconnect\n");
        xResult = TLS_TRANSPORT_DISCONNECT_FAILURE;
    }

    return xResult;
}

int32_t qccTlsTransportSend(NetworkContext_t* pxNetworkContext,
                            const void* pvData, size_t uxDataLen)
{
    int32_t lBytesSent = -1;

    if ((pvData == NULL) || (uxDataLen == 0) || (pxNetworkContext == NULL) || 
        (pxNetworkContext->pxTlsContext == NULL))
    {
        printf("Invalid parameters for TLS send\n");
        return -1;
    }

    TickType_t xTicksToWait = pdMS_TO_TICKS(timeouts.sendTimeoutMs);
    TickType_t startTick = xTaskGetTickCount();

    if (xSemaphoreTake(pxNetworkContext->xTlsContextSemaphore, xTicksToWait) == pdTRUE)
    {
        TlsContext_t* pxTlsContext = pxNetworkContext->pxTlsContext;
        unsigned char* pucData = (unsigned char*)pvData;
        lBytesSent = 0;
        uint32_t sendAttempts = 0;
        const uint32_t maxSendAttempts = 1000; /* Prevent infinite loop */

        while ((lBytesSent < (int32_t)uxDataLen) && (lBytesSent >= 0))
        {
            int lResult = mbedtls_ssl_write(&pxTlsContext->ssl,
                                            &(pucData[lBytesSent]),
                                            uxDataLen - (size_t)lBytesSent);

            if (lResult > 0)
            {
                lBytesSent += (int32_t)lResult;
                sendAttempts = 0; /* Reset attempts counter on successful send */
            }
            else if (lResult == MBEDTLS_ERR_SSL_WANT_WRITE || lResult == MBEDTLS_ERR_SSL_WANT_READ)
            {
                /* Check for timeout */
                TickType_t elapsedTime = xTaskGetTickCount() - startTick;
                if (elapsedTime >= pdMS_TO_TICKS(timeouts.sendTimeoutMs))
                {
                    printf("TLS send timeout after %u ms\n", (unsigned int)(elapsedTime * portTICK_PERIOD_MS));
                    if (lBytesSent == 0)
                    {
                        lBytesSent = -1; /* Timeout with no data sent */
                    }
                    break;
                }

                /* Prevent infinite attempts */
                if (++sendAttempts > maxSendAttempts)
                {
                    printf("TLS send max attempts exceeded\n");
                    if (lBytesSent == 0)
                    {
                        lBytesSent = -1;
                    }
                    break;
                }

                /* Small delay for WANT_READ/WANT_WRITE */
                vTaskDelay(pdMS_TO_TICKS(1));
            }
            else
            {
                printf("mbedtls_ssl_write error: -0x%04x\n", (unsigned int)(-lResult));
                lBytesSent = lResult;
                break;
            }
        }
        
        xSemaphoreGive(pxNetworkContext->xTlsContextSemaphore);
    }
    else
    {
        printf("Failed to acquire semaphore for TLS send\n");
    }

    return lBytesSent;
}

int32_t qccTlsTransportRecv(NetworkContext_t* pxNetworkContext,
                            void* pvData, size_t uxDataLen)
{
    int32_t lBytesReceived = -1;

    if ((pvData == NULL) || (uxDataLen == 0) || (pxNetworkContext == NULL) || 
        (pxNetworkContext->pxTlsContext == NULL))
    {
        printf("Invalid parameters for TLS recv\n");
        return -1;
    }

    TickType_t xTicksToWait = pdMS_TO_TICKS(timeouts.recvTimeoutMs);
    TickType_t startTick = xTaskGetTickCount();

    if (xSemaphoreTake(pxNetworkContext->xTlsContextSemaphore, xTicksToWait) == pdTRUE)
    {
        TlsContext_t* pxTlsContext = pxNetworkContext->pxTlsContext;
        uint32_t recvAttempts = 0;
        const uint32_t maxRecvAttempts = 1000; /* Prevent infinite loop */

        while (true)
        {
            lBytesReceived = mbedtls_ssl_read(&pxTlsContext->ssl, 
                                              (unsigned char*)pvData, 
                                              uxDataLen);

            if (lBytesReceived > 0)
            {
                /* Successfully received data */
                break;
            }
            else if (lBytesReceived == 0)
            {
                /* Connection closed gracefully */
                printf("TLS connection closed by peer\n");
                lBytesReceived = -1;
                break;
            }
            else if (lBytesReceived == MBEDTLS_ERR_SSL_WANT_READ || 
                     lBytesReceived == MBEDTLS_ERR_SSL_WANT_WRITE)
            {
                /* Check for timeout */
                TickType_t elapsedTime = xTaskGetTickCount() - startTick;
                if (elapsedTime >= pdMS_TO_TICKS(timeouts.recvTimeoutMs))
                {
                    lBytesReceived = 0; /* Timeout - no data available */
                    break;
                }

                /* Prevent infinite attempts */
                if (++recvAttempts > maxRecvAttempts)
                {
                    printf("TLS recv max attempts exceeded\n");
                    lBytesReceived = 0;
                    break;
                }

                /* Small delay before retry */
                vTaskDelay(pdMS_TO_TICKS(1));
            }
            else
            {
                /* Other errors */
                printf("mbedtls_ssl_read error: -0x%04x\n", (unsigned int)(-lBytesReceived));
                break;
            }
        }

        xSemaphoreGive(pxNetworkContext->xTlsContextSemaphore);
    }
    else
    {
        printf("Failed to acquire semaphore for TLS recv\n");
    }

    return lBytesReceived;
} 