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
	std::shared_ptr<Register32_t>			 mR0;
	std::shared_ptr<Register32_t>			 mR1;
	std::shared_ptr<Register32_t>			 mR2;
	std::shared_ptr<Register32_t>			 mR3;
	std::shared_ptr<Register32_t>			 mC0;
	std::shared_ptr<Register32_t>			 mC1;
	std::shared_ptr<Register32_t>			 mC2;
	std::shared_ptr<Register32_t>			 mC3;
	std::shared_ptr<VifUnitRegister_CYCLE_t> mCYCLE;
	std::shared_ptr<VifUnitRegister_MASK_t>  mMASK;
	std::shared_ptr<VifUnitRegister_MODE_t>  mMODE;
	std::shared_ptr<VifUnitRegister_ITOP_t>  mITOP;
	std::shared_ptr<VifUnitRegister_ITOPS_t> mITOPS;
	std::shared_ptr<VifUnitRegister_BASE_t>  mBASE;
	std::shared_ptr<VifUnitRegister_OFST_t>  mOFST;
	std::shared_ptr<VifUnitRegister_TOP_t>   mTOP;
	std::shared_ptr<VifUnitRegister_TOPS_t>  mTOPS;
	std::shared_ptr<VifUnitRegister_MASK_t>  mMARK;
	std::shared_ptr<VifUnitRegister_NUM_t>   mNUM;
	std::shared_ptr<VifUnitRegister_CODE_t>  mCODE;
	std::shared_ptr<VifUnitRegister_STAT_t>  mSTAT;
	std::shared_ptr<VifUnitRegister_FBRST_t> mFBRST;
	std::shared_ptr<VifUnitRegister_ERR_t>   mERR;
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