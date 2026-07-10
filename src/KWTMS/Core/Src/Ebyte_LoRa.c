#include "ebyte_lora.h"
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart1;

void LoRa_SendTemperature(float temp)
{
    char buffer[40];

    sprintf(buffer,"TEMP: %.2f C\r\n", temp);

    HAL_UART_Transmit(&huart1,(uint8_t*)buffer,strlen(buffer),100);

    HAL_Delay(100);
}
