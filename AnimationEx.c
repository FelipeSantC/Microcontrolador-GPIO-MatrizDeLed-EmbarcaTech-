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
void desenhar_matriz(PIO pio, uint sm, const float *desenho, float r, float g, float b);

// Função de animação com 5 frames (efeito de onda)
void animacao3(PIO pio, uint sm) {
    // Definindo os 5 frames da animação
    // Vetores de imagens para matriz de LEDs
    const float frame1[NUM_PIXELS] = {
        0.0, 0.3, 0.3, 0.3, 0.0,
        0.0, 0.3, 0.0, 0.3, 0.0, 
        0.0, 0.3, 0.3, 0.3, 0.0,
        0.0, 0.3, 0.0, 0.3, 0.0,
        0.0, 0.3, 0.3, 0.3, 0.0
    };

    const float frame2[NUM_PIXELS] = {
        1.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 1.0
    };
    const float frame3[NUM_PIXELS] = {
        0.0, 0.3, 0.3, 0.3, 0.0,
        0.0, 0.3, 0.0, 0.3, 0.0, 
        0.0, 0.3, 0.3, 0.3, 0.0,
        0.0, 0.3, 0.0, 0.3, 0.0,
        0.0, 0.3, 0.3, 0.3, 0.0
    };

    const float frame4[NUM_PIXELS] = {
        1.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 1.0
    };
    const float frame5[NUM_PIXELS] = {
        0.0, 0.3, 0.3, 0.3, 0.0,
        0.0, 0.3, 0.0, 0.3, 0.0, 
        0.0, 0.3, 0.3, 0.3, 0.0,
        0.0, 0.3, 0.0, 0.3, 0.0,
        0.0, 0.3, 0.3, 0.3, 0.0
    };

    // Array de frames
    const float *frames[5] = {frame1, frame2, frame3, frame4, frame5};

    // Exibindo a animação
    for (int i = 0; i < 5; i++) {
        desenhar_matriz(pio, sm, frames[i], 0.0, 1.0, 0.0); // Verde
        sleep_ms(200); // Intervalo entre os frames
    }
}