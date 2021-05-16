/*
 * can.c
 *
 * Created on: Mar 02, 2020 16:36
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#include "mcal/can.h"

#include "dprint/dprint.h"

uint8_t SetupCan(CANChnDef *chn) {
  CAN_FilterTypeDef sFilterConfig;
  sFilterConfig.FilterBank = chn->rx_filter.filter_bank;
  sFilterConfig.FilterMode = chn->rx_filter.filter_mode;
  sFilterConfig.FilterScale = chn->rx_filter.filter_scale;
  sFilterConfig.FilterIdHigh = chn->rx_filter.filter_id_high;
  sFilterConfig.FilterIdLow = chn->rx_filter.filter_id_low;
  sFilterConfig.FilterMaskIdHigh = chn->rx_filter.filter_mask_id_high;
  sFilterConfig.FilterMaskIdLow = chn->rx_filter.filter_mask_id_low;
  sFilterConfig.FilterFIFOAssignment = chn->rx_filter.filter_fifo_assignment;
  sFilterConfig.FilterActivation = chn->rx_filter.filter_activation;
  sFilterConfig.SlaveStartFilterBank = chn->rx_filter.slave_start_filter_bank;

#ifdef USE_FREERTOS
  chn->rx_frame_buffer =
      xQueueCreate(chn->rx_frame_buffer_length, sizeof(struct StampedCanFrame));
  if (chn->rx_frame_buffer == NULL) {
    DPrintf(0, "FATAL: Failed to create rx_frame_buffer!\n", 0);
    return false;
  }
#endif

  if (HAL_CAN_ConfigFilter(chn->port, &sFilterConfig) != HAL_OK) {
    DWriteString(0, "Failed to configure filter for CAN\n");
    return false;
  }

  if (HAL_CAN_Start(chn->port) != HAL_OK) {
    DWriteString(0, "Failed to start CAN\n");
    return false;
  } else {
    DWriteString(0, "Initialized CAN\n");
  }

  if (HAL_CAN_ActivateNotification(chn->port, chn->active_its) != HAL_OK) {
    DWriteString(0, "Failed to start CAN RX_FIFO interrupt\n");
    return false;
  } else {
    DWriteString(0, "Enabled CAN notifications\n");
  }

  return true;
}

void ShortDelay() {
  for (int i = 0; i < 2500; ++i) {
  }
}

void CanSendFrame(CANChnDef *chn, uint32_t id, bool is_std_id, uint8_t data[],
                  size_t len) {
  uint32_t tx_mail_box;
  CAN_TxHeaderTypeDef tx_header;
  tx_header.RTR = CAN_RTR_DATA;
  if (is_std_id) {
    tx_header.IDE = CAN_ID_STD;
    tx_header.StdId = id;
  } else {
    tx_header.IDE = CAN_ID_EXT;
    tx_header.ExtId = id;
  }
  tx_header.DLC = len;
  tx_header.TransmitGlobalTime = DISABLE;

  if (HAL_CAN_AddTxMessage(chn->port, &tx_header, data, &tx_mail_box) !=
      HAL_OK) {
    DWriteString(0, "Failed to send CAN msg\n");
  }

  // wait until no message is currently pending
  while (HAL_CAN_IsTxMessagePending(chn->port, tx_mail_box)) {
  };
}

static inline void PushFrameToBuffer(CANChnDef *chn, uint32_t can_id,
                                     uint8_t *can_data, uint8_t can_dlc) {
#ifdef USE_FREERTOS
  struct StampedCanFrame rx_frame;
  rx_frame.can_frame.can_id = can_id;
  memcpy(rx_frame.can_frame.data, can_data, can_dlc);
  rx_frame.can_frame.can_dlc = can_dlc;
  rx_frame.time_stamp = xTaskGetTickCount();

  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  xQueueSendFromISR(chn->rx_frame_buffer, (void *)&rx_frame,
                    &xHigherPriorityTaskWoken);
  if (xHigherPriorityTaskWoken == pdTRUE)
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#endif
}

// Functions called in IRQ functions
void CanHandleRxIRQ(CANChnDef *chn) {
  struct can_frame can_frame_rx;
  CAN_RxHeaderTypeDef rx_header;
  HAL_CAN_GetRxMessage(chn->port, chn->rx_fifo, &rx_header, can_frame_rx.data);
  if (rx_header.IDE == CAN_ID_STD)
    can_frame_rx.can_id = rx_header.StdId;
  else
    can_frame_rx.can_id = rx_header.ExtId;
  can_frame_rx.can_dlc = rx_header.DLC;
  PushFrameToBuffer(chn, can_frame_rx.can_id, can_frame_rx.data,
                    can_frame_rx.can_dlc);

  // DPrintf(0, "CAN msg received: %x # ", rx_header.StdId);
  // for (int i = 0; i < rx_header.DLC; ++i)
  //   DPrintf(0, "%x ", can_frame_rx.data[i]);
  // DPrintf(0, "\n", 0);
  //   chn->rx_callback(&chn->rx_frame_buffer, can_frame_rx.can_id,
  //   can_frame_rx.data,
  //                    can_frame_rx.can_dlc);
  // #ifdef USE_FREERTOS
  //   BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  //   xQueueSendFromISR(chn->queue, (void *)&can_frame_rx,
  //                          &xHigherPriorityTaskWoken);
  //   if (xHigherPriorityTaskWoken == pdTRUE)
  //     portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  // #endif
}
