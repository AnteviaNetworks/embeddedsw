/******************************************************************************
* Copyright (c) 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
*******************************************************************************/

/*****************************************************************************/
/**
*
* @file xocp_common.h
* @addtogroup xil_ocpapis DME APIs
* @{
*
* @cond xocp_internal
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date       Changes
* ----- ---- ---------- -------------------------------------------------------
* 1.0   vns  06/27/2022 Initial release
*
* </pre>
*
* @note
* @endcond
*
******************************************************************************/
#ifndef XOCP_COMMON_H
#define XOCP_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xstatus.h"

/************************** Constant Definitions *****************************/
#define XOCP_PCR_SIZE_WORDS			(12U)
#define XOCP_PCR_SIZE_BYTES			(48U)

#define XOCP_DME_DEVICE_ID_SIZE_WORDS		(12U)

#define XOCP_DME_NONCE_SIZE_WORDS		(8U)
#define XOCP_DME_NONCE_SIZE_BYTES		(XOCP_DME_NONCE_SIZE_WORDS << 2U)

#define XOCP_DME_MEASURE_SIZE_WORDS		(12U)
#define XOCP_DME_MEASURE_SIZE_BYTES		(XOCP_DME_MEASURE_SIZE_WORDS << 2U)

#define XOCP_ECC_P384_SIZE_WORDS		(12U)
#define XOCP_ECC_P384_SIZE_BYTES		(48U)
#define XOCP_SIZE_OF_ECC_P384_PUBLIC_KEY_BYTES	(96U)

/**************************** Type Definitions *******************************/

/*
 * Hardware PCR selection
 */
typedef enum {
	XOCP_PCR_0 = 0, /**< PCR 0 */
	XOCP_PCR_1,	/**< PCR 1 */
	XOCP_PCR_2,	/**< PCR 2 */
	XOCP_PCR_3,	/**< PCR 3 */
	XOCP_PCR_4,	/**< PCR 4 */
	XOCP_PCR_5,	/**< PCR 5 */
	XOCP_PCR_6,	/**< PCR 6 */
	XOCP_PCR_7	/**< PCR 7 */
} XOcp_RomHwPcr;

/*
 * DME
 */
typedef struct {
	u32 DeviceID[XOCP_DME_DEVICE_ID_SIZE_WORDS];	/**< Device ID */
	u32 Nonce[XOCP_DME_NONCE_SIZE_WORDS];		/**< Nonce */
	u32 Measurement[XOCP_DME_MEASURE_SIZE_WORDS];	/**< Measurement */
} XOcp_Dme;

/*
 * DME response
 */
typedef struct {
	XOcp_Dme Dme;									/**< DME */
	u32 DmeSignatureR[XOCP_ECC_P384_SIZE_WORDS];	/**< Signature comp R */
	u32 DmeSignatureS[XOCP_ECC_P384_SIZE_WORDS];	/**< Signature comp S */
} XOcp_DmeResponse;

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

#ifdef __cplusplus
}
#endif

#endif  /* XOCP_COMMON_H */
/* @} */
