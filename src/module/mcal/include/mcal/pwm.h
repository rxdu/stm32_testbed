/*
 * pwm.h
 *
 * Created on: Feb 29, 2020 23:24
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef PWM_H
#define PWM_H

#include <stdbool.h>
#include <stdint.h>

#include "mcal/periph.h"

bool SetupPwm(TimerChnDef* chn);
void PwmSetOutputDutyCycle(TimerChnDef* chn, float duty);

#endif /* PWM_H */
