#include "pico/stdlib.h"
#include "hardware/pio.h"

// Definindo o número de LEDs
#define NUM_PIXELS 25

// Declaração da função desenhar_matriz
void desenhar_matriz(PIO pio, uint sm, const float *desenho, float r, float g, float b);

// Função de animação com 5 frames (efeito de onda)
void animacao3(PIO pio, uint sm) {
    // Definindo os 5 frames da animação
    const float frames[5][NUM_PIXELS] = {
        {
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0
        },
        {
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0, 0.0,
            0.0, 1.0, 1.0, 1.0, 0.0,
            0.0, 0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0
        },
        {
            0.0, 0.0, 1.0, 0.0, 0.0,
            0.0, 1.0, 1.0, 1.0, 0.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
            0.0, 1.0, 1.0, 1.0, 0.0,
            0.0, 0.0, 1.0, 0.0, 0.0
        },
        {
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0, 0.0,
            0.0, 1.0, 1.0, 1.0, 0.0,
            0.0, 0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0
        },
        {
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0
        }
    };

    // Exibindo a animação
    for (int frame = 0; frame < 5; frame++) {
        desenhar_matriz(pio, sm, frames[frame], 0.0, 1.0, 0.0); // Apenas verde
        sleep_ms(200); // Intervalo entre os frames
    }
}