#include <stdio.h>
#include <stdlib.h>
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "pio_matrix.pio.h"

//Matriz LED
#define NUM_PIXELS 25
#define OUT_PIN 10

//Animação 2
double framesAnimation2[][25]={
    {
        0.5, 0.0, 0.0, 0.0, 0.5,
        0.0, 0.5, 0.0, 0.5, 0.0,
        0.0, 0.0, 0.5, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.5, 0.0,
        0.5, 0.0, 0.0, 0.0, 0.5,
    },
    {
        0.0, 0.0, 0.0, 0.0, 0.3,
        0.0, 0.0, 0.0, 0.3, 0.0,
        0.0, 0.0, 0.3, 0.0, 0.0,
        0.0, 0.3, 0.0, 0.0, 0.0,
        0.3, 0.0, 0.0, 0.0, 0.0,
    },
    {
        0.4, 0.4, 0.0, 0.0, 0.0,
        0.0, 0.4, 0.4, 0.0, 0.0,
        0.0, 0.0, 0.4, 0.4, 0.0,
        0.0, 0.0, 0.0, 0.4, 0.4,
        0.0, 0.0, 0.0, 0.0, 0.4,
    },
    {
        0.0, 0.0, 0.0, 0.3, 0.3,
        0.0, 0.0, 0.3, 0.3, 0.0,
        0.0, 0.3, 0.3, 0.0, 0.0,
        0.3, 0.3, 0.0, 0.0, 0.0,
        0.3, 0.0, 0.0, 0.0, 0.3,
    },
    {
        0.3, 0.3, 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3, 0.3, 0.3,
        0.3, 0.3, 0.3, 0.3, 0.3,
    }
};
//Controle de Intensidade
uint32_t matrix_rgb(double b, double r, double g){
    unsigned char R, G, B;
    R = r*255;
    G = g*255;
    B = b*255;
    return (G<<24) | (R<<16) | (B<<8);
}
//Parte de desenhar a animação
void desenho_pio(double*desenho, uint32_t, valor_led, PIO pio, uint sm, double r, double g, double b){
    for(int16_t i=0;i<NUM_PIXELS;i++){
        if(i%2==0){
            valor_led=matrix_rgb(desenho[24-i],r=0.0,g=0.0);
            pio_sm_put_blocking(pio, sm, valor_led);

        }else{
            valor_led=matrix_rgb(b=0.0, desenho[24-i, g=0.0]);
            pio_sm_blocking(pio,sm,valor_led);
        }
    }
}

//Função principal para Animação 2
void Animation2(){
    stdio_init_all();
    PIO pio=pio0;
    uint32_t valor_led;
    //Variáveis RGB com valores fixos
    double r=0.5, g=0.2, b=0.7;
    //Configurações PIO
    uint offset=pio_add_program(pio,&pio_matrix_program);
    uint sm=pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    while(true){
        for(int frame=0;frame<5;frame++){
            desenho_pio(framesAnimation2[frame],valor_led,pio,sm,r,g,b)
            sleep_ms(200);
        }
    }
}
