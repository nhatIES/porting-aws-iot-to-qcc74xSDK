SDK_DEMO_PATH ?= .
QCC74x_SDK_BASE ?= $(SDK_DEMO_PATH)/../../..

export QCC74x_SDK_BASE

CHIP ?= qcc743
BOARD ?= ${CHIP}dk
CROSS_COMPILE ?= riscv64-unknown-elf-

OT_NCP ?= 1
OT_FTD ?= 1

cmake_definition+=-DOT_NCP=${OT_NCP}
ifneq ($(OT_NCP), 1)
  cmake_definition+=-DOT_FTD=${OT_FTD}
endif

cmake_definition+=-DOT_CLI=0
cmake_definition+=-DOT_SERIAL=UART
cmake_definition+=-DOT_SERIAL_BUFFER_SIZE=1024
cmake_definition+=-DOT_SERIAL_LINE_SIZE=256

cmake_definition+=-DOPENTHREAD_PROJECT_CORE_CONFIG_FILE=\"openthread-core-proj-config.h\"
cmake_definition+=-DOPENTHREAD_CORE_CONFIG_PLATFORM_CHECK_FILE=\"openthread-core-platform-config-check.h\"

include $(QCC74x_SDK_BASE)/project.build
