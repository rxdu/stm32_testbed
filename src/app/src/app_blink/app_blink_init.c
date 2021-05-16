/*
 * scout_v2_fw_init.c
 *
 * Created on: Dec 01, 2020 15:57
 * Description:
 *
 * Copyright (c) 2020 Ruixiang Du (rdu)
 */

#include "app/init.h"

#include "blink_led.h"

uint16_t InitApp() {
  SetupBlinkLEDTask();
  return RACER_INIT_NO_ERROR;
}