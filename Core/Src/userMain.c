#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void init_TIM_IT(TIM_HandleTypeDef *timer);
void w8(int delay);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern TIM_HandleTypeDef htim4;		// timer
extern UART_HandleTypeDef huart2;	// uart2
extern UART_HandleTypeDef huart3;	// uart2

unsigned counter_IT = 0;
uint16_t message_counter = 0;
char *message_welcome = "\n\n\r_____WELCOME_____\n\n\r";

void userMain()
{
	// init
	init_TIM_IT(&htim4);

	// welcome message
	HAL_UART_Transmit_IT(&huart3, message_welcome, (uint8_t)strlen(message_welcome));
}

void init_TIM_IT(TIM_HandleTypeDef *timer)
{
	HAL_TIM_Base_Start_IT(timer);
}

void w8(int delay)
{
	HAL_Delay(delay);
}

uint16_t msg_len = 80;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)	// 10Hz
{

	if(counter_IT % 1 == 0 && htim->Instance == TIM4)		// 10Hz
	{
		uint8_t *msg = (uint8_t*)calloc(msg_len, sizeof(uint8_t));

		// create & transmit message
		msg_len = sprintf(msg, "Ty piszesz program, a Lewandowski strzelil juz %d goli.\r\n", message_counter);
		HAL_UART_Transmit_IT(&huart3, msg, msg_len);

		free(msg);

		// blink
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		counter_IT = 0;
		message_counter++;
	}
	counter_IT++;
}
