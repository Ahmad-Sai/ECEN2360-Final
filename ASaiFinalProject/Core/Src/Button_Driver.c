/*
 * Button_Driver.c
 *
 *  Created on: Sep 28, 2024
 *      Author: Ahmad
 */
#include <Button_Driver.h>

void BUTTON_Init(){
	GPIO_InitTypeDef buttonConfig = {0};

	buttonConfig.Pin = BUTTON_PIN_NUMBER;
	buttonConfig.Mode = GPIO_MODE_INPUT;
	buttonConfig.Pull = GPIO_NOPULL;
	buttonConfig.Speed = GPIO_SPEED_FREQ_HIGH;

	BUTTON_Clock_Enable();
	HAL_GPIO_Init(GPIOA, &buttonConfig);
}

void BUTTON_Interrupt_Init(){
	GPIO_InitTypeDef buttonConfig = {0};

	buttonConfig.Pin = BUTTON_PIN_NUMBER;
	buttonConfig.Mode = GPIO_MODE_IT_RISING;
	buttonConfig.Pull = GPIO_NOPULL;
	buttonConfig.Speed = GPIO_SPEED_FREQ_HIGH;

	BUTTON_Clock_Enable();
	HAL_GPIO_Init(GPIOA, &buttonConfig);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void BUTTON_Clock_Enable(){
	__HAL_RCC_GPIOA_CLK_ENABLE();
}

bool BUTTON_Status(){
	uint8_t val = HAL_GPIO_ReadPin(BUTTON_PORT_VALUE, BUTTON_PIN_NUMBER);
	if (val==1){
		return true;
	}
	return false;
}
