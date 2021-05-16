/*
 * periph.c
 *
 * Created on: Dec 27, 2020 23:11
 * Description:
 *
 * Copyright (c) 2020 Ruixiang Du (rdu)
 */

#include "mcal/periph.h"
#include "main.h"

#include "main.h"
#include "stm32f4xx_ll_tim.h"

// GPIO
// DIOPinMapping dio = {
//     // input pins
//     .input = {{NULL, 0x00000000, NULL},
//               {NULL, 0x00000000, NULL},
//               {NULL, 0x00000000, NULL},
//               {NULL, 0x00000000, NULL},
//               {NULL, 0x00000000, NULL},
//               {NULL, 0x00000000, NULL},
//               {NULL, 0x00000000, NULL},
//               {NULL, 0x00000000, NULL}},
//     // output pins
//     .output = {/* LED - R/G/B */
//                {LED1_GPIO_Port, LED1_Pin, NULL},
//                {LED2_GPIO_Port, LED2_Pin, NULL},
//                {LED3_GPIO_Port, LED3_Pin, NULL},
//                {LED4_GPIO_Port, LED4_Pin, NULL},
//                /* SBus inversion enable */
//                {SBUS_INV_GPIO_Port, SBUS_INV_Pin, NULL},
//                /* MPU9250 CS*/
//                {MPU9250_CS_GPIO_Port, MPU9250_CS_Pin, NULL},
//                /* Testing */
//                {FREQ_TEST_PIN_GPIO_Port, FREQ_TEST_PIN_Pin, NULL}}};

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
//                       CAN_FILTERMODE_IDMASK, CAN_FILTERSCALE_32BIT, ENABLE, 0},
//         .rx_frame_buffer_length = CAN1_INPUT_QUEUE_LENGTH}};

// // SPI
// SPIChnMapping spi = {.channel[0] = {3, SPI1}};

// // PWM
// PWMChnMapping pwm = {
//     .channel[0] = {TIM4, LL_TIM_CHANNEL_CH2},
//     .channel[1] = {TIM4, LL_TIM_CHANNEL_CH3},
// };