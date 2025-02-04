#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13

//Variável do estado do semárofo, do tipo inteiro e global
int estado_semaforo = 0;


bool repeating_timer_callback(struct repeating_timer *t) {
    // Alterna entre os estados do semáforo
    //Cada case aciona uma cor diferente do LED RGB
    switch (estado_semaforo) {
        case 0:
            gpio_put(LED_VERMELHO, 1); 
            gpio_put(LED_AMARELO, 0);
            gpio_put(LED_VERDE, 0);
            estado_semaforo = 1;
            break;
        case 1:
            gpio_put(LED_VERMELHO, 0);
            gpio_put(LED_AMARELO, 1); 
            gpio_put(LED_VERDE, 0);
            estado_semaforo = 2;
            break;
        case 2:
            gpio_put(LED_VERMELHO, 0);
            gpio_put(LED_AMARELO, 0);
            gpio_put(LED_VERDE, 1); 
            estado_semaforo = 0;
            break;
    }
    return true; 
}

int main() {

    while (1) {
        printf("Running");
    }
}