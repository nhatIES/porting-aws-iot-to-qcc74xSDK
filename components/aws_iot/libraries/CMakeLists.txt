# AWS IoT Libraries CMakeLists
# Thêm include paths cho common logging system
sdk_add_include_directories(common/logging)
sdk_add_include_directories(common/posix_compat)

# Core libraries
add_subdirectory(coreMQTT)
add_subdirectory(coreJSON)
add_subdirectory(coreHTTP)
add_subdirectory(corePKCS11)
add_subdirectory(coreMQTT-Agent)

# AWS IoT specific libraries
add_subdirectory(device-shadow)
add_subdirectory(device-defender)
add_subdirectory(jobs-for-aws)
add_subdirectory(fleet-provisioning)

# Additional libraries
add_subdirectory(backoffAlgorithm)
add_subdirectory(mqtt-file-streams)

# Common utilities
add_subdirectory(common) 