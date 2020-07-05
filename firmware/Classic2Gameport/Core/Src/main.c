/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "classic_controller.h"
#include "gameport.h"
#include "button_mapper.h"
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
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

ButtonMap buttonMapPort1[] =
{
    {MAP_TYPE_AXIS, true, 0, 0,                       AXIS_X2, POSITION_DISCONNECTED, 0},
    {MAP_TYPE_AXIS, true, 0, 0,                       AXIS_Y2, POSITION_DISCONNECTED, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_left,  0, AXIS_X1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_right, 0, AXIS_X1, POSITION_MAX, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_up,    0, AXIS_Y1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_down,  0, AXIS_Y1, POSITION_MAX, 0},
    {MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_b,     0, 0, 0,                0},
    {MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_y,     0, 0, 0,                1},
	{MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_select,0, 0, 0,                1},
    {MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_a,     0, 0, 0,                2},
    {MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_x,     0, 0, 0,                3},
	{MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_start, 0, 0, 0,                3},
    {MAP_TYPE_END,    false, 0                 ,     0, 0, 0,                0},
};

ButtonMap buttonMapPort1Jnr[] =
{
    {MAP_TYPE_AXIS, true, 0, 0,                       AXIS_X2, POSITION_DISCONNECTED, 0},
    {MAP_TYPE_AXIS, true, 0, 0,                       AXIS_Y2, POSITION_DISCONNECTED, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_left,  0, AXIS_X1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_right, 0, AXIS_X1, POSITION_MAX, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_up,    0, AXIS_Y1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_b,     0, AXIS_Y1, POSITION_MIN, 0}, // b is mapped to up
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_down,  0, AXIS_Y1, POSITION_MAX, 0},
    {MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_y,     0, 0, 0,                0},
    {MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_a,     0, 0, 0,                1},
    {MAP_TYPE_END,    false, 0                 ,     0, 0, 0,                0},
};

ButtonMap buttonMapPort2[] =
{
    {MAP_TYPE_AXIS, true, 0, 0,                       AXIS_X2, POSITION_DISCONNECTED, 0},
    {MAP_TYPE_AXIS, true, 0, 0,                       AXIS_Y2, POSITION_DISCONNECTED, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_left,  AXIS_X1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_right, AXIS_X1, POSITION_MAX, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_up,    AXIS_Y1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_down,  AXIS_Y1, POSITION_MAX, 0},
    {MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_b,     0, 0,                0},
    {MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_y,     0, 0,                1},
	{MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_select,0, 0,                1},
    {MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_a,     0, 0,                2},
    {MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_x,     0, 0,                3},
	{MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_start, 0, 0,                3},
    {MAP_TYPE_END,  false, 0,                  0,       0, 0,                0},
};

ButtonMap buttonMapPort2Jnr[] =
{
    {MAP_TYPE_AXIS, true, 0, 0,                       AXIS_X2, POSITION_DISCONNECTED, 0},
    {MAP_TYPE_AXIS, true, 0, 0,                       AXIS_Y2, POSITION_DISCONNECTED, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_left,  AXIS_X1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_right, AXIS_X1, POSITION_MAX, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_up,    AXIS_Y1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_b,     AXIS_Y1, POSITION_MIN, 0}, // b is mapped to up
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_down,  AXIS_Y1, POSITION_MAX, 0},
    {MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_y,     0, 0,                0},
    {MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_a,     0, 0,                1},
    {MAP_TYPE_END,  false, 0,                  0,       0, 0,                0},
};

ButtonMap buttonMapBoth[] =
{
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_left,  0, AXIS_X1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_right, 0, AXIS_X1, POSITION_MAX, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_up,    0, AXIS_Y1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_down,  0, AXIS_Y1, POSITION_MAX, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_left,  AXIS_X2, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_right, AXIS_X2, POSITION_MAX, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_up,    AXIS_Y2, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_down,  AXIS_Y2, POSITION_MAX, 0},
    {MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_b,    0,  0, 0,                0},
    {MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_y,    0,  0, 0,                1},
    {MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_b,     0, 0,                2},
    {MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_y,     0, 0,                3},
    {MAP_TYPE_END, false, 0,                  0,        0, 0,                0},
};

ButtonMap buttonMapBothJnr[] =
{
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_left,  0, AXIS_X1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_right, 0, AXIS_X1, POSITION_MAX, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_up,    0, AXIS_Y1, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_b,     0, AXIS_Y1, POSITION_MIN, 0}, // b is also mapped to up
    {MAP_TYPE_AXIS, false, 1 << CLASSIC_BTN_down,  0, AXIS_Y1, POSITION_MAX, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_left,  AXIS_X2, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_right, AXIS_X2, POSITION_MAX, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_up,    AXIS_Y2, POSITION_MIN, 0},
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_b,     AXIS_Y2, POSITION_MIN, 0}, // b is also mapped to up
    {MAP_TYPE_AXIS, false, 0, 1 << CLASSIC_BTN_down,  AXIS_Y2, POSITION_MAX, 0},
    {MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_y,    0,  0, 0,                0},
    {MAP_TYPE_BUTTON, false, 1 << CLASSIC_BTN_a,    0,  0, 0,                1},
    {MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_y,     0, 0,                2},
    {MAP_TYPE_BUTTON, false, 0, 1 << CLASSIC_BTN_a,     0, 0,                3},
    {MAP_TYPE_END, false, 0,                  0,        0, 0,                0},
};

static const uint16_t normalModeButtons = ~(1 << CLASSIC_BTN_select | 1 << CLASSIC_BTN_down);
static const uint16_t jumpAndRunModeButtons = ~(1 << CLASSIC_BTN_select | 1 << CLASSIC_BTN_up);

bool jumpAndRunMode = false;

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
  MX_I2C2_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
soft_reset:

  HAL_Delay(100);
  initializeClassicController(&hi2c1);
  initializeClassicController(&hi2c2);
  HAL_Delay(100);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  uint16_t classicControllerButtons1 = 0;
  uint16_t classicControllerButtons2 = 0;

  while (1)
  {
    bool pad1Ready = readClassicControllerData(&hi2c1, &classicControllerButtons1);
    bool pad2Ready = readClassicControllerData(&hi2c2, &classicControllerButtons2);


    if (!pad1Ready && !pad2Ready)
    {
      goto soft_reset;
    }

    if (jumpAndRunModeButtons == classicControllerButtons1 || jumpAndRunModeButtons == classicControllerButtons2)
    {
      jumpAndRunMode = true;
    }

    if (normalModeButtons == classicControllerButtons1 || normalModeButtons == classicControllerButtons2)
    {
      jumpAndRunMode = false;
    }



    ButtonMap* map;


    if (pad1Ready && pad2Ready)
    {
      map = jumpAndRunMode?buttonMapBothJnr:buttonMapBoth;
    }
    else if (pad1Ready)
    {
      map = jumpAndRunMode?buttonMapPort1Jnr:buttonMapPort1;
    }
    else
    {
      map = jumpAndRunMode?buttonMapPort2Jnr:buttonMapPort2;
    }
  

    GameportState gameportState = mapButtons(classicControllerButtons1, classicControllerButtons2, map);
    setGameport(&gameportState);

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks 
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00303D5B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00303D5B;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 
                           PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 PA10 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
