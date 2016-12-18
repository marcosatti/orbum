#include "stdafx.h"

#include "PS2Resources/EE/DMAC/EEDmac_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacRegisters_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "Common/Types/Memory/Memory_t.h"
#include "Common/Types/Memory/ConstantMemory_t.h"

EEDmac_t::EEDmac_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Channels
	CHANNEL_VIF0(nullptr),
	CHANNEL_VIF1(nullptr),
	CHANNEL_GIF(nullptr),
	CHANNEL_fromIPU(nullptr),
	CHANNEL_toIPU(nullptr),
	CHANNEL_SIF0(nullptr),
	CHANNEL_SIF1(nullptr),
	CHANNEL_SIF2(nullptr),
	CHANNEL_fromSPR(nullptr),
	CHANNEL_toSPR(nullptr),
	CHANNELS{ nullptr },
	CTRL(std::make_shared<EEDmacRegister_CTRL_t>()),
	STAT(std::make_shared<EEDmacRegister_STAT_t>()),
	PCR(std::make_shared<EEDmacRegister_PCR_t>()),
	SQWC(std::make_shared<EEDmacRegister_SWQC_t>()),
	RBSR(std::make_shared<EEDmacRegister_RBSR_t>()),
	RBOR(std::make_shared<EEDmacRegister_RBOR_t>()),
	STADR(std::make_shared<EEDmacRegister_STADR_t>()),
	MEMORY_E070(std::make_shared<ConstantMemory_t>(0xF90, "mDMAC: DMAC_e070 (reserved)")),
	MEMORY_F500(std::make_shared<Memory_t>(0x20, "Undocumented: F500")),
	ENABLER(std::make_shared<EEDmacRegister_ENABLER_t>()),
	MEMORY_F530(std::make_shared<ConstantMemory_t>(0x60, "mDMAC: F530 (reserved)")),
	ENABLEW(std::make_shared<EEDmacRegister_ENABLEW_t>()),
	MEMORY_F5A0(std::make_shared<ConstantMemory_t>(0x60, "mDMAC: F5A0 (reserved)"))
{
}
