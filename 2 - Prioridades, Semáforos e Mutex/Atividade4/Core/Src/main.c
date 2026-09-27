/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
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
UART_HandleTypeDef huart1;

/* Definitions for Carro1 */
osThreadId_t Carro1Handle;
const osThreadAttr_t Carro1_attributes = {
  .name = "Carro1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Carro2 */
osThreadId_t Carro2Handle;
const osThreadAttr_t Carro2_attributes = {
  .name = "Carro2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Carro3 */
osThreadId_t Carro3Handle;
const osThreadAttr_t Carro3_attributes = {
  .name = "Carro3",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Carro4 */
osThreadId_t Carro4Handle;
const osThreadAttr_t Carro4_attributes = {
  .name = "Carro4",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Carro5 */
osThreadId_t Carro5Handle;
const osThreadAttr_t Carro5_attributes = {
  .name = "Carro5",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for vagas */
osSemaphoreId_t vagasHandle;
const osSemaphoreAttr_t vagas_attributes = {
  .name = "vagas"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
void Carro1_fun(void *argument);
void Carro2_fun(void *argument);
void Carro3_fun(void *argument);
void Carro4_fun(void *argument);
void Carro5_fun(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  srand((unsigned int)HAL_GetTick());
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of vagas */
  vagasHandle = osSemaphoreNew(1, 1, &vagas_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Carro1 */
  Carro1Handle = osThreadNew(Carro1_fun, NULL, &Carro1_attributes);

  /* creation of Carro2 */
  Carro2Handle = osThreadNew(Carro2_fun, NULL, &Carro2_attributes);

  /* creation of Carro3 */
  Carro3Handle = osThreadNew(Carro3_fun, NULL, &Carro3_attributes);

  /* creation of Carro4 */
  Carro4Handle = osThreadNew(Carro4_fun, NULL, &Carro4_attributes);

  /* creation of Carro5 */
  Carro5Handle = osThreadNew(Carro5_fun, NULL, &Carro5_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : BTN_K1_Pin BTN_K0_Pin */
  GPIO_InitStruct.Pin = BTN_K1_Pin|BTN_K0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
int _write(int file, char *ptr, int len) {
    // Transmite os dados recebidos pelo printf via UART
    HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_Carro1_fun */
/**
  * @brief  Function implementing the Carro1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Carro1_fun */
void Carro1_fun(void *argument)
{
  /* USER CODE BEGIN 5 */
	osDelay(100 + (rand() % 100));
  uint32_t tempo_estacionado;
  uint32_t tempo_passeando;

  for(;;)
  {
    printf("[%lu ms] Carro 1: Tentando entrar...\r\n", osKernelGetTickCount());
    osSemaphoreAcquire(vagasHandle, osWaitForever);

    printf("[%lu ms] Carro 1: Entrada autorizada.\r\n", osKernelGetTickCount());

    // Simula tempo estacionado aleatório (entre 1000ms e 3000ms)
    tempo_estacionado = 1000 + (rand() % 2001);
    osDelay(tempo_estacionado);

    printf("[%lu ms] Carro 1: Saindo após %lu ms estacionado.\r\n", osKernelGetTickCount(), tempo_estacionado);
    osSemaphoreRelease(vagasHandle);

    // Simula tempo passeando pela cidade antes de tentar estacionar de novo (entre 2000ms e 5000ms)
    tempo_passeando = 2000 + (rand() % 3001);
    osDelay(tempo_passeando);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_Carro2_fun */
/**
* @brief Function implementing the Carro2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Carro2_fun */
void Carro2_fun(void *argument)
{
  /* USER CODE BEGIN Carro2_fun */
	osDelay(100 + (rand() % 100));
  uint32_t tempo_estacionado;
  uint32_t tempo_passeando;
  /* Infinite loop */
  for(;;)
  {
    printf("[%lu ms] Carro 2: Tentando entrar...\r\n", osKernelGetTickCount());
    osSemaphoreAcquire(vagasHandle, osWaitForever);

    printf("[%lu ms] Carro 2: Entrada autorizada.\r\n", osKernelGetTickCount());

    // Simula tempo estacionado aleatório (entre 1000ms e 3000ms)
    tempo_estacionado = 1000 + (rand() % 2001);
    osDelay(tempo_estacionado);

    printf("[%lu ms] Carro 2: Saindo após %lu ms estacionado.\r\n", osKernelGetTickCount(), tempo_estacionado);
    osSemaphoreRelease(vagasHandle);

    // Simula tempo passeando pela cidade antes de tentar estacionar de novo (entre 2000ms e 5000ms)
    tempo_passeando = 2000 + (rand() % 3001);
    osDelay(tempo_passeando);
  }
  /* USER CODE END Carro2_fun */
}

/* USER CODE BEGIN Header_Carro3_fun */
/**
* @brief Function implementing the Carro3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Carro3_fun */
void Carro3_fun(void *argument)
{
  /* USER CODE BEGIN Carro3_fun */
	osDelay(100 + (rand() % 100));
  uint32_t tempo_estacionado;
  uint32_t tempo_passeando;
  /* Infinite loop */
  for(;;)
  {
	printf("[%lu ms] Carro 3: Tentando entrar...\r\n", osKernelGetTickCount());
	osSemaphoreAcquire(vagasHandle, osWaitForever);

	printf("[%lu ms] Carro 3: Entrada autorizada.\r\n", osKernelGetTickCount());

	// Simula tempo estacionado aleatório (entre 1000ms e 3000ms)
	tempo_estacionado = 1000 + (rand() % 2001);
	osDelay(tempo_estacionado);

	printf("[%lu ms] Carro 3: Saindo após %lu ms estacionado.\r\n", osKernelGetTickCount(), tempo_estacionado);
	osSemaphoreRelease(vagasHandle);

	// Simula tempo passeando pela cidade antes de tentar estacionar de novo (entre 2000ms e 5000ms)
	tempo_passeando = 2000 + (rand() % 3001);
	osDelay(tempo_passeando);
  }
  /* USER CODE END Carro3_fun */
}

/* USER CODE BEGIN Header_Carro4_fun */
/**
* @brief Function implementing the Carro4 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Carro4_fun */
void Carro4_fun(void *argument)
{
  /* USER CODE BEGIN Carro4_fun */
	osDelay(100 + (rand() % 100));
	  uint32_t tempo_estacionado;
	  uint32_t tempo_passeando;
	  /* Infinite loop */
  for(;;)
  {
	printf("[%lu ms] Carro 4: Tentando entrar...\r\n", osKernelGetTickCount());
	osSemaphoreAcquire(vagasHandle, osWaitForever);

	printf("[%lu ms] Carro 4: Entrada autorizada.\r\n", osKernelGetTickCount());

	// Simula tempo estacionado aleatório (entre 1000ms e 3000ms)
	tempo_estacionado = 1000 + (rand() % 2001);
	osDelay(tempo_estacionado);

	printf("[%lu ms] Carro 4: Saindo após %lu ms estacionado.\r\n", osKernelGetTickCount(), tempo_estacionado);
	osSemaphoreRelease(vagasHandle);

	// Simula tempo passeando pela cidade antes de tentar estacionar de novo (entre 2000ms e 5000ms)
	tempo_passeando = 2000 + (rand() % 3001);
	osDelay(tempo_passeando);
  }
  /* USER CODE END Carro4_fun */
}

/* USER CODE BEGIN Header_Carro5_fun */
/**
* @brief Function implementing the Carro5 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Carro5_fun */
void Carro5_fun(void *argument)
{
  /* USER CODE BEGIN Carro5_fun */
	osDelay(100 + (rand() % 100));
  uint32_t tempo_estacionado;
  uint32_t tempo_passeando;
  /* Infinite loop */
  for(;;)
  {
	printf("[%lu ms] Carro 5: Tentando entrar...\r\n", osKernelGetTickCount());
	osSemaphoreAcquire(vagasHandle, osWaitForever);

	printf("[%lu ms] Carro 5: Entrada autorizada.\r\n", osKernelGetTickCount());

	// Simula tempo estacionado aleatório (entre 1000ms e 3000ms)
	tempo_estacionado = 1000 + (rand() % 2001);
	osDelay(tempo_estacionado);

	printf("[%lu ms] Carro 5: Saindo após %lu ms estacionado.\r\n", osKernelGetTickCount(), tempo_estacionado);
	osSemaphoreRelease(vagasHandle);

	// Simula tempo passeando pela cidade antes de tentar estacionar de novo (entre 2000ms e 5000ms)
	tempo_passeando = 2000 + (rand() % 3001);
	osDelay(tempo_passeando);
  }
  /* USER CODE END Carro5_fun */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
#ifdef USE_FULL_ASSERT
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
