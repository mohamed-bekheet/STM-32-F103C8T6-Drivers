

#include "USART_interface.h"
#include "BIT_MATH.h"


void USART_voidInit(USART_MODULES module,u16 baudRate){
	switch (module){
	case USART_1:
		USART1.CR1.UE=1;//enable usart
		USART1.CR1.M = WORD_LENGHT;//select word length in the frame
		USART1.CR2.STOP = STOP_BITS; //stop bits
		USART1.BRR =  baudRate  //select baudrate
		break;
	case USART_2:
			break;
	case USART_3:
			break;
	}
}




void USART_voidTransmitChar(USART_MODULES module,char ch);

void USART_voidTransmitString(USART_MODULES module,char* data );
