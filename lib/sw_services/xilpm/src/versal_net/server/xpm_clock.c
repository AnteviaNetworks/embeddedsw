/******************************************************************************
* Copyright (c) 2018 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


#include "xil_util.h"
#include "xplmi_util.h"
#include "xpm_clock.h"
#include "xpm_pll.h"
#include "xpm_device.h"
#include "xpm_debug.h"

#define CLK_DUMMY_PARENT		0xFFFFFFFF

#define CLOCK_PARENT_INVALID		0U

#define GENERIC_MUX						\
	{									\
		.Type = (u8)TYPE_MUX,				\
		.Param1.Shift = PERIPH_MUX_SHIFT,		\
		.Param2.Width = PERIPH_MUX_WIDTH,		\
		.Clkflags = CLK_SET_RATE_NO_REPARENT,		\
		.Typeflags = NA_TYPE_FLAGS,		\
	}

#define GENERIC_DIV						\
	{									\
		.Type = (u8)TYPE_DIV1,				\
		.Param1.Shift = PERIPH_DIV_SHIFT,		\
		.Param2.Width = PERIPH_DIV_WIDTH,		\
		.Clkflags = CLK_SET_RATE_NO_REPARENT,		\
		.Typeflags = CLK_DIVIDER_ONE_BASED |	\
				 CLK_DIVIDER_ALLOW_ZERO,		\
	}

#define GENERIC_GATE(id)				\
	{									\
		.Type = (u8)TYPE_GATE,				\
		.Param1.Shift = PERIPH_GATE##id##_SHIFT,		\
		.Param2.Width = PERIPH_GATE_WIDTH,				\
		.Clkflags = CLK_SET_RATE_PARENT |		\
				CLK_SET_RATE_GATE,		\
		.Typeflags = NA_TYPE_FLAGS,		\
	}
static struct XPm_ClkTopologyNode GenericMuxDivNodes[] = {
	GENERIC_MUX,
	GENERIC_DIV,
};

static struct XPm_ClkTopologyNode GenericMuxGate2Nodes[] = {
	GENERIC_MUX,
	GENERIC_GATE(2),
};
static struct XPm_ClkTopologyNode GenericDivGate2Nodes[] = {
	GENERIC_DIV,
	GENERIC_GATE(2),
};
static struct XPm_ClkTopologyNode GenericMuxDivGate1Nodes[] = {
	GENERIC_MUX,
	GENERIC_DIV,
	GENERIC_GATE(1),
};

static struct XPm_ClkTopologyNode GenericMuxDivGate2Nodes[] = {
	GENERIC_MUX,
	GENERIC_DIV,
	GENERIC_GATE(2),
};

static XPm_ClkTopology ClkTopologies[ ] = {
	 {&GenericMuxDivNodes, TOPOLOGY_GENERIC_MUX_DIV, ARRAY_SIZE(GenericMuxDivNodes), {0}},
	 {&GenericMuxGate2Nodes, TOPOLOGY_GENERIC_MUX_GATE, ARRAY_SIZE(GenericMuxGate2Nodes), {0}},
	 {&GenericDivGate2Nodes, TOPOLOGY_GENERIC_DIV_GATE, ARRAY_SIZE(GenericDivGate2Nodes), {0}},
	 {&GenericMuxDivGate1Nodes, TOPOLOGY_GENERIC_MUX_DIV_GATE_1, ARRAY_SIZE(GenericMuxDivGate1Nodes), {0}},
	 {&GenericMuxDivGate2Nodes, TOPOLOGY_GENERIC_MUX_DIV_GATE_2, ARRAY_SIZE(GenericMuxDivGate2Nodes), {0}},
};

static XPm_ClockNode *ClkNodeList[(u32)XPM_NODEIDX_CLK_MAX];
static const u32 MaxClkNodes = (u32)XPM_NODEIDX_CLK_MAX;
static u32 PmNumClocks;

static XStatus XPmClock_Init(XPm_ClockNode *Clk, u32 Id, u32 ControlReg,
			     u8 TopologyType, u8 NumCustomNodes, u8 NumParents,
			     u32 PowerDomainId, u8 ClkFlags)
{
	XStatus Status = XST_FAILURE;
	u32 Subclass = NODESUBCLASS(Id);
	u16 DbgErr = XPM_INT_ERR_UNDEFINED;

	if (Subclass == (u32)XPM_NODETYPE_CLOCK_REF) {
		XPmNode_Init(&Clk->Node, Id, (u8)XPM_CLK_STATE_ON, 0);
	} else if (Subclass == (u32)XPM_NODETYPE_CLOCK_OUT) {
		if (NumParents > MAX_MUX_PARENTS) {
			DbgErr = XPM_INT_ERR_MAX_CLK_PARENTS;
			Status = XST_INVALID_PARAM;
			goto done;
		}
		XPm_OutClockNode *OutClkPtr = (XPm_OutClockNode *)Clk;
		XPmNode_Init(&OutClkPtr->ClkNode.Node, Id, (u8)XPM_CLK_STATE_OFF, 0);
		OutClkPtr->ClkNode.Node.BaseAddress = ControlReg;
		OutClkPtr->ClkNode.ClkHandles = NULL;
		OutClkPtr->ClkNode.UseCount = 0;
		OutClkPtr->ClkNode.NumParents = NumParents;
		OutClkPtr->ClkNode.Flags = ClkFlags;
		if (TopologyType == TOPOLOGY_CUSTOM) {
			OutClkPtr->Topology.Id = TOPOLOGY_CUSTOM;
			OutClkPtr->Topology.NumNodes = NumCustomNodes;
			OutClkPtr->Topology.Nodes = XPm_AllocBytes((u32)NumCustomNodes * sizeof(struct XPm_ClkTopologyNode));
			if (OutClkPtr->Topology.Nodes == NULL) {
				DbgErr = XPM_INT_ERR_BUFFER_TOO_SMALL;
				Status = XST_BUFFER_TOO_SMALL;
				goto done;
			}
		} else {
			OutClkPtr->Topology.Id = ClkTopologies[TopologyType-TOPOLOGY_GENERIC_MUX_DIV].Id;
			OutClkPtr->Topology.NumNodes = ClkTopologies[TopologyType-TOPOLOGY_GENERIC_MUX_DIV].NumNodes;
			OutClkPtr->Topology.Nodes = ClkTopologies[TopologyType-TOPOLOGY_GENERIC_MUX_DIV].Nodes;
		}
	} else {
		DbgErr = XPM_INT_ERR_INVALID_SUBCLASS;
		Status = XST_INVALID_PARAM;
		goto done;
	}

	if (((u32)XPM_NODECLASS_POWER != NODECLASS(PowerDomainId)) ||
	    ((u32)XPM_NODESUBCL_POWER_DOMAIN != NODESUBCLASS(PowerDomainId))) {
		Clk->PwrDomain = NULL;
		Status = XST_SUCCESS;
		goto done;
	}

	Clk->PwrDomain = XPmPower_GetById(PowerDomainId);
	if (NULL == Clk->PwrDomain) {
		DbgErr = XPM_INT_ERR_INVALID_PWR_DOMAIN;
		Status = XST_DEVICE_NOT_FOUND;
		goto done;
	}

	Clk->ClkRate = 0;

	Status = XST_SUCCESS;

done:
	XPm_PrintDbgErr(Status, DbgErr);
	return Status;
}

XStatus XPmClock_AddNode(u32 Id, u32 ControlReg, u8 TopologyType,
			 u8 NumCustomNodes, u8 NumParents, u32 PowerDomainId,
			 u8 ClkFlags)
{
	XStatus Status = XST_FAILURE;
	u32 Subclass = NODESUBCLASS(Id);
	XPm_ClockNode *Clk;
	u16 DbgErr = XPM_INT_ERR_UNDEFINED;

	if (NULL != XPmClock_GetById(Id)) {
		DbgErr = XPM_INT_ERR_INVALID_PARAM;
		Status = XST_INVALID_PARAM;
		goto done;
	}

	if (Subclass == (u32)XPM_NODETYPE_CLOCK_REF) {
		Clk = XPm_AllocBytes(sizeof(XPm_ClockNode));
		if (Clk==NULL) {
			DbgErr = XPM_INT_ERR_BUFFER_TOO_SMALL;
			Status = XST_BUFFER_TOO_SMALL;
			goto done;
		}
	} else if (Subclass == (u32)XPM_NODETYPE_CLOCK_OUT) {
		if ((TopologyType >= MAX_TOPOLOGY) ||
		    (TopologyType < TOPOLOGY_GENERIC_MUX_DIV)) {
			DbgErr = XPM_INT_ERR_INVALID_PARAM;
			Status = XST_INVALID_PARAM;
			goto done;
		}
		Clk = XPm_AllocBytes(sizeof(XPm_OutClockNode));
		if (Clk == NULL) {
			DbgErr = XPM_INT_ERR_BUFFER_TOO_SMALL;
			Status = XST_BUFFER_TOO_SMALL;
			goto done;
		}
	} else {
		DbgErr = XPM_INT_ERR_INVALID_SUBCLASS;
		Status = XST_INVALID_PARAM;
		goto done;
	}

	Status = XPmClock_Init(Clk, Id, ControlReg, TopologyType,
			       NumCustomNodes, NumParents, PowerDomainId,
			       ClkFlags);
	if (XST_SUCCESS == Status) {
		Status = XPmClock_SetById(Id, Clk);
	} else {
		DbgErr = XPM_INT_ERR_CLK_INIT;
		/* TODO: Free allocated memory */
	}

done:
	XPm_PrintDbgErr(Status, DbgErr);
	return Status;
}

XStatus XPmClock_AddClkName(u32 Id, const char *Name)
{
	XStatus Status = XST_FAILURE;
	XPm_ClockNode *Clk = XPmClock_GetById(Id);
	const u32 CopySize = MAX_NAME_BYTES;

	if (NULL == Clk) {
		Status = XST_INVALID_PARAM;
		goto done;
	}
	Status = Xil_SMemCpy(Clk->Name, CopySize, Name, CopySize, CopySize);

done:
	return Status;
}

XStatus XPmClock_AddSubNode(u32 Id, u32 Type, u32 ControlReg, u8 Param1, u8 Param2, u32 Flags)
{
	XStatus Status = XST_FAILURE;
	u32 i = 0U;
	const XPm_OutClockNode *OutClkPtr = (XPm_OutClockNode *)XPmClock_GetById(Id);
	struct XPm_ClkTopologyNode *SubNodes;
	u16 DbgErr = XPM_INT_ERR_UNDEFINED;

	if ((OutClkPtr == NULL) ||
	    (OutClkPtr->Topology.Id != TOPOLOGY_CUSTOM))	{
		DbgErr = XPM_INT_ERR_INVALID_PARAM;
		Status = XST_INVALID_PARAM;
		goto done;
	}
	if ((Type <= (u32)TYPE_INVALID) || (Type >= (u32)TYPE_MAX) ||
	    (Type == (u32)TYPE_PLL)) {
		DbgErr = XPM_INT_ERR_INVALID_CLK_TYPE;
		Status = XST_INVALID_PARAM;
		goto done;
	}
	SubNodes = *OutClkPtr->Topology.Nodes;
	for (i=0; i<OutClkPtr->Topology.NumNodes; i++) {
		if (SubNodes[i].Type == 0U) {
			SubNodes[i].Type = (u8)Type;
			SubNodes[i].Reg = ControlReg;
			if (Type == (u32)TYPE_FIXEDFACTOR) {
				SubNodes[i].Param1.Mult = Param1;
				SubNodes[i].Param2.Div = Param2;
			} else {
				SubNodes[i].Param1.Shift = Param1;
				SubNodes[i].Param2.Width = Param2;
			}
			SubNodes[i].Clkflags = (u16)(Flags & 0xFFFFU);
			SubNodes[i].Typeflags = (u16)((Flags >> 16) & 0xFFFFU);
			SubNodes[i].Reg = ControlReg;
			break;
		}
	}
	if (i == OutClkPtr->Topology.NumNodes) {
		DbgErr = XPM_INT_ERR_CLK_TOPOLOGY_MAX_NUM_NODES;
		Status = XST_INVALID_PARAM;
		goto done;
	}

	Status = XST_SUCCESS;

done:
	XPm_PrintDbgErr(Status, DbgErr);
	return Status;
}

XStatus XPmClock_AddParent(u32 Id, const u32 *Parents, u8 NumParents)
{
	XStatus Status = XST_FAILURE;
	u32 Idx = 0;
	u32 LastParentIdx = 0;
	u16 ParentIdx = 0;
	const XPm_ClockNode *ParentClk = NULL;
	XPm_OutClockNode *ClkPtr = (XPm_OutClockNode *)XPmClock_GetById(Id);
	u16 DbgErr = XPM_INT_ERR_UNDEFINED;

	if ((ClkPtr == NULL) ||
	    (NumParents > MAX_MUX_PARENTS) ||
	    (NumParents == 0U)) {
		DbgErr = XPM_INT_ERR_INVALID_PARAM;
		Status = XST_INVALID_PARAM;
		goto done;
	}

	for (Idx = 0; Idx < NumParents; Idx++) {
		u32 ParentId = Parents[Idx];

		/*
		 * FIXME: For GEM0_RX and GEM1_RX parents are EMIO and MIO
		 * clocks and their IDs are 0 which is not valid clock ID.
		 * Consider 0 as a valid parent ID for now.
		 * Remove this condition once EMIO and MIO clocks are added
		 * as valid clocks.
		 */
		if (0U == ParentId) {
			continue;
		}

		if ((!ISOUTCLK(ParentId)) && (!ISREFCLK(ParentId)) &&
		    (!ISPLL(ParentId)) &&
		    ((u32)CLK_DUMMY_PARENT != ParentId)) {
			DbgErr = XPM_INT_ERR_INVALID_CLK_PARENT;
			Status = XST_INVALID_PARAM;
			goto done;
		}
	}

	/*
	 * For clocks which has more than 5 parents add parent command will call
	 * multiple times. Because from single command only 5 parents can add.
	 * So find parent index for second command from there remaining parents
	 * should be stored.
	 */
	while ((0U != ClkPtr->Topology.MuxSources[LastParentIdx]) &&
	       (MAX_MUX_PARENTS != LastParentIdx)) {
		LastParentIdx++;
	}

	/* Parents count should not be greater than clock's numbed of parents */
	if (((LastParentIdx + NumParents) > ClkPtr->ClkNode.NumParents) ||
	    (MAX_MUX_PARENTS == LastParentIdx)) {
		DbgErr = XPM_INT_ERR_MAX_CLK_PARENTS;
		Status = XST_INVALID_PARAM;
		goto done;
	}

	/* For clocks involving mux */
	for (Idx = 0; Idx < NumParents; Idx++) {
		if ((u32)CLK_DUMMY_PARENT == Parents[Idx]) {
			ParentIdx = (u16)CLK_DUMMY_PARENT;
		} else {
			ParentIdx = (u16)(NODEINDEX(Parents[Idx]));
		}
		ClkPtr->Topology.MuxSources[LastParentIdx] = ParentIdx;
		LastParentIdx++;
	}

	/* Assign default parent */
	if (ClkPtr->ClkNode.NumParents > 1U) {
		/*
		 * For mux clocks, parents are initialized when clock
		 * requested. So assign invalid clock parent by default.
		 */
		ClkPtr->ClkNode.ParentIdx = (u16)CLOCK_PARENT_INVALID;
	} else {
		ParentClk = XPmClock_GetByIdx(ClkPtr->Topology.MuxSources[0]);
		if (NULL != ParentClk) {
			ClkPtr->ClkNode.ParentIdx = (u16)(NODEINDEX(ParentClk->Node.Id));
		}
	}

	Status = XST_SUCCESS;

done:
	XPm_PrintDbgErr(Status, DbgErr);
	return Status;
}

XPm_ClockNode* XPmClock_GetById(u32 ClockId)
{
	u32 ClockIndex = NODEINDEX(ClockId);
	u32 NodeType = NODETYPE(ClockId);
	XPm_ClockNode *Clk = NULL;
	u32 MaskId = ((u32)XPM_NODETYPE_CLOCK_SUBNODE == NodeType) ?
		(~((u32)NODE_TYPE_MASK)) : ((~(u32)0x0));

	if (((u32)XPM_NODECLASS_CLOCK != NODECLASS(ClockId)) ||
	    (MaxClkNodes <= ClockIndex)) {
		goto done;
	}

	Clk = ClkNodeList[ClockIndex];
	if (NULL == Clk) {
		goto done;
	}

	/* Check that Clock's ID is same as given ID or not.
	 * NOTE:
	 * For ADD_CLOCK_SUBNODE command, we add the subnodes to the existing
	 * clock nodes in the database. These "existing" clock nodes are stored
	 * with a different node type than the 'XPM_NODETYPE_CLOCK_SUBNODE'
	 * which is passed into this function for retrieval of such nodes.
	 * So, we need to mask the type for this special case while validating.
	 * This is what MaskId does. For all other cases, it is all ones.
	 */
	if ((ClockId & MaskId) != (Clk->Node.Id & MaskId)) {
		Clk = NULL;
	}

done:
	return Clk;
}

XPm_ClockNode* XPmClock_GetByIdx(u32 ClockIdx)
{
        XPm_ClockNode *Clk = NULL;

        if(MaxClkNodes <= ClockIdx) {
                goto done;
        }

        Clk = ClkNodeList[ClockIdx];

done:
        return Clk;
}


XStatus XPmClock_SetById(u32 ClockId, XPm_ClockNode *Clk)
{
	XStatus Status = XST_INVALID_PARAM;
	u32 NodeIndex = NODEINDEX(ClockId);

	/*
	 * We assume that the Node ID class, subclass and type has _already_
	 * been validated before, so only check bounds here against index
	 */
	if ((NULL != Clk) && (MaxClkNodes > NodeIndex)) {
		ClkNodeList[NodeIndex] = Clk;
		PmNumClocks++;
		Status = XST_SUCCESS;
	}

	return Status;
}

XStatus XPmClock_CheckPermissions(u32 SubsystemIdx, u32 ClockId)
{
	XStatus Status = XST_FAILURE;
	const XPm_ClockNode *Clk;
	const XPm_ClockHandle *DevHandle;
	u32 PermissionMask = 0U;
	u16 DbgErr = XPM_INT_ERR_UNDEFINED;

	Clk = XPmClock_GetById(ClockId);
	if (NULL == Clk) {
		DbgErr = XPM_INT_ERR_INVALID_PARAM;
		Status = XST_INVALID_PARAM;
		goto done;
	}

	/* Check for read-only flag */
	if (0U != (CLK_FLAG_READ_ONLY & Clk->Flags)) {
		DbgErr = XPM_INT_ERR_READ_ONLY_CLK;
		Status = XPM_PM_NO_ACCESS;
		goto done;
	}

	/* Check for power domain of clock */
	if ((NULL != Clk->PwrDomain) &&
	    ((u8)XPM_POWER_STATE_ON != Clk->PwrDomain->Node.State)) {
		DbgErr = XPM_INT_ERR_PWR_DOMAIN_OFF;
		Status = XST_FAILURE;
		goto done;
	}

	if (ISPLL(ClockId)) {
		/* Do not allow permission by default when PLL is shared */
		DbgErr = XPM_INT_ERR_PLL_PERMISSION;
		Status = XPM_PM_NO_ACCESS;
		goto done;
	}

	DevHandle = Clk->ClkHandles;
	while (NULL != DevHandle) {
		/* Get permission mask which indicates permission for each subsystem */
		Status = XPmDevice_GetPermissions(DevHandle->Device,
						  &PermissionMask);
		if (XST_SUCCESS != Status) {
			DbgErr = XPM_INT_ERR_GET_DEVICE_PERMISSION;
			goto done;
		}

		DevHandle = DevHandle->NextDevice;
	}

	/* Check permission for given subsystem */
	if (0U == (PermissionMask & ((u32)1U << SubsystemIdx))) {
		DbgErr = XPM_INT_ERR_DEVICE_PERMISSION;
		Status = XPM_PM_NO_ACCESS;
		goto done;
	}

	/* Access is not allowed if resource is shared (multiple subsystems) */
	if (__builtin_popcount(PermissionMask) > 1) {
		DbgErr = XPM_INT_ERR_SHARED_RESOURCE;
		Status = XPM_PM_NO_ACCESS;
		goto done;
	}

	Status = XST_SUCCESS;

done:
	XPm_PrintDbgErr(Status, DbgErr);
	return Status;
}
