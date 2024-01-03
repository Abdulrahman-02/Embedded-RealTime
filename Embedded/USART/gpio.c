#include "gpio.h"

void GPIO_SET_MODE(GPIO_TypeDef* port, uint8_t pin, uint8_t mode){
	port->MODER |=(mode<<2*pin);
}

void gpio_write_pin(GPIO_TypeDef* port, uint8_t pin, uint8_t valeur){
	if(valeur==1)
		port->ODR |=(1<<pin);
	else
		port->ODR =~(1<<pin);
	
	/* ou bien
	if(valeur==1)
		port->BSRR |=(1<<pin);
	else
	  port->BSRR |=(1<<(16 + pin));
	*/
}

uint8_t gpio_read_pin(GPIO_TypeDef* port, uint8_t pin){
	return (port->IDR&(1<<pin))>>pin;
}

void gpio_active_horloge(uint16_t masque){
	RCC->AHB1ENR|=masque;
}
void gpio_select_source_it(GPIO_TypeDef* port, uint8_t pin){
	uint8_t registre, position, valeur;
	position = pin%4;
	registre = pin/4;
	switch((uint32_t)port){
		case((uint32_t)GPIOA): valeur=0;
													 break;
		case((uint32_t)GPIOB): valeur=1;
													 break;
		case((uint32_t)GPIOC): valeur=2;
													 break;
		case((uint32_t)GPIOD): valeur=3;
													 break;
		//......... continuer avec les autres ports
	}
	SYSCFG->EXTICR[registre] |=valeur<<4*position;
}
void gpio_autoriser_it(uint8_t pin){
	EXTI->IMR |=(1<<pin);
}

void gpio_select_front(uint8_t pin, Type_Front front){
	switch(front){
		case FRONT_MONTANT:EXTI->RTSR |=(1<<pin);
		                   break;
		case FRONT_DES: EXTI->FTSR|=(1<<pin);
		                   break;
		case LES_DEUX:EXTI->RTSR |=(1<<pin);
									EXTI->FTSR|=(1<<pin);
									
	}
}

void gpio_effacer_indicateur(uint8_t pin){
	EXTI->PR |=(1<<pin);
}

void select_alt_fun(GPIO_TypeDef* port, uint8_t pin, uint8_t fun){
	if(pin<8)
		port->AFR[0] |= fun<<4*pin;
	else
		port->AFR[1] |= fun<<4*pin;
}