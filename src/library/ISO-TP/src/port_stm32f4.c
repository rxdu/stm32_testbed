/*
 * isotp_stm32f4.c
 *
 * Created on: Jan 01, 2021 23:24
 * Description:
 *
 * Copyright (c) 2020 Ruixiang Du (rdu)
 */

#include "isotp/isotp_user.h"

#include "FreeRTOS.h"
#include "task.h"

#include "mcal/mcal.h"
#include "dprint/dprint.h"

/* user implemented, print debug message */
void isotp_user_debug(const char* message, ...) {
  DPrintf(0, "isotp: %s", message);
}

/* user implemented, send can message */
int isotp_user_send_can(const uint32_t arbitration_id, const uint8_t* data,
                        const uint8_t size) {
  CanSendFrame(&can.channel[CAN_USER_CHN], arbitration_id, true, (uint8_t*)data,
               size);
  return ISOTP_RET_OK;
}

/* user implemented, get millisecond */
uint32_t isotp_user_get_ms(void) { return xTaskGetTickCount(); }