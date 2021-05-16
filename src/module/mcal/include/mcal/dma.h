/*
 * dma.h
 *
 * Created on: Feb 29, 2020 23:49
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef DMA_H
#define DMA_H

#include <stdint.h>

#include "mcal/periph.h"

uint32_t DmaIsActiveFlagTE(DMAChnDef chn);

uint32_t DmaIsActiveFlagTC(DMAChnDef chn);
void DmaClearFlagTC(DMAChnDef chn);

uint32_t DmaIsActiveFlagHT(DMAChnDef chn);
void DmaClearFlagHT(DMAChnDef chn);

#endif /* DMA_H */
