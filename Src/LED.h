/*
 * led.h
 *
 *  Created on: Oct 17, 2023
 *      Author: hdert
 */

#ifndef LED_H_
#define LED_H_

typedef enum
{
	Color_Red = 0b001,
	Color_Green = 0b010,
	Color_Blue = 0b100,
	Color_Purple = Color_Red | Color_Blue,
	Color_Yellow = Color_Red | Color_Green,
	Color_Cyan = Color_Green | Color_Blue,
	Color_White = Color_Red | Color_Green | Color_Blue,
	Color_Off = 0b000,
} Colors_t;

void LED_ColorSet(Colors_t Color);

#endif /* LED_H_ */
