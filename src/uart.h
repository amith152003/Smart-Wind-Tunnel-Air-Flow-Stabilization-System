#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(void);
void uart_transmit(char data);
void uart_transmit_string(const char *str);

#endif
