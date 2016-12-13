#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class Register32_t;
class VifUnitRegister_CYCLE_t;
class VifUnitRegister_MASK_t;
class VifUnitRegister_MODE_t;
class VifUnitRegister_ITOP_t;
class VifUnitRegister_ITOPS_t;
class VifUnitRegister_BASE_t;
class VifUnitRegister_OFST_t;
class VifUnitRegister_TOP_t;
class VifUnitRegister_TOPS_t;
class VifUnitRegister_MARK_t;
class VifUnitRegister_NUM_t;
class VifUnitRegister_CODE_t;
class VifUnitRegister_STAT_t;
class VifUnitRegister_FBRST_t;
class VifUnitRegister_ERR_t;

/*
A base class for an implementation of a VIF unit.
Extended by EEVpuVif0_t and EEVpuVif1_t.
*/
class VifUnit_t
{
public:
	explicit VifUnit_t(const u32 & unitID);

	/*
	ID of the VIF unit. Currently used for debug.
	*/
	const u32 mUnitID;

	/*
	VIF registers. See page 124 of EE Users Manual.
	Implementing classes will set some of these to null (ie: VIF0 sets REGISTER_TOP to null).
	*/
	std::shared_ptr<Register32_t>			 R0;
	std::shared_ptr<Register32_t>			 R1;
	std::shared_ptr<Register32_t>			 R2;
	std::shared_ptr<Register32_t>			 R3;
	std::shared_ptr<Register32_t>			 C0;
	std::shared_ptr<Register32_t>			 C1;
	std::shared_ptr<Register32_t>			 C2;
	std::shared_ptr<Register32_t>			 C3;
	std::shared_ptr<VifUnitRegister_CYCLE_t> CYCLE;
	std::shared_ptr<VifUnitRegister_MASK_t>  MASK;
	std::shared_ptr<VifUnitRegister_MODE_t>  MODE;
	std::shared_ptr<VifUnitRegister_ITOP_t>  ITOP;
	std::shared_ptr<VifUnitRegister_ITOPS_t> ITOPS;
	std::shared_ptr<VifUnitRegister_BASE_t>  BASE;
	std::shared_ptr<VifUnitRegister_OFST_t>  OFST;
	std::shared_ptr<VifUnitRegister_TOP_t>   TOP;
	std::shared_ptr<VifUnitRegister_TOPS_t>  TOPS;
	std::shared_ptr<VifUnitRegister_MASK_t>  MARK;
	std::shared_ptr<VifUnitRegister_NUM_t>   NUM;
	std::shared_ptr<VifUnitRegister_CODE_t>  CODE;
	std::shared_ptr<VifUnitRegister_STAT_t>  STAT;
	std::shared_ptr<VifUnitRegister_FBRST_t> FBRST;
	std::shared_ptr<VifUnitRegister_ERR_t>   ERR;
};

/*
Represents the VIF0 unit.
All registers are defined for VIF0 except for BASE, OFST, TOP and TOPS.
*/
class VifUnit_VIF0_t : public VifUnit_t
{
public:
	explicit VifUnit_VIF0_t();

	static constexpr u32 UNIT_ID = 0;
};

/*
Represents the VIF1 unit.
All registers are defined for VIF1.
*/
class VifUnit_VIF1_t : public VifUnit_t
{
public:
	explicit VifUnit_VIF1_t();

	static constexpr u32 UNIT_ID = 1;
};