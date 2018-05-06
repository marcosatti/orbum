#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"

#include "Resources/Ee/Dmac/REeDmac.hpp"
#include "Resources/Ee/Dmac/EeDmacRegisters.hpp"

REeDmac::REeDmac() :
	channel_vif0(0),
	channel_vif1(1),
	channel_gif(2),
	channel_fromipu(3),
	channel_toipu(4),
	channel_sif0(5),
	channel_sif1(6),
	channel_sif2(7),
	channel_fromspr(8),
	channel_tospr(9),
	memory_8060(0xFA0, 0, true),
	memory_9060(0xFA0, 0, true),
	memory_a060(0xFA0, 0, true),
	memory_b030(0x3D0, 0, true),
	memory_b440(0xBC0, 0, true),
	memory_c030(0x3D0, 0, true),
	memory_c440(0x3C0, 0, true),
	memory_c830(0x7D0, 0, true),
	memory_d030(0x50, 0, true),
	memory_d090(0x370, 0, true),
	memory_d440(0x40, 0, true),
	memory_d490(0xB70, 0, true),
	memory_e070(0xF90, 0, true),
	memory_f500(0x20),
	memory_f530(0x60, 0, true),
	memory_f5a0(0x60, 0, true)
{
}