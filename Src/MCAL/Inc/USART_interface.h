#ifndef _USART_interface_H_
#define _USART_interface_H_

#include "USART_private.h"
#include "USART_config.h"


//donot forget to make GPIO pins alternative function

typedef enum{
	USART_1,
	USART_2,
	USART_3,
}USART_MODULES;

void USART_voidInit(USART_MODULES module,u16 baudRate);
void USART_voidTransmitChar(USART_MODULES module,char ch);
void USART_voidTransmitString(USART_MODULES module,char* data );


char USART_charRecieve();

#endif
