/*
 * task_uart.c
 *
 * Created on: May 20, 2021 23:18
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include "common.h"

#include "periph/uart.h"

void TestUart(TestItemList* list) {
  uint8_t buffer[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
  UartSendDataAndWaitForEcho(&uart_cfg.channel[0], buffer, sizeof(buffer), 10);
}

void TestbedUartTask(void* param) {
  TestItemList* list = (TestItemList*)param;

  const TickType_t task_delay = pdMS_TO_TICKS(1000);
  TickType_t last_waketime = xTaskGetTickCount();

  for (;;) {
    TestUart(list);

    vTaskDelayUntil(&last_waketime, task_delay);
  }
}