#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//arquivo .pio
#include "pio_matrix.pio.h"

// Número de LEDs
#define NUM_PIXELS 25

// Pino de saída
#define OUT_PIN 9

// Definições dos pinos do teclado
#define LINHAS 4
#define COLUNAS 4

extern void animacao_A(PIO pio, uint sm);
extern void animacao_B(PIO pio, uint sm);
extern void animacao_C(PIO pio, uint sm);
extern void animacao_D(PIO pio, uint sm);
extern void animacao_Hashtag(PIO pio, uint sm);
extern void animacaoEx(PIO pio, uint sm);

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

// Acionamento da matriz de LEDs - ws2812b
void desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho) {
    for (int i = 0; i < NUM_PIXELS; i++) { // Aplica a cor ao padrão
        pio_sm_put_blocking(pio, sm, desenho[24-i]);
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

            if (tecla == 'A') {
                animacao_A(pio, sm);
            } else if (tecla == '1')
            {
                 animacaoEx(pio, sm);
            }  else if (tecla == 'B')
            {
                 animacao_B(pio, sm);
            } else if (tecla == 'C')
            {
                 animacao_C(pio, sm);
            } else if (tecla == '#')
            {
                 animacao_Hashtag(pio, sm);
            }  else if (tecla == 'D')
            {
                 animacao_D(pio, sm);
            }
            
            
            tecla_anterior = tecla; // Atualiza a tecla anterior
        }

        sleep_ms(100); // Reduz o tempo de espera
    }
}