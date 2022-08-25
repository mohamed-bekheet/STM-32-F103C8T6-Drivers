/*
 * main.c
 *
 *  Created on: Aug 8, 2022
 *      Author: mohamed moustafa aly ::: mohamed.bekheet2023@gmail.com
 */
#define STM_BLUEBILL


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"

#include "OS_interface.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"
#include "testVoiceData.h"
#include "SEVENSEG_interface.h"

u32 SYSFREQ ;//from rcc

u32 STK_FREQ=0;//from systick handler
unsigned long long STK_COUNTS=0;//from systick handler

#define LED_PORT GPIO_PORTA
#define LED_PIN 4

 u32 OnTime = 100;//in ms
 u32 OffTime = 100;//in ms

 void LED_PWM_RUN(void){
	u32 currT_ms=STK_COUNTS;//*1000/SYSFREQ;
 	if(currT_ms <= OnTime)GPIO_voidSetPinValue(LED_PORT, LED_PIN, GPIO_HIGH);
 	else if (currT_ms < OnTime+OffTime)GPIO_voidSetPinValue(LED_PORT, LED_PIN, GPIO_LOW);
 	else if (currT_ms >= OnTime+OffTime) STK_COUNTS = 0;

 }

void LED_PWM_INIT(u32 OnTime_ms, u32 OffTime_ms){

	STK_voidSetPeriodicInterval( (SYSFREQ/8)/1000 ,LED_PWM_RUN) ;//1000 >>1ms every count is 1microsecond
	OnTime = OnTime_ms ;
	OffTime = OffTime_ms ;
}


void LED_TOG0(void) {

	static u8 x = 0;
	GPIO_voidSetPinValue(GPIO_PORTA, 0, x);
	x = 1 - x;
}

void LED_TOG1(void) {

	static u8 x = 0;
	GPIO_voidSetPinValue(GPIO_PORTA, 1, x);
	x = 1 - x;
}

void LED_TOG2(void) {
	static u8 x = 0;
	GPIO_voidSetPinValue(GPIO_PORTA, 2, x);
	x = 1 - x;
}


SevenSeg_pins_t SevenSeg1 = {
		////a,b,c,d,e,f,g
		{ { GPIO_PORTA, 0 }, { GPIO_PORTA, 1 }, {GPIO_PORTA, 2 }, { GPIO_PORTA, 3 }, { GPIO_PORTA, 4 }, { GPIO_PORTA,5 }, { GPIO_PORTA, 6 } },
		{ GPIO_PORTA, 9},//enable pin
	    .activeHigh= 0,//active High
};
SevenSeg_pins_t SevenSeg2 = {
		////a,b,c,d,e,f,g
		{ { GPIO_PORTA, 0 }, { GPIO_PORTA, 1 }, {GPIO_PORTA, 2 }, { GPIO_PORTA, 3 }, { GPIO_PORTA, 4 }, { GPIO_PORTA,5 }, { GPIO_PORTA, 6 } },
		{ GPIO_PORTA, 10},//enable pin
	    .activeHigh= 0,//active High
};

/*
void SendAudio(u8 *sound_header, unsigned int header_lenght) {
	GPIO_SetPinValue(GPIOA, 8, GPIO_HIGH);
	static u16 x = 0;

	GPIO_SetChannelGroupValue(GPIOA, 0, 8, sound_header[x++]);

	if (x == header_lenght)
		x = 0;

	GPIO_SetPinValue(GPIOA, 8, GPIO_LOW);

}
*/


int main(void) {
//////////////////////////////////////////INITIALIZATION/////////////////////////////////////
	RCC_voidInit();
	RCC_voidPeripheralClockEnable(RCC_APB2, GPIOA);
	SYSFREQ = RCC_u32GetSYSCLK();
	//NVIC_voidInit();
	//NVIC_voidEnableInterrupt(SYSTICK);

	STK_voidInit(SYSFREQ, SYSTICK_AHB_8);


	//output configuration
	//take about 10 micro second
	GPIO_voidSetPinMode(LED_PORT, LED_PIN, GPIO_PIN_MODE_GP_PP_10MHZ_OUTPUT);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//pulled up pin

////////////////////////////////////APPLICATION//////////////////////////////////////////////

LED_PWM_INIT(2, 2);//min 2ms

	while (1) {

	}

	return 0;
}
//********************************************************************************//
	//OS_voidCreateTask(0, 1, 5, LED_TOG0);
	//OS_voidCreateTask(1, 2, 1, LED_TOG1);
	//OS_voidCreateTask(2, 4, 3, LED_TOG2);

	//GPIO_voidSetPinValue(GPIO_PORTA, 8, GPIO_HIGH);
	//OS_voidStartScheduler();
/************************************************************************************/

	//SS_voidWriteDigit(&SevenSeg1, seven);
