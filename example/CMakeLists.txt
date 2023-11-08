cmake_minimum_required(VERSION 3.25)

# Pull in SDK (must be before project)
include("$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake")
include("$ENV{PICO_EXAMPLES_PATH}/pico_extras_import_optional.cmake")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

add_compile_options(
    -Wall
)

set(PROJECT_NAME "rotary-encoder-example")
project(${PROJECT_NAME} C CXX ASM)

SET(PROGRAM_NAME "${PROJECT_NAME}")

pico_sdk_init()

add_subdirectory(../driver build.rotary_encoder)

add_executable(
    ${PROGRAM_NAME}
    main.cpp
)

target_link_libraries(
    ${PROGRAM_NAME}
    pico_stdlib
    rp2040_rotary_encoder
)

pico_enable_stdio_usb(${PROGRAM_NAME} TRUE)
pico_enable_stdio_uart(${PROGRAM_NAME} FALSE)

pico_add_extra_outputs(${PROGRAM_NAME})
