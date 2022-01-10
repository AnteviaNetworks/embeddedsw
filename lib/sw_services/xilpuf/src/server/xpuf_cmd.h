/******************************************************************************
* Copyright (c) 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file xpuf_cmd.h
 *
 * Header file for xpuf_cmd.c
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date        Changes
 * ----- ---- ---------- -------------------------------------------------------
 * 1.0   kpt  01/04/2022 Initial release
 *
 * </pre>
 *
 * @note
 *
 ******************************************************************************/
#ifndef XPUF_CMD_H_
#define XPUF_CMD_H_

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xplmi_config.h"

#ifdef PLM_PUF
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Function Prototypes ******************************/
void XPuf_CmdsInit(void);

#endif /* PLM_PUF */

#ifdef __cplusplus
}
#endif

#endif /* XPUF_CMD_H_ */