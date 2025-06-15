# This gives DEFENDER_INCLUDE_PUBLIC_DIRS, and DEFENDER_SOURCES
include(${CMAKE_CURRENT_LIST_DIR}/Device-Defender/defenderFilePaths.cmake)

sdk_generate_library()

set(DEVICE_DEFENDER_INCLUDE_DIRS
    ${DEFENDER_INCLUDE_PUBLIC_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/config
)

set(DEVICE_DEFENDER_SRCS
    ${DEFENDER_SOURCES}
)

sdk_library_add_sources(${DEVICE_DEFENDER_SRCS})

sdk_add_include_directories(${DEVICE_DEFENDER_INCLUDE_DIRS})