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
TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

/* Definitions for TempTask */
osThreadId_t TempTaskHandle;
const osThreadAttr_t TempTask_attributes = {
  .name = "TempTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
osThreadId_t TempTaskHandle;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM6_Init(void);
void StartDefaultTask(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern TIM_HandleTypeDef htim6;

/* LCD mapping */

#define RS_PORT GPIOB
#define RS_PIN GPIO_PIN_0

#define EN_PORT GPIOB
#define EN_PIN GPIO_PIN_1

#define D4_PORT GPIOB
#define D4_PIN GPIO_PIN_2

#define D5_PORT GPIOB
#define D5_PIN GPIO_PIN_10

#define D6_PORT GPIOB
#define D6_PIN GPIO_PIN_12

#define D7_PORT GPIOB
#define D7_PIN GPIO_PIN_13

#define DS_PORT GPIOA
#define DS_PIN GPIO_PIN_1

void delay_us(uint16_t us)
{
 __HAL_TIM_SET_COUNTER(&htim6,0);
 while(__HAL_TIM_GET_COUNTER(&htim6)<us);
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
  MX_USART2_UART_Init();
  MX_TIM6_Init();
  HAL_TIM_Base_Start(&htim6);
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

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
  /* creation of TempTask */
  TempTaskHandle = osThreadNew(StartDefaultTask, NULL, &TempTask_attributes);

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 83;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* LED pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB12 PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/* LCD functions */

void LCD_Enable()
{
 HAL_GPIO_WritePin(EN_PORT,EN_PIN,1);
 delay_us(50);
 HAL_GPIO_WritePin(EN_PORT,EN_PIN,0);
}

void LCD_Send4(uint8_t data)
{
 HAL_GPIO_WritePin(D4_PORT,D4_PIN,(data>>0)&1);
 HAL_GPIO_WritePin(D5_PORT,D5_PIN,(data>>1)&1);
 HAL_GPIO_WritePin(D6_PORT,D6_PIN,(data>>2)&1);
 HAL_GPIO_WritePin(D7_PORT,D7_PIN,(data>>3)&1);
 LCD_Enable();
}

void LCD_Command(uint8_t cmd)
{
 HAL_GPIO_WritePin(RS_PORT,RS_PIN,0);
 LCD_Send4(cmd>>4);
 LCD_Send4(cmd&0x0F);
 HAL_Delay(2);
}

void LCD_Data(uint8_t data)
{
 HAL_GPIO_WritePin(RS_PORT,RS_PIN,1);
 LCD_Send4(data>>4);
 LCD_Send4(data&0x0F);
 HAL_Delay(2);
}

void LCD_Init()
{
 HAL_Delay(50);
 LCD_Send4(0x03);
 HAL_Delay(5);
 LCD_Send4(0x03);
 HAL_Delay(1);
 LCD_Send4(0x03);
 LCD_Send4(0x02);
 LCD_Command(0x28);
 LCD_Command(0x0C);
 LCD_Command(0x06);
 LCD_Command(0x01);
}

void LCD_SetCursor(int row,int col)
{
 uint8_t addr=(row==0)?0x80:0xC0;
 addr+=col;
 LCD_Command(addr);
}

void LCD_String(char *str)
{
 while(*str)
 LCD_Data(*str++);
}
/* ================= DS18B20 FUNCTIONS ================= */

void DS_Output(void)
{
 GPIO_InitTypeDef GPIO_InitStruct = {0};

 GPIO_InitStruct.Pin = DS_PIN;
 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

 HAL_GPIO_Init(DS_PORT, &GPIO_InitStruct);
}

void DS_Input(void)
{
 GPIO_InitTypeDef GPIO_InitStruct = {0};

 GPIO_InitStruct.Pin = DS_PIN;
 GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
 GPIO_InitStruct.Pull = GPIO_NOPULL;

 HAL_GPIO_Init(DS_PORT, &GPIO_InitStruct);
}

uint8_t DS_Reset(void)
{
 uint8_t response;

 DS_Output();

 HAL_GPIO_WritePin(DS_PORT, DS_PIN, 0);

 delay_us(480);

 DS_Input();

 delay_us(80);

 response = HAL_GPIO_ReadPin(DS_PORT, DS_PIN);

 delay_us(400);

 return response;
}

void DS_WriteBit(uint8_t bit)
{
 DS_Output();

 HAL_GPIO_WritePin(DS_PORT, DS_PIN, 0);

 if(bit)
  delay_us(1);
 else
  delay_us(60);

 DS_Input();

 if(bit)
  delay_us(60);
 else
  delay_us(1);
}

uint8_t DS_ReadBit(void)
{
 uint8_t bit=0;

 DS_Output();
 HAL_GPIO_WritePin(DS_PORT, DS_PIN, 0);

 delay_us(2);

 DS_Input();

 delay_us(10);

 bit = HAL_GPIO_ReadPin(DS_PORT, DS_PIN);

 delay_us(50);

 return bit;
}

void DS_WriteByte(uint8_t data)
{
 for(int i=0;i<8;i++)
 {
  DS_WriteBit(data & 0x01);
  data >>=1;
 }
}

uint8_t DS_ReadByte(void)
{
 uint8_t data=0;

 for(int i=0;i<8;i++)
 {
  data >>=1;

  if(DS_ReadBit())
   data |= 0x80;
 }

 return data;
}

float DS_ReadTemp(void)
{
 uint8_t TL,TH;
 int16_t TEMP;

 DS_Reset();

 DS_WriteByte(0xCC);
 DS_WriteByte(0x44);

 osDelay(750);

 DS_Reset();

 DS_WriteByte(0xCC);
 DS_WriteByte(0xBE);

 TL = DS_ReadByte();
 TH = DS_ReadByte();

 TEMP = (TH<<8)|TL;

 return (float)TEMP/16.0;
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the TempTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
 LCD_Init();

 char buffer[16];
 float temperature;

 for(;;)
 {
  temperature = DS_ReadTemp();

  LCD_SetCursor(0,0);
  LCD_String("Temperature");

  sprintf(buffer,"%.2f C   ",temperature);

  LCD_SetCursor(1,0);
  LCD_String(buffer);

  osDelay(1000);
 }
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
