#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <pico/stdlib.h>

#include "quadrature_encoder.pio.h"
#include "button.pio.h"


int main() {
    stdio_init_all();
    sleep_ms(3*1000);
    printf("booted\n");

    // Base pin to connect the A phase of the encoder.
    // The B phase must be connected to the next pin
    const uint PIN_AB = 0;

    // we don't really need to keep the offset, as this program must be loaded
    // at offset 0
    (void)pio_add_program(pio0, &quadrature_encoder_program);
    quadrature_encoder_program_init(pio0, PIN_AB, 0);

    uint button_offset = 0;

    if (pio_can_add_program_at_offset(pio1, &button_program, button_offset)) {
        printf("adding button at %u\n", button_offset);
    } else {
        printf("can't add button at %u\n", button_offset);
    }

    pio_add_program_at_offset(pio1, &button_program, button_offset);
    printf("loaded button at 0x%08x\n", button_offset);

    uint const button_gpio = 2;

    button_init(pio1, button_offset, button_gpio);

    int old_value = 0;
    for (;;) {
        int new_value, delta;
        // note: thanks to two's complement arithmetic delta will always
        // be correct even when new_value wraps around MAXINT / MININT
        new_value = quadrature_encoder_get_count();
        delta = new_value - old_value;
        old_value = new_value;
        if (delta != 0) {
            printf("position %8d, delta %6d\n", new_value, delta);
        }

        uint32_t button_state;
        if (button_get_state(button_state)) {
            printf("got a button edge: 0x%08lx\n", button_state);
        }
    }
}
