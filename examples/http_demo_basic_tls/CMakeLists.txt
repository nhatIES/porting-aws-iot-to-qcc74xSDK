cmake_minimum_required(VERSION 3.15)

include(proj.conf)

find_package(qcc74x_sdk REQUIRED HINTS $ENV{QCC74x_SDK_BASE})

sdk_set_main_file(main.c)

sdk_add_include_directories(.)

project(http_demo_basic_tls)
