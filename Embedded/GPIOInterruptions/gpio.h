#ifndef GPIO_H
#define GPIO_H
#include "stm32f407xx.h"

#define GPIO_IN 0
#define GPIO_OUT 1
#define GPIO_ALT 2
#define GPIO_ADC 3

typedef enum {
	FRONT_MONTANT,
	FRONT_DES,
	LES_DEUX
} Type_Front;


void GPIO_SET_MODE(GPIO_TypeDef* port, uint8_t pin, uint8_t mode);
void gpio_write_pin(GPIO_TypeDef* port, uint8_t pin, uint8_t valeur);
uint8_t gpio_read_pin(GPIO_TypeDef* port, uint8_t pin);
void gpio_active_horloge(uint16_t masque);
void gpio_select_source_it(GPIO_TypeDef* port, uint8_t pin);
void gpio_autoriser_it(uint8_t pin);
void gpio_select_front(uint8_t pin, Type_Front front);
void gpio_effacer_indicateur(uint8_t pin);

#endif