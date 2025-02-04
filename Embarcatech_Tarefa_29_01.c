#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_VERMELHO 11
#define LED_AMARELO 12
#define LED_VERDE 13

// Variável global para controlar o estado do semáforo
int estado_semaforo = 0;

// Função de callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    // Alterna entre os estados do semáforo
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

void setup() {
    stdio_init_all();

    gpio_init(LED_VERMELHO);
    gpio_init(LED_AMARELO);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    static struct repeating_timer timer; 
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);
}

int main() {
    setup();

    int contador = 0;
    while (1) {
        printf("Tempo decorrido: %d segundos\n", contador++);
        sleep_ms(1000); 
    }
}