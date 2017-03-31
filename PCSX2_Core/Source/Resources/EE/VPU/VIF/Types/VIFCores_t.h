#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class Register32_t;
class VIFCoreRegister_CYCLE_t;
class VIFCoreRegister_MASK_t;
class VIFCoreRegister_MODE_t;
class VIFCoreRegister_ITOP_t;
class VIFCoreRegister_ITOPS_t;
class VIFCoreRegister_BASE_t;
class VIFCoreRegister_OFST_t;
class VIFCoreRegister_TOP_t;
class VIFCoreRegister_TOPS_t;
class VIFCoreRegister_MARK_t;
class VIFCoreRegister_NUM_t;
class VIFCoreRegister_CODE_t;
class VIFCoreRegister_STAT_t;
class VIFCoreRegister_FBRST_t;
class VIFCoreRegister_ERR_t;

/*
A base class for an implementation of a VIF unit.
Extended by EEVpuVif0_t and EEVpuVif1_t.
*/
class VIFCore_t
{
public:
	explicit VIFCore_t(const int vifCoreID);

	/*
	ID of the VIF unit. Currently used for debug.
	*/
	int mVIFCoreID;

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
	std::shared_ptr<VIFCoreRegister_CYCLE_t> CYCLE;
	std::shared_ptr<VIFCoreRegister_MASK_t>  MASK;
	std::shared_ptr<VIFCoreRegister_MODE_t>  MODE;
	std::shared_ptr<VIFCoreRegister_ITOP_t>  ITOP;
	std::shared_ptr<VIFCoreRegister_ITOPS_t> ITOPS;
	std::shared_ptr<VIFCoreRegister_BASE_t>  BASE;
	std::shared_ptr<VIFCoreRegister_OFST_t>  OFST;
	std::shared_ptr<VIFCoreRegister_TOP_t>   TOP;
	std::shared_ptr<VIFCoreRegister_TOPS_t>  TOPS;
	std::shared_ptr<VIFCoreRegister_MASK_t>  MARK;
	std::shared_ptr<VIFCoreRegister_NUM_t>   NUM;
	std::shared_ptr<VIFCoreRegister_CODE_t>  CODE;
	std::shared_ptr<VIFCoreRegister_STAT_t>  STAT;
	std::shared_ptr<VIFCoreRegister_FBRST_t> FBRST;
	std::shared_ptr<VIFCoreRegister_ERR_t>   ERR;
};

/*
Represents the VIF0 unit.
All registers are defined for VIF0 except for BASE, OFST, TOP and TOPS.
*/
class VIFCore_VIF0_t : public VIFCore_t
{
public:
	explicit VIFCore_VIF0_t();

	static constexpr int CORE_ID = 0;
};

/*
Represents the VIF1 unit.
All registers are defined for VIF1.
*/
class VIFCore_VIF1_t : public VIFCore_t
{
public:
	explicit VIFCore_VIF1_t();

	static constexpr int CORE_ID = 1;
};