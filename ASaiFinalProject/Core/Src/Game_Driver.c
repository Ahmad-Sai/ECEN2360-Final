/*
 * Game_Driver.c
 *
 *  Created on: Dec 8, 2024
 *      Author: Ahmad
 */
#include <Game_Driver.h>

uint32_t blocks[7][4][4][4][2] = {
    // I-Block
	{
		{
			{{1, LCD_COLOR_TEAL}, {1, LCD_COLOR_TEAL}, {1, LCD_COLOR_TEAL}, {1, LCD_COLOR_TEAL}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		},
		{
			{{0, 0}, {1, LCD_COLOR_TEAL}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_TEAL}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_TEAL}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_TEAL}, {0, 0}, {0, 0}}
		},
		{
			{{1, LCD_COLOR_TEAL}, {1, LCD_COLOR_TEAL}, {1, LCD_COLOR_TEAL}, {1, LCD_COLOR_TEAL}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		},
		{
			{{0, 0}, {1, LCD_COLOR_TEAL}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_TEAL}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_TEAL}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_TEAL}, {0, 0}, {0, 0}}
		}
	},
    // O-Block
	{
		{
			{{1, LCD_COLOR_YELLOW}, {1, LCD_COLOR_YELLOW}, {0, 0}, {0, 0}},
			{{1, LCD_COLOR_YELLOW}, {1, LCD_COLOR_YELLOW}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		},
		{
			{{1, LCD_COLOR_YELLOW}, {1, LCD_COLOR_YELLOW}, {0, 0}, {0, 0}},
			{{1, LCD_COLOR_YELLOW}, {1, LCD_COLOR_YELLOW}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		},
		{
			{{1, LCD_COLOR_YELLOW}, {1, LCD_COLOR_YELLOW}, {0, 0}, {0, 0}},
			{{1, LCD_COLOR_YELLOW}, {1, LCD_COLOR_YELLOW}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		},
		{
			{{1, LCD_COLOR_YELLOW}, {1, LCD_COLOR_YELLOW}, {0, 0}, {0, 0}},
			{{1, LCD_COLOR_YELLOW}, {1, LCD_COLOR_YELLOW}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}
	},
    // T-Block
	{
		{
			{{0, 0}, {1, LCD_COLOR_MAGENTA}, {0, 0}, {0, 0}},
			{{1, LCD_COLOR_MAGENTA}, {1, LCD_COLOR_MAGENTA}, {1, LCD_COLOR_MAGENTA}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		},
		{
			{{0, 0}, {1, LCD_COLOR_MAGENTA}, {0, 0}, {0, 0}},
			{{1, LCD_COLOR_MAGENTA}, {1, LCD_COLOR_MAGENTA}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_MAGENTA}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		},
		{
			{{1, LCD_COLOR_MAGENTA}, {1, LCD_COLOR_MAGENTA}, {1, LCD_COLOR_MAGENTA}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_MAGENTA}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		},
		{
			{{0, 0}, {1, LCD_COLOR_MAGENTA}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_MAGENTA}, {1, LCD_COLOR_MAGENTA}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_MAGENTA}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}
	},
    // L-Block
	 {
		{
			{{1, LCD_COLOR_BLUE}, {0, 0}, {0, 0}, {0, 0}},
			{{1, LCD_COLOR_BLUE}, {1, LCD_COLOR_BLUE}, {1, LCD_COLOR_BLUE}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		},
		{
			{{0, 0}, {1, LCD_COLOR_BLUE}, {1, LCD_COLOR_BLUE}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_BLUE}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_BLUE}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		},
		{
			{{1, LCD_COLOR_BLUE}, {1, LCD_COLOR_BLUE}, {1, LCD_COLOR_BLUE}, {0, 0}},
			{{0, 0}, {0, 0}, {1, LCD_COLOR_BLUE}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		},
		{
			{{0, 0}, {1, LCD_COLOR_BLUE}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_BLUE}, {0, 0}, {0, 0}},
			{{1, LCD_COLOR_BLUE}, {1, LCD_COLOR_BLUE}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}
	},
    // J-Block
	 {
		{
			{{0, 0}, {0, 0}, {1, LCD_COLOR_ORANGE}, {0, 0}},
			{{1, LCD_COLOR_ORANGE}, {1, LCD_COLOR_ORANGE}, {1, LCD_COLOR_ORANGE}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}, // Up
		{
			{{0, 0}, {1, LCD_COLOR_ORANGE}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_ORANGE}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_ORANGE}, {1, LCD_COLOR_ORANGE}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}, // Right
		{
			{{1, LCD_COLOR_ORANGE}, {1, LCD_COLOR_ORANGE}, {1, LCD_COLOR_ORANGE}, {0, 0}},
			{{1, LCD_COLOR_ORANGE}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}, // Down
		{
			{{1, LCD_COLOR_ORANGE}, {1, LCD_COLOR_ORANGE}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_ORANGE}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_ORANGE}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		} // Left
	},
    // S-Block
	{
		{
			{{0, 0}, {1, LCD_COLOR_RED}, {1, LCD_COLOR_RED}, {0, 0}},
			{{1, LCD_COLOR_RED}, {1, LCD_COLOR_RED}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}, // Horizontal
		{
			{{0, 0}, {1, LCD_COLOR_RED}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_RED}, {1, LCD_COLOR_RED}, {0, 0}},
			{{0, 0}, {0, 0}, {1, LCD_COLOR_RED}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}, // Vertical
		{
			{{0, 0}, {1, LCD_COLOR_RED}, {1, LCD_COLOR_RED}, {0, 0}},
			{{1, LCD_COLOR_RED}, {1, LCD_COLOR_RED}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}, // Horizontal (repeated)
		{
			{{0, 0}, {1, LCD_COLOR_RED}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_RED}, {1, LCD_COLOR_RED}, {0, 0}},
			{{0, 0}, {0, 0}, {1, LCD_COLOR_RED}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		} // Vertical (repeated)
	},
    // Z-Block
	{
		{
			{{1, LCD_COLOR_GREEN}, {1, LCD_COLOR_GREEN}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_GREEN}, {1, LCD_COLOR_GREEN}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}, // Horizontal
		{
			{{0, 0}, {0, 0}, {1, LCD_COLOR_GREEN}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_GREEN}, {1, LCD_COLOR_GREEN}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_GREEN}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}, // Vertical
		{
			{{1, LCD_COLOR_GREEN}, {1, LCD_COLOR_GREEN}, {0, 0}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_GREEN}, {1, LCD_COLOR_GREEN}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		}, // Horizontal (repeated)
		{
			{{0, 0}, {0, 0}, {1, LCD_COLOR_GREEN}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_GREEN}, {1, LCD_COLOR_GREEN}, {0, 0}},
			{{0, 0}, {1, LCD_COLOR_GREEN}, {0, 0}, {0, 0}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}}
		} // Vertical (repeated)
	}
};

uint32_t nextGrid[10][10][2] ={0};
uint32_t currentGrid[10][10][2] ={0};
uint32_t clearGrid[10][10][2] = {0};
uint8_t locationX = 4;
uint8_t locationY = 0;
uint8_t currentRot = 0;
uint32_t currentBlock[4][4][2];
uint32_t clearBlock[4][4][2] = {0};
uint8_t random_num;

void Game_PlaceBlock(uint32_t grid[10][10][2]) {
    for (uint8_t y = 0; y < 4; y++) {
        for (uint8_t x = 0; x < 4; x++) {
            if (currentBlock[y][x][0] == 1) {
                uint8_t gridX = locationX + x;
                uint8_t gridY = locationY + y;
                if (gridX < 10 && gridY < 10) {
                	grid[gridY][gridX][0] = 1;
                	grid[gridY][gridX][1] = currentBlock[y][x][1];
                }
            }
        }
    }
}

void Game_GenerateBlock(){
	random_num = RNG_Generate();
    memcpy(currentBlock, blocks[random_num][0], sizeof(blocks[random_num][0]));
}

void Game_BlockRotate(){
	uint8_t previousRot = currentRot;
	currentRot +=1;
	if (currentRot >= 4) {
	        currentRot = 0;
	}
    memcpy(currentBlock, clearBlock, sizeof(blocks[random_num][currentRot]));
    memcpy(currentBlock, blocks[random_num][currentRot], sizeof(blocks[random_num][currentRot]));
	bool collision = Game_CheckCollision();
	if (!collision){
		memcpy(nextGrid, currentGrid, sizeof(currentGrid));
		Game_PlaceBlock(nextGrid);
		Draw_Grid(currentGrid);
		Draw_Grid(nextGrid);
	} else {
		currentRot = previousRot;
	    memcpy(currentBlock, clearBlock, sizeof(blocks[random_num][currentRot]));
        memcpy(currentBlock, blocks[random_num][currentRot], sizeof(blocks[random_num][currentRot]));
	}
}

void Game_BlockMoveDown(){
	uint8_t previousY = locationY;
	locationY +=1;
	bool collision = Game_CheckCollision();

	if (!collision){
		Game_PlaceBlock(nextGrid);
	} else {
		locationY = previousY;
		Game_PlaceBlock(currentGrid);
	}
}

bool Game_CheckCollision(){
	for (uint8_t y = 0; y < 4; y++) {
		for (uint8_t x = 0; x < 4; x++) {
			if (currentBlock[y][x][0] == 1) {
				uint8_t gridX = locationX + x;
				uint8_t gridY = locationY + y;
				if (gridX >= 10 || gridY >= 10) {
				    memcpy(nextGrid, clearGrid, sizeof(clearGrid));
				    memcpy(currentGrid, clearGrid, sizeof(clearGrid));
					return true;
				}
				if (currentGrid[gridY][gridX][0] != 0) {
					return true;
				}
			}
		}
	}
    return false;
}

uint32_t start_time = 0;
uint32_t end_time = 0;
uint32_t elapsed_time = 0;

void Game_Start() {
    start_time = HAL_GetTick();
    Game_GenerateBlock();
    Game_PlaceBlock(nextGrid);
    Draw_Grid(nextGrid);
    HAL_Delay(1000);
    while (1) {
    	// check top row
    	for(int i =0; i < 10; i++){
        	if(currentGrid[0][i][0]){
        	    end_time = HAL_GetTick();
        	    char game_time[4] = {'\0'};
        	    if(end_time < start_time){
        	    	elapsed_time = (0xFFFFFFFF - start_time)+end_time;
        	    	sprintf(game_time, "%d", elapsed_time/1000);
        	    	ResultScreen(game_time);
        	    } else {
        	    	elapsed_time = end_time - start_time;
        	    	sprintf(game_time, "%d", elapsed_time/1000);
        	    	ResultScreen(game_time);
        	    }
        		return;
        	}

    	}


		if (Game_CheckCollision()) {
			Game_PlaceBlock(currentGrid);
			memcpy(nextGrid, currentGrid, sizeof(currentGrid));
			locationY = 0;
			currentRot = 0;
			Game_GenerateBlock();
			if (Game_CheckCollision()) {
				Game_PlaceBlock(currentGrid);
				Draw_Grid(currentGrid);
				break;
			} else {
				Game_PlaceBlock(nextGrid);
				Draw_Grid(nextGrid);
			}
		} else{
			memcpy(nextGrid, currentGrid, sizeof(currentGrid));
			Game_BlockMoveDown();
			if (!Game_CheckCollision()) {
				Draw_Grid(nextGrid);
			}
		}
		HAL_Delay(1000);
    }
    end_time = HAL_GetTick();

    char game_time[4] = {'\0'};
    if(end_time < start_time){
    	elapsed_time = (0xFFFFFFFF - start_time)+end_time;
    	sprintf(game_time, "%d", elapsed_time/1000);
    	ResultScreen(game_time);
    } else {
    	elapsed_time = end_time - start_time;
    	sprintf(game_time, "%d", elapsed_time/1000);
    	ResultScreen(game_time);
    }
}
