#include <stdio.h> // Biblioteca padrão do C.
#include "pico/stdlib.h" // Biblioteca padrão do Raspberry Pi Pico para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   // Biblioteca para gerenciamento de temporizadores e alarmes.
#include "include/config_leds.h"   //Biblioteca com todas as configurações e funções relacionadas aos leds
#include "include/config_btn.h"     //Biblioteca com todas as configurações e funções relacionadas ao botão

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
