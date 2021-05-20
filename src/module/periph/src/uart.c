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
  HAL_UART_Transmit(chn->handler, data, len, timeout);
  HAL_UART_Receive_IT(chn->handler, chn->rx_buffer, len);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
  for (int i = 0; i < UART_CHN_NUM; ++i) {
    if (uart_cfg.channel[i].handler == huart) {
      DPrintf(0, "UART rx callback triggered from channel: %s\n",
              uart_cfg.channel[i].name);
    }
  }
}