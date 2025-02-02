# Sistema Temporizador de um disparo (One Shot)

---

## Descrição do Projeto

Projeto da atividade **EmbarcaTech**, sobre Clock e Temporizadores. O sistema é ativado por um botão (pushbutton) e controla três LEDs (vermelho, amarelo e verde) em uma sequência pré-definida. O objetivo é demonstrar o uso de temporizadores, interrupções e callbacks no Pico SDK, além de implementar técnicas como debounce de botão para garantir um funcionamento robusto.

![image](https://github.com/user-attachments/assets/bd97eb56-e387-461a-94cb-81b6e9e342e5)


## Requisitos

- **Microcontrolador**: Raspberry Pi Pico ou Raspberry Pi Pico W (opcional)
- **Placa de Desenvolvimento:** BitDogLab (opcional).
- **Conta Criada no Wokwi Simulator**: [Wokwi](https://wokwi.com/).
- **Editor de Código**: Visual Studio Code (VS Code).
- **SDK do Raspberry Pi Pico** configurado no sistema.
- Ferramentas de build: **CMake** e **Ninja**.

---

## Instruções de Uso

### 1. Clone o Repositório

Clone o repositório para o seu computador:
```bash
git clone https://github.com/rafaelsouz10/one_shot_timer.git
cd one_shot_timer
code .
```
---

### 2. Instale as Dependências

Certifique-se de que o SDK do Raspberry Pi Pico está configurado corretamente no VS Code. As extensões recomendadas são:

- **C/C++** (Microsoft).
- **CMake Tools**.
- **Wokwi Simulator**.
- **Raspberry Pi Pico**.

---

### 3. Configure o VS Code

Abra o projeto no Visual Studio Code e siga as etapas abaixo:

1. Certifique-se de que as extensões mencionadas anteriormente estão instaladas.
2. No terminal do VS Code, compile o código clicando em "Compile Project" na interface da extensão do Raspberry Pi Pico.
3. O processo gerará o arquivo `.uf2` necessário para a execução no hardware real.

---

### 4. Teste no Simulador Wokwi Integrado ao VS Code

Após ter configurado o VS Code conforme descrito no item 3, siga os passos abaixo para simular o projeto:

1. Abra o arquivo `diagram.json` no Visual Studio Code.
2. Clique no botão "Play" disponível na interface.
3. Divirta-se interagindo com os componentes disponíveis no simulador integrado!

---

### 5. Teste no Hardware Real

#### Utilizando a Placa de Desenvolvimento BitDogLab com Raspberry Pi Pico W:

1. Conecte a placa ao computador no modo BOTSEEL:
   - Pressione o botão **BOOTSEL** (localizado na parte de trás da placa de desenvolvimento) e, em seguida, o botão **RESET** (localizado na frente da placa).
   - Após alguns segundos, solte o botão **RESET** e, logo depois, solte o botão **BOOTSEL**.
   - A placa entrará no modo de programação.

2. Compile o projeto no VS Code utilizando a extensão do [Raspberry Pi Pico W](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico):
   - Clique em **Compile Project**.

3. Execute o projeto clicando em **Run Project USB**, localizado abaixo do botão **Compile Project**.

---

### 6. Conexões e Esquemático

Abaixo está o mapeamento de conexões entre os componentes e a Raspberry Pi Pico W para os ambientes **Wokwi** (simulação) e **BitDogLab** (hardware físico):

   |  **Componentes** |   **Pino Conectacos (GPIO)**    |
   |------------------|---------------------------------|
   | LED_RED          | GPIO 13                         |
   | LED_YELLOW       | GPIO 12                         |
   | LED_YELLOW_BLUE  | GPIO 11                         |

**Observações**:

- No **Wokwi**, são utilizados LEDs individuais para cada cor (vermelho, amarelo e verde).
- No **BitDogLab**, é utilizado um LED RGB (Vermelho, verde e azul)

---

### 7. Funcionamento do Sistema

1. **Inicialização**:
   - O sistema aguarda o pressionamento do botão.
   - Quando o botão é pressionado, todos os três LEDs são ligados simultaneamente.

2. **Sequência de Temporização**:
   - Após 3 segundos, o LED vermelho é desligado.
   - Após mais 3 segundos, o LED amarelo é desligado.
   - Após mais 3 segundos, o LED verde é desligado.

3. **Bloqueio de Entrada**:
   - Durante a execução da sequência de temporização, o botão é desabilitado para evitar múltiplas ativações.
   - O botão só pode ser pressionado novamente após o término da sequência (quando todos os LEDs estiverem desligados).

4. **Debounce do Botão**:
   - Para evitar leituras errôneas causadas por ruídos mecânicos (bouncing), foi implementada uma rotina de **debounce em software**. O botão só é considerado pressionado se o sinal permanecer estável por **200 ms**.

---
