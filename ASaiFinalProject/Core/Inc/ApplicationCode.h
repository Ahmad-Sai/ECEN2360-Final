/*
 * RNG_Driver.c
 *
 *  Created on: Dec 8, 2024
 *      Author: Ahmad
 */

#include <LCD_Driver.h>
#include <Button_Driver.h>
#include <stm32f4xx_hal.h>
#include <stdbool.h>
#include <stdio.h>
#include <RNG_Driver.h>
#include <Game_Driver.h>

#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

void generateBlock();
void ApplicationInit(void);
void LCD_Visual_Demo(void);
void ClearDisplay(void);
void RotateBlock(void);
#if (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1) && (COMPILE_TOUCH_INTERRUPT_SUPPORT == 0)

#endif /* INC_APPLICATIONCODE_H_ */

