//SMART TUNNEL AIRFLOW STABILIZATION SYSTEM (ADC CONTROL BLOCK)
//CODE BY: Amith Mathew Titus & Anugraha M.
//DATE: 14/12/2024 -> 15/12/2024
//LICENSE: MIT License

#include <avr/io.h>
#include "adc.h"

void adc_init(void) {
    ADMUX = (1 << REFS0); // Set reference voltage to AVcc
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC with prescaler of 128
}

uint16_t adc_read(uint8_t channel) {
    channel &= 0b00000111;           // Ensure channel is within 0-7
    ADMUX = (ADMUX & 0xF8) | channel; // Set the ADC channel
    ADCSRA |= (1 << ADSC);           // Start conversion
    while (ADCSRA & (1 << ADSC));    // Wait for conversion to complete
    return ADC;                      // Return 10-bit ADC value
}
