#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/Register/SizedHwordRegister.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Bus/ByteBus.hpp"

#include "Resources/Ee/Vpu/VuCores.hpp"
#include "Resources/Ee/Vpu/VuCoreRegisters.hpp"
#include "Resources/Ee/Core/EeCoreCop0.hpp"
#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"

VuCore_Base::VuCore_Base(const int core_id) :
	core_id(core_id),
	bus(6, 4) // Number of page index bits optimised for minimum memory usage.
{
}

VuCore_Vu0::VuCore_Vu0(const int core_id) :
	VuCore_Base(core_id),
	memory_micro(Constants::SIZE_4KB),
	memory_mem(Constants::SIZE_4KB),
	ccr{nullptr},
	cop0(nullptr)
{
}

bool VuCore_Vu0::is_usable()
{
	// Check that CU[bit 2] == 1 (ie: >0) in the status register.
	return (cop0->status.extract_field(EeCoreCop0Register_Status::CU) & 0x4) > 0;
}

VuCore_Vu1::VuCore_Vu1(const int core_id) :
	VuCore_Base(core_id),
	memory_micro(Constants::SIZE_16KB),
	memory_mem(Constants::SIZE_16KB)
{
}
