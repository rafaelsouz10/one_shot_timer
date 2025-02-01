#ifndef CONFIG_BTN_H
#define CONFIG_BTN_H

const uint BTN_A = 5;  // Define o pino GPIO 5 para ler o estado do botão.

bool BTN_A_PRESSIONADO = false; // Indica se o botão foi pressionado.

// Variáveis globais
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

// Configuração inicial ds botões
void setup_gpio_button() {
  // Configura o pino BTN_A (5) como entrada digital.
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);
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

#endif