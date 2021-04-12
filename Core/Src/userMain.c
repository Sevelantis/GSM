#include "main.h"

void w8(int delay)
{
	HAL_Delay(delay);
}

void userMain()
{
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(88);
	}
}
