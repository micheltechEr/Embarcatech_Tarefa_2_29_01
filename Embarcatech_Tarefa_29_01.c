#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

int main() {

    while (1) {
        stdio_init_all();
        printf("Running");
         sleep_ms(1000);
    }
}