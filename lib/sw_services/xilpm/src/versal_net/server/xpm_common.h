/******************************************************************************
* Copyright (c) 2018 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


#ifndef XPM_COMMON_H_
#define XPM_COMMON_H_

#include "xstatus.h"
#include "xil_io.h"
#include "xil_util.h"
#include "xpm_err.h"
#include "xplmi_debug.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This macro defines "always false" value which is of boolean type.
 * The purpose of macro is to have boolean value which can be used
 * at loop condition instead of "0U" which is non-boolean value.
 */
#define XPM_FALSE_COND		(0U != 0U)

/**
 * GCC Specific attribute to suppress unused variable/function warning
 */
#ifndef maybe_unused
#define maybe_unused __attribute__((unused))
#endif

#define XPM_POLL_TIMEOUT		(0X1000000U)
/* Enable PSM power control interrupt */
#define ENABLE_WFI(mask)	PmOut32(PSMX_GLOBAL_PWR_CTRL1_IRQ_EN, mask)

/**
 * Platform type definitions
 */
#define PLATFORM_VERSION_SILICON		(0x0U)
#define PLATFORM_VERSION_SPP			(0x1U)
#define PLATFORM_VERSION_EMU			(0x2U)
#define PLATFORM_VERSION_QEMU			(0x3U)
#define PLATFORM_VERSION_FCV			(0x4U)

#define XPM_ALERT_VAL	0x10U
#define XPM_ERR_VAL	0x20U
#define XPM_WARN_VAL	0x30U
#define XPM_INFO_VAL	0x40U
#define XPM_DBG_VAL	0x50U

#define XPM_ALERT   (DEBUG_GENERAL  | XPM_ALERT_VAL)
#define XPM_ERR     (DEBUG_GENERAL  | XPM_ERR_VAL)
#define XPM_WARN    (DEBUG_GENERAL  | XPM_WARN_VAL)
#define XPM_INFO    (DEBUG_INFO     | XPM_INFO_VAL)
#define XPM_DBG     (DEBUG_DETAILED | XPM_DBG_VAL)

#define XPM_DEBUG_MASK	0x70U
#define XPM_DEBUG_SHIFT	4U

/**
 * Poll for mask for a period represented by TimeOut
 */
static inline XStatus XPm_PollForMask(u32 RegAddress, u32 Mask,
				      u32 TimeOut)
{
	return XPlmi_UtilPoll(RegAddress, Mask, Mask, TimeOut);
}

/**
 * Common baseline macro to print debug logs
 */

void XPm_Printf(u32 DebugType, const char *Fnstr, const char8 *Ctrl1, ...);

#define PmPrintCommon(DbgLevel, ...)					\
	do {								\
		if (((DbgLevel) & (XPlmiDbgCurrentTypes)) != (u8)FALSE) {\
			XPm_Printf(DbgLevel, __func__,  __VA_ARGS__);\
		}\
	} while (XPM_FALSE_COND)

/* Debug logs */
#define PmAlert(...)	PmPrintCommon(XPM_ALERT, __VA_ARGS__)
#define PmErr(...)	PmPrintCommon(XPM_ERR, __VA_ARGS__)
#define PmWarn(...)	PmPrintCommon(XPM_WARN, __VA_ARGS__)
#define PmInfo(...)	PmPrintCommon(XPM_INFO, __VA_ARGS__)
#define PmDbg(...)	PmPrintCommon(XPM_DBG, __VA_ARGS__)

#ifdef DEBUG_REG_IO

#define PmIn32(ADDR, VAL)					\
	do {							\
		(VAL) = XPm_In32(ADDR);				\
		PmInfo("RD: 0x%08X -> 0x%08X\r\n", ADDR, VAL);	\
	} while (XPM_FALSE_COND)

#define PmOut32(ADDR, VAL)					\
	do {							\
		PmInfo("WR: 0x%08X <- 0x%08X\r\n", ADDR, VAL);	\
		XPm_Out32(ADDR, VAL);				\
	} while (XPM_FALSE_COND)

#define PmRmw32(ADDR, MASK, VAL)				\
	do {							\
		XPm_RMW32(ADDR, MASK, VAL);			\
		PmInfo("RMW: Addr=0x%08X, Mask=0x%08X, Val=0x%08X, Reg=0x%08X\r\n", \
			ADDR, MASK, VAL, XPm_In32(ADDR));	\
	} while (XPM_FALSE_COND)								\


#else

#define PmIn32(ADDR, VAL)		((VAL) = XPm_In32(ADDR))

#define PmOut32(ADDR, VAL)		XPm_Out32(ADDR, VAL)

#define PmRmw32(ADDR, MASK, VAL)	XPm_RMW32(ADDR, MASK, VAL)

#endif

#define BIT(n)					(1U << (n))
#define BIT8(n)					((u8)1U << (n))
#define BIT16(n)				((u16)1U << (n))
#define BIT32(n)				((u32)1U << (n))

// set the first n bits to 1, rest to 0
#define BITMASK(n)				(u32)((1ULL << (n)) - 1ULL)
// set width specified bits at offset to 1, rest to 0
#define BITNMASK(offset, width) 		(BITMASK(width) << (offset))

#define ARRAY_SIZE(x)				(sizeof(x) / sizeof((x)[0]))

#define XPm_Read32				XPm_In32
#define XPm_Write32				XPm_Out32

void XPm_Out32(u32 RegAddress, u32 l_Val);

u32 XPm_In32(u32 RegAddress);
u32 XPm_GetPlatform(void);

/**
 * Read Modify Write a register
 */
void XPm_RMW32(u32 RegAddress, u32 Mask, u32 Value);

void *XPm_AllocBytes(u32 SizeInBytes);

#ifdef __cplusplus
}
#endif

#endif /* XPM_COMMON_H_ */
