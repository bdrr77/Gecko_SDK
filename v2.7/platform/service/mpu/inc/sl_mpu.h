/***************************************************************************//**
 * @file sl_mpu.h
 * @brief MPU API definition.
 * @version 1.0.0
 *******************************************************************************
 * # License
 * <b>(C) Copyright 2018 Silicon Labs, www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup platform_service
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup sl_mpu MPU
 * @{
 * @brief MPU basic utilities.
 ******************************************************************************/

#ifndef MPU_H
#define MPU_H

#if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)

/***************************************************************************//**
 * Configures internal SRAM as non-executable and enable MPU.
 *
 * @note This function configures the MPU in order to make the entire RAM as
 *       non-executable (with the exception of the functions marked as ramfunc).
 ******************************************************************************/
void sl_mpu_disable_execute_from_ram(void);

/***************************************************************************//**
 * Configures an address range as non-executable and enable MPU.
 *
 * @note This function configures the MPU in order to make an address range as
 *       non-executable. The size of the memory region must be at lease 32 bytes
 *       or bigger.
 *
 * @param address_begin Beginning of memory segment.
 *
 * @param address_end   End of memory segment.
 *
 * @param size          Size of memory segment.
 ******************************************************************************/
void sl_mpu_disable_execute(uint32_t address_begin,
                            uint32_t address_end,
                            uint32_t size);

/** @} (end addtogroup sl_mpu) */
/** @} (end addtogroup platform_service) */

#ifdef __cplusplus
}
#endif

#endif /* defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U) */
#endif /* MPU_H */
