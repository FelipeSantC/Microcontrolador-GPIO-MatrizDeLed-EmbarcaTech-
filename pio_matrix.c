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

extern void animacao_1(PIO pio, uint sm);
extern void animacao_3(PIO pio, uint sm);
extern void animacao_A(PIO pio, uint sm);
extern void animacao_B(PIO pio, uint sm);
extern void animacao_C(PIO pio, uint sm);
extern void animacao_D(PIO pio, uint sm);
extern void animacao_Hashtag(PIO pio, uint sm);
extern void animacaoEx(PIO pio, uint sm);
extern void configurar_teclado();
extern char ler_teclado();

// Acionamento da matriz de LEDs - ws2812b
void desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho) {
    for (int i = 0; i < NUM_PIXELS; i++) { // Aplica a cor ao padrão
        pio_sm_put_blocking(pio, sm, desenho[24-i]);
    }
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
            switch (tecla)
            {
            case '1':
                animacao_1(pio, sm);
                break;

            case '3':
                animacao_3(pio, sm);
                break;
            
            case 'A':
                animacao_A(pio, sm);
                break;

            case 'B':
                animacao_B(pio, sm);
                break;

            case 'C':
                animacao_C(pio, sm);
                break;

            case 'D':
                animacao_D(pio, sm);
                break;

            case '#':
                animacao_Hashtag(pio, sm);
                break;
            default:
                break;
            }
            tecla_anterior = tecla; // Atualiza a tecla anterior
        }

        sleep_ms(100); // Reduz o tempo de espera
    }
}