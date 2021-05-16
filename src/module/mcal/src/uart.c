/*
 * uart.c
 *
 * Created on: Feb 29, 2020 19:56
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#include "mcal/uart.h"

#include "mcal/dma.h"
#include "ringbuf/ringbuf.h"
#include "dprint/dprint.h"

#ifdef STM32F1
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_usart.h"
#elif defined(STM32F4)
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_usart.h"
#endif

static void UARTHandleDMATransferError(UARTChnDef* chn);

uint16_t SetupUart(UARTChnDef* chn, UARTMode mode) {
  if (mode == UART_TX_DMA || mode == UART_TX_RX_DMA) {
    LL_DMA_SetChannelSelection(chn->tx_dma.controller, chn->tx_dma.stream,
                               chn->tx_dma.channel);
    LL_DMA_ConfigTransfer(chn->tx_dma.controller, chn->tx_dma.stream,
                          LL_DMA_DIRECTION_MEMORY_TO_PERIPH |
                              LL_DMA_PRIORITY_HIGH | LL_DMA_MODE_NORMAL |
                              LL_DMA_PERIPH_NOINCREMENT |
                              LL_DMA_MEMORY_INCREMENT | LL_DMA_PDATAALIGN_BYTE |
                              LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_ConfigAddresses(chn->tx_dma.controller, chn->tx_dma.stream,
                           (uint32_t)chn->tx_dma.address,
                           LL_USART_DMA_GetRegAddr(chn->port),
                           LL_DMA_GetDataTransferDirection(
                               chn->tx_dma.controller, chn->tx_dma.stream));

    LL_DMA_EnableIT_TC(chn->tx_dma.controller, chn->tx_dma.stream);
    LL_DMA_EnableIT_TE(chn->tx_dma.controller, chn->tx_dma.stream);

    DWriteString(0, "Initialized USART TX DMA\n");
  }

  if (mode == UART_SBUS || mode == UART_RX_DMA || mode == UART_TX_RX_DMA) {
#ifdef USE_FREERTOS
    if (mode == UART_SBUS)
      chn->rx_semaphore = xSemaphoreCreateBinary();
    else
      chn->rx_semaphore = xSemaphoreCreateCounting(3, 0);
    if (chn->rx_semaphore == NULL) return false;
#endif

    RingbufInit(chn->rx_ring_buffer, chn->rxbuf_data, chn->rxbuf_size);

    LL_DMA_ConfigAddresses(chn->rx_dma.controller, chn->rx_dma.stream,
                           LL_USART_DMA_GetRegAddr(chn->port),
                           (uint32_t)chn->rx_dma.address,
                           LL_DMA_GetDataTransferDirection(
                               chn->rx_dma.controller, chn->rx_dma.stream));
    LL_DMA_SetDataLength(chn->rx_dma.controller, chn->rx_dma.stream,
                         chn->rx_dma.size);

    if (mode != UART_SBUS) {
      LL_DMA_EnableIT_HT(chn->rx_dma.controller, chn->rx_dma.stream);
      LL_DMA_EnableIT_TC(chn->rx_dma.controller, chn->rx_dma.stream);
      LL_DMA_EnableIT_TE(chn->rx_dma.controller, chn->rx_dma.stream);
      DWriteString(0, "Initialized USART RX DMA\n");
    }
  }
  return MCAL_INIT_NO_ERROR;
}

void UartSendBytesBlocking(UARTChnDef* chn, const uint8_t* data, size_t len) {
  const uint8_t* d = data;
  while (len--) {
    LL_USART_TransmitData8(chn->port, *d++);
    while (!LL_USART_IsActiveFlag_TXE(chn->port))
      ;
  }
  while (!LL_USART_IsActiveFlag_TC(chn->port))
    ;
}

bool UartIsDmaTxComplete(UARTChnDef* chn) {
  if (LL_DMA_IsEnabledStream(chn->tx_dma.controller, chn->tx_dma.stream))
    return false;
  else
    return true;
}

void UartStartDmaTxTransfer(UARTChnDef* chn, const uint8_t* data, size_t len) {
  // wait if a previous transmission is still undergoing
  while (LL_DMA_IsEnabledStream(chn->tx_dma.controller, chn->tx_dma.stream)) {
  }

  // Copy data to tx buffer
  memcpy(chn->tx_dma.address, data, len);
  LL_DMA_SetDataLength(chn->tx_dma.controller, chn->tx_dma.stream, len);

  // Enable DMA TX Interrupt
  LL_USART_EnableDMAReq_TX(chn->port);

  // Enable DMA Channel Tx
  LL_DMA_EnableStream(chn->tx_dma.controller, chn->tx_dma.stream);
}

void UartStartDmaRxTransfer(UARTChnDef* chn) {
  // Enable DMA RX Interrupt
  LL_USART_EnableDMAReq_RX(chn->port);
  LL_USART_EnableIT_IDLE(chn->port);

  // Enable DMA Channel Rx
  LL_DMA_EnableStream(chn->rx_dma.controller, chn->rx_dma.stream);

  DWriteString(0, "Enabled USART RX DMA\n");
}

void UartProcessRxDMAData(UARTChnDef* chn) {
  size_t pos;
  size_t len = 0;

  // Calculate current position in buffer
  pos = chn->rx_dma.size -
        LL_DMA_GetDataLength(chn->rx_dma.controller, chn->rx_dma.stream);
  // DPrintf(0, "DMA data length: %d\n",
  if (pos != chn->rx_dma.indexer) {
    /* Check change in received data */
    if (pos > chn->rx_dma.indexer) {
      /* Current position is over previous one */
      /* We are in "linear" mode */
      /* Process data directly by subtracting "pointers" */
      len = pos - chn->rx_dma.indexer;
      RingbufWrite(chn->rx_ring_buffer,
                   &(chn->rx_dma.address[chn->rx_dma.indexer]), len);
      //   total_rx_bytes += len;
    } else {
      /* We are in "overflow" mode */
      /* First process data to the end of buffer */
      len = chn->rx_dma.size - chn->rx_dma.indexer;
      RingbufWrite(chn->rx_ring_buffer,
                   &(chn->rx_dma.address[chn->rx_dma.indexer]), len);
      //   total_rx_bytes += len;
      /* Check and continue with beginning of buffer */
      if (pos > 0) {
        RingbufWrite(chn->rx_ring_buffer, &(chn->rx_dma.address[0]), pos);
        // total_rx_bytes += pos;
        len += pos;
      }
    }
  }
  // Save current position as old
  chn->rx_dma.indexer = pos;

  // Check and manually update if we reached end of buffer
  if (chn->rx_dma.indexer == chn->rx_dma.size) {
    chn->rx_dma.indexer = 0;
  }

  // DPrintf(0, "Total bytes received: %d, len: %d\n", total_rx_bytes,
  // len);
}

size_t UartRingBuffGetSize(UARTChnDef* chn) {
  return RingbufGetOccupiedSpaceSize(chn->rx_ring_buffer);
}

size_t UartRingBuffGetCapacity(UARTChnDef* chn) {
  return chn->rx_ring_buffer->size;
}

size_t UartRingBuffFetchByte(UARTChnDef* chn, uint8_t* data) {
  return RingbufRead(chn->rx_ring_buffer, data, 1);
}

size_t UartRingBuffFetchString(UARTChnDef* chn, uint8_t* data) {
  return RingbufRead(chn->rx_ring_buffer, data, chn->rxbuf_size);
}

void UARTHandleDMATransferError(UARTChnDef* chn) {
  /* Disable Tx Channel */
  LL_DMA_DisableStream(chn->tx_dma.controller, chn->tx_dma.stream);

  /* Disable Rx Channel */
  LL_DMA_DisableStream(chn->rx_dma.controller, chn->rx_dma.stream);
}

void HandleUartTxDMAIRQ(UARTChnDef* chn) {
  // DWriteString(0, ">>>>>> USART DMA Tx IRQ Entered <<<<<< \n");

  if (LL_DMA_IsEnabledIT_TC(chn->tx_dma.controller, chn->tx_dma.stream) &&
      DmaIsActiveFlagTC(chn->tx_dma)) {
    DmaClearFlagTC(chn->tx_dma);
    LL_DMA_DisableStream(chn->tx_dma.controller, chn->tx_dma.stream);
    // DWriteString(0, ">>>>>> USART DMA TX Complete <<<<<< \n");
  } else if (LL_DMA_IsEnabledIT_TE(chn->tx_dma.controller,
                                   chn->tx_dma.stream) &&
             DmaIsActiveFlagTE(chn->tx_dma)) {
    UARTHandleDMATransferError(chn);
    DWriteString(0, ">>>>>> USART DMA TX Error <<<<<< \n");
  }
}

void HandleUartRxDMAIRQ(UARTChnDef* chn) {
  // DWriteString(0, ">>>>>> USART6 DMA RX IRQ Entered <<<<<< \n");
#ifdef USE_FREERTOS
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
#endif

  /* Check half-transfer complete interrupt */
  if (LL_DMA_IsEnabledIT_HT(chn->rx_dma.controller, chn->rx_dma.stream) &&
      DmaIsActiveFlagHT(chn->rx_dma)) {
    DmaClearFlagHT(chn->rx_dma); /* Clear half-transfer complete flag */
#ifdef USE_FREERTOS
    // Notify arrival of new data
    xSemaphoreGiveFromISR(chn->rx_semaphore, &xHigherPriorityTaskWoken);
#else
    // TODO implement callback mechanism
    // UsartProcessRxDMAData();
#endif
    // DWriteString(0, "RX DMA HT IRQ\n");
  }

  /* Check transfer-complete interrupt */
  if (LL_DMA_IsEnabledIT_TC(chn->rx_dma.controller, chn->rx_dma.stream) &&
      DmaIsActiveFlagTC(chn->rx_dma)) {
    DmaClearFlagTC(chn->rx_dma); /* Clear transfer complete flag */
#ifdef USE_FREERTOS
    // Notify arrival of new data
    xSemaphoreGiveFromISR(chn->rx_semaphore, &xHigherPriorityTaskWoken);
#else
    // TODO implement callback mechanism
    // UsartProcessRxDMAData();
#endif
    // DWriteString(0, "RX DMA TC IRQ\n");
  }

#ifdef USE_FREERTOS
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#endif
}

void HandleUartRxTxIRQ(UARTChnDef* chn) {
  //   DWriteString(0, ">>>>>> USART Tx/Rx IRQ Entered <<<<<< \n");
#ifdef USE_FREERTOS
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
#endif

  /* Check for IDLE line interrupt */
  if (LL_USART_IsEnabledIT_IDLE(chn->port) &&
      LL_USART_IsActiveFlag_IDLE(chn->port)) {
    LL_USART_ClearFlag_IDLE(chn->port); /* Clear IDLE line flag */
#ifdef USE_FREERTOS
    // Notify arrival of new data
    xSemaphoreGiveFromISR(chn->rx_semaphore, &xHigherPriorityTaskWoken);
#else
    // TODO implement callback mechanism
    // UsartProcessRxDMAData();
#endif
    // DWriteString(0, "RX IDLE IRQ\n");
  }
#ifdef USE_FREERTOS
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#endif
}
