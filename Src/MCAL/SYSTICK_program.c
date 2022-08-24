/*
 * SYS_TICK_program.c
 *
 *  Created on: Aug 10, 2022
 *      Author: Omar Gamal
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_interface.h"
#include "SYSTICK_config.h"
#include "SYSTICK_private.h"


/*
 *
 * SysTick timer (STK)
 * The processor has a 24-bit system timer, SysTick, that counts down from the reload value to
 * zero, reloads (wraps to) the value in the LOAD register on the next clock edge, then counts
 * down on subsequent clocks.
 * When the processor is halted for debugging the counter does not decrement.
 * */


void (*CallBack)(void) = (void *) 0;

u8 IntervalState = SYSTICK_PERIODIC_INTERVAL;
static u32 StkFlcFreq;
static u32 MAX_TIME_STK_us ; // in milli seconds
/*
 * STK_voidInit
 * description: Selects the clock source of the SysTick (AHB, AHB/8)
 */
void STK_voidInit(u32 Copy_u32SyClckFreq,u8 Copy_u8ClkSRC){

	switch(Copy_u8ClkSRC)
	{
	case SYSTICK_AHB_8:
		CLR_BIT(SYSTICK->CTRL,2);
		StkFlcFreq = Copy_u32SyClckFreq/8;
		break;
	case SYSTICK_AHB:
		SET_BIT(SYSTICK->CTRL,2);
		StkFlcFreq = Copy_u32SyClckFreq;
		break;
	}

	MAX_TIME_STK_us = (1677216/(StkFlcFreq)*1000000);//=1677216
}




/*
 * STK_voidSetBusyWait
 * description: Starts a synchronous wait (normal delay based on frequency of the system clock)
 */
void STK_voidSetBusyWait(u32 Copy_u32TickCount){

	/* Disable the systick interrupt
	 * Set LOAD value
	 * start the timer
	 * empty loop until the flag is raised
	 * reset the flag
	 * Reset the LOAD register
	 * stop the timer
	 */
	CLR_BIT(SYSTICK->CTRL, 1);//Disable the systick interrupt
	SYSTICK->LOAD = (Copy_u32TickCount) & 0x00FFFFFF;//max is 24bit 0x00FFFFFF
	SET_BIT(SYSTICK->CTRL, 0);// Counter enable and start counting
	while(!(GET_BIT(SYSTICK->CTRL, 16)));//bit16::Returns 1 if timer counted to 0 since last time this was read.
	CLR_BIT(SYSTICK->CTRL, 0);// Counter disable and stop counting
}


/*
 * STK_voidSetBusyWait
 * description: Starts a synchronous wait (normal delay based on frequency of the system clock)
 */
void STK_voidDelayus(u32 Copy_u32TimeIn_us){
//need more development
	u32 test = ( (Copy_u32TimeIn_us/1000000)*StkFlcFreq) ;
	u32 test3 = StkFlcFreq ;
	u32 test2 = MAX_TIME_STK_us ;


	u32 test1 =  Copy_u32TimeIn_us*(StkFlcFreq/1000000) ;

	float residual = (Copy_u32TimeIn_us/ MAX_TIME_STK_us);// MAX_TIME_STK_us=1677216
	//STK_voidSetBusyWait((u32) (Copy_u32TimeIn_us % MAX_TIME_STK_us) );
	for (; residual >= 0 ; residual --){
		STK_voidSetBusyWait((u32) test1 );
	}


/*
u32 tempTime2 = 1 ;
do{
    //STK_voidSetBusyWait((u32)(Copy_u32TimeIn_ms*StkFlcFreq/1000));
	u32 tempTime = (Copy_u32TimeIn_ms*StkFlcFreq/1000);
	CLR_BIT(SYSTICK->CTRL, 1);//Disable the systick interrupt
	SYSTICK->LOAD = (tempTime) & 0x00FFFFFF;//max is 24bit 0x00FFFFFF
	SET_BIT(SYSTICK->CTRL, 0);// Counter enable and start counting
	while(!(GET_BIT(SYSTICK->CTRL, 16)));//bit16::Returns 1 if timer counted to 0 since last time this was read.
	CLR_BIT(SYSTICK->CTRL, 0);// Counter disable and stop counting
}
while( Copy_u32TimeIn_ms = Copy_u32TimeIn_ms - 0xf4240);

*/
}

/*
 * STK_voidSetPeriodicInterval
 * description: Starts a periodic interval synchronous wait
 */
void STK_voidSetPeriodicInterval(u32 Copy_u32TickCount, void (*ptr)(void)){

	/* Set LOAD value
	 * assign the callback function to the handler
	 * Enable the interrupt
	 * start the timer
	 */
	IntervalState = SYSTICK_PERIODIC_INTERVAL;
	SYSTICK->LOAD = (Copy_u32TickCount - 1) & 0x00FFFFFF;
	CallBack = ptr;
	SET_BIT(SYSTICK->CTRL, 1);//SysTick exception request enable
	SET_BIT(SYSTICK->CTRL, 0);// Counter enable
}



/*
 * STK_voidSetSingleInterval
 * description: Starts a single interval asynchronous wait
 */
void STK_voidSetSingleInterval(u32 Copy_u32TickCount, void (*ptr)(void)){

	/* Set LOAD value
	 * assign the callback function to the handler
	 * Enable the interrupt
	 * start the timer
	 */

	IntervalState = SYSTICK_SINGLE_INTERVAL;
	SYSTICK->LOAD = (Copy_u32TickCount) & 0x00FFFFFF;
	CallBack = ptr;
	SET_BIT(SYSTICK->CTRL, 1);
	SET_BIT(SYSTICK->CTRL, 0);
}

/*
 * STK_voidStopTimer
 * description: Stops the Timer
 */
void STK_voidStopTimer(void){
	CLR_BIT(SYSTICK->CTRL, 0);// Counter disable
}

/*
 * STK_u32GetRemainingTicks
 * description: Gets the number of ticks remaining until we reach zero
 */
u32 STK_u32GetRemainingTicks(void){


	return 0;
}
/*
 * STK_u32GetElapsedTicks
 * description: Gets the number of ticks elapsed since we started counting
 */
u32 STK_u32GetElapsedTicks(void){

	return 0;
}

void SysTick_Handler(void){
	CallBack();
	if(IntervalState == SYSTICK_PERIODIC_INTERVAL){

	}else{
		CLR_BIT(SYSTICK->CTRL, 0);
	}
	SYSTICK->VAL = 0; // Clearing the flag
}
