#include "Common/Types/Register/Register128_t.h"
#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/Register/Register16_t.h"
#include "Common/Types/Register/PCRegister16_t.h"
#include "Common/Types/Memory/ByteMemory_t.h"
#include "Common/Types/ByteMMU/ByteMMU_t.h"
#include "Common/Types/Register/ConstantRegister128_t.h"
#include "Common/Types/Register/ConstantRegister16_t.h"

#include "Resources/EE/VPU/VU/Types/VUCores_t.h"
#include "Resources/EE/VPU/VU/Types/VUCoreRegisters_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

VUCore_t::VUCore_t(const int vuCoreID) :
	mVUCoreID(vuCoreID),
	VF{ },
	VI{ },
	ACC(nullptr),
	I(nullptr),
	Q(nullptr),
	R(nullptr),
	P(nullptr),
	Status(nullptr),
	MAC(nullptr),
	Clipping(nullptr),
	PC(nullptr),
	CMSAR(nullptr),
	MMU(std::make_shared<ByteMMU_t>(15, 6, 4)), // Number of page index bits optimised for minimum memory usage (Marco Satti).
	MEMORY_Micro(nullptr),
	MEMORY_Mem(nullptr)
{
}

VUCore_VU0_t::VUCore_VU0_t(const std::shared_ptr<EECoreCOP0_t> & cop0) :
	VUCore_t(CORE_ID),
	COP0(cop0)
{
	VF[0] = std::make_shared<ConstantRegister128_t>("VU0 VF0", false, false);
	VF[1] = std::make_shared<Register128_t>("VU0 VF1", false, false);
	VF[2] = std::make_shared<Register128_t>("VU0 VF2", false, false);
	VF[3] = std::make_shared<Register128_t>("VU0 VF3", false, false);
	VF[4] = std::make_shared<Register128_t>("VU0 VF4", false, false);
	VF[5] = std::make_shared<Register128_t>("VU0 VF5", false, false);
	VF[6] = std::make_shared<Register128_t>("VU0 VF6", false, false);
	VF[7] = std::make_shared<Register128_t>("VU0 VF7", false, false);
	VF[8] = std::make_shared<Register128_t>("VU0 VF8", false, false);
	VF[9] = std::make_shared<Register128_t>("VU0 VF9", false, false);
	VF[10] = std::make_shared<Register128_t>("VU0 VF10", false, false);
	VF[11] = std::make_shared<Register128_t>("VU0 VF11", false, false);
	VF[12] = std::make_shared<Register128_t>("VU0 VF12", false, false);
	VF[13] = std::make_shared<Register128_t>("VU0 VF13", false, false);
	VF[14] = std::make_shared<Register128_t>("VU0 VF14", false, false);
	VF[15] = std::make_shared<Register128_t>("VU0 VF15", false, false);
	VF[16] = std::make_shared<Register128_t>("VU0 VF16", false, false);
	VF[17] = std::make_shared<Register128_t>("VU0 VF17", false, false);
	VF[18] = std::make_shared<Register128_t>("VU0 VF18", false, false);
	VF[19] = std::make_shared<Register128_t>("VU0 VF19", false, false);
	VF[20] = std::make_shared<Register128_t>("VU0 VF20", false, false);
	VF[21] = std::make_shared<Register128_t>("VU0 VF21", false, false);
	VF[22] = std::make_shared<Register128_t>("VU0 VF22", false, false);
	VF[23] = std::make_shared<Register128_t>("VU0 VF23", false, false);
	VF[24] = std::make_shared<Register128_t>("VU0 VF24", false, false);
	VF[25] = std::make_shared<Register128_t>("VU0 VF25", false, false);
	VF[26] = std::make_shared<Register128_t>("VU0 VF26", false, false);
	VF[27] = std::make_shared<Register128_t>("VU0 VF27", false, false);
	VF[28] = std::make_shared<Register128_t>("VU0 VF28", false, false);
	VF[29] = std::make_shared<Register128_t>("VU0 VF29", false, false);
	VF[30] = std::make_shared<Register128_t>("VU0 VF30", false, false);
	VF[31] = std::make_shared<Register128_t>("VU0 VF31", false, false);

	VI[0] = std::make_shared<ConstantRegister16_t>("VU0 VI0", false, false);
	VI[1] = std::make_shared<Register16_t>("VU0 VI1", false, false);
	VI[2] = std::make_shared<Register16_t>("VU0 VI2", false, false);
	VI[3] = std::make_shared<Register16_t>("VU0 VI3", false, false);
	VI[4] = std::make_shared<Register16_t>("VU0 VI4", false, false);
	VI[5] = std::make_shared<Register16_t>("VU0 VI5", false, false);
	VI[6] = std::make_shared<Register16_t>("VU0 VI6", false, false);
	VI[7] = std::make_shared<Register16_t>("VU0 VI7", false, false);
	VI[8] = std::make_shared<Register16_t>("VU0 VI8", false, false);
	VI[9] = std::make_shared<Register16_t>("VU0 VI9", false, false);
	VI[10] = std::make_shared<Register16_t>("VU0 VI10", false, false);
	VI[11] = std::make_shared<Register16_t>("VU0 VI11", false, false);
	VI[12] = std::make_shared<Register16_t>("VU0 VI12", false, false);
	VI[13] = std::make_shared<Register16_t>("VU0 VI13", false, false);
	VI[14] = std::make_shared<Register16_t>("VU0 VI14", false, false);
	VI[15] = std::make_shared<Register16_t>("VU0 VI15", false, false);

	ACC = std::make_shared<Register128_t>("VU0 ACC", false, false);
	I = std::make_shared<Register32_t>("VU0 I", false, false);
	Q = std::make_shared<Register32_t>("VU0 Q", false, false);
	R = std::make_shared<Register32_t>("VU0 R", false, false);
	P = std::make_shared<Register32_t>("VU0 P", false, false);
	Status = std::make_shared<VUCoreRegister_Status_t>("VU0 Status", false, false);
	MAC = std::make_shared<VUCoreRegister_MAC_t>("VU0 MAC", false, false, Status);
	Clipping = std::make_shared<VUCoreRegister_Clipping_t>("VU0 Clipping", false, false);
	PC = std::make_shared<PCRegister16_t>("VU0 PC", false, false);
	CMSAR = std::make_shared<VUCoreRegister_CMSAR_t>("VU0 CMSAR", false, false);

	MEMORY_Micro = std::make_shared<ByteMemory_t>("VU0 Micro Mem", false, false, Constants::SIZE_4KB);
	MEMORY_Mem = std::make_shared<ByteMemory_t>("VU0 Main Mem", false, false, Constants::SIZE_4KB);
}

bool VUCore_VU0_t::isCoprocessorUsable(const System_t context) const
{
	// Check that CU[bit 2] == 1 (ie: >0) in the status register.
	if ((COP0->Status->getFieldValue(context, EECoreCOP0Register_Status_t::Fields::CU) & 0x4) > 0)
		return true;
	else
		return false;
}

VUCore_VU1_t::VUCore_VU1_t() :
	VUCore_t(CORE_ID)
{
	VF[0] = std::make_shared<ConstantRegister128_t>("VU1 VF0", false, false);
	VF[1] = std::make_shared<Register128_t>("VU1 VF1", false, false);
	VF[2] = std::make_shared<Register128_t>("VU1 VF2", false, false);
	VF[3] = std::make_shared<Register128_t>("VU1 VF3", false, false);
	VF[4] = std::make_shared<Register128_t>("VU1 VF4", false, false);
	VF[5] = std::make_shared<Register128_t>("VU1 VF5", false, false);
	VF[6] = std::make_shared<Register128_t>("VU1 VF6", false, false);
	VF[7] = std::make_shared<Register128_t>("VU1 VF7", false, false);
	VF[8] = std::make_shared<Register128_t>("VU1 VF8", false, false);
	VF[9] = std::make_shared<Register128_t>("VU1 VF9", false, false);
	VF[10] = std::make_shared<Register128_t>("VU1 VF10", false, false);
	VF[11] = std::make_shared<Register128_t>("VU1 VF11", false, false);
	VF[12] = std::make_shared<Register128_t>("VU1 VF12", false, false);
	VF[13] = std::make_shared<Register128_t>("VU1 VF13", false, false);
	VF[14] = std::make_shared<Register128_t>("VU1 VF14", false, false);
	VF[15] = std::make_shared<Register128_t>("VU1 VF15", false, false);
	VF[16] = std::make_shared<Register128_t>("VU1 VF16", false, false);
	VF[17] = std::make_shared<Register128_t>("VU1 VF17", false, false);
	VF[18] = std::make_shared<Register128_t>("VU1 VF18", false, false);
	VF[19] = std::make_shared<Register128_t>("VU1 VF19", false, false);
	VF[20] = std::make_shared<Register128_t>("VU1 VF20", false, false);
	VF[21] = std::make_shared<Register128_t>("VU1 VF21", false, false);
	VF[22] = std::make_shared<Register128_t>("VU1 VF22", false, false);
	VF[23] = std::make_shared<Register128_t>("VU1 VF23", false, false);
	VF[24] = std::make_shared<Register128_t>("VU1 VF24", false, false);
	VF[25] = std::make_shared<Register128_t>("VU1 VF25", false, false);
	VF[26] = std::make_shared<Register128_t>("VU1 VF26", false, false);
	VF[27] = std::make_shared<Register128_t>("VU1 VF27", false, false);
	VF[28] = std::make_shared<Register128_t>("VU1 VF28", false, false);
	VF[29] = std::make_shared<Register128_t>("VU1 VF29", false, false);
	VF[30] = std::make_shared<Register128_t>("VU1 VF30", false, false);
	VF[31] = std::make_shared<Register128_t>("VU1 VF31", false, false);

	VI[0] = std::make_shared<ConstantRegister16_t>("VU1 VI0", false, false);
	VI[1] = std::make_shared<Register16_t>("VU1 VI1", false, false);
	VI[2] = std::make_shared<Register16_t>("VU1 VI2", false, false);
	VI[3] = std::make_shared<Register16_t>("VU1 VI3", false, false);
	VI[4] = std::make_shared<Register16_t>("VU1 VI4", false, false);
	VI[5] = std::make_shared<Register16_t>("VU1 VI5", false, false);
	VI[6] = std::make_shared<Register16_t>("VU1 VI6", false, false);
	VI[7] = std::make_shared<Register16_t>("VU1 VI7", false, false);
	VI[8] = std::make_shared<Register16_t>("VU1 VI8", false, false);
	VI[9] = std::make_shared<Register16_t>("VU1 VI9", false, false);
	VI[10] = std::make_shared<Register16_t>("VU1 VI10", false, false);
	VI[11] = std::make_shared<Register16_t>("VU1 VI11", false, false);
	VI[12] = std::make_shared<Register16_t>("VU1 VI12", false, false);
	VI[13] = std::make_shared<Register16_t>("VU1 VI13", false, false);
	VI[14] = std::make_shared<Register16_t>("VU1 VI14", false, false);
	VI[15] = std::make_shared<Register16_t>("VU1 VI15", false, false);

	ACC = std::make_shared<Register128_t>("VU1 ACC", false, false);
	I = std::make_shared<Register32_t>("VU1 I", false, false);
	Q = std::make_shared<Register32_t>("VU1 Q", false, false);
	R = std::make_shared<Register32_t>("VU1 R", false, false);
	P = std::make_shared<Register32_t>("VU1 P", false, false);
	Status = std::make_shared<VUCoreRegister_Status_t>("VU1 Status", false, false);
	MAC = std::make_shared<VUCoreRegister_MAC_t>("VU1 MAC", false, false, Status);
	Clipping = std::make_shared<VUCoreRegister_Clipping_t>("VU1 Clipping", false, false);
	PC = std::make_shared<PCRegister16_t>("VU1 PC", false, false);
	CMSAR = std::make_shared<VUCoreRegister_CMSAR_t>("VU1 CMSAR", false, false);

	MEMORY_Micro = std::make_shared<ByteMemory_t>("VU1 Micro Mem", false, false, Constants::SIZE_16KB);
	MEMORY_Mem = std::make_shared<ByteMemory_t>("VU1 Main Mem", false, false, Constants::SIZE_16KB);
}
