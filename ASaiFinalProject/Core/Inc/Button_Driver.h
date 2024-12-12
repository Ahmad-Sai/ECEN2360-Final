/*
 * Button_Driver.h
 *
 *  Created on: Sep 26, 2024
 *      Author: Ahmad
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_
#include <stdbool.h>

#include <stm32f4xx_hal.h>

#define BUTTON_PORT_VALUE GPIOA
#define BUTTON_PIN_NUMBER GPIO_PIN_0
#define BUTTON_PRESSED 1
#define BUTTON_UNPRESSED 0


void BUTTON_Init();
void BUTTON_Interrupt_Init();
void BUTTON_Clock_Enable();
bool BUTTON_Status();

#endif /* BUTTON_DRIVER_H_ */
