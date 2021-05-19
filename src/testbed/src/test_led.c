/*
 * test_led.c
 *
 * Created on: May 19, 2021 22:04
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include "test_items.h"

#include "main.h"
#include "dprint/dprint.h"

#include "periph/led.h"

static uint32_t count = 0;
static uint32_t led_select = 0;

void TestLed(TestItemList* list, uint32_t freq_div) {
  if (++count % freq_div == 0) {
    for (int i = 0; i < list->led_num; ++i)
      if (led_select % list->led_num == i) ToggleLed(&led_cfg.led[i]);
    ++led_select;
  }
}