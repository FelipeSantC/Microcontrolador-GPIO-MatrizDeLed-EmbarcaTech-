#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

#define NUM_PIXELS 25

// Declaração da função desenhar_matriz
void desenhar_matriz(PIO pio, uint sm, const uint32_t *desenho);

// Função de animação com 5 frames (efeito de onda)
void animacao_Hashtag(PIO pio, uint sm) {
    // Definindo os 5 frames da animação
    // Vetores de imagens para matriz de LEDs
    const uint32_t frame1[NUM_PIXELS] = {
        0x33333300, 0x33333300, 0x33333300, 0x33333300, 0x33333300,
        0x33333300, 0x33333300, 0x33333300, 0x33333300, 0x33333300, 
        0x33333300, 0x33333300, 0x33333300, 0x33333300, 0x33333300,
        0x33333300, 0x33333300, 0x33333300, 0x33333300, 0x33333300,
        0x33333300, 0x33333300, 0x33333300, 0x33333300, 0x33333300
    };
    // Exibindo a animação
    desenhar_matriz(pio, sm, frame1); 
    sleep_ms(200); // Intervalo entre os frames
}