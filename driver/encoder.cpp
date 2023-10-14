#include <cstdio>
#include <pico/stdlib.h>

#include "encoder.h"


static uint const enc_a_gpio = 0;  // pin 1
static uint const enc_b_gpio = 1;  // pin 2

// A in bit 1, B in bit 0
static int enc_state_old;

static bool enc_initializing;


void encoder_init(void) {
    bool enc_a;
    bool enc_b;

    // these gpios are driven by the main processor
    gpio_set_function(enc_a_gpio, GPIO_FUNC_SIO);
    gpio_set_function(enc_b_gpio, GPIO_FUNC_SIO);

    // these gpios are inputs
    gpio_set_dir(enc_a_gpio, false);
    gpio_set_dir(enc_b_gpio, false);

    // these gpios are pulled up
    gpio_pull_up(enc_a_gpio);
    gpio_pull_up(enc_b_gpio);

    sleep_ms(1);

    enc_a = gpio_get(enc_a_gpio);
    enc_b = gpio_get(enc_b_gpio);
    enc_state_old = (enc_a << 1) | enc_b;

    enc_initializing = true;
}


int encoder_scan(void) {
    static int count = 0;

    bool enc_a = gpio_get(enc_a_gpio);
    bool enc_b = gpio_get(enc_b_gpio);
    int enc_state = (enc_a << 1) | enc_b;

    if (enc_initializing) {
        if (enc_state != 3) {
            return 0;
        } else {
            enc_initializing = false;
            // printf("encoder initalized!\n");
            enc_state_old = enc_state;
            count = 0;
        }
    }

    if (enc_state == enc_state_old) {
        // no change
        return 0;
    }

    // printf("enc state change, new=%d, old=%d\n", enc_state, enc_state_old);

    if (enc_state_old == 3) {
        if (enc_state == 2) {
            count -= 1;
        } else if (enc_state == 1) {
            count += 1;
        } else {
            printf("encoder state transition error\n");
            enc_initializing = true;
            return 0;
        }
    } else if (enc_state_old == 2) {
        if (enc_state == 3) {
            count += 1;
        } else if (enc_state == 0) {
            count -= 1;
        } else {
            printf("encoder state transition error\n");
            enc_initializing = true;
            return 0;
        }
    } else if (enc_state_old == 1) {
        if (enc_state == 3) {
            count -= 1;
        } else if (enc_state == 0) {
            count += 1;
        } else {
            printf("encoder state transition error\n");
            enc_initializing = true;
            return 0;
        }
    } else if (enc_state_old == 0) {
        if (enc_state == 2) {
            count += 1;
        } else if (enc_state == 1) {
            count -= 1;
        } else {
            printf("encoder state transition error\n");
            enc_initializing = true;
            return 0;
        }
    } else {
        printf("encoder state transition error\n");
        enc_initializing = true;
        return 0;
    }

    // printf("count=%d\n", count);

    enc_state_old = enc_state;

    if (count == 4) {
        count = 0;
        return 1;
    } else if (count == -4) {
        count = 0;
        return -1;
    }

    return 0;
}
