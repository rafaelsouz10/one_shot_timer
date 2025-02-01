#include <stdio.h> // Biblioteca padrão do C.
#include "pico/stdlib.h" // Biblioteca padrão do Raspberry Pi Pico para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   // Biblioteca para gerenciamento de temporizadores e alarmes.

const uint LED_RED = 6;    // Define o pino GPIO 11 para controlar o LED vermelho.
const uint LED_YELLOW = 7;     // Pino GPIO 12 para o LED amarelo.
const uint LED_GREEN = 8;   // Pino GPIO 13 para o LED verde.
const uint BTN_A = 5;  // Define o pino GPIO 5 para ler o estado do botão.

// Variáveis globais
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
bool BTN_A_PRESSIONADO = false; // Indica se o botão foi pressionado.
bool leds_active  = false;  // Indica se o temporizador está em execução.
int state = 0; // Variável para controlar o estado da sequência de LEDs.

void setup_gpio_leds() {
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
}

// Configuração inicial ds botões
void setup_gpio_button() {
  // Configura o pino BTN_A (5) como entrada digital.
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);
}

// Função para ligar todos os LEDs
void turn_on_all_leds() {
    gpio_put(LED_YELLOW, true);
    gpio_put(LED_RED, true);
    gpio_put(LED_GREEN, true);
}

// Função de callback para desligar o LED após o tempo programado.
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    switch (state) {
        case 0: //liga todos os leds
            gpio_put(LED_RED, false);
            state = 1;
        break;
        case 1:
            gpio_put(LED_YELLOW, false);
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

// Função de callback para o botão
void gpio_irq_handler(uint gpio, uint32_t events) {

    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 200000) { // 200 ms de debouncing
        last_time = current_time; // Atualiza o tempo do último evento
        if (!leds_active) { // Se não tiver led aceso, BTN_A_PRESSIONADO volta a ser false
            BTN_A_PRESSIONADO = true; // Indica que o botão foi pressionado.
        }
    }
}

int main() {
    
    stdio_init_all();// Inicializa a comunicação serial para permitir o uso de printf.

    setup_gpio_leds();// Configura os pinos dos leds
    setup_gpio_button();//Configura os pinos do botão

    // Configura a interrupção para o botão.
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {    
        if (BTN_A_PRESSIONADO) { // Verifica se o botão foi pressionado.
            BTN_A_PRESSIONADO = false; // Volta a verificação do botão pressionado para false
            leds_active = true;    // Define 'led_active' como true para indicar que ainda tem led aceso
            turn_on_all_leds();
            add_alarm_in_ms(3000, turn_off_callback, NULL, false); // Agenda o primeiro alarme.
        }
        sleep_ms(10);
    }
    return 0;
}
