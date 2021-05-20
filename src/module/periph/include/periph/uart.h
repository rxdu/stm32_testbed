/*
 * uart.h
 *
 * Created on: May 20, 2021 21:32
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#ifndef UART_H
#define UART_H

#include "periph/periph.h"

void UartSendDataAndWaitForEcho(UartChnDef* chn, uint8_t* data, size_t len,
                                uint32_t timeout);

#endif /* UART_H */
