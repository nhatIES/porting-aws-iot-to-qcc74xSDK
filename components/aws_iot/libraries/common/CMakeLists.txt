# AWS IoT Common utilities

# Generate library for network transport
sdk_generate_library()

# Add network transport source
sdk_library_add_sources(network_transport/network_transport.c)

# Add include paths that will be inherited by parent projects
sdk_add_include_directories(logging)
sdk_add_include_directories(posix_compat)
sdk_add_include_directories(network_transport)

# Include subdirectories để build posix_compat library  
add_subdirectory(posix_compat)