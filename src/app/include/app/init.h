/*
 * init.h
 *
 * Created on: Dec 01, 2020 14:29
 * Description:
 *  a typical use case is to call InitApp() in either
 *  - main()
 *  - MX_FREERTOS_Init()
 *
 * Copyright (c) 2020 Ruixiang Du (rdu)
 */

#ifndef APP_INIT_H
#define APP_INIT_H

#include "stdint.h"

uint16_t InitApp();

#endif /* APP_INIT_H */
