#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void init_TIM_IT(TIM_HandleTypeDef *timer);
void w8(int delay);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern TIM_HandleTypeDef htim4;		// timer
extern UART_HandleTypeDef huart2;	// uart2

unsigned counter_IT = 0;
uint16_t message_counter = 0;
char *message_welcome = "\n\n\r_____WELCOME_____\n\n\r";

void userMain()
{
	// init
	init_TIM_IT(&htim4);

	// welcome message
//	HAL_UART_Transmit_IT(&huart2, message_welcome, strlen(message_welcome));
}

void init_TIM_IT(TIM_HandleTypeDef *timer)
{
	HAL_TIM_Base_Start_IT(timer);
}

void w8(int delay)
{
	HAL_Delay(delay);
}

uint16_t msg_len = 40;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)	// 10Hz
{

	if(counter_IT % 5 == 0 && htim->Instance == TIM4)		// 1Hz
	{
		// allocate memory for message
		uint8_t msg[40];

		// create & transmit message
		sprintf(msg, "wiadoomosc nr %d.\n\r", message_counter);
		HAL_UART_Transmit_IT(&huart2, msg, 40);

		// blink
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		counter_IT = 0;
		message_counter++;
	}
	counter_IT++;
}
