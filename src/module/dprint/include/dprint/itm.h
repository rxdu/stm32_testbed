/*
 * itm.h
 *
 * Created on: May 04, 2020 19:18
 * Description:
 *
 * Copyright (c) 2020 Ruixiang Du (rdu)
 */

#ifndef ITM_H
#define ITM_H

#include <stdint.h>

void InitITM(uint32_t stimulusport_en_bits, uint32_t cpu_core_freq_hz,
             uint32_t swo_freq_hz);
void ITMSendChar(char ch, uint8_t port_number);

#endif /* ITM_H */
