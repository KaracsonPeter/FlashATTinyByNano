#include "avr/io.h"        // PORT definitions
#include "avr/interrupt.h" // ISR definition
#include "compat/ina90.h"  // _SLEEP()
#include "adc_pwm.h"
#include <stdbool.h>


void flip_output(int bit_to_flip) {
    PORTB ^= bit_to_flip;
}


volatile bool completed = true;
void start_adc_conversion(uint8_t ch) {
    // Select ADC channel with safety mask
    ADMUX = (ADMUX & 0xF0) | (ch & 0x0F);
    if (completed) {
        ADCSRA |= (1 << ADSC);
        completed = false;
        flip_output(PB4_MASK);
    }
}


volatile uint8_t adc_result = 0;
volatile uint16_t adc_moving_average = 0;
void sec_task() {
    // flip_output(PB3_MASK);
}

void ms_task() {
    start_adc_conversion(ADC1);
    adc_moving_average += adc_result;
    adc_moving_average = adc_moving_average>>1; //  /2
    OCR0B = adc_moving_average;
}


// Dumb down ADC from 10 to 8 bit
ISR(ADC_vect) {
    if (ADIF) {
        flip_output(PB3_MASK);
    }
    adc_result = ADCH;
    completed = true;
}


volatile uint16_t ms_count = 0;
ISR(TIMER1_COMPA_vect) {
    ms_task();
    if (ms_count > 10) {
        ms_count = 0;
        // Timer Interrupt called subroutine
        sec_task();
    }
    else {
        ms_count++;
    }
}

 
int main (void)
{
    system_init();
 
    while(1) {
        _SLEEP();
    }

    return 0;
}