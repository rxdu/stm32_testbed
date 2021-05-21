/*
 * periph.h
 *
 * Created on: Jan 13, 2020 16:50
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef PERIPH_H
#define PERIPH_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#ifdef STM32F1
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_can.h"
#elif defined(STM32F4)
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_can.h"
#endif

#include "FreeRTOS.h"
#include "semphr.h"
// #include "queue.h"

#define DI_PIN_NUM 16
#define DO_PIN_NUM 16
#define LED_NUM 8

#define UART_CHN_NUM 8
#define UART_PORT_NAME_LEN 16
#define UART_RX_BUFFER_SIZE 64

#define CAN_CHN_NUM 2
#define SPI_CHN_NUM 2

#define TIMER_CHN_NUM 4
#define PWM_CHN_NUM 4

//------------------------------------------------------------------//

// digital input/output
typedef enum {
  DIO_TEST_NONE = 0,
  DI_EXTI,
  DI_POLLING,
  DO_TOGGLING,
  DO_CONST_SET,
  DO_CONST_RESET
} DioTestMode;

typedef struct {
  GPIO_TypeDef* port;
  uint32_t pin;
  DioTestMode mode;
} DioPinDef;

typedef struct {
  DioPinDef input[DI_PIN_NUM];
  DioPinDef output[DO_PIN_NUM];
  uint8_t led_pin_num;
} DioConfig;

typedef struct {
  DioPinDef* pin;
  bool active_low;
} LedPinDef;

typedef struct {
  LedPinDef led[LED_NUM];
} LedConfig;

// UART
typedef struct {
  char name[UART_PORT_NAME_LEN];
  UART_HandleTypeDef* handler;
  SemaphoreHandle_t rx_semaphore;
  uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
} UartChnDef;

typedef struct {
  UartChnDef channel[UART_CHN_NUM];
} UartConfig;

// // SPI
// typedef struct {
//   uint8_t cs_pin;
//   SPIPortDef port;
// } SPIChnDef;

// typedef struct {
//   SPIChnDef channel[SPI_CHN_NUM];
// } SPIChnMapping;

// // Timer
// typedef struct {
//   TimerDef timer;
//   uint32_t channel;
// } TimerChnDef;

// typedef struct {
//   TimerChnDef channel[PWM_CHN_NUM];
// } PWMChnMapping;

// typedef struct {
//   TimerChnDef channel[TIMER_CHN_NUM];
// } GTimerChnMapping;

// // CAN
// typedef struct {
//   uint32_t filter_id_high;
//   uint32_t filter_id_low;
//   uint32_t filter_mask_id_high;
//   uint32_t filter_mask_id_low;
//   uint32_t filter_fifo_assignment;
//   uint32_t filter_bank;
//   uint32_t filter_mode;
//   uint32_t filter_scale;
//   uint32_t filter_activation;
//   uint32_t slave_start_filter_bank;
// } CANFilter;

// typedef struct {
//   CanDef port;
//   uint32_t active_its;
//   uint32_t rx_fifo;
//   CANFilter rx_filter;
//   // handle received data
// #ifdef USE_FREERTOS
//   QueueHandle_t rx_frame_buffer;
//   uint32_t rx_frame_buffer_length;
// #endif
// } CANChnDef;

// typedef struct {
//   CANChnDef channel[CAN_CHN_NUM];
// } CANChnMapping;

//------------------------------------------------------------------//

// Port/Device Mapping
extern DioConfig dio_cfg;
extern LedConfig led_cfg;

extern UartConfig uart_cfg;
// extern SPIChnMapping spi;
// extern CANChnMapping can;

// extern PWMChnMapping pwm;

#endif /* PERIPH_H */
