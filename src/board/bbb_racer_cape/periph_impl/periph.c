/*
 * periph.c
 *
 * Created on: Dec 27, 2020 23:11
 * Description:
 *
 * Copyright (c) 2020 Ruixiang Du (rdu)
 */

#include "periph/periph.h"

#include "main.h"

#include "stm32f4xx_ll_tim.h"

// GPIO
DioConfig dio_cfg = {
    // input pins
    .input = {{DI1_GPIO_Port, DI1_Pin, DI_EXTI},
              {DI2_GPIO_Port, DI2_Pin, DI_POLLING},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE},
              {NULL, 0x00000000, DIO_TEST_NONE}},
    // output pins
    .output = {{LED1_GPIO_Port, LED1_Pin, DO_TOGGLING},
               {LED2_GPIO_Port, LED2_Pin, DO_TOGGLING},
               {LED3_GPIO_Port, LED3_Pin, DO_TOGGLING},
               {LED4_GPIO_Port, LED4_Pin, DO_TOGGLING},
               {DO1_GPIO_Port, DO1_Pin, DO_TOGGLING},
               {VDD_SENSOR_EN_GPIO_Port, VDD_SENSOR_EN_Pin, DO_CONST_SET},
               {NULL, 0x00000000, DIO_TEST_NONE},
               {NULL, 0x00000000, DIO_TEST_NONE},
               {NULL, 0x00000000, DIO_TEST_NONE},
               {NULL, 0x00000000, DIO_TEST_NONE},
               {NULL, 0x00000000, DIO_TEST_NONE},
               {NULL, 0x00000000, DIO_TEST_NONE},
               {NULL, 0x00000000, DIO_TEST_NONE},
               {NULL, 0x00000000, DIO_TEST_NONE},
               {NULL, 0x00000000, DIO_TEST_NONE},
               {NULL, 0x00000000, DIO_TEST_NONE}},
    .led_pin_num = 4};

// LED
LedConfig led_cfg = {.led[0] = {&dio_cfg.output[0], true},
                     .led[1] = {&dio_cfg.output[1], true},
                     .led[2] = {&dio_cfg.output[2], true},
                     .led[3] = {&dio_cfg.output[3], true},
                     .led[4] = {NULL, true},
                     .led[5] = {NULL, true},
                     .led[6] = {NULL, true},
                     .led[7] = {NULL, true}};

// USART3 - for SBUS communication
// #define SBUS_DMA_RX_BUFFER_SIZE 64
// #define SBUS_FRAME_BUFFER_SIZE 256
// static uint8_t sbus_dma_buffer[SBUS_DMA_RX_BUFFER_SIZE];
// static Ringbuf sbus_ring_buffer;
// static uint8_t sbus_rx_buffer[SBUS_FRAME_BUFFER_SIZE];

// UARTChnMapping uart = {
//     // sbus
//     .channel[0] = {.port = USART6,
//                    .rx_dma = {DMA2, LL_DMA_STREAM_1, LL_DMA_CHANNEL_5,
//                               sbus_dma_buffer, SBUS_DMA_RX_BUFFER_SIZE, 0},
//                    .tx_dma = {NULL, 0, 0, 0, 0},
//                    // ring buffer
//                    .rx_ring_buffer = &sbus_ring_buffer,
//                    .rxbuf_data = sbus_rx_buffer,
//                    .rxbuf_size = SBUS_FRAME_BUFFER_SIZE}};

// // CAN
// #define CAN1_INPUT_QUEUE_LENGTH 32

// CANChnMapping can = {
//     .channel[0] = {
//         .port = &hcan1,
//         .active_its = CAN_IT_RX_FIFO0_MSG_PENDING,
//         .rx_fifo = CAN_RX_FIFO0,
//         .rx_filter = {0x0000, 0x0000, 0x0000, 0x0000, CAN_RX_FIFO0, 0,
//                       CAN_FILTERMODE_IDMASK, CAN_FILTERSCALE_32BIT, ENABLE,
//                       0},
//         .rx_frame_buffer_length = CAN1_INPUT_QUEUE_LENGTH}};

// // SPI
// SPIChnMapping spi = {.channel[0] = {3, SPI1}};

// // PWM
// PWMChnMapping pwm = {
//     .channel[0] = {TIM4, LL_TIM_CHANNEL_CH2},
//     .channel[1] = {TIM4, LL_TIM_CHANNEL_CH3},
// };