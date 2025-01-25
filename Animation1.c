#include <stdio.h>
#include <stdlib.h>
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

#include "pio_matrix.pio.h"

//Matriz de LED 
#define NUM_PIXELS 25
#define OUT_PIN 9


void initPio(){

    PIO pio = pio0; 

    //configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

}
int main(){

    bool ok;
    uint16_t i;
    uint32_t valor_led;
    double r = 0.0, b = 0.0 , g = 0.0;

    stdio_init_all();

    return 0;
}