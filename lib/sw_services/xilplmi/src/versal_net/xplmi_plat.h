/******************************************************************************
* Copyright (c) 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


/*****************************************************************************/
/**
*
* @file xplmi_plat.h
*
* This file contains declarations for versal_net specific APIs
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  bm   07/06/2022 Initial release
*       ma   07/08/2022 Add ScatterWrite and ScatterWrite2 commands to versal
*       dc   07/12/2022 Added API XPlmi_RomISR() API
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XPLMI_PLAT_H
#define XPLMI_PLAT_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xplmi_hw.h"
#include "xplmi_dma.h"
#include "xplmi_event_logging.h"
#include "xplmi_update.h"
#include "xplmi_cmd.h"

/************************** Constant Definitions *****************************/

#define XPLMI_PLM_BANNER	"Xilinx VersalNet Platform Loader and Manager \n\r"

/* PLM RunTime Configuration Area Base Address */
#define XPLMI_RTCFG_BASEADDR			(0xF2014000U)

#define XPLMI_RTCFG_PMC_ERR1_STATUS_ADDR	(XPLMI_RTCFG_BASEADDR + 0x154U)
#define XPLMI_RTCFG_PSM_ERR1_STATUS_ADDR	(XPLMI_RTCFG_BASEADDR + 0x15CU)
#define XPLMI_RTCFG_PMC_ERR3_STATUS_ADDR	(XPLMI_RTCFG_BASEADDR + 0x190U)
#define XPLMI_RTCFG_PSM_ERR3_STATUS_ADDR	(XPLMI_RTCFG_BASEADDR + 0x1A0U)

#define XPLMI_ROM_SERVICE_TIMEOUT			(1000000U)

/**************************** Type Definitions *******************************/
/* Minor Error Codes */
/* Add any platform specific minor error codes from 0xA0 */
enum {
	XPLMI_ERR_CURRENT_UART_INVALID = 0x2, /**< 0x2 - Error when current uart
						selected has invalid base address */
	XPLMI_ERR_INVALID_UART_SELECT, /**< 0x3 - Error when invalid uart select
						argument is passed */
	XPLMI_ERR_INVALID_UART_ENABLE, /**< 0x4 - Error when invalid uart enable
						argument is passed */
	XPLMI_ERR_NO_UART_PRESENT, /**< 0x5 - Error when no uart is present to
						configure in run-time */
};

typedef struct {
	u8 Mode;
} XPlmi_ModuleOp;

typedef int (*XPlmi_UpdateHandler_t)(XPlmi_ModuleOp Op);

/* ROM interrupt services */
typedef enum {
	XPLMI_DME_CHL_SIGN_GEN = 0U,	/**< DME channel signature generation */
	XPLMI_PCR_OP,			/**< PCR extenstion */
	XPLMI_SHA2_HASH_GEN,		/**< SHA2 hash calculation */
	XPLMI_PLM_UPDT_REQ,		/**< In place PLM update */
	XPLMI_INVALID_INT		/**< Invalid interrupt */
} XPlmi_RomIntr;
/***************** Macros (Inline Functions) Definitions *********************/
/* PLMI GENERIC MODULE Data Structures IDs */
#define XPLMI_WDT_DS_ID			(0x01U)
#define XPLMI_TRACELOG_DS_ID		(0x02U)
#define XPLMI_LPDINITIALIZED_DS_ID	(0x03U)
#define XPLMI_UPDATE_IPIMASK_DS_ID	(0x04U)
#define XPLMI_UART_BASEADDR_DS_ID	(0x05U)

/*
 * SLR Types
 */
#define XPLMI_SSIT_MONOLITIC		(0x7U)
#define XPLMI_SSIT_MASTER_SLR		(0x6U)
#define XPLMI_SSIT_SLAVE0_SLR_TOP	(0x5U)
#define XPLMI_SSIT_SLAVE0_SLR_NTOP	(0x4U)
#define XPLMI_SSIT_SLAVE1_SLR_TOP	(0x3U)
#define XPLMI_SSIT_SLAVE1_SLR_NTOP	(0x2U)
#define XPLMI_SSIT_SLAVE2_SLR_TOP	(0x1U)
#define XPLMI_SSIT_INVALID_SLR		(0x0U)

/* Macros for command ids */
#define XPLMI_PSM_SEQUENCE_CMD_ID	(31U)

/* GIC related Macros */
#define XPLMI_GICP_SOURCE_COUNT		(0x5U)
#define XPLMI_GICP_INDEX_SHIFT		(16U)
#define XPLMI_GICPX_INDEX_SHIFT		(24U)
#define XPLMI_GICPX_LEN			(0x14U)

/*
 * PMC GIC interrupts
 */
#define XPLMI_PMC_GIC_IRQ_GICP0		(0U)
#define XPLMI_PMC_GIC_IRQ_GICP1		(1U)
#define XPLMI_PMC_GIC_IRQ_GICP2		(2U)
#define XPLMI_PMC_GIC_IRQ_GICP3		(3U)
#define XPLMI_PMC_GIC_IRQ_GICP4		(4U)
#define XPLMI_PMC_GIC_IRQ_GICP5		(5U)
#define XPLMI_PMC_GIC_IRQ_GICP6		(6U)

/*
 * PMC GICP0 interrupts
 */
#define XPLMI_GICP0_SRC20	(20U) /**< GPIO Interrupt */
#define XPLMI_GICP0_SRC21	(21U) /**< I2C_0 Interrupt */
#define XPLMI_GICP0_SRC22	(22U) /**< I2C_1 Interrupt */
#define XPLMI_GICP0_SRC23	(23U) /**< SPI_0 Interrupt */
#define XPLMI_GICP0_SRC24	(24U) /**< SPI_1 Interrupt */
#define XPLMI_GICP0_SRC25	(25U) /**< UART_0 Interrupt */
#define XPLMI_GICP0_SRC26	(26U) /**< UART_1 Interrupt */
#define XPLMI_GICP0_SRC27	(27U) /**< CAN_0 Interrupt */
#define XPLMI_GICP0_SRC28	(28U) /**< CAN_1 Interrupt */
#define XPLMI_GICP0_SRC29	(29U) /**< USB_0 Interrupt */
#define XPLMI_GICP0_SRC30	(30U) /**< USB_0 Interrupt */
#define XPLMI_GICP0_SRC31	(31U) /**< USB_0 Interrupt */

/*
 * PMC GICP1 interrupts
 */
#define XPLMI_GICP1_SRC0	(0U) /**< USB_0 Interrupt */
#define XPLMI_GICP1_SRC1	(1U) /**< USB_0 Interrupt */
#define XPLMI_GICP1_SRC2	(2U) /**< USB_1 Interrupt */
#define XPLMI_GICP1_SRC3	(3U) /**< USB_1 Interrupt */
#define XPLMI_GICP1_SRC4	(4U) /**< USB_1 Interrupt */
#define XPLMI_GICP1_SRC5	(5U) /**< USB_1 Interrupt */
#define XPLMI_GICP1_SRC6	(6U) /**< USB_1 Interrupt */
#define XPLMI_GICP1_SRC7	(7U) /**< GEM_0 Interrupt */
#define XPLMI_GICP1_SRC8	(8U) /**< GEM_0 Interrupt */
#define XPLMI_GICP1_SRC9	(9U) /**< GEM_1 Interrupt */
#define XPLMI_GICP1_SRC10	(10U) /**< GEM_1 Interrupt */
#define XPLMI_GICP1_SRC11	(11U) /**< TTC_0 Interrupt */
#define XPLMI_GICP1_SRC12	(12U) /**< TTC_0 Interrupt */
#define XPLMI_GICP1_SRC13	(13U) /**< TTC_0 Interrupt */
#define XPLMI_GICP1_SRC14	(14U) /**< TTC_1 Interrupt */
#define XPLMI_GICP1_SRC15	(15U) /**< TTC_1 Interrupt */
#define XPLMI_GICP1_SRC16	(16U) /**< TTC_1 Interrupt */
#define XPLMI_GICP1_SRC17	(17U) /**< TTC_2 Interrupt */
#define XPLMI_GICP1_SRC18	(18U) /**< TTC_2 Interrupt */
#define XPLMI_GICP1_SRC19	(19U) /**< TTC_2 Interrupt */
#define XPLMI_GICP1_SRC20	(20U) /**< TTC_3 Interrupt */
#define XPLMI_GICP1_SRC21	(21U) /**< TTC_3 Interrupt */
#define XPLMI_GICP1_SRC22	(22U) /**< TTC_3 Interrupt */

/*
 * PMC GICP2 interrupts
 */
#define XPLMI_GICP2_SRC8	(8U) /**< ADMA_0 Interrupt */
#define XPLMI_GICP2_SRC9	(9U) /**< ADMA_1 Interrupt */
#define XPLMI_GICP2_SRC10	(10U) /**< ADMA_2 Interrupt */
#define XPLMI_GICP2_SRC11	(11U) /**< ADMA_3 Interrupt */
#define XPLMI_GICP2_SRC12	(12U) /**< ADMA_4 Interrupt */
#define XPLMI_GICP2_SRC13	(13U) /**< ADMA_5 Interrupt */
#define XPLMI_GICP2_SRC14	(14U) /**< ADMA_6 Interrupt */
#define XPLMI_GICP2_SRC15	(15U) /**< ADMA_7 Interrupt */

/*
 * PMC GICP3 interrupts
 */
#define XPLMI_GICP3_SRC2	(2U) /**< USB_0 Interrupt */
#define XPLMI_GICP3_SRC3	(3U) /**< USB_1 Interrupt */

/*
 * PMC GICP4 interrupts
 */
#define XPLMI_GICP5_SRC22	(22U) /**< OSPI Interrupt */
#define XPLMI_GICP5_SRC23	(23U) /**< QSPI Interrupt */
#define XPLMI_GICP5_SRC24	(24U) /**< SD_0 Interrupt */
#define XPLMI_GICP5_SRC25	(25U) /**< SD_0 Interrupt */
#define XPLMI_GICP5_SRC26	(26U) /**< SD_1 Interrupt */
#define XPLMI_GICP5_SRC27	(27U) /**< SD_1 Interrupt */

/*
 * PMC GICP6 interrupts
 */
#define XPLMI_GICP6_SRC1	(1U) /**< SBI Interrupt */

#define XPLMI_SBI_GICP_INDEX	(XPLMI_PMC_GIC_IRQ_GICP6)
#define XPLMI_SBI_GICPX_INDEX	(XPLMI_GICP6_SRC1)

#define XPLMI_IPI_INTR_ID	(0x1CU)
#define XPLMI_IPI_INDEX_SHIFT	(24U)

/* PPU1 HW Interrupts */
#define XPLMI_HW_INT_GIC_IRQ	(0U)

#define XPLMI_HW_SW_INTR_MASK	(0xFF00U)
#define XPLMI_HW_SW_INTR_SHIFT	(0x8U)

/* Defines related to module commands */
#define XPLMI_PLM_GENERIC_PLMUPDATE		(0x20U)

/* Module Operations */
#define XPLMI_MODULE_SHUTDOWN_INITIATE		(1U)
#define XPLMI_MODULE_SHUTDOWN_COMPLETE		(2U)

#define XPlmi_SsitSyncMaster	NULL
#define XPlmi_SsitSyncSlaves	NULL
#define XPlmi_SsitWaitSlaves	NULL

#define GET_RTCFG_PMC_ERR_ADDR(Index)	(Index > 1U) ? \
			(XPLMI_RTCFG_PMC_ERR3_STATUS_ADDR) : \
			(XPLMI_RTCFG_PMC_ERR1_STATUS_ADDR + (Index * 4U))
#define GET_RTCFG_PSM_ERR_ADDR(Index)		(Index > 1U) ? \
			(XPLMI_RTCFG_PSM_ERR3_STATUS_ADDR + ((Index - 2U) * 4U)) : \
			(XPLMI_RTCFG_PSM_ERR1_STATUS_ADDR + (Index * 4U))

/*****************************************************************************/
/**
 * @brief	This function provides the Slr Type
 *
 * @return 	SlrType
 *
 *****************************************************************************/
static inline u8 XPlmi_GetSlrType(void)
{
	return XPLMI_SSIT_MONOLITIC;
}

/*****************************************************************************/
/**
 * @brief	This function processes and provides readback length
 *
 * @param	Len is the current readback length

 * @return	Readback length
 *
 *****************************************************************************/
static inline u32 XPlmi_GetReadbackLen(u32 Len)
{
	return Len;
}

#ifdef PLM_ENABLE_PLM_TO_PLM_COMM
/****************************************************************************/
/**
* @brief    This function enables the SSIT interrupts
*
* @return   None
*
****************************************************************************/
static inline void XPlmi_EnableSsitErrors(void)
{
	/* Not Applicable for versalnet */
	return;
}
#endif

/*****************************************************************************/
/**
 * @brief	This function Disables CFRAME Isolation
 *
 * @return	None
 *
 *****************************************************************************/
static inline void XPlmi_DisableCFrameIso(void)
{
	/* Not Applicable for Versal Net */
	return;
}

/************************** Function Prototypes ******************************/
u32 *XPlmi_GetLpdInitialized(void);
void XPlmi_PreInit(void);
void XPlmi_RtcaPlatInit(void);
u8 XPlmi_IsPlmUpdateDone(void);
void XPlmi_SssMask(u32 InputSrc, u32 OutputSrc);
XPlmi_CircularBuffer *XPlmi_GetTraceLogInst(void);
void XPlmi_GetReadbackSrcDest(u32 SlrType, u64 *SrcAddr, u64 *DestAddrRead);
int XPlmi_GenericHandler(XPlmi_ModuleOp Op);
void XPlmi_GicAddTask(u32 PlmIntrId);
int XPlmi_RegisterNEnableIpi(void);
void XPlmi_EnableIomoduleIntr(void);
int XPlmi_SetPmcIroFreq(void);
int XPlmi_GetPitResetValues(u32 *Pit1ResetValue, u32 *Pit2ResetValue);
int XPlmi_VerifyAddrRange(u64 StartAddr, u64 EndAddr);
XInterruptHandler *XPlmi_GetTopLevelIntrTbl(void);
u8 XPlmi_GetTopLevelIntrTblSize(void);
XPlmi_WaitForDmaDone_t XPlmi_GetPlmiWaitForDone(u64 DestAddr);
void XPlmi_PrintRomVersion(void);
u32 XPlmi_GetGicIntrId(u32 GicPVal, u32 GicPxVal);
u32 XPlmi_GetIpiIntrId(u32 BufferIndex);
void XPlmi_EnableIpiIntr(void);
void XPlmi_ClearIpiIntr(void);
u32 *XPlmi_GetUartBaseAddr(void);

/* Functions defined in xplmi_plat_cmd.c */
int XPlmi_CheckIpiAccess(u32 CmdId, u32 IpiReqType);
int XPlmi_ValidateCmd(u32 ModuleId, u32 ApiId);
int XPlmi_InPlacePlmUpdate(XPlmi_Cmd *Cmd);
int XPlmi_PsmSequence(XPlmi_Cmd *Cmd);

int XPlmi_RomISR(XPlmi_RomIntr RomServiceReq);

/************************** Variable Definitions *****************************/

#ifdef __cplusplus
}
#endif

#endif  /* XPLMI_PLAT_H */
