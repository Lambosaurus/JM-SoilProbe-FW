#include "Core.h"
#include "GPIO.h"
#include "LED.h"
#include "UART.h"

bool ButtonWasPressed = false;
bool ContinueCyclingColors = false;

void ButtonOnPress(void)
{
	ButtonWasPressed = true;
	ContinueCyclingColors = false;
}

int main(void)
{
	CORE_Init();
	UART_Init(UART_1, 115200, UART_Mode_Default);
	GPIO_EnableInput(PA15, GPIO_Pull_Up);
	GPIO_OnChange(PA15, GPIO_IT_Falling, ButtonOnPress);

	while (1)
	{
		if (ButtonWasPressed)
		{
			UART_WriteStr(UART_1, "Hello, World!\r\n");
			ButtonWasPressed = false;
		}
	}
}

void CycleColors(void)
{
	ContinueCyclingColors = true;
	Color_Set(Color_Off);
	while (ContinueCyclingColors)
	{
		CORE_Delay(1000);
		Color_Set(Color_Off);
		CORE_Delay(1000);
		Color_Set(Color_Red);
		CORE_Delay(1000);
		Color_Set(Color_Yellow);
		CORE_Delay(1000);
		Color_Set(Color_Green);
		CORE_Delay(1000);
		Color_Set(Color_Cyan);
		CORE_Delay(1000);
		Color_Set(Color_Blue);
		CORE_Delay(1000);
		Color_Set(Color_Purple);
		CORE_Delay(1000);
		Color_Set(Color_White);
	}
}