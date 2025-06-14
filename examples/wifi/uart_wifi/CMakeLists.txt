cmake_minimum_required(VERSION 3.15)

include(proj.conf)

find_package(qcc74x_sdk REQUIRED HINTS $ENV{QCC74x_SDK_BASE})

# User
sdk_add_compile_definitions(-DCONFIG_CLI_CMD_ENABLE)
sdk_add_compile_definitions(-DAT_NET_TX_MAX_LEN=6144)

sdk_add_compile_definitions(-DMQTT_USE_CUSTOM_SOCKET_HANDLE=1)

if (CONFIG_LPAPP)
    target_sources(app PRIVATE
                       app/src/app_uartwifi.c
                       app/src/atmoudle/app_atmoudle.c
                       app/src/pm/app_pm.c
                       )
else ()
    if(NOT CONFIG_PSRAM_COPY_CODE)
        sdk_add_compile_definitions(-DCFG_LINK_ALL_IN_FLASH=1)
        sdk_add_compile_definitions(-DCONFIG_HIGH_PERFORMANCE=1)
    endif()

#sdk_add_compile_definitions(-DQCC743_DHCP_DEBUG)

target_sources(app PRIVATE
                   app/src/app_uartwifi.c
                   app/src/atmoudle/app_atmoudle.c
                   )
endif()

sdk_add_include_directories(.)
sdk_add_include_directories(./app/include)

sdk_set_main_file(main.c)

project(uart_wifi)
