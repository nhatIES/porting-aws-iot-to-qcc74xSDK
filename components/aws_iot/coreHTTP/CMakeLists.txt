# Include HTTP library's source and header path variables.
include( "${CMAKE_CURRENT_LIST_DIR}/coreHTTP/httpFilePaths.cmake" )

sdk_generate_library()

sdk_library_add_sources(${HTTP_SOURCES})
sdk_library_add_sources(${HTTP_THIRD_PARTY_SOURCES})

sdk_add_include_directories(${HTTP_INCLUDE_PUBLIC_DIRS})
sdk_add_include_directories(${CMAKE_CURRENT_LIST_DIR}/../common/logging/)
sdk_add_include_directories(${CMAKE_CURRENT_LIST_DIR}/../network_transport)
sdk_add_include_directories(config)
sdk_add_include_directories(.)


set_source_files_properties(
    "${CMAKE_CURRENT_LIST_DIR}/coreHTTP/source/core_http_client.c"
    PROPERTIES COMPILE_FLAGS -Wno-stringop-truncation
)