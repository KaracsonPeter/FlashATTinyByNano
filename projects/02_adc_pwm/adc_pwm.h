#define PB0_MASK 0b00000001
#define PB1_MASK 0b00000010
#define PB2_MASK 0b00000100
#define PB3_MASK 0b00001000
#define PB4_MASK 0b00010000

#define ADC0 0b00000000
#define ADC1 0b00000001


void system_init() {
    // Turn off pull-up resistors
    MCUCR |= 0b01000000;

    // Set Pin 2 as output, all others as input
    DDRB |= PB1_MASK;
    DDRB |= PB3_MASK;
    DDRB |= PB4_MASK;

    // 5V(00x0) OR 1.1V internal ref (10x0), ADC Left Adjust Result, ADC1 is choosen 0001
    ADMUX = 0b00100001;  // page 134/234
    // Enable ADC, Start Conversion, Auto Trigger off, Conversion result is updated, ADC ISR on, Pre-scaler 32 (101)
    ADCSRA = 0b10001101; // 136/234 (Pre-scaler 32)
    // ADCSRB = 0b01000000; // Bipolar mode off, ACME must be 1, Input Polarity Reversal off, x, x, Free Running mode

    TCCR0A = 0b00100011;
    TCCR0B = 0b00001010;

    OCR0A = 255; // PWM: Value of 100% Duty
    OCR0B = 127; // PWM: Init with 50% duty

    // Prescale 500kHz with 64 (page 101/234)
    TCCR1 = 0b11011101;
    // Set compare register to 255/124 to get roughly 1 ms interrupt
    OCR1A = 210;  // 1000Hz -> (0.001 / (1 / 6400000/64)) - 1
    // Enable Timer/Counter1 related interrupts
    TIMSK = 0b01000000;

    // Enable Global interrupts
    sei();
    ADCSRA |= (1 << ADSC);
}