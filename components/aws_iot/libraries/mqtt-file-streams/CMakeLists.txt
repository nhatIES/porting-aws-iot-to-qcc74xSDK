# This gives OTA_INCLUDE_PUBLIC_DIRS, and OTA_SOURCES
include(${CMAKE_CURRENT_LIST_DIR}/mqtt-file-streams/mqttFileDownloaderFilePaths.cmake)

sdk_generate_library()

set(AWS_OTA_PORT_INCLUDE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/port
    ${CMAKE_CURRENT_LIST_DIR}/../common/logging/
)

set(AWS_OTA_INCLUDE_DIRS
    ${MQTT_FILE_DOWNLOADER_INCLUDES}
    ${CMAKE_CURRENT_LIST_DIR}/config
    ${AWS_OTA_PORT_INCLUDE_DIRS}
)

set(AWS_OTA_PORT_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/port/aws_esp_ota_ops.c
    ${CMAKE_CURRENT_LIST_DIR}/port/ota_pal.c
    ${CMAKE_CURRENT_LIST_DIR}/port/ota_os_freertos.c
)

# Filter out CBOR implementation as it requires external CBOR library
set(AWS_OTA_SRCS_FILTERED "")
foreach(src ${MQTT_FILE_DOWNLOADER_SOURCES})
    # Skip CBOR specific implementation
    if(NOT ${src} MATCHES "MQTTFileDownloader_cbor.c")
        list(APPEND AWS_OTA_SRCS_FILTERED ${src})
    endif()
endforeach()

set(AWS_OTA_SRCS
    ${AWS_OTA_SRCS_FILTERED}
    ${AWS_OTA_PORT_SRCS}
)

sdk_library_add_sources(${AWS_OTA_SRCS})

sdk_add_include_directories(${AWS_OTA_INCLUDE_DIRS})

set_source_files_properties(
"${CMAKE_CURRENT_LIST_DIR}/aws-iot-core-mqtt-file-streams-embedded-c/source/MQTTFileDownloader.c"
PROPERTIES COMPILE_FLAGS -Wno-format)

if (NOT CONFIG_MQTT_STREAMS_USE_CUSTOM_CONFIG)
sdk_add_compile_definitions(-DMQTT_STREAMS_DO_NOT_USE_CUSTOM_CONFIG=1)
endif()
