#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "time.h"

#define BLINK_DELAY_MS 250
#define F_CPU 8000000UL

#define PB0_MASK 0b00000001
#define PB1_MASK 0b00000010
#define PB2_MASK 0b00000100
#define PB3_MASK 0b00001000
#define PB4_MASK 0b00010000

void flip_output(int bit_to_flip) {
    PORTB ^= PB3_MASK;
}

ISR(TIMER1_OVF_vect) {
    flip_output(PB3_MASK);
}

void system_init() {
    DDRB = PB3_MASK;

    TCCR1 = 0b00001001;
    OCR1A = 50;
    TIMSK = 0b00000100;

    sei();
}

 
int main (void)
{
    system_init();
 
    while(1) {
        // Do other task
    }
    return 0;
}