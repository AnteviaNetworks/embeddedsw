/******************************************************************************
* Copyright (c) 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


/*****************************************************************************/
/**
*
* @file xplmi_err_plat.h
*
* This file contains declarations for versal EAM code
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  bm   07/06/2022 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XPLMI_ERR_H
#define XPLMI_ERR_H

#ifdef __cplusplus
extern "C" {
#endif

/************************** Include Files *****************************/
#include "xplmi_error_node.h"
#include "xplmi_hw.h"
#include "xplmi_err_common.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define GET_PMC_ERR_ACTION_OFFSET(Index)	(Index * PMC_PSM_ERR_REG_OFFSET)
#define GET_PMC_ERR_ACTION_ADDR(PmcMask, Index) \
					(PmcMask + (Index * PMC_PSM_ERR_REG_OFFSET))

#define GET_PMC_ERR_OUT_MASK(RegOffset)	(PMC_GLOBAL_PMC_ERR_OUT1_MASK + RegOffset)
#define GET_PMC_POR_MASK(RegOffset)	(PMC_GLOBAL_PMC_POR1_MASK + RegOffset)
#define GET_PMC_IRQ_MASK(RegOffset)	(PMC_GLOBAL_PMC_IRQ1_MASK + RegOffset)
#define GET_PMC_SRST_MASK(RegOffset)	(PMC_GLOBAL_PMC_SRST1_MASK + RegOffset)

/****************************************************************************/
/**
* @brief	This function restricts error actions.
*
* @param	NodeType of Error
* @param	RegMask of Error
* @param	ErrorAction of the the Error
*
* @return	XST_SUCCESS on success and error code on failure
*
****************************************************************************/
static inline int XPlmi_RestrictErrActions(XPlmi_EventType NodeType,
		u32 RegMask, u32 ErrorAction)
{
	(void)NodeType;
	(void)RegMask;
	(void)ErrorAction;

	return XST_SUCCESS;
}

/************************** Function Prototypes ******************************/
XPlmi_Error_t *XPlmi_GetErrorTable(void);
void XPlmi_TriggerSsitErrToMaster(void);
void XPlmi_SysmonClkSetIro(void);
void XPlmi_HandleLinkDownError(u32 Cpm5PcieIrStatusReg,
		u32 Cpm5DmaCsrIntDecReg, u32 ProcId);
void XPlmi_DumpErrNGicStatus(void);
u8 XPlmi_GetEventIndex(u32 ErrorNodeType);
void XPlmi_DisablePmcErrAction(u32 ErrIndex, u32 RegMask);
void XPlmi_ClearSsitErrors(u32 *PmcErrStatus, u32 Index);
#ifdef PLM_ENABLE_PLM_TO_PLM_COMM
void XPlmi_EnableSsitErrors(void);
#endif

/************************** Variable Definitions *****************************/

/*****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* XPLMI_ERR_H */
