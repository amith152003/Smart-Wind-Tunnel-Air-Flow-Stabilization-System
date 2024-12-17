//SMART WIND TUNNEL AIR FLOW STABILIZATION SYSTEM (MAIN SYSTEM)
//CODE BY: Amith Mathew Titus & Anugraha M.
//DATE: 14/12/2024 -> 15/12/2024
//LICENSE: MIT License

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "adc.h"
#include "uart.h"
#include "pwm.h"
#include "pid.h"

#define TIME_DELAY 100 // Delay in milliseconds

int main(void) {
    char buffer[80]; // Buffer for formatted string

    // Initialize modules
    adc_init();      // Initialize ADC
    uart_init();     // Initialize UART
    pwm_init();      // Initialize PWM

    // Main loop
    while (1) {
        // Read setpoint from potentiometer (ADC0)
        uint16_t pot_value = adc_read(0);
        float setpoint = pot_value * (255.0 / 1023.0); // Map to 0-255
        float angle_set = 30 + pot_value * ((60 - 30)/ 1023.0);
        // Read feedback from flex sensor (ADC1)
        uint16_t flex_value = adc_read(1);
        float feedback = flex_value * (255.0 / 1023.0); // Map to 0-255
        float angle_Present = 30 + flex_value * ((60 - 30)/ 1023.0);
        // Compute PID output
        float control_signal = pid_control(setpoint, feedback);

        // Clamp control signal to PWM range (0-255)
        if (control_signal > 255) control_signal = 255;
        if (control_signal < 0) control_signal = 0;
        pwm_set_duty((uint8_t)control_signal);

        // Transmit debugging information
        sprintf(buffer, "Setpoint: %u, Feedback: %u, Set Angle: %u, Flap Angle: %u, Output: %u\r\n",
                (uint16_t)setpoint, (uint16_t)feedback, (uint16_t)angle_set, (uint16_t)angle_Present, (uint16_t)control_signal);
        uart_transmit_string(buffer);

        _delay_ms(TIME_DELAY); // Small delay for stability
    }

    return 0; // This line is never reached
}
