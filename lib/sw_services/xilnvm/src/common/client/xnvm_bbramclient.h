/******************************************************************************
* Copyright (c) 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
*******************************************************************************/

/*****************************************************************************/
/**
*
* @file xnvm_bbramclient.h
* @addtogroup xnvm_bbram_client_apis XilNvm BBRAM Versal Client APIs
* @{
* @cond xnvm_internal
* This file Contains the client function prototypes, defines and macros for
* the BBRAM programming.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.0   kal  07/05/21 Initial release
*       kpt  03/16/22 Removed IPI related code and added mailbox support
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XNVM_BBRAMCLIENT_H
#define XNVM_BBRAMCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xil_types.h"
#include "xnvm_mailbox.h"
#include "xnvm_defs.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
int XNvm_BbramWriteAesKey(XNvm_ClientInstance *InstancePtr, const u64 KeyAddr, const u32 KeyLen);
int XNvm_BbramZeroize(XNvm_ClientInstance *InstancePtr);
int XNvm_BbramWriteUsrData(XNvm_ClientInstance *InstancePtr, const u32 UsrData);
int XNvm_BbramReadUsrData(XNvm_ClientInstance *InstancePtr, const u64 OutDataAddr);
int XNvm_BbramLockUsrDataWrite(XNvm_ClientInstance *InstancePtr);

/************************** Variable Definitions *****************************/

#ifdef __cplusplus
}
#endif

#endif  /* XNVM_BBRAMCLIENT_H */
