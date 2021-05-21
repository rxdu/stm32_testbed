/*
 * test_items.h
 *
 * Created on: May 16, 2021 23:07
 * Description:
 *
 * Copyright (c) 2021 Ruixiang Du (rdu)
 */

#ifndef TEST_ITEMS_H
#define TEST_ITEMS_H

#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"

#include "dprint/dprint.h"

// init
typedef struct {
  uint8_t dio_input_num;
  uint8_t dio_output_num;
  bool enable_dio_test;
  uint8_t led_num;
  bool enable_led_test;
  uint8_t uart_num;
  bool enable_uart_test;
  uint8_t can_num;
  bool enable_can_test;
} TestItemList;

void InitTestItems(TestItemList* list);

// tasks
void TestbedDioTask(void* param);
void TestbedUartTask(void* param);
void TestbedCanTask(void* param);

#endif /* TEST_ITEMS_H */
