#include <memory>

#include "Resources/EE/VPU/VIF/Types/VIFCores_t.h"
#include "Resources/EE/VPU/VIF/Types/VIFCoreRegisters_t.h"

VIFCore_t::VIFCore_t(const int vifCoreID) :
	mVIFCoreID(vifCoreID),
	R0(nullptr),
	R1(nullptr),
	R2(nullptr),
	R3(nullptr),
	C0(nullptr),
	C1(nullptr),
	C2(nullptr),
	C3(nullptr),
	CYCLE(nullptr),
	MASK(nullptr),
	MODE(nullptr),
	ITOP(nullptr),
	ITOPS(nullptr),
	BASE(nullptr),
	OFST(nullptr),
	TOP(nullptr),
	TOPS(nullptr),
	MARK(nullptr),
	NUM(nullptr),
	CODE(nullptr),
	STAT(nullptr),
	FBRST(nullptr),
	ERR(nullptr)
{
}

VIFCore_VIF0_t::VIFCore_VIF0_t() :
	VIFCore_t(CORE_ID)
{
	R0 = std::make_shared<Register32_t>("VIF0 R0", false, false);
	R1 = std::make_shared<Register32_t>("VIF0 R1", false, false);
	R2 = std::make_shared<Register32_t>("VIF0 R2", false, false);
	R3 = std::make_shared<Register32_t>("VIF0 R3", false, false);
	C0 = std::make_shared<Register32_t>("VIF0 C0", false, false);
	C1 = std::make_shared<Register32_t>("VIF0 C1", false, false);
	C2 = std::make_shared<Register32_t>("VIF0 C2", false, false);
	C3 = std::make_shared<Register32_t>("VIF0 C3", false, false);
	CYCLE = std::make_shared<VIFCoreRegister_CYCLE_t>("VIF0 CYCLE", false, false);
	MASK = std::make_shared<VIFCoreRegister_MASK_t>("VIF0 MASK", false, false);
	MODE = std::make_shared<VIFCoreRegister_MODE_t>("VIF0 MODE", false, false);
	ITOP = std::make_shared<VIFCoreRegister_ITOP_t>("VIF0 ITOP", false, false);
	ITOPS = std::make_shared<VIFCoreRegister_ITOPS_t>("VIF0 ITOPS", false, false);
	BASE = std::make_shared<VIFCoreRegister_BASE_t>("VIF0 BASE", false, false);
	OFST = std::make_shared<VIFCoreRegister_OFST_t>("VIF0 OFST", false, false);
	TOP = std::make_shared<VIFCoreRegister_TOP_t>("VIF0 TOP", false, false);
	TOPS = std::make_shared<VIFCoreRegister_TOPS_t>("VIF0 TOPS", false, false);
	MARK = std::make_shared<VIFCoreRegister_MASK_t>("VIF0 MARK", false, false);
	NUM = std::make_shared<VIFCoreRegister_NUM_t>("VIF0 NUM", false, false);
	CODE = std::make_shared<VIFCoreRegister_CODE_t>("VIF0 CODE", false, false);
	STAT = std::make_shared<VIFCoreRegister_STAT_t>("VIF0 STAT", false, false);
	FBRST = std::make_shared<VIFCoreRegister_FBRST_t>("VIF0 FBRST", false, false);
	ERR = std::make_shared<VIFCoreRegister_ERR_t>("VIF0 ERR", false, false);
}

VIFCore_VIF1_t::VIFCore_VIF1_t() :
	VIFCore_t(CORE_ID)
{
	R0 = std::make_shared<Register32_t>("VIF1 R0", false, false);
	R1 = std::make_shared<Register32_t>("VIF1 R1", false, false);
	R2 = std::make_shared<Register32_t>("VIF1 R2", false, false);
	R3 = std::make_shared<Register32_t>("VIF1 R3", false, false);
	C0 = std::make_shared<Register32_t>("VIF1 C0", false, false);
	C1 = std::make_shared<Register32_t>("VIF1 C1", false, false);
	C2 = std::make_shared<Register32_t>("VIF1 C2", false, false);
	C3 = std::make_shared<Register32_t>("VIF1 C3", false, false);
	CYCLE = std::make_shared<VIFCoreRegister_CYCLE_t>("VIF1 CYCLE", false, false);
	MASK = std::make_shared<VIFCoreRegister_MASK_t>("VIF1 MASK", false, false);
	MODE = std::make_shared<VIFCoreRegister_MODE_t>("VIF1 MODE", false, false);
	ITOP = std::make_shared<VIFCoreRegister_ITOP_t>("VIF1 ITOP", false, false);
	ITOPS = std::make_shared<VIFCoreRegister_ITOPS_t>("VIF1 ITOPS", false, false);
	BASE = std::make_shared<VIFCoreRegister_BASE_t>("VIF1 BASE", false, false);
	OFST = std::make_shared<VIFCoreRegister_OFST_t>("VIF1 OFST", false, false);
	TOP = std::make_shared<VIFCoreRegister_TOP_t>("VIF1 TOP", false, false);
	TOPS = std::make_shared<VIFCoreRegister_TOPS_t>("VIF1 TOPS", false, false);
	MARK = std::make_shared<VIFCoreRegister_MASK_t>("VIF1 MARK", false, false);
	NUM = std::make_shared<VIFCoreRegister_NUM_t>("VIF1 NUM", false, false);
	CODE = std::make_shared<VIFCoreRegister_CODE_t>("VIF1 CODE", false, false);
	STAT = std::make_shared<VIFCoreRegister_STAT_t>("VIF1 STAT", false, false);
	FBRST = std::make_shared<VIFCoreRegister_FBRST_t>("VIF1 FBRST", false, false);
	ERR = std::make_shared<VIFCoreRegister_ERR_t>("VIF1 ERR", false, false);
}
