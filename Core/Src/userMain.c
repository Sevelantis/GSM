#include "main.h"

extern UART_HandleTypeDef huart2;

void w8(int delay)
{
	HAL_Delay(delay);
}

void userMain()
{
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		w8(88);
	}
}
