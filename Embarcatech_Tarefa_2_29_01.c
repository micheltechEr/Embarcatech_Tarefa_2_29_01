#include <stdio.h>               
#include "pico/stdlib.h"         
#include "pico/time.h"            

// Definição dos pinos GPIO para os LEDs e o botão.
#define RED_LED_PIN    11        
#define YELLOW_LED_PIN 12         
#define GREEN_LED_PIN  13        
#define BUTTON_PIN     5          

bool is_led_active = false;       // Indica se o LED está ativo (aceso).

// Função para configurar um pino GPIO como entrada ou saída.
void configure_gpio(uint pin, bool is_output, bool initial_state) {
    gpio_init(pin);                              // Inicializa o pino.
    gpio_set_dir(pin, is_output ? GPIO_OUT : GPIO_IN); // Configura direção (entrada/saída).
    gpio_put(pin, initial_state);                // Define o estado inicial do pino.
}

// Callback para desligar o LED verde após o tempo programado.
int64_t turn_off_green(alarm_id_t id, void *user_data) {
    gpio_put(GREEN_LED_PIN, false);              // Desliga o LED verde.
    is_led_active = false;                       // Atualiza o estado do LED para inativo.
    return 0;                                    // Retorna 0 para indicar que o alarme não deve se repetir.
}

// Callback para desligar o LED amarelo e agendar o desligamento do verde.
int64_t turn_off_yellow(alarm_id_t id, void *user_data) {
    gpio_put(YELLOW_LED_PIN, false);             // Desliga o LED amarelo.
    add_alarm_in_ms(3000, turn_off_green, NULL, false); // Agenda o desligamento do LED verde.
    return 0;
}

// Callback para desligar o LED vermelho e agendar o desligamento do amarelo.
int64_t turn_off_red(alarm_id_t id, void *user_data) {
    gpio_put(RED_LED_PIN, false);                // Desliga o LED vermelho.
    add_alarm_in_ms(3000, turn_off_yellow, NULL, false); // Agenda o desligamento do LED amarelo.
    return 0;
}

void setup() {
    stdio_init_all();                            // Inicializa a interface padrão de E/S.
    // Configura os pinos dos LEDs como saída e inicializa-os apagados.
    configure_gpio(RED_LED_PIN, true, false);
    configure_gpio(YELLOW_LED_PIN, true, false);
    configure_gpio(GREEN_LED_PIN, true, false);
    // Configura o pino do botão como entrada com resistor pull-up interno.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
}

void has_button_pressed() {
    // Verifica se o botão foi pressionado (nível baixo) e se nenhum LED está ativo.
    if (gpio_get(BUTTON_PIN) == 0 && !is_led_active) {
        sleep_ms(50);                        // Pequeno atraso para debounce.
        
        // Confirma novamente o estado do botão após o debounce.
        if (gpio_get(BUTTON_PIN) == 0) {
            // Acende todos os LEDs.
            gpio_put(RED_LED_PIN, true);
            gpio_put(YELLOW_LED_PIN, true);
            gpio_put(GREEN_LED_PIN, true);
            is_led_active = true;           // Marca os LEDs como ativos.
            
            // Agenda o desligamento sequencial dos LEDs.
            add_alarm_in_ms(3000, turn_off_red, NULL, false);
        }
    }
}

int main() {
    setup(); // Configura os pinos e inicializa os componentes uma única vez.

    // Loop principal do programa.
    while (true) {
        has_button_pressed();
        sleep_ms(10);                            // Pequena pausa para reduzir o uso da CPU.
    }

    return 0;                                    // Retorno padrão (nunca será alcançado).
}