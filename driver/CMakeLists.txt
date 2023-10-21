set(LIBRARY_NAME rp2040_rotary_encoder)

add_library(${LIBRARY_NAME} STATIC)

target_sources(
    ${LIBRARY_NAME} PRIVATE
    button.cpp
    encoder.cpp
)

target_compile_options(
    ${LIBRARY_NAME}
    PRIVATE
    "-Wall"
)

target_link_libraries(
    ${LIBRARY_NAME}
    pico_stdlib
)

target_include_directories(
    ${LIBRARY_NAME}
    PUBLIC
    "./include"
)
