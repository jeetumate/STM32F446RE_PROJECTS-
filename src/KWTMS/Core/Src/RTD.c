#include "rtd.h"

extern ADC_HandleTypeDef hadc1;

float ReadTemperature(void)
{
    uint32_t sum = 0;

    for(int i=0;i<20;i++)
    {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1,10);

        sum += HAL_ADC_GetValue(&hadc1);

        HAL_ADC_Stop(&hadc1);

        HAL_Delay(5);
    }

    float adcValue = sum / 20.0f;

    /* Convert ADC value to voltage */
    float voltage = adcValue * (3.3f / 4095.0f);

    /* Convert voltage to temperature (same logic as Arduino code) */
    float temperature = voltage * 20.0f;

    /* calibration correction */
    float scaleFactor = 1.17f;
    float offset = 4.10f;

    temperature = temperature * scaleFactor + offset;

    return temperature;
}
