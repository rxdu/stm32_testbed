/*
 * dma.c
 *
 * Created on: Feb 29, 2020 23:49
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#include "mcal/dma.h"

#ifdef STM32F1
#include "stm32f1xx_ll_dma.h"
#elif defined(STM32F4)
#include "stm32f4xx_ll_dma.h"
#endif

uint32_t DmaIsActiveFlagTE(DMAChnDef chn) {
  uint32_t res;
  switch (chn.stream) {
    case LL_DMA_STREAM_0:
      res = LL_DMA_IsActiveFlag_TE0(chn.controller);
      break;
    case LL_DMA_STREAM_1:
      res = LL_DMA_IsActiveFlag_TE1(chn.controller);
      break;
    case LL_DMA_STREAM_2:
      res = LL_DMA_IsActiveFlag_TE2(chn.controller);
      break;
    case LL_DMA_STREAM_3:
      res = LL_DMA_IsActiveFlag_TE3(chn.controller);
      break;
    case LL_DMA_STREAM_4:
      res = LL_DMA_IsActiveFlag_TE4(chn.controller);
      break;
    case LL_DMA_STREAM_5:
      res = LL_DMA_IsActiveFlag_TE5(chn.controller);
      break;
    case LL_DMA_STREAM_6:
      res = LL_DMA_IsActiveFlag_TE6(chn.controller);
      break;
    case LL_DMA_STREAM_7:
      res = LL_DMA_IsActiveFlag_TE7(chn.controller);
      break;
    default:
      res = 0xff;
      break;
  }
  return res;
}

uint32_t DmaIsActiveFlagTC(DMAChnDef chn) {
  uint32_t res;
  switch (chn.stream) {
    case LL_DMA_STREAM_0:
      res = LL_DMA_IsActiveFlag_TC0(chn.controller);
      break;
    case LL_DMA_STREAM_1:
      res = LL_DMA_IsActiveFlag_TC1(chn.controller);
      break;
    case LL_DMA_STREAM_2:
      res = LL_DMA_IsActiveFlag_TC2(chn.controller);
      break;
    case LL_DMA_STREAM_3:
      res = LL_DMA_IsActiveFlag_TC3(chn.controller);
      break;
    case LL_DMA_STREAM_4:
      res = LL_DMA_IsActiveFlag_TC4(chn.controller);
      break;
    case LL_DMA_STREAM_5:
      res = LL_DMA_IsActiveFlag_TC5(chn.controller);
      break;
    case LL_DMA_STREAM_6:
      res = LL_DMA_IsActiveFlag_TC6(chn.controller);
      break;
    case LL_DMA_STREAM_7:
      res = LL_DMA_IsActiveFlag_TC7(chn.controller);
      break;
    default:
      res = 0xff;
      break;
  }
  return res;
}

void DmaClearFlagTC(DMAChnDef chn) {
  switch (chn.stream) {
    case LL_DMA_STREAM_0:
      LL_DMA_ClearFlag_TC0(chn.controller);
      break;
    case LL_DMA_STREAM_1:
      LL_DMA_ClearFlag_TC1(chn.controller);
      break;
    case LL_DMA_STREAM_2:
      LL_DMA_ClearFlag_TC2(chn.controller);
      break;
    case LL_DMA_STREAM_3:
      LL_DMA_ClearFlag_TC3(chn.controller);
      break;
    case LL_DMA_STREAM_4:
      LL_DMA_ClearFlag_TC4(chn.controller);
      break;
    case LL_DMA_STREAM_5:
      LL_DMA_ClearFlag_TC5(chn.controller);
      break;
    case LL_DMA_STREAM_6:
      LL_DMA_ClearFlag_TC6(chn.controller);
      break;
    case LL_DMA_STREAM_7:
      LL_DMA_ClearFlag_TC7(chn.controller);
      break;
    default:
      break;
  }
}

uint32_t DmaIsActiveFlagHT(DMAChnDef chn) {
  uint32_t res;
  switch (chn.stream) {
    case LL_DMA_STREAM_0:
      res = LL_DMA_IsActiveFlag_HT0(chn.controller);
      break;
    case LL_DMA_STREAM_1:
      res = LL_DMA_IsActiveFlag_HT1(chn.controller);
      break;
    case LL_DMA_STREAM_2:
      res = LL_DMA_IsActiveFlag_HT2(chn.controller);
      break;
    case LL_DMA_STREAM_3:
      res = LL_DMA_IsActiveFlag_HT3(chn.controller);
      break;
    case LL_DMA_STREAM_4:
      res = LL_DMA_IsActiveFlag_HT4(chn.controller);
      break;
    case LL_DMA_STREAM_5:
      res = LL_DMA_IsActiveFlag_HT5(chn.controller);
      break;
    case LL_DMA_STREAM_6:
      res = LL_DMA_IsActiveFlag_HT6(chn.controller);
      break;
    case LL_DMA_STREAM_7:
      res = LL_DMA_IsActiveFlag_HT7(chn.controller);
      break;
    default:
      res = 0xff;
      break;
  }
  return res;
}

void DmaClearFlagHT(DMAChnDef chn) {
  switch (chn.stream) {
    case LL_DMA_STREAM_0:
      LL_DMA_ClearFlag_HT0(chn.controller);
      break;
    case LL_DMA_STREAM_1:
      LL_DMA_ClearFlag_HT1(chn.controller);
      break;
    case LL_DMA_STREAM_2:
      LL_DMA_ClearFlag_HT2(chn.controller);
      break;
    case LL_DMA_STREAM_3:
      LL_DMA_ClearFlag_HT3(chn.controller);
      break;
    case LL_DMA_STREAM_4:
      LL_DMA_ClearFlag_HT4(chn.controller);
      break;
    case LL_DMA_STREAM_5:
      LL_DMA_ClearFlag_HT5(chn.controller);
      break;
    case LL_DMA_STREAM_6:
      LL_DMA_ClearFlag_HT6(chn.controller);
      break;
    case LL_DMA_STREAM_7:
      LL_DMA_ClearFlag_HT7(chn.controller);
      break;
    default:
      break;
  }
}