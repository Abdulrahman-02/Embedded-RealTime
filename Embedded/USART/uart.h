#ifndef UART_H
#define UART_H

#include "gpio.h"
#include <stdio.h>

void uart2_init(uint32_t br);
void uart2_printChar(char car);
char uart2_readChar(void);
void uart2_printString(char* message);


#endif