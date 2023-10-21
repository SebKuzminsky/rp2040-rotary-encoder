#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <pico/stdlib.h>

#include "encoder.h"
#include "button.h"


int main() {
    stdio_init_all();

    encoder_init();
    button_init();

    int r;

    for (;;) {
        r = encoder_scan();
        if (r == 1) {
            printf("cw\n");
        } else if (r == -1) {
            printf("ccw\n");
        }

        r = button_scan();
        if (r == 1) {
            // click
            printf("click!\n");
        }
    }
}
