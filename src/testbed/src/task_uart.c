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

#define UART_RX_TIMEOUT 2000

static uint8_t tx_buffer[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};

void TestbedUartTask(void* param) {
  TestItemList* list = (TestItemList*)param;
  (void)list;

  // initialize uart ports
  for (int i = 0; i < UART_CHN_NUM; ++i) {
    if (uart_cfg.channel[i].handler != NULL) {
      uart_cfg.channel[i].rx_semaphore = xSemaphoreCreateBinary();
      if (uart_cfg.channel[i].rx_semaphore == NULL)
        DPrintf(0, "[ERROR][UART] Failed to create semaphore for %s\n",
                uart_cfg.channel[i].name);
    }
  }

  const TickType_t task_delay = pdMS_TO_TICKS(5000);
  TickType_t last_waketime = xTaskGetTickCount();

  for (;;) {
    for (int i = 0; i < UART_CHN_NUM; ++i) {
      if (uart_cfg.channel[i].handler != NULL) {
        UartSendDataAndWaitForEcho(&uart_cfg.channel[i], tx_buffer,
                                   sizeof(tx_buffer), 10);
        if (xSemaphoreTake(uart_cfg.channel[i].rx_semaphore, UART_RX_TIMEOUT) ==
            pdPASS) {
          bool echo_matched = true;
          for (int j = 0; j < 8; ++j) {
            if (uart_cfg.channel[i].rx_buffer[j] != tx_buffer[j]) {
              echo_matched = false;
              break;
            }
          }
          if (echo_matched) {
            DPrintf(0, "[INFO][UART] Echo received correctly from %s <------\n",
                    uart_cfg.channel[i].name);
          } else {
            DPrintf(0, "[INFO][UART] Echo received with mismatch from %s\n",
                    uart_cfg.channel[i].name);
          }
        } else {
          DPrintf(0,
                  "[INFO][UART] Echo not received within TIMEOUT (%d ms) from "
                  "%s ?????? \n",
                  UART_RX_TIMEOUT, uart_cfg.channel[i].name);
        }
      }
    }

    vTaskDelayUntil(&last_waketime, task_delay);
  }
}