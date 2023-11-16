set(LIBRARY_NAME rp2040_rotary_encoder)

add_library(${LIBRARY_NAME} STATIC)

pico_generate_pio_header(rp2040_rotary_encoder ${CMAKE_CURRENT_LIST_DIR}/quadrature_encoder.pio)
pico_generate_pio_header(rp2040_rotary_encoder ${CMAKE_CURRENT_LIST_DIR}/button.pio)

target_sources(
    ${LIBRARY_NAME} PRIVATE
)

target_compile_options(
    ${LIBRARY_NAME}
    PRIVATE
    "-Wall"
)

target_link_libraries(
    ${LIBRARY_NAME}
    pico_stdlib
    hardware_pio
)

target_include_directories(
    ${LIBRARY_NAME}
    PUBLIC
    "./include"
)
