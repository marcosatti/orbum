#include "stdafx.h"

#include <memory>

#include "PS2Resources/EE/VPU/Types/VifUnits_t.h"
#include "PS2Resources/EE/VPU/Types/VifUnitRegisters_t.h"

VifUnit_t::VifUnit_t(const u32 & unitID) :
	mUnitID(unitID),
	mR0(std::make_shared<VifUnitRegister_R_t>()),
	mR1(std::make_shared<VifUnitRegister_R_t>()),
	mR2(std::make_shared<VifUnitRegister_R_t>()),
	mR3(std::make_shared<VifUnitRegister_R_t>()),
	mC0(std::make_shared<VifUnitRegister_C_t>()),
	mC1(std::make_shared<VifUnitRegister_C_t>()),
	mC2(std::make_shared<VifUnitRegister_C_t>()),
	mC3(std::make_shared<VifUnitRegister_C_t>()),
	mCYCLE(std::make_shared<VifUnitRegister_CYCLE_t>()),
	mMASK(std::make_shared<VifUnitRegister_MASK_t>()),
	mMODE(std::make_shared<VifUnitRegister_MODE_t>()),
	mITOP(std::make_shared<VifUnitRegister_ITOP_t>()),
	mITOPS(std::make_shared<VifUnitRegister_ITOPS_t>()),
	mBASE(std::make_shared<VifUnitRegister_BASE_t>()),
	mOFST(std::make_shared<VifUnitRegister_OFST_t>()),
	mTOP(std::make_shared<VifUnitRegister_TOP_t>()),
	mTOPS(std::make_shared<VifUnitRegister_TOPS_t>()),
	mMARK(std::make_shared<VifUnitRegister_MASK_t>()),
	mNUM(std::make_shared<VifUnitRegister_NUM_t>()),
	mCODE(std::make_shared<VifUnitRegister_CODE_t>()),
	mSTAT(std::make_shared<VifUnitRegister_STAT_t>()),
	mFBRST(std::make_shared<VifUnitRegister_FBRST_t>()),
	mERR(std::make_shared<VifUnitRegister_ERR_t>())
{
}

VifUnit_VIF0_t::VifUnit_VIF0_t() :
	VifUnit_t(UNIT_ID)
{
}

VifUnit_VIF1_t::VifUnit_VIF1_t() :
	VifUnit_t(UNIT_ID)
{
}
