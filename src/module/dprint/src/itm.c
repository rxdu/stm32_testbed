/*
 * itm.c
 *
 * Created on: Apr 08, 2020 13:16
 * Description:
 *
 * Reference:
 *  [1]
 * https://mcuoneclipse.com/2016/10/17/tutorial-using-single-wire-output-swo-with-arm-cortex-m-and-eclipse/
 *  [2] https://blog.japaric.io/itm/
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#include "dprint/itm.h"

#ifdef ARMCM7
#include "stm32f7xx.h"
#elif defined(ARMCM4)
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#elif defined(ARMCM3)
#include "stm32f1xx.h"
#endif

void InitITM(uint32_t stimulusport_en_bits, uint32_t cpu_core_freq_hz,
             uint32_t swo_freq_hz) {
  //   uint32_t SWOSpeed = 64000; /* default 64k baud rate */
  uint32_t swo_prescaler = (cpu_core_freq_hz / swo_freq_hz) - 1;

  /* setup TUIP register */
  // enable trace in core debug: 1 - SWO manchester, 2 - SWO NRZ
  CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk;
  // selected pin protoco
  *((volatile unsigned *)(ITM_BASE + 0x400F0)) = 0x00000002;
  // scale the baud rate of the asynchronous output
  *((volatile unsigned *)(ITM_BASE + 0x40010)) = swo_prescaler;
  // ITM Lock Access Register, C5ACCE55 enables more write access to Control
  // Register 0xE00 :: 0xFFC
  *((volatile unsigned *)(ITM_BASE + 0x00FB0)) = 0xC5ACCE55;

  /* setup ITM register */
  // ITM trace control register, RM0090 Rev18 P1700
  ITM->TCR = ITM_TCR_TraceBusID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_SYNCENA_Msk |
             ITM_TCR_ITMENA_Msk;
  // ITM trace privilege register
  ITM->TPR = ITM_TPR_PRIVMASK_Msk;
  // ITM stimulus ports
  ITM->TER = stimulusport_en_bits;

  // DWT_CTRL
  *((volatile unsigned *)(ITM_BASE + 0x01000)) = 0x400003FE;
  // formatter and flush control register
  *((volatile unsigned *)(ITM_BASE + 0x40304)) = 0x00000100;

  /* setup DBGMCU_CR register*/
  // reset and enable trace io
  DBGMCU->CR &= DBGMCU_CR_TRACE_MODE_Msk;
  DBGMCU->CR |= DBGMCU_CR_TRACE_IOEN;
}

void ITMSendChar(char ch, uint8_t port_number) {
  volatile int timeout;
  timeout = 5000;
  if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) &&
      ((ITM->TER & (1UL << port_number)) != 0UL)) {
    // wait until STIMx is ready, then send data
    while (ITM->PORT[port_number].u32 == 0) {
      if (--timeout == 0) return;
    }
    ITM->PORT[0].u16 = 0x08 | (ch << 8);
  }
}

int _putchar(int ch) { return ITM_SendChar(ch); }