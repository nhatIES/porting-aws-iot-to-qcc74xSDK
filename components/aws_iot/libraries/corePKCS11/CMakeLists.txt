# This gives PKCS_INCLUDE_PUBLIC_DIRS, and PKCS_SOURCES
include(${CMAKE_CURRENT_LIST_DIR}/corePKCS11/pkcsFilePaths.cmake)


sdk_generate_library()

set(COREPKCS11_LOCATION "${CMAKE_CURRENT_LIST_DIR}/corePKCS11")

set(CORE_PKCS11_3RDPARTY_LOCATION "${COREPKCS11_LOCATION}/source/dependency/3rdparty")

set(COREPKCS_PORT_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/port
    ${CMAKE_CURRENT_LIST_DIR}/../common/logging/
)

set(COREPKCS_INCLUDE_DIRS
    ${PKCS_INCLUDE_PUBLIC_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/config
    ${COREPKCS_PORT_INCLUDE_DIRS}
)

set(COREPKCS_PORT_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/port/core_pkcs11_pal.c
    ${CMAKE_CURRENT_LIST_DIR}/port/iot_crypto.c
)

# Filter out mbedTLS implementation as QCC74x SDK provides its own
set(COREPKCS_SRCS_FILTERED "")
foreach(src ${PKCS_SOURCES})
    # Skip mbedTLS specific implementation
    if(NOT ${src} MATCHES "core_pkcs11_mbedtls.c")
        list(APPEND COREPKCS_SRCS_FILTERED ${src})
    endif()
endforeach()

set(COREPKCS_SRCS
    ${COREPKCS_SRCS_FILTERED}
    ${COREPKCS_PORT_SRCS}
)


sdk_library_add_sources(${COREPKCS_SRCS})
# Comment out mbedtls_utils.c to avoid conflicts with QCC74x SDK mbedTLS
# sdk_library_add_sources(${CORE_PKCS11_3RDPARTY_LOCATION}/mbedtls_utils/mbedtls_utils.c)


sdk_add_include_directories(${COREPKCS_INCLUDE_DIRS})
# Comment out mbedtls_utils include to avoid conflicts
# sdk_add_include_directories(${CORE_PKCS11_3RDPARTY_LOCATION}/mbedtls_utils)

# Add mbedTLS include paths from QCC74x SDK
sdk_add_include_directories(${CMAKE_CURRENT_LIST_DIR}/../../../crypto/mbedtls/mbedtls/include)
sdk_add_include_directories(${CMAKE_CURRENT_LIST_DIR}/../../../crypto/mbedtls/port)

# Add mbedTLS config definition to use QCC74x SDK's mbedTLS config
sdk_add_compile_definitions(-DMBEDTLS_CONFIG_FILE=\"mbedtls_sample_config.h\")


