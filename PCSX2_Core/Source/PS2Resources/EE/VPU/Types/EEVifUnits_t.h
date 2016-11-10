#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class EEVifUnitRegister_R_t;
class EEVifUnitRegister_C_t;
class EEVifUnitRegister_CYCLE_t;
class EEVifUnitRegister_MASK_t;
class EEVifUnitRegister_MODE_t;
class EEVifUnitRegister_ITOP_t;
class EEVifUnitRegister_ITOPS_t;
class EEVifUnitRegister_BASE_t;
class EEVifUnitRegister_OFST_t;
class EEVifUnitRegister_TOP_t;
class EEVifUnitRegister_TOPS_t;
class EEVifUnitRegister_MARK_t;
class EEVifUnitRegister_NUM_t;
class EEVifUnitRegister_CODE_t;
class EEVifUnitRegister_STAT_t;
class EEVifUnitRegister_FBRST_t;
class EEVifUnitRegister_ERR_t;

/*
A base class for an implementation of a VIF unit.
Extended by EEVpuVif0_t and EEVpuVif1_t.
*/
class EEVifUnit_t
{
public:
	explicit EEVifUnit_t(const u32 & unitID);

	/*
	ID of the VIF unit. Currently used for debug.
	*/
	const u32 mUnitID;

	/*
	VIF registers. See page 124 of EE Users Manual.
	Implementing classes will set some of these to null (ie: VIF0 sets REGISTER_TOP to null).
	*/
	std::shared_ptr<EEVifUnitRegister_R_t>     mR0;
	std::shared_ptr<EEVifUnitRegister_R_t>     mR1;
	std::shared_ptr<EEVifUnitRegister_R_t>     mR2;
	std::shared_ptr<EEVifUnitRegister_R_t>     mR3;
	std::shared_ptr<EEVifUnitRegister_C_t>     mC0;
	std::shared_ptr<EEVifUnitRegister_C_t>     mC1;
	std::shared_ptr<EEVifUnitRegister_C_t>     mC2;
	std::shared_ptr<EEVifUnitRegister_C_t>     mC3;
	std::shared_ptr<EEVifUnitRegister_CYCLE_t> mCYCLE;
	std::shared_ptr<EEVifUnitRegister_MASK_t>  mMASK;
	std::shared_ptr<EEVifUnitRegister_MODE_t>  mMODE;
	std::shared_ptr<EEVifUnitRegister_ITOP_t>  mITOP;
	std::shared_ptr<EEVifUnitRegister_ITOPS_t> mITOPS;
	std::shared_ptr<EEVifUnitRegister_BASE_t>  mBASE;
	std::shared_ptr<EEVifUnitRegister_OFST_t>  mOFST;
	std::shared_ptr<EEVifUnitRegister_TOP_t>   mTOP;
	std::shared_ptr<EEVifUnitRegister_TOPS_t>  mTOPS;
	std::shared_ptr<EEVifUnitRegister_MASK_t>  mMARK;
	std::shared_ptr<EEVifUnitRegister_NUM_t>   mNUM;
	std::shared_ptr<EEVifUnitRegister_CODE_t>  mCODE;
	std::shared_ptr<EEVifUnitRegister_STAT_t>  mSTAT;
	std::shared_ptr<EEVifUnitRegister_FBRST_t> mFBRST;
	std::shared_ptr<EEVifUnitRegister_ERR_t>   mERR;
};

/*
Represents the VIF0 unit.
All registers are defined for VIF0 except for BASE, OFST, TOP and TOPS.
*/
class EEVifUnit_0_t : public EEVifUnit_t
{
public:
	explicit EEVifUnit_0_t();

	static constexpr u32 UNIT_ID = 0;
};

/*
Represents the VIF1 unit.
All registers are defined for VIF1.
*/
class EEVifUnit_1_t : public EEVifUnit_t
{
public:
	explicit EEVifUnit_1_t();

	static constexpr u32 UNIT_ID = 1;
};