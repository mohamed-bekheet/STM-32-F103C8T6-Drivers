#ifndef _USART_private_H_
#define _USART_private_H_

#include "STD_TYPES.h"
//this controller have multiple USART module

typedef struct{
	vu32 SBK:1;
	vu32 RWU:1;
	vu32 RE:1;
	vu32 TE:1;
	vu32 IDLEIE:1;
	vu32 RXNEIE:1;
	vu32 TCIE:1;
	vu32 TXEIE:1;
	vu32 PEIE:1;
	vu32 PS:1;
	vu32 PCE:1;
	vu32 WAKE:1;
	vu32 M:1;
	vu32 UE:1;
	vu32 RES:18;
}USART_CR1_t;

typedef struct{
	vu32 ADD:4;
	vu32 RES1:1;
	vu32 LBDL:1;
	vu32 RES2:1;
	vu32 LBCL:1;
	vu32 CHPA:1;
	vu32 CPOL:1;
	vu32 CLKEN:1;
	vu32 STOP:2;
	vu32 LINEN:1;
	vu32 RES3:1;
}USART_CR2_t;

typedef struct{
	vu32 SR;
	vu32 DR;
	vu32 BRR;
	USART_CR1_t CR1;
	USART_CR2_t CR2;
	vu32 CR3;
	vu32 GTPR;
}USART_t;

#define USART1   	(*((volatile USART_t*)0x40013800))
#define USART2   	(*((volatile USART_t*)0x40004400))
#define USART3   	(*((volatile USART_t*)0x40004800))



#endif
