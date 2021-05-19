/*
 * led.h
 *
 * Created on: May 19, 2021 21:44
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#ifndef LED_H
#define LED_H

#include "periph/periph.h"

void TurnOnLed(LedPinDef* led_pin);
void TurnOffLed(LedPinDef* led_pin);
void ToggleLed(LedPinDef* led_pin);

#endif /* LED_H */
