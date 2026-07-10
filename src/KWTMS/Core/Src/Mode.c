#include "mode.h"

uint8_t currentPage = 1;
uint8_t lastPage = 0;

static uint8_t lastButtonState = GPIO_PIN_SET;   // add this line

void CheckButton(void)
{
    uint8_t button = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);

    if(button == GPIO_PIN_RESET && lastButtonState == GPIO_PIN_SET)
    {
        currentPage++;

        if(currentPage > 2)
            currentPage = 1;

        HAL_Delay(200);
    }

    lastButtonState = button;
}
