/*
 * can.c
 *
 * Created on: May 21, 2021 22:02
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include "periph/can.h"

#include "dprint/dprint.h"

bool SetupCan(CanChnDef *chn) {
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

  chn->rx_semaphore = xSemaphoreCreateBinary();
  if (chn->rx_semaphore == NULL)
    DPrintf(0, "[ERROR][UART] Failed to create semaphore for %s\n", chn->name);

  if (HAL_CAN_ConfigFilter(chn->handler, &sFilterConfig) != HAL_OK) {
    DPrintf(0, "[ERROR][CAN] Failed to configure filter for %s\n", chn->name);
    return false;
  }

  if (HAL_CAN_Start(chn->handler) != HAL_OK) {
    DPrintf(0, "[ERROR][CAN] Failed to start %s\n", chn->name);
    return false;
  } else {
    DPrintf(0, "[INFO][CAN] Initialized %s\n", chn->name);
  }

  if (HAL_CAN_ActivateNotification(chn->handler, chn->active_its) != HAL_OK) {
    DPrintf(0, "[ERROR][CAN] Failed to start CAN RX_FIFO interrupt for %s\n",
            chn->name);

    return false;
  } else {
    DPrintf(0, "[INFO][CAN] Enabled CAN notifications for %s\n", chn->name);
  }

  return true;
}

void CanSendFrame(CanChnDef *chn, uint32_t id, bool is_std_id, uint8_t data[],
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

  if (HAL_CAN_AddTxMessage(chn->handler, &tx_header, data, &tx_mail_box) !=
      HAL_OK) {
    DPrintf(0, "[ERROR][CAN] Failed to send frame from %s\n", chn->name);
  }

  // wait until no message is currently pending
  while (HAL_CAN_IsTxMessagePending(chn->handler, tx_mail_box)) {
  };

  DPrintf(0, "[INFO][CAN] Frame sent from %s \n", chn->name);
}

void CanRxCpltCallback(CAN_HandleTypeDef *hcan) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  for (int i = 0; i < CAN_CHN_NUM; ++i) {
    if (can_cfg.channel[i].handler == hcan) {
      CAN_RxHeaderTypeDef rx_header;
      HAL_CAN_GetRxMessage(can_cfg.channel[i].handler,
                           can_cfg.channel[i].rx_fifo, &rx_header,
                           can_cfg.channel[i].rx_frame.data);
      if (rx_header.IDE == CAN_ID_STD)
        can_cfg.channel[i].rx_frame.can_id = rx_header.StdId;
      else
        can_cfg.channel[i].rx_frame.can_id = rx_header.ExtId;
      can_cfg.channel[i].rx_frame.can_dlc = rx_header.DLC;

      xSemaphoreGiveFromISR(can_cfg.channel[i].rx_semaphore,
                            &xHigherPriorityTaskWoken);
    }
  }
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  CanRxCpltCallback(hcan);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  CanRxCpltCallback(hcan);
}
