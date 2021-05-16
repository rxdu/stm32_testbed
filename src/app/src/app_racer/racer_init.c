/*
 * racer_init.c
 *
 * Created on: Dec 28, 2020 21:09
 * Description:
 *
 * Copyright (c) 2020 Ruixiang Du (rdu)
 */

#include "app/init.h"
#include "dprint/dprint.h"
#include "racer/racer.h"

uint16_t InitApp() {
  DWriteString(0, "\n\n##################################################\n\n");
  DWriteString(0, "<------------------- Hardware Init -------------------->\n");

  // setup hardware interfaces
  if (InitHardware() != RACER_INIT_NO_ERROR) {
    DWriteString(0, "Failed to initialize hardware!\n");
    EnterPanicLoop();
  }
  DWriteString(0, "Hardware initialized\n");

  DWriteString(0, "<-------------------- Setup Tasks --------------------->\n");

  // setup RTOS tasks
  if (InitRTOSTasks() != RACER_INIT_NO_ERROR) {
    DWriteString(0, "Failed to initialize RTOS tasks!\n");
    EnterPanicLoop();
  }
  DWriteString(0, "RTOS tasks initialized\n");

  DWriteString(0, "<------------------------------------------------------>\n");

#ifdef ENABLE_SYSTEMVIEW
  SEGGER_SYSVIEW_Start();
  DWriteString(0, "SystemView started\n");
  DWriteString(0, "<------------------------------------------------------>\n");
#endif

  return RACER_INIT_NO_ERROR;
}