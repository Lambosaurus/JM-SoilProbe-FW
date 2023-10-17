/*
 * led.c
 *
 *  Created on: Oct 17, 2023
 *      Author: hdert
 */
#include "GPIO.h"
#include "LED.h"

void LED_ColorSet(Colors_t Color)
{
	GPIO_EnableOutput(PB3, !(Color & Color_Red));
	GPIO_EnableOutput(PB4, !(Color & Color_Green));
	GPIO_EnableOutput(PB5, !(Color & Color_Blue));
}
