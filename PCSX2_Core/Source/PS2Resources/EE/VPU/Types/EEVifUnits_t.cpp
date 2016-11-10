#include "stdafx.h"

#include <memory>

#include "PS2Resources/EE/VPU/Types/EEVifUnits_t.h"
#include "PS2Resources/EE/VPU/Types/EEVifUnitRegisters_t.h"

EEVifUnit_t::EEVifUnit_t(const u32 & unitID) :
	mUnitID(unitID),
	mR0(std::make_shared<EEVifUnitRegister_R_t>()),
	mR1(std::make_shared<EEVifUnitRegister_R_t>()),
	mR2(std::make_shared<EEVifUnitRegister_R_t>()),
	mR3(std::make_shared<EEVifUnitRegister_R_t>()),
	mC0(std::make_shared<EEVifUnitRegister_C_t>()),
	mC1(std::make_shared<EEVifUnitRegister_C_t>()),
	mC2(std::make_shared<EEVifUnitRegister_C_t>()),
	mC3(std::make_shared<EEVifUnitRegister_C_t>()),
	mCYCLE(std::make_shared<EEVifUnitRegister_CYCLE_t>()),
	mMASK(std::make_shared<EEVifUnitRegister_MASK_t>()),
	mMODE(std::make_shared<EEVifUnitRegister_MODE_t>()),
	mITOP(std::make_shared<EEVifUnitRegister_ITOP_t>()),
	mITOPS(std::make_shared<EEVifUnitRegister_ITOPS_t>()),
	mBASE(std::make_shared<EEVifUnitRegister_BASE_t>()),
	mOFST(std::make_shared<EEVifUnitRegister_OFST_t>()),
	mTOP(std::make_shared<EEVifUnitRegister_TOP_t>()),
	mTOPS(std::make_shared<EEVifUnitRegister_TOPS_t>()),
	mMARK(std::make_shared<EEVifUnitRegister_MASK_t>()),
	mNUM(std::make_shared<EEVifUnitRegister_NUM_t>()),
	mCODE(std::make_shared<EEVifUnitRegister_CODE_t>()),
	mSTAT(std::make_shared<EEVifUnitRegister_STAT_t>()),
	mFBRST(std::make_shared<EEVifUnitRegister_FBRST_t>()),
	mERR(std::make_shared<EEVifUnitRegister_ERR_t>())
{
}

EEVifUnit_0_t::EEVifUnit_0_t() :
	EEVifUnit_t(UNIT_ID)
{
}

EEVifUnit_1_t::EEVifUnit_1_t() :
	EEVifUnit_t(UNIT_ID)
{
}
