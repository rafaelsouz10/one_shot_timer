#ifndef CONFIG_LEDS_H
#define CONFIG_LEDS_H

#define LED_RED 13    // Define o pino GPIO 13 para controlar o LED vermelho.
#define LED_GREEN 12   // Pino GPIO 12 para o LED verde.
#define LED_YELLOW_BLUE 11     // Pino GPIO 11 para o LED amarelo no Wokwi e LED verde na BitDogLab.


// Variáveis globais
bool leds_active  = false;  // Indica se o temporizador está em execução.
int state = 0; // Variável para controlar o estado da sequência de LEDs.

void setup_gpio_leds() {
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_YELLOW_BLUE);
    gpio_set_dir(LED_YELLOW_BLUE, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
}

// Função para ligar todos os LEDs
void turn_on_all_leds() {
    gpio_put(LED_RED, true);
    gpio_put(LED_GREEN, true);
    gpio_put(LED_YELLOW_BLUE, true);
}

// Função de callback para desligar o LED após o tempo programado.
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    switch (state) {
        case 0: //liga todos os leds
            gpio_put(LED_RED, false);
            state = 1;
        break;
        case 1:
            gpio_put(LED_YELLOW_BLUE, false);
            state = 2;
        break;
        case 2:
            gpio_put(LED_GREEN, false);
            state = 0;
            leds_active  = false; // Indica que todos os leds foram desativados
        break;
    }
    return 3000 * 1000; // Retorna 3000 ms (3 segundos) para o próximo alarme.
}

#endif