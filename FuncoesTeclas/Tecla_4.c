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

#define NUM_PIXELS 25

// Declaração da função desenhar_matriz
void desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho);

// Função de animação com 5 frames (efeito de onda)
void animacao_4(PIO pio, uint sm) {
    // Definindo os 5 frames da animação
    // Vetores de imagens para matriz de LEDs
    const uint32_t frame1[NUM_PIXELS] = {
        0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000,
        0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000,
        0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000,
        0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000,
        0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000
    };

    const uint32_t frame2[NUM_PIXELS] = {
        0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000,


    };
    const uint32_t frame3[NUM_PIXELS] = {
        0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00,
        0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 
        0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00,
        0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000
    };

    const uint32_t frame4[NUM_PIXELS] = {
        0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00,
        0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000, 
        0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00,
        0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000,
        0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00
    };

    const uint32_t frame5[NUM_PIXELS] = {
        0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000,
        0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000, 
        0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00,
        0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000,
        0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000
    };

    // Array de frames
    const uint32_t *frames[5] = {frame1, frame2, frame3, frame4, frame5};

    // Exibindo a animação
    for (int i = 0; i < 5; i++) {
        desenhar_matriz(pio, sm, frames[i]); // Verde
        sleep_ms(500); // Intervalo entre os frames
    }
}
