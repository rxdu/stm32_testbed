/*
 * can.h
 *
 * Created on: Mar 02, 2020 16:17
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef CAN_H
#define CAN_H

#include <stdbool.h>
#include <stdint.h>

#include "mcal/periph.h"

struct can_frame {
  uint32_t can_id;
  uint8_t can_dlc;
  uint8_t __pad;  /* padding */
  uint8_t __res0; /* reserved / padding */
  uint8_t __res1; /* reserved / padding */
  uint8_t data[8] __attribute__((aligned(8)));
};

struct StampedCanFrame{
  struct can_frame can_frame;
  uint32_t time_stamp;
};

uint8_t SetupCan(CANChnDef *chn);

void CanSendFrame(CANChnDef *chn, uint32_t id, bool is_std_id, uint8_t data[],
                  size_t len);

// Functions called in IRQ functions
void CanHandleRxIRQ(CANChnDef *chn);

#endif /* CAN_H */
