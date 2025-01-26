#include <stdio.h>
#include <stdlib.h>
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

#include "pio_matrix.pio.h"

// Matriz de LED
#define NUM_PIXELS 25
#define OUT_PIN 9

// Animação
double framesAnimation[5][25] = {
    {
     0.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 1.0, 0.0, 0.0,
     0.0, 1.0, 1.0, 1.0, 0.0,
     1.0, 1.0, 1.0, 1.0, 1.0,
    },
    {
     1.0, 1.0, 1.0, 1.0, 1.0,
     0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 0.0, 1.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0, 0.0,
    },
    {
     1.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 1.0, 1.0,
     1.0, 1.0, 1.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 1.0, 1.0,
     1.0, 0.0, 0.0, 0.0, 0.0,
    },
    {
     0.0, 0.0, 0.0, 0.0, 1.0,
     1.0, 1.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 0.0, 1.0,
    },
    {
     1.0, 0.0, 0.0, 0.0, 1.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     0.0, 0.0, 1.0, 0.0, 0.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     1.0, 0.0, 0.0, 0.0, 1.0,
    }
};

// Função para controle de intensidade das cores dos LEDs
uint32_t matrix_rgb(double b, double r, double g)
{
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Função para desenhar a animação
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b) {
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        // Ajusta o brilho do LED com base no valor do desenho
        valor_led = matrix_rgb(b * desenho[24 - i], r * desenho[24 - i], g * desenho[24 - i]);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Função Principal do Código
void Animation1() {
    stdio_init_all();

    PIO pio = pio0;
    uint32_t valor_led;

    // Configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    // Define as cores para cada frame (R, G, B)
    double colors[5][3] = {
        {0.0, 0.0, 1.0}, // Azul
        {1.0, 0.0, 0.0}, // Vermelho
        {0.0, 1.0, 0.0}, // Verde
        {1.0, 1.0, 0.0}, // Amarelo
        {0.5, 0.0, 0.5}  // Roxo
    };

    while (true) {
        for (int frame = 0; frame < 5; frame++) {
            double r = colors[frame][0];
            double g = colors[frame][1];
            double b = colors[frame][2];

            
            desenho_pio(framesAnimation[frame], valor_led, pio, sm, r, g, b);
            sleep_ms(300); // Tempo entre os quadros
        }
    }
}
