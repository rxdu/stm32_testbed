/*
 * blink_led.c
 *
 * Created on: Dec 01, 2020 17:45
 * Description:
 *
 * Copyright (c) 2020 Ruixiang Du (rdu)
 */

#include "blink_led.h"

#include "app/init.h"
#include "app-def.h"
#include "led/led.h"
#include "periphdef.h"

static void vTaskBlinkLED(void *p);

static LED led1;
static LED led2;
static LED led3;

void SetupBlinkLEDTask() {
  led1.pin = &dio.output[DO_LED_WARN];
  led1.active_level = DIO_LEVEL_LOW;

  led2.pin = &dio.output[DO_LED_STATUS];
  led2.active_level = DIO_LEVEL_LOW;

  led3.pin = &dio.output[DO_LED_BLUE];
  led3.active_level = DIO_LEVEL_LOW;

  TurnOnLED(&led1);
  TurnOnLED(&led2);
  TurnOffLED(&led3);

  xTaskCreate(vTaskBlinkLED, (const char *)"BlinkLED", 128, NULL,
              TASK_PRIORITY_MID, NULL);
}

void vTaskBlinkLED(void *p) {
  const TickType_t task_delay = pdMS_TO_TICKS(500);
  TickType_t last_waketime = xTaskGetTickCount();
  for (;;) {
    ToggleLED(&led1);
    ToggleLED(&led2);
    ToggleLED(&led3);
    vTaskDelayUntil(&last_waketime, task_delay);
  }
}