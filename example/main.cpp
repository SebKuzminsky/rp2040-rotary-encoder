#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <pico/stdlib.h>

#include "encoder.h"


#define DO_BUTTON 1


#if DO_BUTTON
#include "button.pio.h"
#endif


int main() {
    stdio_init_all();
    sleep_ms(3*1000);
    printf("booted\n");

    encoder_init();

    PIO pio = pio0;

#if DO_BUTTON
    uint button_offset = 0;

    if (pio_can_add_program_at_offset(pio, &button_program, button_offset)) {
        printf("adding button at %u\n", button_offset);
    } else {
        printf("can't add button at %u\n", button_offset);
    }

    pio_add_program_at_offset(pio, &button_program, button_offset);
    printf("loaded button at 0x%08x\n", button_offset);

    uint const button_gpio = 2;

    button_init(pio, button_offset, button_gpio);
#endif

    for (;;) {
        int r = encoder_scan();
        if (r == 1) {
            printf("cw\n");
        } else if (r == -1) {
            printf("ccw\n");
        }

#if DO_BUTTON
        uint32_t button_state;
        if (button_get_state(button_state)) {
            printf("got a button edge: 0x%08lx\n", button_state);
        }
#endif
    }
}
