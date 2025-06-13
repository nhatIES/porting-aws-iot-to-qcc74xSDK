# Include coreJSON library's source and header path variables.
include( "${CMAKE_CURRENT_LIST_DIR}/coreJSON/jsonFilePaths.cmake" )

sdk_generate_library()

sdk_library_add_sources(${JSON_SOURCES})

sdk_add_include_directories(${JSON_INCLUDE_PUBLIC_DIRS})
sdk_add_include_directories(.)
