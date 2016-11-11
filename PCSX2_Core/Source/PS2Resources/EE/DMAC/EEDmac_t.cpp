#include "stdafx.h"

#include "PS2Resources/EE/DMAC/EEDmac_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacRegisters_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "Common/Types/Memory/Memory_t.h"
#include "Common/Types/Memory/DeadMemory_t.h"

EEDmac_t::EEDmac_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Channels
	CHANNEL_VIF0(std::make_shared<EEDmacChannel_VIF0_t>()),
	CHANNEL_VIF1(std::make_shared<EEDmacChannel_VIF1_t>()),
	CHANNEL_GIF(std::make_shared<EEDmacChannel_GIF_t>()),
	CHANNEL_fromIPU(std::make_shared<EEDmacChannel_fromIPU_t>()),
	CHANNEL_toIPU(std::make_shared<EEDmacChannel_toIPU_t>()),
	CHANNEL_SIF0(std::make_shared<EEDmacChannel_SIF0_t>()),
	CHANNEL_SIF1(std::make_shared<EEDmacChannel_SIF1_t>()),
	CHANNEL_SIF2(std::make_shared<EEDmacChannel_SIF2_t>()),
	CHANNEL_fromSPR(std::make_shared<EEDmacChannel_fromSPR_t>()),
	CHANNEL_toSPR(std::make_shared<EEDmacChannel_toSPR_t>()),
	CHANNELS{ CHANNEL_VIF0, CHANNEL_VIF1, CHANNEL_GIF, CHANNEL_fromIPU, CHANNEL_toIPU, 
			  CHANNEL_SIF0, CHANNEL_SIF1, CHANNEL_SIF2, CHANNEL_fromSPR, CHANNEL_toSPR},
	REGISTER_CTRL(std::make_shared<EEDmacRegister_CTRL_t>()),
	REGISTER_STAT(std::make_shared<EEDmacRegister_STAT_t>()),
	REGISTER_PCR(std::make_shared<EEDmacRegister_PCR_t>()),
	REGISTER_SQWC(std::make_shared<EEDmacRegister_SWQC_t>()),
	REGISTER_RBSR(std::make_shared<EEDmacRegister_RBSR_t>()),
	REGISTER_RBOR(std::make_shared<EEDmacRegister_RBOR_t>()),
	REGISTER_STADR(std::make_shared<EEDmacRegister_STADR_t>()),
	MEMORY_e070(std::make_shared<DeadMemory_t>(0xF90, "DMAC: DMAC_e070 (reserved)")),
	MEMORY_F500(std::make_shared<Memory_t>(0x20, "Undocumented: F500")),
	REGISTER_ENABLER(std::make_shared<EEDmacRegister_ENABLER_t>()),
	MEMORY_F530(std::make_shared<DeadMemory_t>(0x60, "DMAC: F530 (reserved)")),
	REGISTER_ENABLEW(std::make_shared<EEDmacRegister_ENABLEW_t>()),
	MEMORY_F5A0(std::make_shared<DeadMemory_t>(0x60, "DMAC: F5A0 (reserved)"))
{
}
