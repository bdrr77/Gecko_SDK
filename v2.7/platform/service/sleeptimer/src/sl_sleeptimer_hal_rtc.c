/***************************************************************************//**
 * @file
 * @brief SLEEPTIMER Hardware abstraction implementation for RTC.
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

#include "em_rtc.h"
#include "sl_sleeptimer.h"
#include "sl_sleeptimer_hal.h"
#include "em_core.h"
#include "em_cmu.h"

#if SL_SLEEPTIMER_PERIPHERAL == SL_SLEEPTIMER_PERIPHERAL_RTC

// Use RTC compare channel B.
#define SLEEPTIMER_RTC_COMP_SHIFT (2u)
#define SLEEPTIMER_RTC_COMP       (1 << SLEEPTIMER_RTC_COMP_SHIFT)

// Minimum difference between current count value and what the comparator of the timer can be set to.
// Almost always current count + 1. However, the RTC on legacy gecko (EFM32G) requires the comparator to be set to at least current cnt + 4.
#ifdef _EFM32_GECKO_FAMILY
#define SLEEPTIMER_COMPARE_MIN_DIFF  5
#else
#define SLEEPTIMER_COMPARE_MIN_DIFF  2
#endif

#define SLEEPTIMER_TMR_WIDTH (_RTC_CNT_MASK)
#define SLEEPTIMER_TMR_BIT_WIDTH 24u

__STATIC_INLINE uint32_t get_time_diff(uint32_t a,
                                       uint32_t b);

static volatile uint8_t rtc_overflow_count = 0;
static volatile uint32_t compare_value_32 = 0;
/******************************************************************************
 * Initializes RTC sleep timer.
 *****************************************************************************/
void sleeptimer_hal_init_timer()
{
  RTC_Init_TypeDef rtc_init;

  CMU_ClockDivSet(cmuClock_RTC, SL_SLEEPTIMER_FREQ_DIVIDER);
  CMU_ClockEnable(cmuClock_RTC, true);

  // Initialize RTC.
  rtc_init.comp0Top = false;
  rtc_init.debugRun = false;
  rtc_init.enable = true;
  RTC_Init(&rtc_init);
  RTC_IntDisable(_RTC_IEN_MASK);
  RTC_IntClear(_RTC_IFC_MASK);
#if !defined(_EFM32_GECKO_FAMILY)
  RTC_CounterSet(0u);
#endif

  // Setup RTC interrupt
  NVIC_ClearPendingIRQ(RTC_IRQn);
  NVIC_EnableIRQ(RTC_IRQn);
}

/******************************************************************************
 * Gets RTC counter.
 *****************************************************************************/
uint32_t sleeptimer_hal_get_counter(void)
{
  return RTC_CounterGet() | ((uint32_t)rtc_overflow_count << SLEEPTIMER_TMR_BIT_WIDTH);
}

/******************************************************************************
 * Gets RTC compare value
 *****************************************************************************/
uint32_t sleeptimer_hal_get_compare(void)
{
  return compare_value_32;
}

/******************************************************************************
 * Sets RTC compare value
 *****************************************************************************/
void sleeptimer_hal_set_compare(uint32_t value)
{
  uint32_t counter = sleeptimer_hal_get_counter();
  uint32_t compare_value = value;
  if (((RTC_IntGet() & SLEEPTIMER_RTC_COMP) != 0)
      || get_time_diff(compare_value_32, counter) > SLEEPTIMER_COMPARE_MIN_DIFF
      || compare_value_32 == counter) {
    // Add margin if necessary
    if (get_time_diff(compare_value, counter) < SLEEPTIMER_COMPARE_MIN_DIFF) {
      compare_value = counter + SLEEPTIMER_COMPARE_MIN_DIFF;
    }

    compare_value_32 = compare_value;
    if (compare_value_32 - counter <= SLEEPTIMER_TMR_WIDTH) {
      RTC_CompareSet(1, compare_value_32 % (SLEEPTIMER_TMR_WIDTH + 1));
      sleeptimer_hal_enable_int(SLEEPTIMER_EVENT_COMP);
    } else {
      sleeptimer_hal_disable_int(SLEEPTIMER_EVENT_COMP);
    }
  }
}

/******************************************************************************
 * Enables RTC interrupts.
 *****************************************************************************/
void sleeptimer_hal_enable_int(uint8_t local_flag)
{
  uint32_t rtc_ien = 0u;

  if (local_flag & SLEEPTIMER_EVENT_OF) {
    rtc_ien |= RTC_IEN_OF;
  }

  if (local_flag & SLEEPTIMER_EVENT_COMP) {
    rtc_ien |= SLEEPTIMER_RTC_COMP;
  }

  RTC_IntEnable(rtc_ien);
}

/******************************************************************************
 * Disables RTC interrupts.
 *****************************************************************************/
void sleeptimer_hal_disable_int(uint8_t local_flag)
{
  uint32_t rtc_int_clr = 0u;

  if (local_flag & SLEEPTIMER_EVENT_OF) {
    rtc_int_clr |= RTC_IEN_OF;
  }

  if (local_flag & SLEEPTIMER_EVENT_COMP) {
    rtc_int_clr |= SLEEPTIMER_RTC_COMP;
  }

  RTC_IntDisable(rtc_int_clr);
}

/*******************************************************************************
 * Gets RTC timer frequency.
 ******************************************************************************/
uint32_t sleeptimer_hal_get_timer_frequency(void)
{
  return CMU_ClockFreqGet(cmuClock_RTC);
}

/*******************************************************************************
 * RTC interrupt handler.
 ******************************************************************************/
void RTC_IRQHandler(void)
{
  CORE_DECLARE_IRQ_STATE;
  uint8_t local_flag = 0;
  uint32_t irq_flag;
  uint32_t compare_value_24 = 0;

  CORE_ENTER_ATOMIC();
  irq_flag = RTC_IntGet();

  if (irq_flag & RTC_IF_OF) {
    if (((rtc_overflow_count << SLEEPTIMER_TMR_BIT_WIDTH) + SLEEPTIMER_TMR_WIDTH) == UINT32_MAX) {
      local_flag |= SLEEPTIMER_EVENT_OF;
    }
    rtc_overflow_count++;
    compare_value_24 = compare_value_32;
    compare_value_24 -= (rtc_overflow_count << SLEEPTIMER_TMR_BIT_WIDTH);
    if (compare_value_24 <= SLEEPTIMER_TMR_WIDTH) {
      RTC_CompareSet(1, compare_value_24);
      sleeptimer_hal_enable_int(SLEEPTIMER_EVENT_COMP);
    }
  }
  if (irq_flag & SLEEPTIMER_RTC_COMP) {
    local_flag |= SLEEPTIMER_EVENT_COMP;
  }
  RTC_IntClear(irq_flag & (RTC_IFC_OF | SLEEPTIMER_RTC_COMP));

  if (local_flag != 0) {
    process_timer_irq(local_flag);
  }
  CORE_EXIT_ATOMIC();
}

/*******************************************************************************
 * Computes difference between two times taking into account timer wrap-around.
 *
 * @param a Time.
 * @param b Time to substract from a.
 *
 * @return Time difference.
 ******************************************************************************/
__STATIC_INLINE uint32_t get_time_diff(uint32_t a,
                                       uint32_t b)
{
  return (a - b);
}

#endif
