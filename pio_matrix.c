#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

// Declaração da função animacao3 (definida em animacao3.c)
extern void animacao3(PIO pio, uint sm);

//arquivo .pio
#include "pio_matrix.pio.h"

// Número de LEDs
#define NUM_PIXELS 25

// Pino de saída
#define OUT_PIN 9

// Definições dos pinos do teclado
#define LINHAS 4
#define COLUNAS 4

// Pinagem das linhas e colunas do teclado
const uint pinos_linhas[LINHAS] = {8, 7, 6, 5}; 
const uint pinos_colunas[COLUNAS] = {4, 3, 2, 28}; 

// Mapeamento das teclas do teclado
const char teclas[LINHAS][COLUNAS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Vetores de imagens para matriz de LEDs
const float desenho[NUM_PIXELS] = {
    0.0, 0.3, 0.3, 0.3, 0.0,
    0.0, 0.3, 0.0, 0.3, 0.0, 
    0.0, 0.3, 0.3, 0.3, 0.0,
    0.0, 0.3, 0.0, 0.3, 0.0,
    0.0, 0.3, 0.3, 0.3, 0.0
};

const float desenho2[NUM_PIXELS] = {
    1.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0, 0.0, 
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 1.0
};

// Definição da intensidade de cores do LED
uint32_t matrix_rgb(float b, float r, float g) {
    return ((uint32_t)(g * 255) << 24) | ((uint32_t)(r * 255) << 16) | ((uint32_t)(b * 255) << 8);
}

// Acionamento da matriz de LEDs - ws2812b
void desenhar_matriz(PIO pio, uint sm, const float *desenho, float r, float g, float b) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(b, r, desenho[24 - i]); // Aplica a cor ao padrão
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Configuração do teclado
void configurar_teclado() {
    for (int i = 0; i < LINHAS; i++) {
        gpio_init(pinos_linhas[i]);
        gpio_set_dir(pinos_linhas[i], GPIO_OUT);
    }
    for (int i = 0; i < COLUNAS; i++) {
        gpio_init(pinos_colunas[i]);
        gpio_set_dir(pinos_colunas[i], GPIO_IN);
        gpio_pull_down(pinos_colunas[i]);
    }
}

// Leitura do teclado com debounce
char ler_teclado() {
    for (int linha = 0; linha < LINHAS; linha++) {
        gpio_put(pinos_linhas[linha], 1);
        sleep_ms(5); // Debounce
        for (int coluna = 0; coluna < COLUNAS; coluna++) {
            if (gpio_get(pinos_colunas[coluna])) {
                gpio_put(pinos_linhas[linha], 0);
                return teclas[linha][coluna];
            }
        }
        gpio_put(pinos_linhas[linha], 0);
    }
    return '\0'; 
}

// Função principal
int main() {
    PIO pio = pio0; 
    bool ok;

    // Configuração do clock para 128 MHz
    ok = set_sys_clock_khz(128000, false);
    stdio_init_all();

    configurar_teclado();

    printf("Iniciando a transmissão PIO\n");
    if (ok) printf("Clock set to %ld Hz\n", clock_get_hz(clk_sys));

    // Configuração da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    // Variável para armazenar a tecla anterior
    char tecla_anterior = '\0';

    while (true) {
        char tecla = ler_teclado();
        if (tecla != '\0' && tecla != tecla_anterior) { // Só redesenha se a tecla mudar
            printf("Tecla pressionada: %c\n", tecla);

            if (tecla == 'C') {
                // Desenho padrão (vermelho)
                desenhar_matriz(pio, sm, desenho, 1.0, 0.0, 0.0); // Vermelho
            } else if (tecla == '3') {
                // Executa a animação 3
                animacao3(pio, sm); // Chamada da função da animação 3
            } else {
                // Desenho "X" (azul)
                desenhar_matriz(pio, sm, desenho2, 0.0, 0.0, 1.0); // Azul
            }

            tecla_anterior = tecla; // Atualiza a tecla anterior
        }

        sleep_ms(100); // Reduz o tempo de espera
    }
}