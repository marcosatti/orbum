#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/Register/SizedHwordRegister.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Bus/ByteBus.hpp"

#include "Resources/Ee/Vpu/Vu/VuUnits.hpp"
#include "Resources/Ee/Vpu/Vu/VuUnitRegisters.hpp"
#include "Resources/Ee/Core/EeCoreCop0.hpp"
#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"

VuUnit_Base::VuUnit_Base(const int core_id) :
	core_id(core_id),
	vi_zero_register(0, true),
	vi{nullptr},
	bus(16) // TODO: fine tune.
{
}

VuUnit_Vu0::VuUnit_Vu0(const int core_id) :
	VuUnit_Base(core_id),
	memory_micro(Constants::SIZE_4KB),
	memory_mem(Constants::SIZE_4KB),
	ccr{nullptr},
	cop0(nullptr)
{
}

bool VuUnit_Vu0::is_usable()
{
	// Check that CU[bit 2] == 1 (ie: >0) in the status register.
	return (cop0->status.extract_field(EeCoreCop0Register_Status::CU) & 0x4) > 0;
}

VuUnit_Vu1::VuUnit_Vu1(const int core_id) :
	VuUnit_Base(core_id),
	memory_micro(Constants::SIZE_16KB),
	memory_mem(Constants::SIZE_16KB)
{
}
