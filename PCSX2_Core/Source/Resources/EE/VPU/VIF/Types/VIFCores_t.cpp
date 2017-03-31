#include "stdafx.h"

#include <memory>

#include "Resources/EE/VPU/VIF/Types/VIFCores_t.h"
#include "Resources/EE/VPU/VIF/Types/VIFCoreRegisters_t.h"

VIFCore_t::VIFCore_t(const int vifCoreID) :
	mVIFCoreID(vifCoreID),
	R0(std::make_shared<Register32_t>()),
	R1(std::make_shared<Register32_t>()),
	R2(std::make_shared<Register32_t>()),
	R3(std::make_shared<Register32_t>()),
	C0(std::make_shared<Register32_t>()),
	C1(std::make_shared<Register32_t>()),
	C2(std::make_shared<Register32_t>()),
	C3(std::make_shared<Register32_t>()),
	CYCLE(std::make_shared<VIFCoreRegister_CYCLE_t>()),
	MASK(std::make_shared<VIFCoreRegister_MASK_t>()),
	MODE(std::make_shared<VIFCoreRegister_MODE_t>()),
	ITOP(std::make_shared<VIFCoreRegister_ITOP_t>()),
	ITOPS(std::make_shared<VIFCoreRegister_ITOPS_t>()),
	BASE(std::make_shared<VIFCoreRegister_BASE_t>()),
	OFST(std::make_shared<VIFCoreRegister_OFST_t>()),
	TOP(std::make_shared<VIFCoreRegister_TOP_t>()),
	TOPS(std::make_shared<VIFCoreRegister_TOPS_t>()),
	MARK(std::make_shared<VIFCoreRegister_MASK_t>()),
	NUM(std::make_shared<VIFCoreRegister_NUM_t>()),
	CODE(std::make_shared<VIFCoreRegister_CODE_t>()),
	STAT(std::make_shared<VIFCoreRegister_STAT_t>()),
	FBRST(std::make_shared<VIFCoreRegister_FBRST_t>()),
	ERR(std::make_shared<VIFCoreRegister_ERR_t>())
{
}

VIFCore_VIF0_t::VIFCore_VIF0_t() :
	VIFCore_t(CORE_ID)
{
}

VIFCore_VIF1_t::VIFCore_VIF1_t() :
	VIFCore_t(CORE_ID)
{
}
