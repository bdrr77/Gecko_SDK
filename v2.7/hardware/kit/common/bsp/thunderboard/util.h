/***************************************************************************//**
 * @file
 * @brief Utility Functions for the Thunderboard Sense
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************//**
* @addtogroup TBSense_BSP
* @{
******************************************************************************/

/***************************************************************************//**
 * @addtogroup Util
 * @{
 ******************************************************************************/

#define UTIL_SUPPLY_TYPE_UNKNOWN    0 /**< Unknown power supply type                */
#define UTIL_SUPPLY_TYPE_USB        1 /**< The board powered from the USB connector */
#define UTIL_SUPPLY_TYPE_AA         2 /**< The board powered from AA batteries      */
#define UTIL_SUPPLY_TYPE_AAA        3 /**< The board powered from AAA batteries     */
#define UTIL_SUPPLY_TYPE_CR2032     4 /**< The board powered from a CR2032 battery  */

uint32_t UTIL_init        (void);
void     UTIL_delay       (uint32_t ms);
void     UTIL_shutdown    (void);

uint32_t UTIL_sleepInit   (void);
void     UTIL_sleep       (uint32_t ms);
uint32_t UTIL_waitForEvent(uint32_t timeout);

void     UTIL_supplyProbe                (void);
void     UTIL_supplyGetCharacteristics   (uint8_t *type, float *voltage, float *ir);
uint8_t  UTIL_supplyGetType              (void);
bool     UTIL_isLowPower                 (void);

/** @} */
/** @} */

#endif // UTIL_H
