#include "stm32f407xx.h"

void RCC_Init(void){
	//activer HSE a 8 MHZ
	RCC->CR |=(1<<16);
	
	//attendre que HSE soit prete
	while(!(RCC->CR&(1<<17)));
	
	// Choisir HSE comme source d'horloge
	RCC->CFGR |=(1<<0);
	
	// configurer HCLK a 4 MHZ (SYSCLK/2)
	RCC->CFGR |= (8<<4);
	
	// APB1 a 1 MHZ (HCLK/4)
	RCC->CFGR |= (5<<10);
	
	//APB2 a 2 MHZ (HCLK/2)
	RCC->CFGR |=(4<<13);
	
	// Sortir l'horloge SYSCLK réduite a 2 MHZ (SYSCLK/4)
	
	//1. activer l'horloge du Port C
	RCC->AHB1ENR |= (1<<2);
	
	//2. configurer la broche 9 comme fonction alternative
	GPIOC->MODER |= (1<<19);
	
	//3. réduire MCO2 a 2 MHZ (Sysclk /4);
	RCC->CFGR |=(6<<27);
}
int main(void){
	RCC_Init();
	while(1);
	
}