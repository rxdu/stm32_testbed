/*
 * task_can.c
 *
 * Created on: May 21, 2021 22:12
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#include "common.h"

#include "periph/can.h"

#define CAN_RX_TIMEOUT 2000
#define CAN_TEST_MSG_ID_BASE 0x100

static uint8_t tx_buffer[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};

void TestbedCanTask(void* param) {
  TestItemList* list = (TestItemList*)param;
  (void)list;

  // initialize uart ports
  for (int i = 0; i < CAN_CHN_NUM; ++i) {
    if (can_cfg.channel[i].handler != NULL) {
      if (SetupCan(&can_cfg.channel[i]) == false)
        DPrintf(0, "[ERROR][CAN] Failed to setup %s\n",
                can_cfg.channel[i].name);
    }
  }

  const TickType_t task_delay = pdMS_TO_TICKS(5000);
  TickType_t last_waketime = xTaskGetTickCount();

  for (;;) {
    for (int i = 0; i < CAN_CHN_NUM; ++i) {
      if (can_cfg.channel[i].handler != NULL) {
        CanSendFrame(&can_cfg.channel[i], CAN_TEST_MSG_ID_BASE + i, true,
                     tx_buffer, sizeof(tx_buffer));

        // wait for echo
        if (xSemaphoreTake(can_cfg.channel[i].rx_semaphore, CAN_RX_TIMEOUT) ==
            pdPASS) {
          //   DPrintf(0, "[INFO][CAN] Frame received from %s\n",
          //           can_cfg.channel[i].name);
          //   for (int j = 0; j < 8; ++j) {
          //     DPrintf(0, "%x ", can_cfg.channel[i].rx_frame.data[j], 0);
          //   }
          //   DPrintf(0, "\n", 0);

          bool echo_matched = true;
          for (int j = 0; j < 8; ++j) {
            if ((can_cfg.channel[i].rx_frame.can_id !=
                 CAN_TEST_MSG_ID_BASE + i) ||
                (can_cfg.channel[i].rx_frame.data[j] != tx_buffer[j])) {
              echo_matched = false;
              break;
            }
          }
          if (echo_matched) {
            DPrintf(0, "[INFO][CAN] Echo received correctly from %s <------\n",
                    can_cfg.channel[i].name);
          } else {
            DPrintf(0, "[INFO][CAN] Echo received with mismatch (id or data) from %s\n",
                    can_cfg.channel[i].name);
          }
        } else {
          DPrintf(
              0,
              "[INFO][CAN] Echo not received within TIMEOUT (%d ms) from %s ?????? \n",
              CAN_RX_TIMEOUT, can_cfg.channel[i].name);
        }
      }
    }

    vTaskDelayUntil(&last_waketime, task_delay);
  }
}
