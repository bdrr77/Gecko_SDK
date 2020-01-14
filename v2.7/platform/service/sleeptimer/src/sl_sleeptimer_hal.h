/***************************************************************************//**
 * @file
 * @brief SLEEPTIMER hardware abstraction layer definition.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SLEEPTIMER_HAL_H
#define SLEEPTIMER_HAL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "em_device.h"
#include "sl_sleeptimer_config.h"

#define SLEEPTIMER_EVENT_OF (0x01)
#define SLEEPTIMER_EVENT_COMP (0x02)

#if SL_SLEEPTIMER_PERIPHERAL == SL_SLEEPTIMER_PERIPHERAL_DEFAULT
#if defined(RTCC_PRESENT) && RTCC_COUNT >= 1
#undef SL_SLEEPTIMER_PERIPHERAL
#define SL_SLEEPTIMER_PERIPHERAL SL_SLEEPTIMER_PERIPHERAL_RTCC
#elif defined(RTC_PRESENT) && RTC_COUNT >= 1
#undef SL_SLEEPTIMER_PERIPHERAL
#define SL_SLEEPTIMER_PERIPHERAL SL_SLEEPTIMER_PERIPHERAL_RTC
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Hardware Abstraction Layer of the sleep timer init.
 ******************************************************************************/
void sleeptimer_hal_init_timer(void);

/*******************************************************************************
 * Hardware Abstraction Layer to get the current timer count.
 *
 * @return Value in ticks of the timer counter.
 ******************************************************************************/
uint32_t sleeptimer_hal_get_counter(void);

/*******************************************************************************
 * Hardware Abstraction Layer to get a timer comparator value.
 *
 * @return Value in ticks of the timer comparator.
 ******************************************************************************/
uint32_t sleeptimer_hal_get_compare(void);

/*******************************************************************************
 * Hardware Abstraction Layer to set a timer comparator value.
 *
 * @param value Number of ticks to set.
 ******************************************************************************/
void sleeptimer_hal_set_compare(uint32_t value);

/*******************************************************************************
 * Hardware Abstraction Layer to get the timer frequency.
 ******************************************************************************/
uint32_t sleeptimer_hal_get_timer_frequency(void);

/*******************************************************************************
 * Hardware Abstraction Layer to enable timer interrupts.
 *
 * @param local_flag Internal interrupt flag.
 ******************************************************************************/
void sleeptimer_hal_enable_int(uint8_t local_flag);

/*******************************************************************************
 * Hardware Abstraction Layer to disable timer interrupts.
 *
 * @param local_flag Internal interrupt flag.
 ******************************************************************************/
void sleeptimer_hal_disable_int(uint8_t local_flag);

/*******************************************************************************
 * Process the timer interrupt.
 *
 * @param flags Internal interrupt flag.
 ******************************************************************************/
void process_timer_irq(uint8_t local_flag);

#ifdef __cplusplus
}
#endif

#endif /* SLEEPTIMER_HAL_H */
