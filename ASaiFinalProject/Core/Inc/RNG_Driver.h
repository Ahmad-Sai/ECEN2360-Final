/*
 * RNG_Driver.h
 *
 *  Created on: Dec 8, 2024
 *      Author: Ahmad
 */

#ifndef INC_RNG_DRIVER_H_
#define INC_RNG_DRIVER_H_

#include <stm32f4xx_hal.h>

void RNG_Init();
uint32_t RNG_Generate();

#endif /* INC_RNG_DRIVER_H_ */
