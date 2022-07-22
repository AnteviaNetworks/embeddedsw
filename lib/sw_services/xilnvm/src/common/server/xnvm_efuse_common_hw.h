/******************************************************************************
* Copyright (c) 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/******************************************************************************/
/**
*
* @file xnvm_efuse_common_hw.h
*
* This file contains eFUSE controller register definitions which are common
* for Versal and Versal_Net
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- ---------- --------------------------------------------------------
* 1.0   kal  07/16/2022 Initial release
*
* </pre>
*
* @note
*
*******************************************************************************/
#ifndef XNVM_EFUSE_COMMON_HW_H
#define XNVM_EFUSE_COMMON_HW_H

#ifdef __cplusplus
extern "C" {
#endif

/****************************** Include Files *********************************/
#include "xparameters.h"

/*************************** Constant Definitions *****************************/
/**
 * @name CRP base address definition
 */
/**< CRP Base Address */
#define XNVM_CRP_BASE_ADDR				(0xF1260000U)
/** @} */

/**
 * @name CRP eFUSE Clock Control Register
 */
/**< CRP REF_CLK offset and definition */
#define XNVM_CRP_EFUSE_REF_CLK_REG_OFFSET		(0x00000134U)
#define XNVM_CRP_EFUSE_REF_CLK_SELSRC_SHIFT		(2U)
#define XNVM_CRP_EFUSE_REF_CLK_IN			((u32)0x01U << \
					XNVM_CRP_EFUSE_REF_CLK_SELSRC_SHIFT)
#define XNVM_CRP_EFUSE_REF_CLK_SELSRC		(XNVM_CRP_EFUSE_REF_CLK_IN)
/** @} */

/**
 * @name eFUSE Controller base address
 */
/**< eFUSE Control Base Address */
#define XNVM_EFUSE_CTRL_BASEADDR			(0xF1240000U)
/** @} */

/**
 * @name eFUSE Controller Register Offsets
 */
/**< eFUSE CTRL Register Offsets */
#define XNVM_EFUSE_WR_LOCK_REG_OFFSET			(0x00000000U)
#define XNVM_EFUSE_CFG_REG_OFFSET			(0x00000004U)
#define XNVM_EFUSE_STATUS_REG_OFFSET			(0x00000008U)
#define XNVM_EFUSE_PGM_ADDR_REG_OFFSET			(0x0000000CU)
#define XNVM_EFUSE_RD_ADDR_REG_OFFSET			(0x00000010U)
#define XNVM_EFUSE_RD_DATA_REG_OFFSET			(0x00000014U)
#define XNVM_EFUSE_TPGM_REG_OFFSET			(0x00000018U)
#define XNVM_EFUSE_TRD_REG_OFFSET			(0x0000001CU)
#define XNVM_EFUSE_TSU_H_PS_REG_OFFSET			(0x00000020U)
#define XNVM_EFUSE_TSU_H_PS_CS_REG_OFFSET		(0x00000024U)
#define XNVM_EFUSE_TRDM_REG_OFFSET			(0x00000028U)
#define XNVM_EFUSE_TSU_H_CS_REG_OFFSET			(0x0000002CU)
#define XNVM_EFUSE_ISR_REG_OFFSET			(0x00000030U)
#define XNVM_EFUSE_CACHE_LOAD_REG_OFFSET		(0x00000040U)
#define XNVM_EFUSE_AES_CRC_REG_OFFSET			(0x00000048U)
#define XNVM_EFUSE_AES_USR_KEY0_CRC_REG_OFFSET		(0x0000004CU)
#define XNVM_EFUSE_AES_USR_KEY1_CRC_REG_OFFSET		(0x00000050U)
#define XNVM_EFUSE_PD_REG_OFFSET			(0x00000054U)
#define XNVM_EFUSE_TEST_CTRL_REG_OFFSET			(0x00000100U)
/** @} */

/**
 * @name Register: EFUSE_CTRL_CFG
 */
/**< eFUSE CTRL STATUS Register Masks */
#define XNVM_EFUSE_CTRL_CFG_MARGIN_RD_MASK    		(0x00000004U)

/* access_type: ro  */
#define XNVM_EFUSE_CTRL_STATUS_AES_USER_KEY_1_CRC_PASS_MASK	(0x00000800U)
#define XNVM_EFUSE_CTRL_STATUS_AES_USER_KEY_1_CRC_DONE_MASK	(0x00000400U)
#define XNVM_EFUSE_CTRL_STATUS_AES_USER_KEY_0_CRC_PASS_MASK	(0x00000200U)
#define XNVM_EFUSE_CTRL_STATUS_AES_USER_KEY_0_CRC_DONE_MASK	(0x00000100U)
#define XNVM_EFUSE_CTRL_STATUS_AES_CRC_PASS_MASK		(0x00000080U)
#define XNVM_EFUSE_CTRL_STATUS_AES_CRC_DONE_MASK		(0x00000040U)
/** @} */

/**
 * @name  EFUSE_CACHE Base Address
 */
/**< eFUSE Cache Base Address */
#define XNVM_EFUSE_CACHE_BASEADDR				(0xF1250000U)
/** @} */

/**
 * @name  Register: EFUSE_CACHE_SECURITY_MISC_0
 */
/**< eFUSE Cache DEC_EFUSE_ONLY Mask */
#define XNVM_EFUSE_CACHE_DEC_EFUSE_ONLY_MASK			(0x0000ffffU)
/**
 * @name  WR_UNLOCK Code
 */
/**< eFUSE Write Unlock Passcode */
#define XNVM_EFUSE_WR_UNLOCK_PASSCODE			(0xDF0DU)
/** @} */

/**
 * @name eFUSE Controller CFG register
 */
/**< eFUSE CFG Modes */
#define XNVM_EFUSE_CFG_ENABLE_PGM			(0x01U << 1U)
#define XNVM_EFUSE_CFG_MARGIN_RD			(0x01U << 2U)
#define XNVM_EFUSE_CFG_NORMAL_RD			(0x00U << 2U)
/** @} */

/**
 * @name eFUSE STATUS register
 */
/**< eFUSE Status Register Masks */
#define XNVM_EFUSE_STATUS_TBIT_0			(0x01U << 0U)
#define XNVM_EFUSE_STATUS_TBIT_1			(0x01U << 1U)
#define XNVM_EFUSE_STATUS_TBIT_2			(0x01U << 2U)
#define XNVM_EFUSE_STATUS_CACHE_DONE			(0x01U << 5U)
/** @} */

/**
 * @name eFUSE Controller PGM_ADDR register
 */
/**< eFUSE Addres Shifts */
#define XNVM_EFUSE_ADDR_COLUMN_SHIFT			(0U)
#define XNVM_EFUSE_ADDR_ROW_SHIFT			(5U)
#define XNVM_EFUSE_ADDR_PAGE_SHIFT			(13U)
/** @} */

/**< eFUse Cache load mask */
#define XNVM_EFUSE_CACHE_LOAD_MASK			(0x01U)


#define XNVM_EFUSE_SECURITY_MISC_1_PROT_MASK		(0x1FFFU)
/**< eFuse Protection Row Mask */

/**
 * @name eFUSE ISR Register
 */
/**< eFuse ISR registers masks */
#define XNVM_EFUSE_ISR_PGM_DONE				(0x01U << 0U)
#define XNVM_EFUSE_ISR_PGM_ERROR			(0x01U << 1U)
#define XNVM_EFUSE_ISR_RD_DONE				(0x01U << 2U)
#define XNVM_EFUSE_ISR_CACHE_ERROR			(0x01U << 4U)
/** @} */

/**< eFUSE Controller PD register definition */
#define XNVM_EFUSE_PD_ENABLE				(0x01U << 0U)


#define XNVM_PS_REF_CLK_FREQ			(XPAR_PSU_PSS_REF_CLK_FREQ_HZ)
					/**< PS Ref clock definition in Hz */

#define XNVM_NUM_OF_ROWS_PER_PAGE			(256U)
					/**< Number of Rows per Page */

/**
 * @name Timeout values
 */
/**< Timeout in term of number of times status register polled to check eFUSE
 * read operation complete
 */
#define XNVM_EFUSE_RD_TIMEOUT_VAL			(100U)

/**< Timeout in term of number of times status register polled to check eFUSE
 * programming operation complete
 */
#define XNVM_EFUSE_PGM_TIMEOUT_VAL			(100U)

/**< Timeout in term of number of times status register polled to check eFuse
 * Cache load is done
 */
#define XNVM_EFUSE_CACHE_LOAD_TIMEOUT_VAL		(0x800U)

/**< Timeout in term of number of times status register polled to check eFuse
 * Crc check id done.
 */
#define XNVM_POLL_TIMEOUT				(0x400U)
/** @} */

#ifdef __cplusplus
}
#endif

#endif	/* XNVM_EFUSE_COMMON_HW_H */
