# Provide default FreeRTOSConfig.h for AWS IoT
# Projects can override this by providing their own FreeRTOSConfig.h in their include path
sdk_add_include_directories(.)

add_subdirectory(libraries)

