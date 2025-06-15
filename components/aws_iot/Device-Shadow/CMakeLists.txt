# Include Device Shadow library's source and header path variables.
include( "${CMAKE_CURRENT_LIST_DIR}/Device-Shadow/shadowFilePaths.cmake" )

sdk_generate_library()

sdk_library_add_sources(${SHADOW_SOURCES})

sdk_add_include_directories(${SHADOW_INCLUDE_PUBLIC_DIRS})
sdk_add_include_directories(config)
sdk_add_include_directories(.)
