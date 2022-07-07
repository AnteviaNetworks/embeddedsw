/******************************************************************************
* Copyright (c) 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xnvm_bbarm_ipihandler.h
* @addtogroup xnvm_apis XilNvm Versal APIs
* @{
* @cond xnvm_internal
* This file contains the xilnvm BBRAM IPI handler declaration.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kal   07/05/2021 Initial release
* 2.4   bsv  09/09/2021 Added PLM_NVM macro
*
* </pre>
*
* @note
* @endcond
*
******************************************************************************/

#ifndef XNVM_BBRAM_IPIHANDLER_H_
#define XNVM_BBRAM_IPIHANDLER_H_

#ifdef __cplusplus
extern "c" {
#endif

/***************************** Include Files *********************************/
#include "xplmi_config.h"

#ifdef PLM_NVM
#include "xplmi_cmd.h"

/************************** Constant Definitions *****************************/
int XNvm_BbramIpiHandler(XPlmi_Cmd *Cmd);

#endif /* PLM_NVM */

#ifdef __cplusplus
}
#endif

#endif /* XNVM_BBRAM_IPIHANDLER_H_ */