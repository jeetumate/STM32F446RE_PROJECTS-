# STM32F446RE_PROJECTS-
# STM32 LED Blink

## Overview
This project demonstrates how to blink a single LED using the STM32F446RE microcontroller and STM32CubeIDE.

## Features
- GPIO Output Configuration
- LED ON/OFF control
- Delay using HAL_Delay()
- Basic STM32 programming

## Hardware
- STM32 NUCLEO-F446RE
- Built-in LED (LD2)

## Working
The GPIO pin connected to the onboard LED is configured as Output.
Inside the infinite loop:
- LED turns ON
- Delay
- LED turns OFF
- Delay
This process repeats continuously.

## Concepts Covered
- GPIO
- HAL Library
- Infinite Loop
- Digital Output

## Software
- STM32CubeIDE
- STM32 HAL Driver