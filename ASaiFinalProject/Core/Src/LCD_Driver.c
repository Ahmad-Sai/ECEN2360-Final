/*
 * LCD_Driver.c
 *
 *  Created on: Sep 28, 2023
 *      Author: Ahmad
 */

#include "LCD_Driver.h"

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */


static LTDC_HandleTypeDef hltdc;
static RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
static FONT_t *LCD_Currentfonts;
static uint16_t CurrentTextColor   = 0xFFFF;

/*
 * fb[y*W+x] OR fb[y][x]
 * Alternatively, we can modify the linker script to have an end address of 20013DFB instead of 2002FFFF, so it does not place variables in the same region as the frame buffer. In this case it is safe to just specify the raw address as frame buffer.
 */
//uint32_t frameBuffer[(LCD_PIXEL_WIDTH*LCD_PIXEL_WIDTH)/2] = {0};		//16bpp pixel format. We can size to uint32. this ensures 32 bit alignment


//Someone from STM said it was "often accessed" a 1-dim array, and not a 2d array. However you still access it like a 2dim array,  using fb[y*W+x] instead of fb[y][x].
uint16_t frameBuffer[LCD_PIXEL_WIDTH*LCD_PIXEL_HEIGHT] = {0};			//16bpp pixel format.


void LCD_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable the LTDC clock */
  __HAL_RCC_LTDC_CLK_ENABLE();

  /* Enable GPIO clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /* GPIOA configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 |
                           GPIO_PIN_11 | GPIO_PIN_12;
  GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Alternate= GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

 /* GPIOB configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_8 | \
                           GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

 /* GPIOC configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

 /* GPIOD configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_6;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

 /* GPIOF configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_10;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

 /* GPIOG configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | \
                           GPIO_PIN_11;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);

  /* GPIOB configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
  GPIO_InitStructure.Alternate= GPIO_AF9_LTDC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* GPIOG configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_12;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
}

void LTCD_Layer_Init(uint8_t LayerIndex)
{
	LTDC_LayerCfgTypeDef  pLayerCfg;

	pLayerCfg.WindowX0 = 0;	//Configures the Window HORZ START Position.
	pLayerCfg.WindowX1 = LCD_PIXEL_WIDTH;	//Configures the Window HORZ Stop Position.
	pLayerCfg.WindowY0 = 0;	//Configures the Window vertical START Position.
	pLayerCfg.WindowY1 = LCD_PIXEL_HEIGHT;	//Configures the Window vertical Stop Position.
	pLayerCfg.PixelFormat = LCD_PIXEL_FORMAT_1;  //INCORRECT PIXEL FORMAT WILL GIVE WEIRD RESULTS!! IT MAY STILL WORK FOR 1/2 THE DISPLAY!!! //This is our buffers pixel format. 2 bytes for each pixel
	pLayerCfg.Alpha = 255;
	pLayerCfg.Alpha0 = 0;
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
	if (LayerIndex == 0){
		pLayerCfg.FBStartAdress = (uintptr_t)frameBuffer;
	}
	pLayerCfg.ImageWidth = LCD_PIXEL_WIDTH;
	pLayerCfg.ImageHeight = LCD_PIXEL_HEIGHT;
	pLayerCfg.Backcolor.Blue = 0;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;
	if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, LayerIndex) != HAL_OK)
	{
		LCD_Error_Handler();
	}
}

void clearScreen(void)
{
  LCD_Clear(0,LCD_COLOR_WHITE);
}

void LTCD__Init(void)
{
	hltdc.Instance = LTDC;
	/* Configure horizontal synchronization width */
	hltdc.Init.HorizontalSync = ILI9341_HSYNC;
	/* Configure vertical synchronization height */
	hltdc.Init.VerticalSync = ILI9341_VSYNC;
	/* Configure accumulated horizontal back porch */
	hltdc.Init.AccumulatedHBP = ILI9341_HBP;
	/* Configure accumulated vertical back porch */
	hltdc.Init.AccumulatedVBP = ILI9341_VBP;
	/* Configure accumulated active width */
	hltdc.Init.AccumulatedActiveW = 269;
	/* Configure accumulated active height */
	hltdc.Init.AccumulatedActiveH = 323;
	/* Configure total width */
	hltdc.Init.TotalWidth = 279;
	/* Configure total height */
	hltdc.Init.TotalHeigh = 327;
	/* Configure R,G,B component values for LCD background color */
	hltdc.Init.Backcolor.Red = 0;
	hltdc.Init.Backcolor.Blue = 0;
	hltdc.Init.Backcolor.Green = 0;

	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
	PeriphClkInitStruct.PLLSAI.PLLSAIR = 4;
	PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_8;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
	/* Polarity */
	hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

	LCD_GPIO_Init();

	if (HAL_LTDC_Init(&hltdc) != HAL_OK)
	 {
	   LCD_Error_Handler();
	 }

	ili9341_Init();
}

void LCD_Draw_Pixel(uint16_t x, uint16_t y, uint16_t color)
{
	if (x<0 || x>239 || y<0 || y> 319){return;}
	frameBuffer[y*LCD_PIXEL_WIDTH+x] = color;
}


void LCD_Draw_Circle_Fill(uint16_t Xpos, uint16_t Ypos, uint16_t radius, uint16_t color)
{
    for(int16_t y=-radius; y<=radius; y++)
    {
        for(int16_t x=-radius; x<=radius; x++)
        {
            if(x*x+y*y <= radius*radius)
            {
            	LCD_Draw_Pixel(x+Xpos, y+Ypos, color);
            }
        }
    }
}

void LCD_Draw_Block(uint16_t Xpos, uint16_t Ypos, uint16_t Color){
	for(int y =Ypos; y<=Ypos+32; y++){
		LCD_Draw_Horizontal_Line(Xpos,y,24, Color);
	}
}


void DrawGrid(){
	for(int x =0; x<=240; x+=24){
		LCD_Draw_Vertical_Line(x,0,320,LCD_COLOR_WHITE);
	}
	for(int y =0; y<=320; y+=32){
		LCD_Draw_Horizontal_Line(0,y,240,LCD_COLOR_WHITE);
	}
}


void Draw_Grid(uint32_t currentGrid[10][10][2]){
	LCD_Clear(0,LCD_COLOR_BLACK);
	for(int y =0; y<10; y++){
		for(int x = 0; x<10; x++){
			if(currentGrid[y][x][0]){
				LCD_Draw_Block(x*24, y*32, currentGrid[y][x][1]);
			}
		}
	}
	DrawGrid();
}


void LCD_Draw_Vertical_Line(uint16_t x, uint16_t y, uint16_t len, uint16_t color)
{
  for (uint16_t i = 0; i < len; i++)
  {
	  LCD_Draw_Pixel(x, i+y, color);
  }
}

void LCD_Draw_Horizontal_Line(uint16_t x, uint16_t y, uint16_t len, uint16_t color)
{
  for (uint16_t i = 0; i < len; i++)
  {
	  LCD_Draw_Pixel(i+x, y, color);
  }
}

void LCD_Clear(uint8_t LayerIndex, uint16_t Color)
{
	if (LayerIndex == 0){
		for (uint32_t i = 0; i < LCD_PIXEL_WIDTH * LCD_PIXEL_HEIGHT; i++){
			frameBuffer[i] = Color;
		}
	}
  // TODO: Add more Layers if needed
}

//This was taken and adapted from stm32's mcu code
void LCD_SetTextColor(uint16_t Color)
{
  CurrentTextColor = Color;
}

//This was taken and adapted from stm32's mcu code
void LCD_SetFont(FONT_t *fonts)
{
  LCD_Currentfonts = fonts;
}

//This was taken and adapted from stm32's mcu code
void LCD_Draw_Char(uint16_t Xpos, uint16_t Ypos, const uint16_t *c)
{
  uint32_t index = 0, counter = 0;
  for(index = 0; index < LCD_Currentfonts->Height; index++)
  {
    for(counter = 0; counter < LCD_Currentfonts->Width; counter++)
    {
      if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> counter)) == 0x00) && (LCD_Currentfonts->Width <= 12)) || (((c[index] & (0x1 << counter)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))
      {
         //Background If want to overrite text under then add a set color here
      }
      else
      {
    	  LCD_Draw_Pixel(counter + Xpos,index + Ypos,CurrentTextColor);
      }
    }
  }
}


//This was taken and adapted from stm32's mcu code
void LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii)
{
  Ascii -= 32;
  LCD_Draw_Char(Xpos, Ypos, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
}


Shapes shapes[7] = {
    {1, 96, 0, LCD_COLOR_BLUE, 1},  // Left L
    {2, 96, 0, LCD_COLOR_ORANGE, 1},  // Right L
    {3, 96, 0, LCD_COLOR_YELLOW, 1},  // Square
    {4, 96, 0, LCD_COLOR_MAGENTA, 1},  // T Shape
    {5, 96, 0, LCD_COLOR_GREEN, 1},  // Left S
    {6, 96, 0, LCD_COLOR_RED, 1},  // Right S
    {7, 96, 0, LCD_COLOR_TEAL, 1}   // I Shape
};

void ResultScreen(char game_time[4]){
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);
	LCD_DisplayChar(90, 100, 'G');
	LCD_DisplayChar(106, 100, 'A');
	LCD_DisplayChar(122, 100, 'M');
	LCD_DisplayChar(138, 100, 'E');

	LCD_DisplayChar(90, 125, 'O');
	LCD_DisplayChar(106, 125, 'V');
	LCD_DisplayChar(122, 125, 'E');
	LCD_DisplayChar(138, 125, 'R');

	int t = 74;
	for(int i=0; i<4; i++){
		if (game_time[i] == '\0'){
			continue;
		}else{
			LCD_DisplayChar(t, 150, game_time[i]);
			t+=16;
		}
	}
	LCD_DisplayChar(t+16, 150, 'S');
	LCD_DisplayChar(t+32, 150, 'e');
	LCD_DisplayChar(t+48, 150, 'c');
}

void MainMenu(void)
{
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);
//	DrawGrid();
	LCD_Clear(0,LCD_COLOR_BLACK);
	LCD_Draw_Left_L(120,0,LCD_COLOR_BLUE,0);
	LCD_Draw_Right_L(72,96,LCD_COLOR_ORANGE,0);
	LCD_Draw_Square(96,192,LCD_COLOR_YELLOW,0);
	LCD_Draw_T(24,0,LCD_COLOR_MAGENTA,0);
	LCD_Draw_Left_S(168, 96,LCD_COLOR_GREEN,0);
	LCD_Draw_Right_S(24, 256, LCD_COLOR_RED,0);
	LCD_Draw_I(144,288,LCD_COLOR_TEAL,0);

	LCD_DisplayChar(72, 70, 'T');
	LCD_DisplayChar(88, 70, 'E');
	LCD_DisplayChar(104, 70, 'T');
	LCD_DisplayChar(120, 70, 'R');
	LCD_DisplayChar(132, 70, 'I');
	LCD_DisplayChar(144, 70, 'S');


	LCD_DisplayChar(24, 165, 'T');
	LCD_DisplayChar(40, 165, 'o');
	LCD_DisplayChar(56, 165, 'u');
	LCD_DisplayChar(72, 165, 'c');
	LCD_DisplayChar(88, 165, 'h');

	LCD_DisplayChar(115, 165, 'T');
	LCD_DisplayChar(131, 165, 'o');

	LCD_DisplayChar(158, 165, 'S');
	LCD_DisplayChar(174, 165, 't');
	LCD_DisplayChar(190, 165, 'a');
	LCD_DisplayChar(206, 165, 'r');
	LCD_DisplayChar(222, 165, 't');
	DrawGrid();
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void LCD_Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

// Touch Functionality   //

#if COMPILE_TOUCH_FUNCTIONS == 1

void InitializeLCDTouch(void)
{
  if(STMPE811_Init() != STMPE811_State_Ok)
  {
	 for(;;); // Hang code due to error in initialzation
  }
}

STMPE811_State_t returnTouchStateAndLocation(STMPE811_TouchData * touchStruct)
{
	return STMPE811_ReadTouch(touchStruct);
}

void DetermineTouchPosition(STMPE811_TouchData * touchStruct)
{
	STMPE811_DetermineTouchPosition(touchStruct);
}

uint8_t ReadRegisterFromTouchModule(uint8_t RegToRead)
{
	return STMPE811_Read(RegToRead);
}

void WriteDataToTouchModule(uint8_t RegToWrite, uint8_t writeData)
{
	STMPE811_Write(RegToWrite, writeData);
}

#endif // COMPILE_TOUCH_FUNCTIONS



void LCD_Draw_I(uint16_t Xpos, uint16_t Ypos, uint16_t color, uint16_t rotation)
{
	if(rotation == 0){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+48, Ypos, color);
		LCD_Draw_Block(Xpos+72, Ypos, color);
	} else if  (rotation == 1){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos, Ypos+64, color);
		LCD_Draw_Block(Xpos, Ypos+96, color);
	} else if  (rotation == 2){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+48, Ypos, color);
		LCD_Draw_Block(Xpos+72, Ypos, color);
	} else if  (rotation == 3){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos, Ypos+64, color);
		LCD_Draw_Block(Xpos, Ypos+96, color);
	}
}

void LCD_Draw_Left_L(uint16_t Xpos, uint16_t Ypos, uint16_t color, uint16_t rotation){
	if(rotation == 0){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos+48, Ypos+32, color);
	} else if  (rotation == 1){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos, Ypos+64, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
	} else if  (rotation == 2){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+48, Ypos, color);
		LCD_Draw_Block(Xpos+48, Ypos+32, color);
	} else if  (rotation == 3){
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos+64, color);
		LCD_Draw_Block(Xpos+0, Ypos+64, color);
	}
}

void LCD_Draw_Right_L(uint16_t Xpos, uint16_t Ypos, uint16_t color, uint16_t rotation){
	if(rotation == 0){
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos+48, Ypos+32, color);
		LCD_Draw_Block(Xpos+48, Ypos, color);
	} else if  (rotation == 1){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos, Ypos+64, color);
		LCD_Draw_Block(Xpos+24, Ypos+64, color);
	} else if  (rotation == 2){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+48, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
	} else if  (rotation == 3){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos+64, color);
	}
}


void LCD_Draw_Square(uint16_t Xpos, uint16_t Ypos, uint16_t color, uint16_t rotation){
	if(rotation == 0){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
	} else if  (rotation == 1){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
	} else if  (rotation == 2){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
	} else if  (rotation == 3){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
	}
}



void LCD_Draw_T(uint16_t Xpos, uint16_t Ypos, uint16_t color, uint16_t rotation){
	if(rotation == 0){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos-24, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
	} else if  (rotation == 1){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos, Ypos+64, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
	} else if  (rotation == 2){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+48, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
	} else if  (rotation == 3){
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos+64, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
	}
}


void LCD_Draw_Left_S(uint16_t Xpos, uint16_t Ypos, uint16_t color, uint16_t rotation)
{
	if(rotation == 0){
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos+48, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
	} else if  (rotation == 1){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos+64, color);
	} else if  (rotation == 2){
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos+48, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
	} else if  (rotation == 3){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos+24, Ypos+64, color);
	}
}

void LCD_Draw_Right_S(uint16_t Xpos, uint16_t Ypos, uint16_t color, uint16_t rotation){
	if(rotation == 0){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos+48, Ypos+32, color);
	} else if  (rotation == 1){
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos, Ypos+64, color);
	} else if  (rotation == 2){
		LCD_Draw_Block(Xpos, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos+48, Ypos+32, color);
	} else if  (rotation == 3){
		LCD_Draw_Block(Xpos+24, Ypos, color);
		LCD_Draw_Block(Xpos+24, Ypos+32, color);
		LCD_Draw_Block(Xpos, Ypos+32, color);
		LCD_Draw_Block(Xpos, Ypos+64, color);
	}
}
