#include "Core.h"
#include "GPIO.h"
#include "LED.h"
#include "UART.h"
#include "TSC.h"
#include "stdio.h"

#define Max(a, b) ((a > b) ? a : b)

bool ButtonWasPressed = false;
bool ContinueCyclingColors = false;

void ButtonOnPress(void)
{
	ButtonWasPressed = true;
	ContinueCyclingColors = false;
}

uint32_t Capacitance(void)
{
	const uint32_t REFERENCE_SIZE = 10000;
	TSC_Init();

	TSC_EnableCapacitor(TSC_G1_Channel2, PA1);
	TSC_EnableInput(TSC_G1_Channel3, PA2);

	uint32_t result = REFERENCE_SIZE / TSC_Read(TSC_G1_Channel3);

	TSC_Deinit();

	return result;
}

uint32_t Percentage(uint32_t capacitance)
{
	const uint32_t MIN = 12;
	const uint32_t MAX = 526;
	const uint32_t RELATIVE_MAX = MAX - MIN;
	return ((Max(capacitance, MIN) - MIN) * 100) / RELATIVE_MAX;
}

Colors_t ColorFromPercentage(uint32_t percentage)
{
	if (percentage > 40) {
		return Color_Blue;
	}
	if (percentage > 20) {
		return Color_Green;
	}
	if (percentage > 10) {
		return Color_Yellow;
	}
	return Color_Red;
}

void PrintResult(uint32_t result, uint32_t percentage)
{
	const uint32_t SIZE = 20;
	char output[SIZE];

	snprintf(output, SIZE, "%ld: %lu%%\r\n", result, percentage);
	UART_WriteStr(UART_1, output);
}

void FlashColor(Colors_t Color)
{
	uint32_t loop = 4;
	const uint32_t DELAY = 250;
	while (loop--)
	{
		LED_ColorSet(Color);
		CORE_Delay(DELAY);
		LED_ColorSet(Color_Off);
		CORE_Delay(DELAY);
	}
}

void CycleColors(void)
{
	ContinueCyclingColors = true;
	LED_ColorSet(Color_Off);
	while (ContinueCyclingColors)
	{
		CORE_Delay(1000);
		LED_ColorSet(Color_Off);
		CORE_Delay(1000);
		LED_ColorSet(Color_Red);
		CORE_Delay(1000);
		LED_ColorSet(Color_Yellow);
		CORE_Delay(1000);
		LED_ColorSet(Color_Green);
		CORE_Delay(1000);
		LED_ColorSet(Color_Cyan);
		CORE_Delay(1000);
		LED_ColorSet(Color_Blue);
		CORE_Delay(1000);
		LED_ColorSet(Color_Purple);
		CORE_Delay(1000);
		LED_ColorSet(Color_White);
	}
}

int main(void)
{
	CORE_Init();
//	UART_Init(UART_1, 115200, UART_Mode_Default);
	GPIO_EnableInput(PA15, GPIO_Pull_Up);
	GPIO_OnChange(PA15, GPIO_IT_Falling, ButtonOnPress);
//	uint32_t result;

	while (1)
	{
		if (ButtonWasPressed)
		{
			FlashColor(ColorFromPercentage(Percentage(Capacitance())));
//			result = Capacitance();
//			FlashColor(ColorForRange(Percentage(result)));
//			PrintResult(result, Percentage(result));
//			UART_WriteStr(UART_1, "Hello, World!\r\n");
			ButtonWasPressed = false;
		}
		CORE_Stop();
	}
}

