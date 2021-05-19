/*
 * testbed_task.c
 *
 * Created on: May 16, 2021 21:26
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include "testbed/testbed.h"

#include "FreeRTOS.h"
#include "task.h"

#include "dprint/dprint.h"

#include "test_items.h"

#define TASK_PRIORITY_HIGHEST 4
#define TASK_PRIORITY_HIGH 3
#define TASK_PRIORITY_MID 2
#define TASK_PRIORITY_LOW 1

TestItemList item_list;

static void TestbedMainTask();

void StartTestbed() {
  DPrintf(0, "\n\n\n", 0);
  DPrintf(0, "****************************************************\n", 0);
  DPrintf(0, "Starting STM32 testbed, target board: %s\n", BOARD_NAME);
  DPrintf(0, "----------------------------------------------------\n", 0);

  InitTestItems(&item_list);

  xTaskCreate(TestbedMainTask, (const char*)"TestBedMain", 256, NULL,
              TASK_PRIORITY_MID, NULL);

  DPrintf(0, "----------------------------------------------------\n", 0);
  DPrintf(0, "[INFO] Testing task started \n", 0);
}

void TestbedMainTask() {
  const TickType_t task_delay = pdMS_TO_TICKS(10);
  TickType_t last_waketime = xTaskGetTickCount();

  // main loop runs at 100Hz (10ms)
  for (;;) {
    // LED task runs 2Hz (500ms)
    TestLed(&item_list, 50);

    // DIO task runs at 0.5Hz (2s)
    TestDio(&item_list, 200);

    vTaskDelayUntil(&last_waketime, task_delay);
  }
}