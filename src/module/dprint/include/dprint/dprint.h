/*
 * dprint.h
 *
 * Created on: Apr 08, 2020 12:43
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */

#ifndef DPRINT_H
#define DPRINT_H

#ifdef DBG_PRINT

#ifdef DBG_OUTPUT_ITM

#include "dprint/itm.h"
#include "printf/printf.h"

#define DPrintInit() InitITM(0x00000001, 168000000UL, 2000000UL)
#define DPrintf(chan, fmt, ...) printf(fmt, __VA_ARGS__)
#define DWriteString(chan, str) printf("%s", str)

#elif defined(DBG_OUTPUT_RTT)

#include "SEGGER_RTT.h"

#define DPrintInit()
#define DPrintf(chan, fmt, ...) SEGGER_RTT_printf(chan, fmt, __VA_ARGS__)
#define DWriteString(chan, str) SEGGER_RTT_WriteString(chan, str)
#endif

#else /* DBG_PRINT */

#define DPrintInit()
#define DPrintf(chan, fmt, ...)
#define DWriteString(chan, str)

#endif /* DBG_PRINT */

#endif /* DPRINT_H */
