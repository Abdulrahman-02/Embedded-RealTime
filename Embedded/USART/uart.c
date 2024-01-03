#include "uart.h"
#include <string.h>
void uart2_init(uint32_t br){
	//1. Activer les horloges des ports GPIO à utiliser comme Tx et Rx
  gpio_active_horloge(1);
	
	//2. Configurer le mode des pins à utiliser comme mode de fonction alternative
	// PA2 -> TX
	// PA3 -> RX
	GPIO_SET_MODE(GPIOA, 2, GPIO_ALT);
	GPIO_SET_MODE(GPIOA, 3, GPIO_ALT);
	select_alt_fun(GPIOA,2,7);
	select_alt_fun(GPIOA,3,7);
	
	//3. Activer l’horloge de l’UART 2
	RCC->APB1ENR |= (1<<17);
	
	// 4. choisir le BR
	double div, frac;
	int m, f;
	div = 16000000.0/(16*br);
	m =(int)(div);
	frac = div -m;
	f = (int)(frac*16);
	USART2->BRR |=(m<<4)|f;
	
	//5. demarrer usart2
	USART2->CR1 |=(1<<2)|(1<<3)|(1<<13);
} 
void uart2_printChar(char car){
	while(!(USART2->SR&(1<<7)));
	USART2->DR = car;
}

char uart2_readChar(void){
		while(!(USART2->SR&(1<<5)));
	return USART2->DR;
}

void uart2_printString(char* message){
	for(int i=0;i< strlen(message); i++){
		uart2_printChar(message[i]);
	}
}



// interfacage avec stdio.h

struct __FILE{
 int handle;
};

FILE __stdin={0};
FILE __stdout={1};
FILE __stder={2};

int fgetc(FILE *f){
   return uart2_readChar();
}

int fputc(int c,FILE *f){
	uart2_printChar(c);
}

