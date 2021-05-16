/*
 * mcu.h
 *
 * Created on: Feb 05, 2020 11:29
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef MCU_H
#define MCU_H

#include "stm32.h"

#define DI_PIN_NUM 16
#define DO_PIN_NUM 16

#define DMA_CHN_NUM 16
#define TIMER_CHN_NUM 4
#define PWM_CHN_NUM 4

#define CAN_CHN_NUM 2
#define UART_CHN_NUM 8
#define SPI_CHN_NUM 2

#define MCAL_INIT_NO_ERROR ((uint16_t)0x0000)
#define MCAL_INIT_ADC_ERROR ((uint16_t)0x0001)
#define MCAL_INIT_CAN_ERROR ((uint16_t)0x0002)
#define MCAL_INIT_DIO_ERROR ((uint16_t)0x0004)
#define MCAL_INIT_DMA_ERROR ((uint16_t)0x0008)
#define MCAL_INIT_I2C_ERROR ((uint16_t)0x0010)
#define MCAL_INIT_PWM_ERROR ((uint16_t)0x0020)
#define MCAL_INIT_SPI_ERROR ((uint16_t)0x0040)
#define MCAL_INIT_UART_ERROR ((uint16_t)0x0080)

#endif /* MCU_H */
