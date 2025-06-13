# Include Fleet Provisioning library's source and header path variables.
include( "${CMAKE_CURRENT_LIST_DIR}/fleet-provisioning/fleetprovisioningFilePaths.cmake" )

sdk_generate_library()

sdk_library_add_sources(${FLEET_PROVISIONING_SOURCES})


sdk_add_include_directories(${FLEET_PROVISIONING_INCLUDE_PUBLIC_DIRS})
sdk_add_include_directories(config)
sdk_add_include_directories(.)
