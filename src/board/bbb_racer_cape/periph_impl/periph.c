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
#include "usart.h"
#include "can.h"

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
               {FRSKY_INV_GPIO_Port, FRSKY_INV_Pin, DO_CONST_RESET},
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

// UART
UartConfig uart_cfg = {.channel[0] = {"USART6", &huart6},
                       .channel[1] = {"UART8", &huart8},
                       .channel[2] = {"NULL", NULL},
                       //    .channel[2] = {"USART3", &huart3},
                       .channel[3] = {"NULL", NULL},
                       .channel[4] = {"NULL", NULL},
                       .channel[5] = {"NULL", NULL},
                       .channel[6] = {"NULL", NULL},
                       .channel[7] = {"NULL", NULL}};

// CAN
CanConfig can_cfg = {
    // CAN1
    .channel[0] = {.name = "CAN1",
                //    .handler = &hcan1,
                     .handler = NULL,
                   .active_its = CAN_IT_RX_FIFO0_MSG_PENDING,
                   .rx_fifo = CAN_RX_FIFO0,
                   .rx_filter = {0x0000, 0x0000, 0x0000, 0x0000, CAN_RX_FIFO0,
                                 0, CAN_FILTERMODE_IDMASK,
                                 CAN_FILTERSCALE_32BIT, ENABLE, 0}},
    // CAN2
    .channel[1] = {.name = "CAN2",
                   .handler = &hcan2,
                   .active_its = CAN_IT_RX_FIFO1_MSG_PENDING,
                   .rx_fifo = CAN_RX_FIFO1,
                   .rx_filter = {0x0000, 0x0000, 0x0000, 0x0000, CAN_RX_FIFO1,
                                 14, CAN_FILTERMODE_IDMASK,
                                 CAN_FILTERSCALE_32BIT, ENABLE, 14}}};

// // SPI
// SPIChnMapping spi = {.channel[0] = {3, SPI1}};

// // PWM
// PWMChnMapping pwm = {
//     .channel[0] = {TIM4, LL_TIM_CHANNEL_CH2},
//     .channel[1] = {TIM4, LL_TIM_CHANNEL_CH3},
// };