#include "avr/io.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "time.h"
#include "compat/ina90.h"

#define F_CPU 1000000UL

#define PB0_MASK 0b00000001
#define PB1_MASK 0b00000010
#define PB2_MASK 0b00000100
#define PB3_MASK 0b00001000
#define PB4_MASK 0b00010000

void flip_output(int bit_to_flip) {
    PORTB ^= PB3_MASK;
}

int main_task() {
    flip_output(PB3_MASK);
    return 0;
}

ISR(TIMER1_OVF_vect) {
    // Timer Interrupt called subroutine
    int result = main_task();
}

void system_init() {
    // Set Pin 2 as output, all others as input
    DDRB = PB3_MASK;

    // Prescale 1MHz with 1024
    TCCR1 = 0b00001101;
    // Set compare register to 256/250 to get roughly 1 second interrupt
    OCR1A = 250;
    // Enable Timer/Counter1 related interrupts
    TIMSK = 0b01100100;

    // Enable Global interrupts
    sei();
}

 
int main (void)
{
    system_init();
 
    while(1) {
        _SLEEP();
    }

    return 0;
}