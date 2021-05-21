/*
 * can.h
 *
 * Created on: May 21, 2021 22:02
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#ifndef CAN_H
#define CAN_H

#include "periph/periph.h"

bool SetupCan(CanChnDef *chn);
void CanSendFrame(CanChnDef *chn, uint32_t id, bool is_std_id, uint8_t data[],
                  size_t len);

#endif /* CAN_H */
