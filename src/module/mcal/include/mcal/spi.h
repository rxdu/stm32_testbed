/*
 * spi.h
 *
 * Created on: Feb 05, 2020 15:12
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include "mcal/periph.h"

typedef enum { SPI_MASTER, SPI_SLAVE } SPIMode;

uint8_t SetupSpi(SPIChnDef* chn);
void SetSpiMode(SPIChnDef* chn, SPIMode mode);

uint8_t SpiReadWriteByte(SPIChnDef* chn, uint8_t TxData);

#endif /* SPI_H */
