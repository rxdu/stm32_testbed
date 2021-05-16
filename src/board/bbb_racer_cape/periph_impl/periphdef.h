/*
 * periphdef.h
 *
 * Created on: May 04, 2020 00:12
 * Description:
 *
 * Copyright (c) 2020 Ruixiang Du (rdu)
 */

#ifndef PERIPHDEF_H
#define PERIPHDEF_H

/* standard definitions */
// LED
#define DO_LED_WARN 0
#define DO_LED_STATUS 1

// SBus
#define DO_SBUS_INV 3
#define UART_SBUS_CHN 0

// CAN
#define CAN_USER_CHN 0

// PWM
#define PWM_DRIVING_CHANNEL 0
#define PWM_STEERING_CHANNEL 1

/* board-specific definitions */
#define DO_LED_BLUE 2
#define DO_FREQ_TEST 5

// #define DO_SBUS_INV 2
// #define DO_GPIO_0 3
// #define DO_GPIO_1 4
// #define DO_GPIO_2 5
// #define DO_GPIO_3 6

// #define DI_EXTI_1 8
// #define DI_EXTI_2 1


#endif /* PERIPHDEF_H */
