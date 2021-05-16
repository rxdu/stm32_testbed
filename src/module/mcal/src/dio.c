/*
 * dio.c
 *
 * Created on: Jan 13, 2020 16:56
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#include "mcal/dio.h"

#include "mcal/periph.h"
#include "dprint/dprint.h"

#ifdef STM32F1
#include "stm32f1xx_ll_gpio.h"
#elif defined(STM32F4)
#include "stm32f4xx_ll_gpio.h"
#endif

inline void DioSet(DIOPinDef* digital_io) {
  LL_GPIO_SetOutputPin(digital_io->port, digital_io->pin);
}

inline void DioReset(DIOPinDef* digital_io) {
  LL_GPIO_ResetOutputPin(digital_io->port, digital_io->pin);
}

inline void DioToggle(DIOPinDef* digital_io) {
  LL_GPIO_TogglePin(digital_io->port, digital_io->pin);
}

inline uint8_t DioGetPinLevel(DIOPinDef* digital_io) {
  uint8_t pin_state = LL_GPIO_IsInputPinSet(digital_io->port, digital_io->pin);

  if (pin_state)
    pin_state = DIO_LEVEL_HIGH;
  else
    pin_state = DIO_LEVEL_LOW;

  return pin_state;
}

inline void HandleExtiIRQ(DIOPinDef input[], uint8_t pin_index) {
  DIOPinDef* digital_io = &input[pin_index];
  if (digital_io->callback != NULL)
    digital_io->callback(pin_index, DioGetPinLevel(digital_io));
}