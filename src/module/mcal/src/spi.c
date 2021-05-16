/*
 * spi.c
 *
 * Created on: Feb 05, 2020 15:31
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#include "mcal/spi.h"

#ifdef STM32F1
#include "stm32f1xx_ll_spi.h"
#elif defined(STM32F4)
#include "stm32f4xx_ll_spi.h"
#endif

#include "mcal/dio.h"

uint8_t SetupSpi(SPIChnDef* chn) {
  LL_SPI_Enable(chn->port);
  return LL_SPI_IsEnabled(chn->port);
}

void SetSpiMode(SPIChnDef* chn, SPIMode mode) {
  if (mode == SPI_MASTER)
    LL_SPI_SetMode(chn->port, LL_SPI_MODE_MASTER);
  else if (mode == SPI_SLAVE)
    LL_SPI_SetMode(chn->port, LL_SPI_MODE_SLAVE);
}

uint8_t SpiReadWriteByte(SPIChnDef* chn, uint8_t TxData) {
  while (LL_SPI_IsActiveFlag_TXE(chn->port) == 0) {
  };
  LL_SPI_TransmitData8(chn->port, TxData);
  while (LL_SPI_IsActiveFlag_RXNE(chn->port) == 0) {
  };
  return LL_SPI_ReceiveData8(chn->port);
}