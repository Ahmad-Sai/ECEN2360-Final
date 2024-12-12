/*
 * RNG_Driver.c
 *
 *  Created on: Dec 8, 2024
 *      Author: Ahmad
 */

#include <RNG_Driver.h>
#include <stdio.h>
RNG_HandleTypeDef hrng;

void RNG_Init() {
    __HAL_RCC_RNG_CLK_ENABLE();
    hrng.Instance = RNG;
    HAL_RNG_Init(&hrng);
}

uint32_t RNG_Generate() {
    uint32_t randomValue;
    HAL_RNG_GenerateRandomNumber(&hrng, &randomValue);
    int t = (randomValue)%7;
    printf("TEST");
    printf("%d\n",t);
    return (randomValue)%7;
}
