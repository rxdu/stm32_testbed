/*
 * task_dio.c
 *
 * Created on: May 20, 2021 23:13
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include "common.h"

#include "periph/dio.h"
#include "periph/led.h"

static uint32_t dio_count = 0;
static uint32_t led_count = 0;
static uint32_t led_select = 0;

void TestDio(TestItemList* list, uint32_t freq_div) {
  if (++dio_count % freq_div == 0) {
    assert(dio_cfg.led_pin_num < LED_NUM);

    // input pins
    for (int i = 0; i < list->dio_input_num; ++i) {
      if (dio_cfg.input[i].mode == DI_POLLING) {
        DPrintf(0, "[INFO] DIO input pin %d: %d\n", i,
                GetDioPinLevel(&dio_cfg.input[i]));
      }
    }

    // output pins
    for (int i = list->led_num; i < list->dio_output_num; ++i) {
      if (dio_cfg.output[i].mode == DO_TOGGLING) ToggleDio(&dio_cfg.output[i]);
      if (dio_cfg.output[i].mode == DO_CONST_SET) SetDio(&dio_cfg.output[i]);
      if (dio_cfg.output[i].mode == DO_CONST_RESET)
        ResetDio(&dio_cfg.output[i]);
    }
  }
}

void TestLed(TestItemList* list, uint32_t freq_div) {
  if (++led_count % freq_div == 0) {
    for (int i = 0; i < list->led_num; ++i)
      if (led_select % list->led_num == i) ToggleLed(&led_cfg.led[i]);
    ++led_select;
  }
}

void TestbedDioTask(void* param) {
  TestItemList* list = (TestItemList*)param;
  
  const TickType_t task_delay = pdMS_TO_TICKS(10);
  TickType_t last_waketime = xTaskGetTickCount();

  // main loop runs at 100Hz (10ms)
  for (;;) {
    // LED task runs 2Hz (500ms)
    if (list->enable_led_test) TestLed(list, 50);

    // DIO task runs at 0.5Hz (2s)
    if (list->enable_dio_test) TestDio(list, 200);

    // // UART task runs at 1Hz (1s)
    // TestUart(&item_list, 100);

    vTaskDelayUntil(&last_waketime, task_delay);
  }
}