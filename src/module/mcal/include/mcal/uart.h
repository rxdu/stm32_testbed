/*
 * uart.h
 *
 * Created on: Feb 29, 2020 19:46
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef UART_H
#define UART_H

#include <stdbool.h>
#include <stdint.h>

#include "mcal/periph.h"

typedef enum {
  UART_NO_DMA = 0,
  // additional settings for DMA mode
  UART_TX_DMA,
  UART_RX_DMA,
  UART_TX_RX_DMA,
  UART_SBUS
} UARTMode;

/// Setup and enable UART
uint16_t SetupUart(UARTChnDef* chn, UARTMode mode);

// USART DMA RX (non-blocking)
void UartStartDmaRxTransfer(UARTChnDef* chn);

// USART data TX (blocking)
void UartSendBytesBlocking(UARTChnDef* chn, const uint8_t* data, size_t len);

// USART DMA TX (non-blocking)
bool UartIsDmaTxComplete(UARTChnDef* chn);
void UartStartDmaTxTransfer(UARTChnDef* chn, const uint8_t* data, size_t len);

// Get/query data from ring buffer with the following functions
size_t UartRingBuffGetSize(UARTChnDef* chn);
size_t UartRingBuffGetCapacity(UARTChnDef* chn);
size_t UartRingBuffFetchByte(UARTChnDef* chn, uint8_t* data);
size_t UartRingBuffFetchString(UARTChnDef* chn, uint8_t* data);

// This function should be called when usart_rx_dma_semaphore is taken
void UartProcessRxDMAData(UARTChnDef* chn);

// Functions called in IRQ functions
void HandleUartTxDMAIRQ(UARTChnDef* chn);
void HandleUartRxDMAIRQ(UARTChnDef* chn);
void HandleUartRxTxIRQ(UARTChnDef* chn);

#endif /* UART_H */
