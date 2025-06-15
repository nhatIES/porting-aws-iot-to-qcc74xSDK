# HTTP Demo Basic TLS for QCC74x

This demo demonstrates how to use the HTTP Client library with TLS over WiFi on QCC74x platform.

## Features

- Secure HTTP (HTTPS) connections using TLS
- Support for GET, HEAD, PUT, and POST requests
- Exponential backoff retry logic for connection failures
- Amazon Root CA 1 certificate embedded
- Compatible with QCC74x SDK architecture

## Configuration

Edit `demo_config.h` to modify:

- `SERVER_HOST`: HTTP server hostname (default: "httpbin.org")
- `HTTPS_PORT`: HTTPS port (default: 443)
- `ROOT_CA_CERT_PATH`: Root CA certificate (Amazon Root CA 1 embedded)
- HTTP paths for different methods (GET, HEAD, PUT, POST)
- `REQUEST_BODY`: JSON payload for PUT/POST requests

## Build Instructions

1. Make sure you have QCC74x SDK properly configured
2. Build the example:
   ```bash
   make http_demo_basic_tls
   ```

## Usage

1. Connect to WiFi network using shell commands:
   ```
   wifi_sta_connect "Your_SSID" "Your_Password"
   ```

2. The demo will automatically:
   - Establish TLS connection to the configured server
   - Send HTTP GET, HEAD, PUT, and POST requests
   - Display response headers and body
   - Retry failed connections with exponential backoff
   - Loop every 5 seconds

## Expected Output

```
[HTTPDemo] Establishing a TLS session to httpbin.org:443.
[HTTPDemo] TLS connection to httpbin.org:443 established successfully.
[HTTPDemo] Sending HTTP GET request to httpbin.org/get...
[HTTPDemo] Received HTTP response from httpbin.org/get...
Response Status: 200
Response Body: {"args":{},"headers":{"Host":"httpbin.org",...}
```

## Dependencies

- AWS IoT Device SDK for Embedded C (HTTP Client library)
- QCC74x TLS transport layer
- LwIP TCP/IP stack
- WiFi6 component
- mbedTLS for cryptographic operations

## Notes

- This example automatically handles WiFi events but requires manual WiFi connection
- TLS certificate verification is enabled by default
- Supports both IPv4 and IPv6 (if enabled in LwIP configuration)
- Memory optimized for embedded systems with limited RAM
