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

#include "dprint/dprint.h"
#include "test_items.h"

#define TASK_PRIORITY_HIGHEST 4
#define TASK_PRIORITY_HIGH 3
#define TASK_PRIORITY_MID 2
#define TASK_PRIORITY_LOW 1

static void TestbedMainTask();

bool InitTestbed() {
  DPrintf(0, "Starting STM32 testbed\n", 0);

  xTaskCreate(TestbedMainTask, (const char *)"TestBedMain", 256, NULL,
              TASK_PRIORITY_MID, NULL);
  return true;
}

void TestbedMainTask() {
  const TickType_t task_delay = pdMS_TO_TICKS(10);
  TickType_t last_waketime = xTaskGetTickCount();

  for (;;) {
    TestLed();

    vTaskDelayUntil(&last_waketime, task_delay);
  }
}