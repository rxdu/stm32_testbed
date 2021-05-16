/*
 * led_test.c
 *
 * Created on: May 16, 2021 23:08
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include "test_items.h"

#include "main.h"

static uint8_t count = 0;
static uint8_t led_select = 0;

uint8_t TestLed() {
  // update LED every 50 iterations
  if (++count % 50 == 0) {
    if (led_select % 4 == 0) HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    if (led_select % 4 == 1) HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    if (led_select % 4 == 2) HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
    if (led_select % 4 == 3) HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
    ++led_select;
  }
}