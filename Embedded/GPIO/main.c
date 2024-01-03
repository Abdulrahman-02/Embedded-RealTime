#include "gpio.h"

void init_app(void){
	gpio_active_horloge(9);
	GPIO_SET_MODE(GPIOA,0,GPIO_IN);
	GPIO_SET_MODE(GPIOD,12,GPIO_OUT);
}

int main(void){
	init_app();
	while(1){
		if(gpio_read_pin(GPIOA, 0)==1)
			gpio_write_pin(GPIOD,12, 1);
		else
			gpio_write_pin(GPIOD,12, 0);
	}
}