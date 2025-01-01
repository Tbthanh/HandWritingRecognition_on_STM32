/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body of TFT_touch_xpt2046 to calib screen
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "st7789.h"
#include "xpt2046.h"
#include "cnn.h"
#include "constants.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi1_tx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void clearCNNinput(volatile float *in_mat)
{
	uint8_t i = 0;
	uint8_t j = 0;
	for (i = 0; i < INPUT_SIZE; i++)
	{
		for (j = 0; j < INPUT_SIZE; j ++)
		{
			uint16_t in_mat_idx = i * INPUT_SIZE + j;
			in_mat[in_mat_idx] = 0;
		}
	}
}

void resetButtonPressed(volatile float* cnn_input, volatile uint16_t coordinate_x, volatile uint16_t coordinate_y)
{
	if ((coordinate_x > 157 && coordinate_x < 208) &&
		(coordinate_y >  23 && coordinate_y <  43))
	{
		ST7789_DrawFilledRectangle(10, 90, 220, 220, WHITE);
		ST7789_DrawFilledRectangle(10, 10, 28, 28, WHITE);
		HAL_Delay(100);
		ST7789_WriteString(45, 10, "Predicted: _", Font_7x10, RED, WHITE);
		ST7789_WriteString(45, 25, "Conf.: _____", Font_7x10, RED, WHITE);
		clearCNNinput(cnn_input);
	}
}

void drawInterface()
{
	// Turn screen Black
//	ST7789_InvertColors(ST7789_INVOFF);
	ST7789_Fill_Color(WHITE);
	HAL_Delay(500);
//	ST7789_WriteString(10, 20, "Touch Test", Font_11x18, RED, WHITE);
//	HAL_Delay(500);

	// Draw resset button
	ST7789_DrawFilledRectangle(158, 8, 59, 22, BLACK);
	ST7789_WriteString(160, 10, "RESET", Font_11x18, CYAN, BLACK);// 160~226 - 20~38

	// Draw CNN button
	ST7789_DrawFilledRectangle(158, 38, 59, 22, BLACK);
	ST7789_WriteString(160, 40, " CNN ", Font_11x18, CYAN, BLACK);// 160~226 - 20~38

	// Minimap border
	ST7789_DrawRectangle(8, 8, 40, 40, BLACK);
	ST7789_WriteString(8, 45, "CNN input:", Font_7x10, RED, WHITE);
	ST7789_WriteString(45, 10, "Predicted: _", Font_7x10, RED, WHITE);
	ST7789_WriteString(45, 25, "Conf.: _____", Font_7x10, RED, WHITE);

	// Draw drawing border
	ST7789_DrawRectangle(8, 88, 232, 312, BLACK);
}

void drawMinimap(volatile float *in_mat)
{
	// (x1, y1) = (10, 10)
	uint8_t i = 0;
	uint8_t j = 0;
	uint16_t in_mat_idx = 0;

	// Loop through matrix and draw pixels
	for (i = 0; i < INPUT_SIZE; i++)
	{
		for (j = 0; j < INPUT_SIZE; j++)
		{
			in_mat_idx = i * INPUT_SIZE + j;  // Calculate the index once per loop
			uint16_t color = (in_mat[in_mat_idx] == 0) ? WHITE : RED; // Determine color
			ST7789_DrawPixel(10 + i, 10 + j, color);  // Draw pixel with selected color
		}
	}
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  ST7789_Init();

  xpt2046_spi(&hspi2);
  xpt2046_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  ST7789_Test();
  char print_string[30];
  uint8_t change_flag = 0;
  volatile uint16_t coordinate_x = 0;
  volatile uint16_t coordinate_y = 0;
  volatile float cnn_input[INPUT_SIZE * INPUT_SIZE];	// to store CNN input
	for (uint16_t i = 0; i < INPUT_SIZE; i++)
	{
		for (uint16_t j = 0; j < INPUT_SIZE; j++)
		{
			uint16_t in_mat_idx = i * INPUT_SIZE + j;  // Calculate the index once per loop
			cnn_input[in_mat_idx] = 0;
		}
	}

  drawInterface();
  while (1)
  {
	uint16_t pre_coordinate_x = coordinate_x;
	uint16_t pre_coordinate_y = coordinate_y;
	xpt2046_read_position(&coordinate_x, &coordinate_y);
	if (coordinate_x == 0 && coordinate_y == 0)
	{
		// do smt
		if (change_flag != 0)
		{
			ST7789_DrawFilledRectangle(38, 66, 60, 10, WHITE);
			sprintf(print_string,"x = 0");
			ST7789_WriteString(10, 66, print_string, Font_7x10, RED, WHITE);
			HAL_Delay(50);
			ST7789_DrawFilledRectangle(38, 78, 60, 9, WHITE);
			sprintf(print_string,"y = 0");
			ST7789_WriteString(10, 78, print_string, Font_7x10, RED, WHITE);
			HAL_Delay(50);
			change_flag = 0;
		}
	}
	else
	{
		// update screen
		sprintf(print_string,"x = %d", coordinate_x);
		ST7789_WriteString(10, 66, print_string, Font_7x10, RED, WHITE);
//		HAL_Delay(100);
		sprintf(print_string,"y = %d", coordinate_y );
		ST7789_WriteString(10, 78, print_string, Font_7x10, RED, WHITE);
//		HAL_Delay(100);
		change_flag = 1;
	}

//	// Draw function
	if (
			// bounding of draw box
			(coordinate_x >  25 && coordinate_x < 221) &&
			(coordinate_y > 108 && coordinate_y < 307) &&
			// prevent jumping in value
			(coordinate_x < pre_coordinate_x + 10) && (coordinate_x > pre_coordinate_x - 10) &&
			(coordinate_y < pre_coordinate_y + 10) && (coordinate_y > pre_coordinate_y - 10)
		)
	{
		ST7789_DrawFilledRectangle(coordinate_x - 4, coordinate_y - 4, 8, 8, RED);

		// update input mat
		uint8_t cnn_input_idx_x = (coordinate_x - 25)/ 7;
		uint8_t cnn_input_idx_y = (coordinate_y - 108)/ 7;
		// make the input bolder - enlarge the input to 4 pixel
		uint16_t cnn_input_index00 = cnn_input_idx_x * INPUT_SIZE + cnn_input_idx_y;
		uint16_t cnn_input_index01 = (cnn_input_idx_x - 1) * INPUT_SIZE + cnn_input_idx_y - 1;
		uint16_t cnn_input_index02 = (cnn_input_idx_x - 1) * INPUT_SIZE + cnn_input_idx_y;
		uint16_t cnn_input_index03 = (cnn_input_idx_x - 1) * INPUT_SIZE + cnn_input_idx_y + 1;
		uint16_t cnn_input_index04 = cnn_input_idx_x * INPUT_SIZE + cnn_input_idx_y - 1;
		uint16_t cnn_input_index05 = cnn_input_idx_x * INPUT_SIZE + cnn_input_idx_y + 1;
		uint16_t cnn_input_index06 = (cnn_input_idx_x + 1) * INPUT_SIZE + cnn_input_idx_y - 1;
		uint16_t cnn_input_index07 = (cnn_input_idx_x + 1) * INPUT_SIZE + cnn_input_idx_y;
		uint16_t cnn_input_index08 = (cnn_input_idx_x + 1) * INPUT_SIZE + cnn_input_idx_y + 1;

		if (cnn_input_index00 < INPUT_SIZE * INPUT_SIZE)
		{
		    cnn_input[cnn_input_index00] = 1.0f;
		}

		if (cnn_input_index01 < INPUT_SIZE * INPUT_SIZE)
		{
			cnn_input[cnn_input_index01] = 0.5f;
		}

		if (cnn_input_index02 < INPUT_SIZE * INPUT_SIZE)
		{
			cnn_input[cnn_input_index02] = 1.0f;
		}

		if (cnn_input_index03 < INPUT_SIZE * INPUT_SIZE)
		{
			cnn_input[cnn_input_index03] = 0.5f;
		}

		if (cnn_input_index04 < INPUT_SIZE * INPUT_SIZE)
		{
			cnn_input[cnn_input_index04] = 1.0f;
		}

		if (cnn_input_index05 < INPUT_SIZE * INPUT_SIZE)
		{
			cnn_input[cnn_input_index05] = 1.0f;
		}

		if (cnn_input_index06 < INPUT_SIZE * INPUT_SIZE)
		{
			cnn_input[cnn_input_index06] = 0.5f;
		}

		if (cnn_input_index07 < INPUT_SIZE * INPUT_SIZE)
		{
			cnn_input[cnn_input_index07] = 1.0f;
		}

		if (cnn_input_index08 < INPUT_SIZE * INPUT_SIZE)
		{
			cnn_input[cnn_input_index08] = 0.5f;
		}
	}

	// CNN button:
	if ((coordinate_x > 157 && coordinate_x < 208) &&
			(coordinate_y >  59 && coordinate_y <  71))
	{
		volatile uint8_t predicted_num = 0;
		volatile float predicted_num_confidence = 0.0;

		float cnn_input_flip[INPUT_SIZE * INPUT_SIZE];
		uint16_t in_mat_idx_flip = 0;
		uint16_t in_mat_idx = 0;

		for (int i = 0; i < INPUT_SIZE; i++)
		{
			for (int j = 0; j < INPUT_SIZE; j++)
			{
				in_mat_idx_flip = j * INPUT_SIZE + i;  // Calculate the index once per loop
				in_mat_idx = i * INPUT_SIZE + j;  // Calculate the index once per loop
				cnn_input_flip[in_mat_idx_flip] = cnn_input[in_mat_idx];
			}
		}

		feedforward(cnn_input, &predicted_num, &predicted_num_confidence);

		sprintf(print_string,"Predicted: %d", predicted_num);
		ST7789_WriteString(45, 10, print_string, Font_7x10, RED, WHITE);
		sprintf(print_string,"Conf.: %.3f", predicted_num_confidence);
		ST7789_WriteString(45, 25, print_string, Font_7x10, RED, WHITE);
	}

	// draw mini drawin plane
	drawMinimap(cnn_input);

	// Reset button
	resetButtonPressed(cnn_input,  coordinate_x, coordinate_y);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ST7789_DC_Pin|ST7789_RST_Pin|ST7789_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ST7789_DC_Pin ST7789_RST_Pin ST7789_CS_Pin */
  GPIO_InitStruct.Pin = ST7789_DC_Pin|ST7789_RST_Pin|ST7789_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : T_IRQ_Pin */
  GPIO_InitStruct.Pin = T_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(T_IRQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : T_CS_Pin */
  GPIO_InitStruct.Pin = T_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(T_CS_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
