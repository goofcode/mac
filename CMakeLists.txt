cmake_minimum_required(VERSION 3.12)
project(contiki)

set(CMAKE_C_STANDARD 90)

# set include path
include_directories(core)
include_directories(core/lib)
include_directories(cpu/msp430)
include_directories(platform/sky)

# set project files
set(DEV_PROJECT_PATH project)
file(GLOB_RECURSE src_list
        "${DEV_PROJECT_PATH}/*.h"
        "${DEV_PROJECT_PATH}/*.c")

add_executable(contiki ${src_list})