/*
 * dio.h
 *
 * Created on: Feb 05, 2020 10:17
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef DIO_H
#define DIO_H

#include "periph/periph.h"

#define DIO_LEVEL_LOW ((uint8_t)0x00)
#define DIO_LEVEL_HIGH ((uint8_t)0x01)

void SetDio(DioPinDef *digital_io);
void ResetDio(DioPinDef *digital_io);
void ToggleDio(DioPinDef *digital_io);

uint8_t GetDioPinLevel(DioPinDef *digital_io);

#endif /* DIO_H */
