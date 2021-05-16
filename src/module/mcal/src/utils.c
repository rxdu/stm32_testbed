/*
 * utils.c
 *
 * Created on: Feb 05, 2020 17:05
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#include "mcal/utils.h"

#ifdef STM32F1
#include "stm32f1xx_ll_utils.h"
#elif defined(STM32F4)
#include "stm32f4xx_ll_utils.h"
#endif

inline void DelayMs(uint32_t t) {
  // Note: LL_mDelay(t) will not work properly if SysTick is not initialized
  // (e.g. before the scheduler is started)
#ifdef USE_HAL_LIB
  HAL_Delay(t);
#else
#warning Warning: make sure DelayMs() is only called after SysTick is started
#endif
}