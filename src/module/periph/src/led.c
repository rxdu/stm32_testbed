/*
 * led.c
 *
 * Created on: May 19, 2021 21:44
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include "periph/led.h"

#include "periph/dio.h"

void TurnOnLed(LedPinDef* led_pin) {
  assert(led_pin != NULL);
  if (led_pin->active_low)
    SetDio(led_pin->pin);
  else
    ResetDio(led_pin->pin);
}

void TurnOffLed(LedPinDef* led_pin) {
  assert(led_pin != NULL);
  if (led_pin->active_low)
    ResetDio(led_pin->pin);
  else
    SetDio(led_pin->pin);
}

void ToggleLed(LedPinDef* led_pin) {
  assert(led_pin != NULL);
  ToggleDio(led_pin->pin);
}