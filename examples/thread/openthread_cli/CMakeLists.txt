cmake_minimum_required(VERSION 3.15)

include(proj.conf)

find_package(qcc74x_sdk REQUIRED HINTS $ENV{QCC74x_SDK_BASE})

string(TOLOWER "${CHIP}" lower_case_chip)
string(TOUPPER "${CHIP}" upper_case_chip)

sdk_add_compile_definitions(-DOPENTHREAD_CONFIG_PLATFORM_INFO=\"${upper_case_chip}\")

if(CONFIG_LMAC154_LOG)
sdk_add_compile_definitions(-DCONFIG_LMAC154_LOG=1)
sdk_add_compile_definitions(-DAPP_PRINT=lmac154_log)
else()
sdk_add_compile_definitions(-DAPP_PRINT=printf)
endif()

if (CONFIG_SHELL AND CONFIG_LMAC154_CMD) 
sdk_add_compile_definitions(-DCONFIG_LMAC154_CMD=1)
endif()

if ("${OT_SERIAL}" STREQUAL "SYS_CLI")
sdk_add_compile_definitions(-DOT_SERIAL_SHELL)
elseif ("${OT_SERIAL}" STREQUAL "UART") 
sdk_add_compile_definitions(-DOT_SERIAL_UART)
endif()

sdk_add_include_directories(.)

sdk_set_main_file(main.c)

project(openthread_cli)
