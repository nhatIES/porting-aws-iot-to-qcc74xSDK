cmake_minimum_required(VERSION 3.15)

include(proj.conf)

find_package(qcc74x_sdk REQUIRED HINTS $ENV{QCC74x_SDK_BASE})

sdk_add_compile_definitions(-DCONFIG_OTBR_REST=${CONFIG_OTBR_REST})

if(CONFIG_LMAC154_LOG)
sdk_add_compile_definitions(-DCONFIG_LMAC154_LOG=1)
sdk_add_compile_definitions(-DAPP_PRINT=lmac154_log)
else()
sdk_add_compile_definitions(-DAPP_PRINT=printf)
endif()

if (CONFIG_SHELL AND CONFIG_LMAC154_CMD) 
sdk_add_compile_definitions(-DCONFIG_LMAC154_CMD=1)
endif()

sdk_add_include_directories(.)

target_sources(app PRIVATE otbr_cmd.c)

sdk_set_main_file(main.c)

project(openthread_wifi_br)
