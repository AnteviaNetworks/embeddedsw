/******************************************************************************
* Copyright (c) 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xnvm_bbram_cdohandler.h
* @addtogroup xnvm_apis XilNvm Versal_Net APIs
* @{
* @cond xnvm_internal
* This file contains the Versal_Net XilNvm BBRAM Cdo handler declaration.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kal   07/05/2021 Initial release
*
* </pre>
*
* @note
* @endcond
*
******************************************************************************/

#ifndef XNVM_BBRAM_CDOHANDLER_H_
#define XNVM_BBRAM_CDOHANDLER_H_

#ifdef __cplusplus
extern "c" {
#endif

/***************************** Include Files *********************************/
#include "xplmi_config.h"

#ifdef PLM_NVM
#include "xplmi_cmd.h"

/************************** Constant Definitions *****************************/
int XNvm_BbramCdoHandler(XPlmi_Cmd *Cmd);

#endif /* PLM_NVM */

#ifdef __cplusplus
}
#endif

#endif /* XNVM_BBRAM_CDOHANDLER_H_ */
