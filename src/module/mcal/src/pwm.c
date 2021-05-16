/*
 * timer_stm32f4.c
 *
 * Created on: Aug 11, 2019 22:22
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#include "mcal/pwm.h"

#ifdef STM32F1
#include "stm32f1xx_ll_tim.h"
#elif defined(STM32F4)
#include "stm32f4xx_ll_tim.h"
#endif

bool SetupPwm(TimerChnDef* chn) {
  LL_TIM_CC_EnableChannel(chn->timer, chn->channel);
  LL_TIM_EnableAllOutputs(chn->timer);
  LL_TIM_EnableCounter(chn->timer);

  return true;
}

void PwmSetOutputDutyCycle(TimerChnDef* chn, float duty) {
  if (duty > 1.0) duty = 1.0;
  if (duty < 0) duty = 0;

  uint32_t pulse_duration = duty * (LL_TIM_GetAutoReload(chn->timer) + 1);

  switch (chn->channel) {
    case LL_TIM_CHANNEL_CH1:
      LL_TIM_OC_SetCompareCH1(chn->timer, pulse_duration);
      break;
    case LL_TIM_CHANNEL_CH2:
      LL_TIM_OC_SetCompareCH2(chn->timer, pulse_duration);
      break;
    case LL_TIM_CHANNEL_CH3:
      LL_TIM_OC_SetCompareCH3(chn->timer, pulse_duration);
      break;
    case LL_TIM_CHANNEL_CH4:
      LL_TIM_OC_SetCompareCH4(chn->timer, pulse_duration);
      break;
  }
}