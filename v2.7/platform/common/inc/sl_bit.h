/***************************************************************************//**
 * @file
 * @brief Implementation of bit operations.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BIT_H
#define SL_BIT_H

/***************************************************************************//**
 * @addtogroup platform_common
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup BIT
 * @{
 ******************************************************************************/

/****************************************************************************************************//**
 *                                               SL_SET_BIT()
 *
 * @brief    Set specified bit(s) in a value.
 *
 * @param    val     Value to modify by setting specified bit(s).
 *
 * @param    mask    Mask of bits to set.
 *
 * @return   Modified value with specified bit(s) set.
 *
 * @note     'val' & 'mask' SHOULD be unsigned integers.
 *******************************************************************************************************/

#define SL_SET_BIT(val, mask)                      ((val) = ((val) | (mask)))

/****************************************************************************************************//**
 *                                               SL_CLEAR_BIT()
 *
 * @brief    Clear specified bit(s) in a value.
 *
 * @param    val     Value to modify by clearing specified bit(s).
 *
 * @param    mask    Mask of bits to clear.
 *
 * @return   Modified value with specified bit(s) clear.
 *
 * @note     'val' & 'mask' SHOULD be unsigned integers.
 *
 * @note     'mask' SHOULD be cast with the same data type than 'val'.
 *******************************************************************************************************/

#define SL_CLEAR_BIT(val, mask)  ((val) = ((val) & (~(mask))))

/****************************************************************************************************//**
 *                                               SL_IS_BIT_SET()
 *
 * @brief    Determine if specified bit(s) in a value are set.
 *
 * @param    val     Value to check for specified bit(s) set.
 *
 * @param    mask    Mask of bits to check if set.
 *
 * @return   true, if ALL specified bit(s) are     set in value.
 *
 *           false, if ALL specified bit(s) are NOT set in value.
 *
 * @note     'val' & 'mask' SHOULD be unsigned integers.
 *
 * @note     NULL 'mask' allowed; returns 'false' since NO mask bits specified.
 *******************************************************************************************************/

#define SL_IS_BIT_SET(val, mask)  (((((val) & (mask)) == (mask)) && ((mask) != 0u)) ? (true) : (false))

/****************************************************************************************************//**
 *                                               SL_IS_BIT_CLEAR()
 *
 * @brief    Determine if specified bit(s) in a value are clear.
 *
 * @param    val     Value to check for specified bit(s) clear.
 *
 * @param    mask    Mask of bits to check if clear.
 *
 * @return   true, if ALL specified bit(s) are     clear in value.
 *
 *           false, if ALL specified bit(s) are NOT clear in value.
 *
 * @note     val' & 'mask' SHOULD be unsigned integers.
 *
 * @note     NULL 'mask' allowed; returns 'false' since NO mask bits specified.
 *******************************************************************************************************/
#define SL_IS_BIT_CLEAR(val, mask)  (((((val) & (mask)) == 0u) && ((mask) != 0u)) ? (true) : (false))

/****************************************************************************************************//**
 *                                           SL_IS_ANY_BIT_SET()
 *
 * @brief    Determine if any specified bit(s) in a value are set.
 *
 * @param    val     Value to check for specified bit(s) set.
 *
 * @param    mask    Mask of bits to check if set (see Note #2).
 *
 * @return   true, if ANY specified bit(s) are     set in value.
 *
 *           false, if ALL specified bit(s) are NOT set in value.
 *
 * @note     'val' & 'mask' SHOULD be unsigned integers.
 *
 * @note     NULL 'mask' allowed; returns 'false' since NO mask bits specified.
 *******************************************************************************************************/

#define  SL_IS_ANY_BIT_SET(val, mask)  ((((val) & (mask)) == 0u) ? (false) : (true))

/****************************************************************************************************//**
 *                                           SL_IS_ANY_BIT_CLEAR()
 *
 * @brief    Determine if any specified bit(s) in a value are clear.
 *
 * @param    val     Value to check for specified bit(s) clear.
 *
 * @param    mask    Mask of bits to check if clear (see Note #2).
 *
 * @return   true, if ANY specified bit(s) are     clear in value.
 *
 *           false,  if ALL specified bit(s) are NOT clear in value.
 *
 * @note     'val' & 'mask' SHOULD be unsigned integers.
 *
 * @note     NULL 'mask' allowed; returns 'false' since NO mask bits specified.
 *******************************************************************************************************/

#define  SL_IS_ANY_BIT_CLEAR(val, mask)  ((((val) & (mask)) == (mask))  ? (false) : (true))

/*******************************************************************************
 ******************************   DEFINES   ************************************
 ******************************************************************************/

/** @} (end addtogroup BIT) */
/** @} (end addtogroup platform_common) */

#endif /* SL_BIT_H */
