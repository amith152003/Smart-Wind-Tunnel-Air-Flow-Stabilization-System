//SMART TUNNEL AIRFLOW STABILIZATION SYSTEM (PWM SYSTEM BLOCK)
//CODE BY: Amith Mathew Titus & Anugraha M.
//DATE: 14/12/2024 -> 15/12/2024
//LICENSE: MIT License

#include <avr/io.h>
#include <util/delay.h> // Include this for _delay_us
#include "pwm.h"

void pwm_init(void) {
    DDRB |= (1 << PB1);                    // Set PB1 (OC1A) as output
    TCCR1A = (1 << WGM11) | (1 << COM1A1); // Fast PWM mode, non-inverted output
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS11); // Prescaler of 8, fast PWM mode
    ICR1 = 255;                            // Set the TOP value for 8-bit resolution
}

void pwm_set_duty(uint8_t duty) {
    OCR1A = duty; // Set PWM duty cycle (0-255)
    _delay_us(10);
}


