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

/* Definitions for TaskSensor */
osThreadId_t TaskSensorHandle;
const osThreadAttr_t TaskSensor_attributes = {
  .name = "TaskSensor",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskProcessamen */
osThreadId_t TaskProcessamenHandle;
const osThreadAttr_t TaskProcessamen_attributes = {
  .name = "TaskProcessamen",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskSupervisao */
osThreadId_t TaskSupervisaoHandle;
const osThreadAttr_t TaskSupervisao_attributes = {
  .name = "TaskSupervisao",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskLog */
osThreadId_t TaskLogHandle;
const osThreadAttr_t TaskLog_attributes = {
  .name = "TaskLog",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for TaskAlarme */
osThreadId_t TaskAlarmeHandle;
const osThreadAttr_t TaskAlarme_attributes = {
  .name = "TaskAlarme",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for mutexUart */
osMutexId_t mutexUartHandle;
const osMutexAttr_t mutexUart_attributes = {
  .name = "mutexUart"
};
/* Definitions for mutexValorProcessado */
osMutexId_t mutexValorProcessadoHandle;
const osMutexAttr_t mutexValorProcessado_attributes = {
  .name = "mutexValorProcessado"
};
/* Definitions for mutexVariavelEstatisticas */
osMutexId_t mutexVariavelEstatisticasHandle;
const osMutexAttr_t mutexVariavelEstatisticas_attributes = {
  .name = "mutexVariavelEstatisticas"
};
/* Definitions for semaforoSensor */
osSemaphoreId_t semaforoSensorHandle;
const osSemaphoreAttr_t semaforoSensor_attributes = {
  .name = "semaforoSensor"
};
/* Definitions for semaforoSupervisao */
osSemaphoreId_t semaforoSupervisaoHandle;
const osSemaphoreAttr_t semaforoSupervisao_attributes = {
  .name = "semaforoSupervisao"
};
/* Definitions for semaforoAlarme */
osSemaphoreId_t semaforoAlarmeHandle;
const osSemaphoreAttr_t semaforoAlarme_attributes = {
  .name = "semaforoAlarme"
};
/* Definitions for semaforoOperacao */
osSemaphoreId_t semaforoOperacaoHandle;
const osSemaphoreAttr_t semaforoOperacao_attributes = {
  .name = "semaforoOperacao"
};
/* USER CODE BEGIN PV */
int valorProcessado = 0;
int pecasOK = 0;
int pecasFalha = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
void TaskSensor_fun(void *argument);
void TaskProcessamento_fun(void *argument);
void TaskSupervisao_fun(void *argument);
void TaskLog_fun(void *argument);
void TaskAlarme_fun(void *argument);

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
  /* Create the mutex(es) */
  /* creation of mutexUart */
  mutexUartHandle = osMutexNew(&mutexUart_attributes);

  /* creation of mutexValorProcessado */
  mutexValorProcessadoHandle = osMutexNew(&mutexValorProcessado_attributes);

  /* creation of mutexVariavelEstatisticas */
  mutexVariavelEstatisticasHandle = osMutexNew(&mutexVariavelEstatisticas_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of semaforoSensor */
  semaforoSensorHandle = osSemaphoreNew(1, 0, &semaforoSensor_attributes);

  /* creation of semaforoSupervisao */
  semaforoSupervisaoHandle = osSemaphoreNew(1, 0, &semaforoSupervisao_attributes);

  /* creation of semaforoAlarme */
  semaforoAlarmeHandle = osSemaphoreNew(1, 0, &semaforoAlarme_attributes);

  /* creation of semaforoOperacao */
  semaforoOperacaoHandle = osSemaphoreNew(1, 1, &semaforoOperacao_attributes);

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
  /* creation of TaskSensor */
  TaskSensorHandle = osThreadNew(TaskSensor_fun, NULL, &TaskSensor_attributes);

  /* creation of TaskProcessamen */
  TaskProcessamenHandle = osThreadNew(TaskProcessamento_fun, NULL, &TaskProcessamen_attributes);

  /* creation of TaskSupervisao */
  TaskSupervisaoHandle = osThreadNew(TaskSupervisao_fun, NULL, &TaskSupervisao_attributes);

  /* creation of TaskLog */
  TaskLogHandle = osThreadNew(TaskLog_fun, NULL, &TaskLog_attributes);

  /* creation of TaskAlarme */
  TaskAlarmeHandle = osThreadNew(TaskAlarme_fun, NULL, &TaskAlarme_attributes);

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
  HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, BUZZER_PIN_Pin|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_PIN_Pin */
  GPIO_InitStruct.Pin = LED_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_PIN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_K1_Pin BTN_K0_Pin */
  GPIO_InitStruct.Pin = BTN_K1_Pin|BTN_K0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : BUZZER_PIN_Pin PA6 PA7 */
  GPIO_InitStruct.Pin = BUZZER_PIN_Pin|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : IR_SENSOR_PIN_Pin */
  GPIO_InitStruct.Pin = IR_SENSOR_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(IR_SENSOR_PIN_GPIO_Port, &GPIO_InitStruct);

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

/* USER CODE BEGIN Header_TaskSensor_fun */
/**
  * @brief  Function implementing the TaskSensor thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TaskSensor_fun */
void TaskSensor_fun(void *argument)
{
  /* USER CODE BEGIN 5 */

  /* Infinite loop */
  for(;;)
  {
	osSemaphoreAcquire(semaforoOperacaoHandle, osWaitForever); // Semáforo de permissão para operar

	if(HAL_GPIO_ReadPin(IR_SENSOR_PIN_GPIO_Port, IR_SENSOR_PIN_Pin)){
    	osSemaphoreRelease(semaforoSensorHandle);
    	osDelay(200);
    }

	osSemaphoreRelease(semaforoOperacaoHandle);
    osDelay(10);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_TaskProcessamento_fun */
/**
* @brief Function implementing the TaskProcessamen thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskProcessamento_fun */
void TaskProcessamento_fun(void *argument)
{
  /* USER CODE BEGIN TaskProcessamento_fun */
  /* Infinite loop */
  for(;;)
  {
	  if(osSemaphoreAcquire(semaforoSensorHandle, osWaitForever) == osOK){


		  osMutexAcquire(mutexValorProcessadoHandle, osWaitForever);
		  valorProcessado = (rand() % 100);
		  osMutexRelease(mutexValorProcessadoHandle);

		  osSemaphoreRelease(semaforoSupervisaoHandle);
	  }
  }
  /* USER CODE END TaskProcessamento_fun */
}

/* USER CODE BEGIN Header_TaskSupervisao_fun */
/**
* @brief Function implementing the TaskSupervisao thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskSupervisao_fun */
void TaskSupervisao_fun(void *argument)
{
  /* USER CODE BEGIN TaskSupervisao_fun */
  int valorProcessadoLocal = 0;
  /* Infinite loop */
  for(;;)
  {

	  if(osSemaphoreAcquire(semaforoSupervisaoHandle, osWaitForever) == osOK){


		  osMutexAcquire(mutexValorProcessadoHandle, osWaitForever);
		  valorProcessadoLocal = valorProcessado;
		  osMutexRelease(mutexValorProcessadoHandle);




		  osMutexAcquire(mutexUartHandle, osWaitForever);
		  osMutexAcquire(mutexVariavelEstatisticasHandle, osWaitForever);

		  if(valorProcessadoLocal >= 95){
			  pecasFalha++;
			  printf("[%lu ms] ERRO DETECTADO - Necessária intervenção manual\r\n", osKernelGetTickCount());
			  osSemaphoreRelease(semaforoAlarmeHandle);

		  } else {
			  pecasOK++;
			  printf("[%lu ms] Peça processada no valor de %d", osKernelGetTickCount(), valorProcessadoLocal);
		  }

		  osMutexRelease(mutexUartHandle);
		  osMutexRelease(mutexVariavelEstatisticasHandle);

	  }
  }
  /* USER CODE END TaskSupervisao_fun */
}

/* USER CODE BEGIN Header_TaskLog_fun */
/**
* @brief Function implementing the TaskLog thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskLog_fun */
void TaskLog_fun(void *argument)
{
  /* USER CODE BEGIN TaskLog_fun */
  /* Infinite loop */
  for(;;)
  {
	osMutexAcquire(mutexUartHandle, osWaitForever);
	osMutexAcquire(mutexVariavelEstatisticasHandle, osWaitForever);
	printf("[%lu ms][LOG] PEÇAS PROCESSADAS: %d ERROS REGISTRADOS: %d\r\n", osKernelGetTickCount(), pecasOK, pecasFalha);
	osMutexRelease(mutexUartHandle);
	osMutexRelease(mutexVariavelEstatisticasHandle);
	osDelay(10000);
  }
  /* USER CODE END TaskLog_fun */
}

/* USER CODE BEGIN Header_TaskAlarme_fun */
/**
* @brief Function implementing the TaskAlarme thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskAlarme_fun */
void TaskAlarme_fun(void *argument)
{
  /* USER CODE BEGIN TaskAlarme_fun */
  HAL_GPIO_WritePin(BUZZER_PIN_GPIO_Port, BUZZER_PIN_Pin, 0);
  /* Infinite loop */
  for(;;)
  {
	  if(osSemaphoreAcquire(semaforoAlarmeHandle, osWaitForever) == osOK){
		  osSemaphoreAcquire(semaforoOperacaoHandle, osWaitForever);
		  HAL_GPIO_WritePin(BUZZER_PIN_GPIO_Port, BUZZER_PIN_Pin, 1);

		  while(HAL_GPIO_ReadPin(BTN_K1_GPIO_Port, BTN_K1_Pin) == 0){
			  osDelay(50);
		  }

		  HAL_GPIO_WritePin(BUZZER_PIN_GPIO_Port, BUZZER_PIN_Pin, 0);
		  osSemaphoreRelease(semaforoOperacaoHandle);
	  }
  }
  /* USER CODE END TaskAlarme_fun */
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
