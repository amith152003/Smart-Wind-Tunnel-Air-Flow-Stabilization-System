//SMART TUNNEL AIRFLOW STABILIZATION SYSTEM (UART SYSTEM)
//CODE BY: Amith Mathew Titus & Anugraha M.
//DATE: 14/12/2024 -> 15/12/2024
//LICENSE: MIT License

#include <avr/io.h>
#include "uart.h"

#define BAUD 9600
#define BAUDRATE ((F_CPU / (BAUD * 16UL)) - 1)

void uart_init(void) {
    UBRR0H = (BAUDRATE >> 8); // Set baud rate high byte
    UBRR0L = BAUDRATE;        // Set baud rate low byte
    UCSR0B = (1 << TXEN0);    // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Set data frame: 8 data bits, 1 stop bit
}

void uart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait until buffer is empty
    UDR0 = data;                      // Transmit data
}

void uart_transmit_string(const char *str) {
    while (*str) {
        uart_transmit(*str++);
    }
}
