/*
 * main.c
 *
 *  Created on: Aug 8, 2022
 *      Author: Omar Gamal
 */
#define STM_BLUEBILL


#include "STD_TYPES.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "OS_interface.h"
#include "SYSTICK_interface.h"
#include "testVoiceData.h"
#include "SEVENSEG_interface.h"

void LED_TOG0(void) {

	static u8 x = 0;
	GPIO_voidSetPinValue(GPIO_PORTA, 5, x);
	x = 1 - x;
}

void LED_TOG1(void) {

	static u8 x = 0;
	GPIO_voidSetPinValue(GPIO_PORTA, 6, x);
	x = 1 - x;
}

void LED_TOG2(void) {
	static u8 x = 0;
	GPIO_voidSetPinValue(GPIO_PORTA, 7, x);
	x = 1 - x;
}


SevenSeg_pins_t SevenSeg1 = {
		////a,b,c,d,e,f,g
		{ { GPIO_PORTA, 0 }, { GPIO_PORTA, 1 }, {GPIO_PORTA, 2 }, { GPIO_PORTA, 3 }, { GPIO_PORTA, 4 }, { GPIO_PORTA,5 }, { GPIO_PORTA, 6 } },
		{ GPIO_PORTA, 9},//enable pin
	    .activeHigh= 0,//active High
};
SevenSeg_pins_t SevenSeg2;

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

	RCC_voidInit();
	RCC_voidPeripheralClockEnable(RCC_APB2, GPIOA);
	STK_voidInit(RCC_u32GetSYSCLK(), SYSTICK_AHB_8);

//output configuration
	GPIO_voidSetPinMode(GPIO_PORTA, 0, GPIO_PIN_MODE_GP_PP_10MHZ_OUTPUT);
	GPIO_voidSetPinMode(GPIO_PORTA, 1, GPIO_PIN_MODE_GP_PP_10MHZ_OUTPUT);
	GPIO_voidSetPinMode(GPIO_PORTA, 2, GPIO_PIN_MODE_GP_PP_10MHZ_OUTPUT);


//pulled up pin
	//pulse to trigger logic analyzer
	GPIO_voidSetPinValue(GPIO_PORTA, 0, GPIO_HIGH);
	GPIO_voidSetPinValue(GPIO_PORTA, 0, GPIO_LOW);


	//GPIO_voidSetPinValue(GPIO_PORTA, 6, GPIO_HIGH);
	//STK_voidSetBusyWait(10000);
	//GPIO_voidSetPinValue(GPIO_PORTA, 6, GPIO_LOW);
	//STK_voidSetBusyWait(50000);
	//GPIO_voidSetPinValue(GPIO_PORTA, 6, GPIO_HIGH);

	//OS_voidCreateTask(0, 1, 5, LED_TOG0);
	//OS_voidCreateTask(1, 2, 1, LED_TOG1);
	//OS_voidCreateTask(2, 4, 3, LED_TOG2);

	//GPIO_voidSetPinValue(GPIO_PORTA, 8, GPIO_HIGH);
	//OS_voidStartScheduler();
	//SS_voidWriteDigit(&SevenSeg1, seven);
	while (1) {

	}

	return 0;
}

