/*
 * init_test.c
 *
 * Created on: May 19, 2021 22:50
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include "common.h"

#include "periph/periph.h"

#define TASK_PRIORITY_HIGHEST 4
#define TASK_PRIORITY_HIGH 3
#define TASK_PRIORITY_MID 2
#define TASK_PRIORITY_LOW 1

TestItemList item_list;

void InitTestItems(TestItemList* list) {
  DPrintf(0, "[INFO] Check peripheral configuration... \n", 0);

  //---------------------------------------------//

  list->dio_input_num = 0;
  for (int i = 0; i < DI_PIN_NUM; ++i) {
    if (dio_cfg.input[i].port != NULL) list->dio_input_num++;
  }

  list->dio_output_num = 0;
  for (int i = 0; i < DO_PIN_NUM; ++i) {
    if (dio_cfg.output[i].port != NULL) list->dio_output_num++;
  }

  //---------------------------------------------//

  list->led_num = 0;
  for (int i = 0; i < LED_NUM; ++i) {
    if (led_cfg.led[i].pin != NULL) list->led_num++;
  }

  DPrintf(0, "[INFO] Summay of defined peripherals: \n", 0);
  DPrintf(0, "[INFO] - Dio input pin number: %d\n", list->dio_input_num);
  DPrintf(0, "[INFO] - Dio output pin number: %d (%d LEDs)\n",
          list->dio_output_num - list->led_num, list->led_num);
  DPrintf(0, "[INFO] - LED pin number: %d\n", list->led_num);

  //---------------------------------------------//

  // check which items to run
  if (list->dio_input_num == 0 && (list->dio_output_num - list->led_num) == 0)
    list->enable_dio_test = false;
  else
    list->enable_dio_test = true;

  if (list->led_num == 0)
    list->enable_led_test = false;
  else
    list->enable_led_test = true;

  // sanity check
  bool ret = false;
  if (list->led_num > list->dio_output_num) {
    ret = true;
    DPrintf(0, "[ERROR] Inconsistency found in LED definition\n", 0);
  }

  if (!ret) {
    DPrintf(0,
            "[INFO] Sanity check completed, no inconsistency found in "
            "peripheral configuration\n",
            0);
    DPrintf(0, "[INFO] Checklist for STM32CubeMX configurations \n", 0);
    if (list->enable_dio_test) {
      DPrintf(0,
              "[INFO] - DI GPIO: set rising edge trigger detection with pull "
              "down \n",
              0);
      DPrintf(0,
              "[INFO] - DI EXTI: you've enabled the EXTI interrupt in NVIC "
              "settings\n",
              0);
    }
  } else {
    DPrintf(0,
            "[ERROR] Inconsistency found in peripheral configuration, please "
            "fix the error first!!!\n",
            0);
  }
}

void StartTestbed() {
  DPrintf(0, "\n\n\n", 0);
  DPrintf(0, "****************************************************\n", 0);
  DPrintf(0, "Starting STM32 testbed, target board: %s\n", BOARD_NAME);
  DPrintf(0, "----------------------------------------------------\n", 0);

  InitTestItems(&item_list);

  xTaskCreate(TestbedDioTask, (const char*)"TestbedIO", 256, &item_list,
              TASK_PRIORITY_MID, NULL);
  xTaskCreate(TestbedUartTask, (const char*)"TestbedUart", 256, &item_list,
              TASK_PRIORITY_MID, NULL);

  DPrintf(0, "----------------------------------------------------\n", 0);
  DPrintf(0, "[INFO] Testing task started \n", 0);
}
