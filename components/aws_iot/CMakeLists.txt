add_subdirectory(common)
add_subdirectory(backoffAlgorithm)
add_subdirectory(network_transport)  # Shared transport component
add_subdirectory(coreHTTP)
add_subdirectory(coreMQTT)
add_subdirectory(coreJSON)
add_subdirectory(Device-Defender)        
add_subdirectory(Device-Shadow)          
add_subdirectory(coreMQTT-Agent)

sdk_add_include_directories(.)
