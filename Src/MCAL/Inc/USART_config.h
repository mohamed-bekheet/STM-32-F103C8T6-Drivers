#ifndef _USART_config_H_
#define _USART_config_H_


//CR1
#define WORD_LENGHT 0//(0 > 8databit,1 > 9 data bit)

/*
 * These bits are used for programming the stop bits.
00: 1 Stop bit
01: 0.5 Stop bit
10: 2 Stop bits
11: 1.5 Stop bit
The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5*/
//CR2
#define STOP_BITS 0 //

#endif
