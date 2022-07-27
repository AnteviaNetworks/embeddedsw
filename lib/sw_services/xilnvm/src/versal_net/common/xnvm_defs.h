/******************************************************************************
* Copyright (c) 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
*******************************************************************************/

/*****************************************************************************/
/**
*
* @file xnvm_defs.h
* @addtogroup xnvm_api_ids XilNvm API IDs
* @{
*
* @cond xnvm_internal
* This file contains the xilnvm Versal_Net API IDs
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.0   kal  01/05/22 Initial release
*
* </pre>
* @note
*
* @endcond
******************************************************************************/

#ifndef XNVM_DEFS_H
#define XNVM_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xil_printf.h"
#include "xil_types.h"
#include "xnvm_common_defs.h"

/************************** Constant Definitions ****************************/
/**@cond xnvm_internal
 * @{
 */
/* Enable client printfs by setting XNVM_DEBUG to 1 */
#define XNVM_DEBUG	(0U)

#if (XNVM_DEBUG)
#define XNVM_DEBUG_GENERAL (1U)
#else
#define XNVM_DEBUG_GENERAL (0U)
#endif

/***************** Macros (Inline Functions) Definitions *********************/
#define XNvm_Printf(DebugType, ...)	\
	if ((DebugType) == 1U) {xil_printf (__VA_ARGS__);}

/* Macro to typecast XILNVM API ID */
#define XNVM_API(ApiId)	((u32)ApiId)

#define XNVM_API_ID_MASK		(0xFFU)
#define XNVM_EFUSE_CRC_AES_ZEROS 	(0x6858A3D5U)
#define XNVM_NUM_OF_CACHE_ADDR_PER_PAGE	(0x400U)
#define XNVM_EFUSE_ERROR_BYTE_SHIFT	(8U)
#define XNVM_EFUSE_ERROR_NIBBLE_SHIFT	(4U)

/************************** Variable Definitions *****************************/
#define XNVM_UDS_SIZE_IN_WORDS          (12U)
#define XNVM_DME_USER_KEY_SIZE_IN_WORDS	(12U)

/**************************** Type Definitions *******************************/
typedef struct {
	u16 StartOffset;
	u16 RegCount;
	u32 AddrLow;
	u32 AddrHigh;
} XNvm_RdCachePload;

typedef struct {
	u32 CdoHdr;
	XNvm_RdCachePload Pload;
} XNvm_RdCacheCdo;

typedef struct {
	u32 KeyType;
	u32 AddrLow;
	u32 AddrHigh;
} XNvm_AesKeyWritePload;

typedef struct {
	u32 CdoHdr;
	XNvm_AesKeyWritePload Pload;
} XNvm_AesKeyWriteCdo;

typedef struct {
	u32 PpkType;
	u32 AddrLow;
	u32 AddrHigh;
} XNvm_PpkWritePload;

typedef struct {
	u32 CdoHdr;
	XNvm_PpkWritePload Pload;
} XNvm_PpkWriteCdo;

typedef struct {
	u32 IvType;
	u32 AddrLow;
	u32 AddrHigh;
} XNvm_IvWritePload;

typedef struct {
	u32 CdoHdr;
	XNvm_IvWritePload Pload;
} XNvm_IvWriteCdo;

typedef struct {
	u32 Uds[XNVM_UDS_SIZE_IN_WORDS];
} XNvm_Uds;

typedef enum {
	XNVM_EFUSE_DME_USER_KEY_0 = 0,
	XNVM_EFUSE_DME_USER_KEY_1,
	XNVM_EFUSE_DME_USER_KEY_2,
	XNVM_EFUSE_DME_USER_KEY_3
} XNvm_DmeKeyType;

typedef struct {
	u32 Key[XNVM_DME_USER_KEY_SIZE_IN_WORDS];
} XNvm_DmeKey;

typedef enum {
	XNVM_EFUSE_DME_REVOKE_0 = 0,
	XNVM_EFUSE_DME_REVOKE_1,
	XNVM_EFUSE_DME_REVOKE_2,
	XNVM_EFUSE_DME_REVOKE_3
} XNvm_DmeRevoke;

typedef struct {
	u32 EnvMonitorDis;
	u32 SecCtrlBits;
} XNvm_SecCtrlBitsWritePload;

typedef struct {
	u32 CdoHdr;
	XNvm_SecCtrlBitsWritePload Pload;
} XNvm_SecCtrlBitsWriteCdo;

typedef struct {
	u32 AddrLow;
	u32 AddrHigh;
} XNvm_PufWritePload;

typedef struct {
	u32 CdoHdr;
	XNvm_PufWritePload Pload;
} XNvm_PufWriteCdo;

typedef struct {
	u32 PufSecCtrlBits;
	u32 PrgmPufHelperData;
	u32 EnvMonitorDis;
	u32 EfuseSynData[XNVM_PUF_FORMATTED_SYN_DATA_LEN_IN_WORDS];
	u32 Chash;
	u32 Aux;
	u32 RoSwap;
} XNvm_EfusePufHdAddr;

/* XilNVM API ids */
typedef enum {
	XNVM_API_FEATURES = 0,
	XNVM_API_ID_BBRAM_WRITE_AES_KEY,
	XNVM_API_ID_BBRAM_ZEROIZE,
	XNVM_API_ID_BBRAM_WRITE_USER_DATA,
	XNVM_API_ID_BBRAM_READ_USER_DATA,
	XNVM_API_ID_BBRAM_LOCK_WRITE_USER_DATA,
	XNVM_API_ID_BBRAM_WRITE_AES_KEY_FROM_PLOAD,
	XNVM_API_ID_EFUSE_WRITE_AES_KEY = 20,
	XNVM_API_ID_EFUSE_WRITE_AES_KEY_FROM_PLOAD,
	XNVM_API_ID_EFUSE_WRITE_PPK_HASH,
	XNVM_API_ID_EFUSE_WRITE_PPK_HASH_FROM_PLOAD,
	XNVM_API_ID_EFUSE_WRITE_IV,
	XNVM_API_ID_EFUSE_WRITE_IV_FROM_PLOAD,
	XNVM_API_ID_EFUSE_WRITE_GLITCH_CONFIG,
	XNVM_API_ID_EFUSE_WRITE_DEC_ONLY,
	XNVM_API_ID_EFUSE_WRITE_REVOCATION_ID,
	XNVM_API_ID_EFUSE_WRITE_OFFCHIP_REVOKE_ID,
	XNVM_API_ID_EFUSE_WRITE_MISC_CTRL_BITS,
	XNVM_API_ID_EFUSE_WRITE_SEC_CTRL_BITS,
	XNVM_API_ID_EFUSE_WRITE_MISC1_CTRL_BITS,
	XNVM_API_ID_EFUSE_WRITE_BOOT_ENV_CTRL_BITS,
	XNVM_API_ID_EFUSE_WRITE_FIPS_INFO,
	XNVM_API_ID_EFUSE_WRITE_UDS_FROM_PLOAD,
	XNVM_API_ID_EFUSE_WRITE_DME_KEY_FROM_PLOAD,
	XNVM_API_ID_EFUSE_WRITE_DME_REVOKE,
	XNVM_API_ID_EFUSE_WRITE_PLM_UPDATE,
	XNVM_API_ID_EFUSE_WRITE_BOOT_MODE_DISABLE,
	XNVM_API_ID_EFUSE_WRITE_PUF_FROM_PLOAD,
	XNVM_API_ID_EFUSE_WRITE_PUF,
	XNVM_API_ID_EFUSE_READ_CACHE = 47,
	XNVM_API_ID_EFUSE_RELOAD_N_PRGM_PROT_BITS,
	XNVM_API_MAX,
} XNvm_ApiId;

/**
 * @}
 * @endcond
 */

#ifdef __cplusplus
}
#endif

#endif  /* XNVM_DEFS_H */
