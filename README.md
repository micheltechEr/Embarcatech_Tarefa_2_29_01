# Temporizador One-Shot com Transição de LEDs - Raspberry Pi Pico

## Descrição do Projeto
Este projeto foi desenvolvido para praticar o uso de **temporizadores one-shot** conforme ensinado na aula. A atividade consiste em implementar um sistema onde, ao pressionar um botão, três LEDs (vermelho, amarelo e verde) são acionados simultaneamente e desligados sequencialmente após intervalos de tempo pré-definidos.

O código utiliza alarmes (`add_alarm_in_ms`) para gerenciar as transições entre os estados dos LEDs, garantindo que cada LED permaneça aceso por 3 segundos antes de ser desligado. Além disso, o sistema implementa **debounce** para evitar múltiplas detecções de pressionamento do botão em um único clique.

---

## Componentes Utilizados
- **LED Vermelho (Pino 11):** Primeiro LED a ser desligado após 3 segundos.
- **LED Amarelo (Pino 12):** Segundo LED a ser desligado após 6 segundos.
- **LED Verde (Pino 13):** Último LED a ser desligado após 9 segundos.
- **Botão (Pino 5):** Aciona a sequência de LEDs.
- **Raspberry Pi Pico:** Placa utilizada para executar o código.
- **Resistores:** Para limitar a corrente nos LEDs (recomenda-se 220Ω ou 330Ω).

---

## Funcionalidades do Projeto
- **Acionamento via Botão:**
  - Ao pressionar o botão, todos os LEDs (vermelho, amarelo e verde) são acesos simultaneamente.
- **Transição Sequencial:**
  - Após 3 segundos, o LED vermelho é desligado.
  - Após mais 3 segundos, o LED amarelo é desligado.
  - Após outros 3 segundos, o LED verde é desligado.
- **Debounce:**
  - Implementação de debounce para evitar múltiplas detecções de pressionamento do botão.

---

## Guia de Funcionamento na Sua Máquina

Para executar este projeto localmente, siga as instruções abaixo:

### 1. **Clone o repositório:**
   - Abra o **VS Code** e clone este repositório para sua máquina.

### 2. **Importe o projeto:**
   - Certifique-se de ter as extensões do **Raspberry Pi Pico** instaladas no VS Code.
   - Importe o projeto para poder compilá-lo e executá-lo na placa RP2040.

### 3. **Conecte a placa:**
   - Conecte a placa ao computador via USB e coloque-a no modo **BOOTSEL**.

### 4. **Compile o código:**
   - Compile o código diretamente no VS Code.

### 5. **Simulação no Wokwi:**
   - Para simular o projeto, abra o arquivo `diagram.json` disponível nos arquivos do projeto e execute-o no [Wokwi](https://wokwi.com).

### 6. **Execute na placa:**
   - Após a compilação e com a placa no modo **BOOTSEL**, clique em **Executar** ou **Run** para carregar o programa na placa.

---

## Funcionamento do Sistema

O sistema funciona da seguinte forma:
1. **Estado Inicial:**
   - Todos os LEDs estão apagados.
   - O botão está pronto para ser pressionado.

2. **Pressionamento do Botão:**
   - Quando o botão é pressionado:
     - Todos os LEDs (vermelho, amarelo e verde) são acesos simultaneamente.
     - Um alarme é agendado para desligar o LED vermelho após 3 segundos.

3. **Desligamento Sequencial:**
   - Após 3 segundos:
     - O LED vermelho é desligado.
     - Um novo alarme é agendado para desligar o LED amarelo após mais 3 segundos.
   - Após outros 3 segundos:
     - O LED amarelo é desligado.
     - Um novo alarme é agendado para desligar o LED verde após mais 3 segundos.
   - Finalmente, o LED verde é desligado, e o sistema retorna ao estado inicial.

4. **Debounce:**
   - O código implementa debounce com um pequeno atraso de 50 ms para evitar múltiplas detecções de pressionamento do botão em um único clique.

---

## Código Fonte

O código fonte está organizado da seguinte forma:
- **Função `configure_gpio`:** Configura os pinos GPIO como entrada ou saída.
- **Callbacks de Alarme (`turn_off_red`, `turn_off_yellow`, `turn_off_green`):** Controlam o desligamento sequencial dos LEDs.
- **Função `has_button_pressed`:** Detecta o pressionamento do botão e inicia a sequência de LEDs.
- **Loop Principal (`main`):** Verifica continuamente se o botão foi pressionado.

---

## Observações Finais

Este projeto foi desenvolvido com foco em boas práticas de programação, organização e documentação. Ele é ideal para estudantes que desejam praticar o uso de temporizadores one-shot e GPIOs no Raspberry Pi Pico.

Caso tenha dúvidas ou sugestões, sinta-se à vontade para abrir uma **issue** ou entrar em contato.

---

### Créditos
- **Autor:** Ângelo Miguel Ribeiro Cerqueira Lima
- **Data:** 03/02/2024

---
