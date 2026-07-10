#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include "main.h"
extern const uint8_t image[1024];

void SSD1306_Init(void);
void SSD1306_Clear(void);
void SSD1306_DisplayImage(const uint8_t *img);

void SSD1306_DisplayTemperature(float temp);
void SSD1306_DisplayMAC(void);
void SSD1306_DrawScrollingText(void);

#endif
