#include "gpio.h"

int32_t temps_attente = 0;
void initsystick(void){
	
	SysTick->LOAD |=16000-1;
	SysTick->CTRL |=7;
	
}
void delay(uint32_t delai){
	temps_attente = delai;
	while(temps_attente>0);
}
void init_gpio(){
	gpio_active_horloge(8);
	GPIO_SET_MODE(GPIOD, 12, GPIO_OUT);
}

int main(void){
	initsystick();
	init_gpio();
	while(1){
		gpio_write_pin(GPIOD, 12, 1);
		delay(1000);
		gpio_write_pin(GPIOD, 12, 0);
		delay(1000);
	}
}

void SysTick_Handler(void){
	if(temps_attente>0)
		temps_attente--;
}