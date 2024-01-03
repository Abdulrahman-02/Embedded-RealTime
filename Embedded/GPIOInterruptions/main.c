#include "gpio.h"

void init_application(void){
	gpio_active_horloge(9); // activer les ports A et D
	RCC->APB2ENR |=(1<<14); //activer l'horloge de SYSCFG
	GPIO_SET_MODE(GPIOD, 12, GPIO_OUT);
	GPIO_SET_MODE(GPIOA, 0, GPIO_IN);
	gpio_select_source_it(GPIOA, 0);
	gpio_select_front(0, FRONT_MONTANT); // choisir le front montant
	// autoriserles its
	gpio_autoriser_it(0);
	NVIC_EnableIRQ(EXTI0_IRQn);
	__enable_irq();
}

int main(void){
	init_application();
	while(1){
	}
}

void EXTI0_IRQHandler(void){
	if(gpio_read_pin(GPIOD,12)==0)
		gpio_write_pin(GPIOD,12,1);
	else
		gpio_write_pin(GPIOD,12,0);
	// effacer l'indicateur d'interruption
	gpio_effacer_indicateur(0);
}
