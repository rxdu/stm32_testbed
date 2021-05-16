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

#define DMA_CHN_NUM 16
#define TIMER_CHN_NUM 4
#define PWM_CHN_NUM 4

#define CAN_CHN_NUM 2
#define UART_CHN_NUM 8
#define SPI_CHN_NUM 2

//------------------------------------------------------------------//

// digital input/output
typedef struct {
  GPIO_TypeDef *port;
  uint32_t pin;
} DIOPinDef;

typedef struct {
  DIOPinDef input[DI_PIN_NUM];
  DIOPinDef output[DO_PIN_NUM];
} DIOPinMapping;

// // DMA
// typedef struct {
//   DMAControllerDef controller;
//   uint32_t stream;
//   uint32_t channel;
//   uint8_t *address;
//   uint32_t size;
//   size_t indexer;
// } DMAChnDef;

// // SPI
// typedef struct {
//   uint8_t cs_pin;
//   SPIPortDef port;
// } SPIChnDef;

// typedef struct {
//   SPIChnDef channel[SPI_CHN_NUM];
// } SPIChnMapping;

// // UART
// typedef struct {
//   UARTPortDef port;
//   DMAChnDef rx_dma;
//   DMAChnDef tx_dma;
// #ifdef USE_FREERTOS
//   SemaphoreHandle_t rx_semaphore;
// #else
//   bool new_data_received;
// #endif
//   // data managed inside driver
//   Ringbuf *rx_ring_buffer;
//   uint8_t *rxbuf_data;
//   uint32_t rxbuf_size;
// } UARTChnDef;

// typedef struct {
//   UARTChnDef channel[UART_CHN_NUM];
// } UARTChnMapping;

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
extern DIOPinMapping dio;

// extern UARTChnMapping uart;
// extern SPIChnMapping spi;
// extern CANChnMapping can;

// extern PWMChnMapping pwm;

#endif /* PERIPH_H */
