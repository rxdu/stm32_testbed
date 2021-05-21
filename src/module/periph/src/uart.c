/*
 * uart.c
 *
 * Created on: May 20, 2021 21:32
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include "periph/uart.h"

#include "dprint/dprint.h"

void UartSendDataAndWaitForEcho(UartChnDef* chn, uint8_t* data, size_t len,
                                uint32_t timeout) {
  DPrintf(0, "[INFO][UART] Data sent from %s\n", chn->name);
  HAL_UART_Receive_IT(chn->handler, chn->rx_buffer, len);
  HAL_UART_Transmit(chn->handler, data, len, timeout);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  for (int i = 0; i < UART_CHN_NUM; ++i) {
    if (uart_cfg.channel[i].handler == huart) {
      //   DPrintf(0, "[INFO][UART] Data received from %s\n",
      //           uart_cfg.channel[i].name);
      //   for (int i = 0; i < 8; ++i) {
      //     DPrintf(0, "%x ", uart_cfg.channel[0].rx_buffer[i]);
      //   }
      //   DPrintf(0, "\n", 0);
      xSemaphoreGiveFromISR(uart_cfg.channel[i].rx_semaphore,
                            &xHigherPriorityTaskWoken);
    }
  }
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}