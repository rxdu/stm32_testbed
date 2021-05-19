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

static uint32_t count = 0;

void TestDio(TestItemList* list, uint32_t freq_div) {
  if (++count % freq_div == 0) {
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