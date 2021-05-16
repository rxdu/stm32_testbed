/* 
 * test_dio.c
 * 
 * Created on: May 17, 2021 00:09
 * Description: 
 * 
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */ 

#include "test_items.h"

#include "main.h"
#include "dprint/dprint.h"

#include "periph/dio.h"

static uint8_t count = 0;
static uint8_t led_select = 0;

uint8_t TestDio() {
  // update LED every 50 iterations
  if (++count % 100 == 0) {
    if (led_select % 4 == 0) DioToggle(&dio.output[0]);
    if (led_select % 4 == 1) DioToggle(&dio.output[1]);
    if (led_select % 4 == 2) DioToggle(&dio.output[2]);
    if (led_select % 4 == 3) DioToggle(&dio.output[3]);
    ++led_select;
  }
  return 0;
}