/*
 * testbed_task.c
 *
 * Created on: May 16, 2021 21:26
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include "testbed/testbed_init.h"

#include "FreeRTOS.h"
#include "task.h"

#include "main.h"

#define TASK_PRIORITY_HIGHEST 4
#define TASK_PRIORITY_HIGH 3
#define TASK_PRIORITY_MID 2
#define TASK_PRIORITY_LOW 1

static void TestbedMainTask();

bool InitTestbed() {
  xTaskCreate(TestbedMainTask, (const char *)"TestBedMain", 256, NULL,
              TASK_PRIORITY_MID, NULL);
  return true;
}

void TestbedMainTask() {
  const TickType_t task_delay = pdMS_TO_TICKS(200);
  TickType_t last_waketime = xTaskGetTickCount();

  for (;;) {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
    HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);

    vTaskDelayUntil(&last_waketime, task_delay);
  }
}