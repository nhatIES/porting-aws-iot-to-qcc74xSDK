SDK_DEMO_PATH ?= .
QCC74x_SDK_BASE ?= $(SDK_DEMO_PATH)/../../../

export QCC74x_SDK_BASE

CHIP ?= qcc743
BOARD ?= qcc743dk
CROSS_COMPILE ?= riscv64-unknown-elf-

# add custom cmake definition
#cmake_definition+=-Dxxx=sss

CONFIG_RCP_ENABLE ?= 0
cmake_definition+=-DCONFIG_RCP_ENABLE=$(CONFIG_RCP_ENABLE)

CONFIG_USE_LPAPP ?= 1
cmake_definition+=-DCONFIG_USE_LPAPP=$(CONFIG_USE_LPAPP)

CONFIG_BLUETOOTH_APP ?= 1
cmake_definition+=-DCONFIG_BLUETOOTH_APP=$(CONFIG_BLUETOOTH_APP)

CONFIG_MQTT ?= 1
cmake_definition+=-DCONFIG_MQTT=$(CONFIG_MQTT)

CONFIG_HTTP ?= 1
cmake_definition+=-DCONFIG_HTTP=$(CONFIG_HTTP)

CONFIG_NETWORK ?= 1
cmake_definition+=-DCONFIG_NETWORK=$(CONFIG_NETWORK)

CONFIG_ANTENNA_CONTROL ?= 1
cmake_definition+=-DCONFIG_ANTENNA_CONTROL=$(CONFIG_ANTENNA_CONTROL)

cmake_definition+=-DCONFIG_PSRAM_COPY_CODE=$(CONFIG_PSRAM_COPY_CODE)

include $(QCC74x_SDK_BASE)/project.build 
