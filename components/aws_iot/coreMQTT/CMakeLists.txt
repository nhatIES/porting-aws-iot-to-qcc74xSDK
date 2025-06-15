# This gives MQTT_INCLUDE_PUBLIC_DIRS, MQTT_SOURCES, and MQTT_SERIALIZER_SOURCES
include(${CMAKE_CURRENT_LIST_DIR}/coreMQTT/mqttFilePaths.cmake)


sdk_generate_library()

set(COREMQTT_INCLUDE_DIRS
    ${MQTT_INCLUDE_PUBLIC_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/config
    ${CMAKE_CURRENT_LIST_DIR}/../common/logging/
    ${CMAKE_CURRENT_LIST_DIR}/../network_transport
)

set(COREMQTT_SRCS
    ${MQTT_SOURCES}
    ${MQTT_SERIALIZER_SOURCES}
)

sdk_library_add_sources(${COREMQTT_SRCS})

sdk_add_include_directories(${COREMQTT_INCLUDE_DIRS})

set_source_files_properties(
"${CMAKE_CURRENT_LIST_DIR}/coreMQTT/source/core_mqtt.c"
PROPERTIES COMPILE_FLAGS -Wno-format)