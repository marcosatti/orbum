#include "Resources/Ee/Ipu/RIpu.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"

RIpu::RIpu() :
	memory_2040(0xFC0, 0, true)
{
}
