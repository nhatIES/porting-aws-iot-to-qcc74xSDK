include( "${CMAKE_CURRENT_LIST_DIR}/jobs-for-aws/jobsFilePaths.cmake" )


sdk_generate_library()


sdk_library_add_sources(${JOBS_SOURCES})
sdk_library_add_sources(${OTA_HANDLER_SOURCES})


sdk_add_include_directories(${JOBS_INCLUDE_PUBLIC_DIRS})
sdk_add_include_directories(${OTA_HANDLER_INCLUDES})
sdk_add_include_directories(.)