/*
 * stm32.h
 *
 * Created on: Feb 05, 2020 11:26
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef STM32_H
#define STM32_H

#include <stdint.h>

#ifdef STM32F1
#include "stm32f1xx.h" 
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_can.h"
#elif defined(STM32F4)
#include "stm32f4xx.h" 
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_can.h"
#endif

typedef GPIO_TypeDef *DIOPortDef;

typedef SPI_TypeDef *SPIPortDef;

typedef USART_TypeDef *UARTPortDef;

typedef DMA_TypeDef *DMAControllerDef;

typedef TIM_TypeDef *TimerDef;

typedef CAN_HandleTypeDef *CanDef;

#endif /* STM32_H */
