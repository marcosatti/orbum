#include "stdafx.h"

#include "PS2Resources/EE/DMAC/DMAC_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacRegisters_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "Common/Types/Memory/Memory_t.h"
#include "Common/Types/Memory/DeadMemory_t.h"

DMAC_t::DMAC_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Channels
	DMAC_CHANNEL_VIF0(std::make_shared<EEDmacChannel_VIF0_t>()),
	DMAC_CHANNEL_VIF1(std::make_shared<EEDmacChannel_VIF1_t>()),
	DMAC_CHANNEL_GIF(std::make_shared<EEDmacChannel_GIF_t>()),
	DMAC_CHANNEL_fromIPU(std::make_shared<EEDmacChannel_fromIPU_t>()),
	DMAC_CHANNEL_toIPU(std::make_shared<EEDmacChannel_toIPU_t>()),
	DMAC_CHANNEL_SIF0(std::make_shared<EEDmacChannel_SIF0_t>()),
	DMAC_CHANNEL_SIF1(std::make_shared<EEDmacChannel_SIF1_t>()),
	DMAC_CHANNEL_SIF2(std::make_shared<EEDmacChannel_SIF2_t>()),
	DMAC_CHANNEL_fromSPR(std::make_shared<EEDmacChannel_fromSPR_t>()),
	DMAC_CHANNEL_toSPR(std::make_shared<EEDmacChannel_toSPR_t>()),
	DMAC_CHANNELS{ DMAC_CHANNEL_VIF0, DMAC_CHANNEL_VIF1, DMAC_CHANNEL_GIF, DMAC_CHANNEL_fromIPU, DMAC_CHANNEL_toIPU, 
				   DMAC_CHANNEL_SIF0, DMAC_CHANNEL_SIF1, DMAC_CHANNEL_SIF2, DMAC_CHANNEL_fromSPR, DMAC_CHANNEL_toSPR},
	DMAC_REGISTER_D_CTRL(std::make_shared<EEDmacRegister_CTRL_t>()),
	DMAC_REGISTER_D_STAT(std::make_shared<EEDmacRegister_STAT_t>()),
	DMAC_REGISTER_D_PCR(std::make_shared<EEDmacRegister_PCR_t>()),
	DMAC_REGISTER_D_SQWC(std::make_shared<EEDmacRegister_SWQC_t>()),
	DMAC_REGISTER_D_RBSR(std::make_shared<EEDmacRegister_RBSR_t>()),
	DMAC_REGISTER_D_RBOR(std::make_shared<EEDmacRegister_RBOR_t>()),
	DMAC_REGISTER_D_STADR(std::make_shared<EEDmacRegister_STADR_t>()),
	DMAC_MEMORY_e070(std::make_shared<DeadMemory_t>(0xF90, "DMAC: DMAC_e070 (reserved)")),
	DMAC_MEMORY_F500(std::make_shared<Memory_t>(0x20, "Undocumented: F500")),
	DMAC_REGISTER_D_ENABLER(std::make_shared<EEDmacRegister_ENABLER_t>()),
	DMAC_MEMORY_F530(std::make_shared<DeadMemory_t>(0x60, "DMAC: F530 (reserved)")),
	DMAC_REGISTER_D_ENABLEW(std::make_shared<EEDmacRegister_ENABLEW_t>()),
	DMAC_MEMORY_F5A0(std::make_shared<DeadMemory_t>(0x60, "DMAC: F5A0 (reserved)"))
{
}
