/*
 * dio.c
 *
 * Created on: Jan 13, 2020 16:56
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#include "periph/dio.h"

#include "dprint/dprint.h"

#define PRINT_EXTI_SOURCE(pin) \
  { DPrintf(0, "[INFO][DIO] EXTI callback triggered: %s \n", #pin); }

#ifdef STM32F1
#include "stm32f1xx_hal_gpio.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal_gpio.h"
#endif

inline void SetDio(DioPinDef* digital_io) {
  assert(digital_io != NULL);
  HAL_GPIO_WritePin(digital_io->port, digital_io->pin, GPIO_PIN_SET);
}

inline void ResetDio(DioPinDef* digital_io) {
  assert(digital_io != NULL);
  HAL_GPIO_WritePin(digital_io->port, digital_io->pin, GPIO_PIN_RESET);
}

inline void ToggleDio(DioPinDef* digital_io) {
  assert(digital_io != NULL);
  HAL_GPIO_TogglePin(digital_io->port, digital_io->pin);
}

inline uint8_t GetDioPinLevel(DioPinDef* digital_io) {
  assert(digital_io != NULL);
  GPIO_PinState pin_state = HAL_GPIO_ReadPin(digital_io->port, digital_io->pin);

  if (pin_state == GPIO_PIN_SET)
    pin_state = DIO_LEVEL_HIGH;
  else
    pin_state = DIO_LEVEL_LOW;

  return pin_state;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  switch (GPIO_Pin) {
    case GPIO_PIN_0:
      PRINT_EXTI_SOURCE(GPIO_PIN_0);
      break;
    case GPIO_PIN_1:
      PRINT_EXTI_SOURCE(GPIO_PIN_1);
      break;
    case GPIO_PIN_2:
      PRINT_EXTI_SOURCE(GPIO_PIN_2);
      break;
    case GPIO_PIN_3:
      PRINT_EXTI_SOURCE(GPIO_PIN_3);
      break;
    case GPIO_PIN_4:
      PRINT_EXTI_SOURCE(GPIO_PIN_4);
      break;
    case GPIO_PIN_5:
      PRINT_EXTI_SOURCE(GPIO_PIN_5);
      break;
    case GPIO_PIN_6:
      PRINT_EXTI_SOURCE(GPIO_PIN_6);
      break;
    case GPIO_PIN_7:
      PRINT_EXTI_SOURCE(GPIO_PIN_7);
      break;
    case GPIO_PIN_8:
      PRINT_EXTI_SOURCE(GPIO_PIN_8);
      break;
    case GPIO_PIN_9:
      PRINT_EXTI_SOURCE(GPIO_PIN_9);
      break;
    case GPIO_PIN_10:
      PRINT_EXTI_SOURCE(GPIO_PIN_10);
      break;
    case GPIO_PIN_11:
      PRINT_EXTI_SOURCE(GPIO_PIN_11);
      break;
    case GPIO_PIN_12:
      PRINT_EXTI_SOURCE(GPIO_PIN_12);
      break;
    case GPIO_PIN_13:
      PRINT_EXTI_SOURCE(GPIO_PIN_13);
      break;
    case GPIO_PIN_14:
      PRINT_EXTI_SOURCE(GPIO_PIN_14);
      break;
    case GPIO_PIN_15:
      PRINT_EXTI_SOURCE(GPIO_PIN_15);
      break;
    default:
      DPrintf(0, "[ERROR][DIO] EXTI callback triggered: Unknonwn\n", 0);
      break;
  }
}