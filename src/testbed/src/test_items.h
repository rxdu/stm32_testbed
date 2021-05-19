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

typedef struct {
  uint8_t dio_input_num;
  uint8_t dio_output_num;
  uint8_t led_num;
} TestItemList;

void InitTestItems(TestItemList* list);

void TestDio(TestItemList* list, uint32_t freq_div);
void TestLed(TestItemList* list, uint32_t freq_div);

#endif /* TEST_ITEMS_H */
