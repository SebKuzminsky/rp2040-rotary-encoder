#include <pico/stdlib.h>

#include "button.h"


static uint const button_gpio = 2;  // pin 4

static bool button_old;


void button_init(void) {
    // this gpio is driven by the main processor
    gpio_set_function(button_gpio, GPIO_FUNC_SIO);

    // this gpio is input
    gpio_set_dir(button_gpio, false);

    // this gpio is pulled up
    gpio_pull_up(button_gpio);

    button_old = gpio_get(button_gpio);
}


// FIXME: needs debounce
// Returns true if a click just happened, false if no click.
bool button_scan(void) {
    bool r;
    bool button = gpio_get(button_gpio);

    if (button_old & !button) {
        r = true;
    } else {
        r = false;
    }

    button_old = button;

    return r;
}
