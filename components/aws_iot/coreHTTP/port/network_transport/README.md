# QCC74x Network Transport for coreHTTP

Đây là implementation hoàn chỉnh của network transport layer cho coreHTTP trên platform QCC74x, sử dụng LwIP TCP/IP stack và mbedTLS cho TLS/SSL.

## Tính năng

### 🔐 TLS/SSL Support
- **mbedTLS Integration**: Sử dụng mbedTLS cho encrypted connections
- **Certificate Management**: Hỗ trợ CA certificates, client certificates và private keys
- **SNI Support**: Server Name Indication for virtual hosting
- **ALPN Support**: Application Layer Protocol Negotiation
- **Certificate Verification**: Đầy đủ chain validation

### 🌐 Plain TCP Support  
- **Standard TCP Sockets**: Sử dụng LwIP sockets API
- **Connection Management**: Reliable connect/disconnect
- **Error Handling**: Comprehensive error reporting

### ⚡ Performance Features
- **Thread Safety**: FreeRTOS semaphore protection
- **Socket Options**: Keep-alive, timeouts, TCP_NODELAY
- **Non-blocking Operations**: Proper handling of EAGAIN/EWOULDBLOCK
- **Memory Management**: Efficient mbedTLS context management

## Files Structure

```
network_transport/
├── network_transport.h              # Header với API definitions
├── network_transport.c              # Main implementation
├── network_transport_example.c      # Usage examples
└── README.md                        # Documentation này
```

## Configuration

### Build Configuration

Trong `CMakeLists.txt` hoặc build config:

```cmake
# Enable mbedTLS for TLS support
set(CONFIG_MBEDTLS 1)

# Include paths
target_include_directories(your_target PRIVATE
    path/to/mbedtls/include
    path/to/lwip/include
)

# Link libraries
target_link_libraries(your_target
    mbedtls
    mbedx509
    mbedcrypto
    lwip
)
```

### Runtime Configuration

```c
NetworkContext_t networkContext;

// Initialize context
memset(&networkContext, 0, sizeof(NetworkContext_t));
networkContext.xTlsContextSemaphore = xSemaphoreCreateMutex();

// Set connection details
networkContext.pcHostname = "your-server.com";
networkContext.xPort = 443;  // HTTPS port

// Set CA certificate (required for TLS)
networkContext.pcServerRootCA = ca_cert_pem;
networkContext.pcServerRootCASize = strlen(ca_cert_pem) + 1;

// Optional: Client certificate for mutual TLS
networkContext.pcClientCert = client_cert_pem;
networkContext.pcClientCertSize = strlen(client_cert_pem) + 1;
networkContext.pcClientKey = client_key_pem;
networkContext.pcClientKeySize = strlen(client_key_pem) + 1;

// Configuration options
networkContext.disableSni = pdFALSE;  // Enable SNI
networkContext.timeoutMs = 10000;     // 10 second timeout
```

## API Usage

### TLS Connection

```c
#include "network_transport.h"

// Connect với TLS
TlsTransportStatus_t status = xTlsConnect(&networkContext);
if (status == TLS_TRANSPORT_SUCCESS) {
    printf("TLS connection established!\n");
    
    // Send data
    const char* data = "GET / HTTP/1.1\r\n\r\n";
    int32_t sent = qcc74xTlsTransportSend(&networkContext, data, strlen(data));
    
    // Receive data
    char buffer[1024];
    int32_t received = qcc74xTlsTransportRecv(&networkContext, buffer, sizeof(buffer));
    
    // Disconnect
    xTlsDisconnect(&networkContext);
}
```

### Plain TCP Connection

```c
// Connect với plain TCP
TlsTransportStatus_t status = xTcpConnect(&networkContext);
if (status == TLS_TRANSPORT_SUCCESS) {
    printf("TCP connection established!\n");
    
    // Send/receive tương tự nhưng sử dụng TCP functions
    int32_t sent = qcc74xTcpTransportSend(&networkContext, data, strlen(data));
    int32_t received = qcc74xTcpTransportRecv(&networkContext, buffer, sizeof(buffer));
    
    xTcpDisconnect(&networkContext);
}
```

### Integration với coreHTTP

```c
#include "core_http_client.h"
#include "transport_interface.h"

TransportInterface_t transportInterface;
NetworkContext_t networkContext;

// Setup transport interface
transportInterface.pNetworkContext = &networkContext;
transportInterface.send = qcc74xTlsTransportSend;  // hoặc qcc74xTcpTransportSend
transportInterface.recv = qcc74xTlsTransportRecv;  // hoặc qcc74xTcpTransportRecv

// Connect
xTlsConnect(&networkContext);  // hoặc xTcpConnect

// Use với coreHTTP
HTTPRequestInfo_t requestInfo;
HTTPResponse_t response;
// ... setup request info ...

HTTPStatus_t httpStatus = HTTPClient_Send(&transportInterface,
                                         &requestInfo,
                                         NULL, 0,
                                         &response,
                                         0);
```

## Error Handling

```c
TlsTransportStatus_t status = xTlsConnect(&networkContext);

switch (status) {
    case TLS_TRANSPORT_SUCCESS:
        printf("Connection successful\n");
        break;
    case TLS_TRANSPORT_CONNECT_FAILURE:
        printf("Failed to connect to server\n");
        break;
    case TLS_TRANSPORT_HANDSHAKE_FAILED:
        printf("TLS handshake failed\n");
        break;
    case TLS_TRANSPORT_INVALID_CREDENTIALS:
        printf("Invalid certificates\n");
        break;
    default:
        printf("Unknown error: %d\n", status);
        break;
}
```

## Socket Configuration

Implementation tự động set các socket options:

- **SO_RCVTIMEO/SO_SNDTIMEO**: Receive/send timeouts
- **SO_KEEPALIVE**: TCP keep-alive
- **TCP_NODELAY**: Disable Nagle's algorithm cho low latency

## Memory Management

- **Automatic Cleanup**: mbedTLS contexts được cleanup tự động khi disconnect
- **Thread Safety**: FreeRTOS semaphore protection cho concurrent access
- **Resource Management**: Proper socket và memory resource cleanup

## Debugging

Enable mbedTLS debug output bằng cách modify `my_debug()` function trong source code.

```c
static void my_debug(void *ctx, int level, const char *file, int line, const char *str)
{
    printf("mbedTLS [%d] %s:%d: %s", level, file, line, str);
}
```

## Performance Tips

1. **Reuse Connections**: Giữ connection alive cho multiple requests
2. **Buffer Sizes**: Tune receive buffer sizes theo application needs
3. **Timeouts**: Set appropriate timeouts cho network conditions
4. **Certificate Caching**: Cache parsed certificates nếu possible

## Examples

Xem `network_transport_example.c` để có complete working examples cho cả TLS và TCP connections.

## Troubleshooting

### Common Issues

1. **Certificate Errors**: 
   - Verify CA certificate format và content
   - Check certificate chain completeness

2. **Connection Timeouts**:
   - Increase timeout values
   - Check network connectivity
   - Verify hostname resolution

3. **mbedTLS Errors**:
   - Enable debug output để see detailed error messages
   - Check mbedTLS error codes documentation

4. **Memory Issues**:
   - Ensure sufficient heap memory cho mbedTLS contexts
   - Monitor stack usage trong FreeRTOS tasks

### Build Issues

- Ensure `CONFIG_MBEDTLS` is defined nếu using TLS
- Verify all required headers are included
- Check linking với mbedTLS libraries

---

**Lưu ý**: Đây là production-ready implementation được optimize cho QCC74x platform với LwIP và mbedTLS. Nó đảm bảo reliability, security và performance cho AWS IoT applications. 