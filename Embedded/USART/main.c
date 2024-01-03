#include "uart.h"

const char* message = "Hello World!\r\n";
int nombre= 10;
float c = 30.4;

int main(void){
	uart2_init(115200);
	printf("%s",message);
	printf("La valeur de nombre est %d",nombre);
	while(1){
		char c = uart2_readChar();
		if(c=='\r')
			uart2_printChar('\n');
		uart2_printChar(c);
	}
}