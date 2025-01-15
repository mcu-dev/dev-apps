# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
add_definitions(-DPLATFORM_ZEPHYR)
project(lsm303)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE
  ${app_sources}
  )
add_subdirectory(src/driver/src)
add_subdirectory(src/driver/src/utils)
