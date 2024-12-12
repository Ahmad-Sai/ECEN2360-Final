/*
 * Game_Driver.h
 *
 *  Created on: Dec 8, 2024
 *      Author: Ahmad
 */

#ifndef INC_GAME_DRIVER_H_
#define INC_GAME_DRIVER_H_

#include <stm32f4xx_hal.h>
#include <RNG_Driver.h>
#include <stdbool.h>
#include <string.h>
#include <LCD_Driver.h>

// Tetris Logic
void Game_CheckSpace();
void Game_PlaceBlock();
void Game_GenerateBlock();
bool Game_CheckCollision();

// Functions to move block
void Game_BlockRotate();
void Game_BlockMoveLeft();
void Game_BlockMoveLeft();
void Game_BlockMoveDown();
#endif /* INC_GAME_DRIVER_H_ */
