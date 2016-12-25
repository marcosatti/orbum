#include "stdafx.h"

#include "PS2Resources/EE/DMAC/EEDmac_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacRegisters_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/Common/Common_t.h"
#include "Common/Types/Memory/Memory_t.h"
#include "Common/Types/Memory/ConstantMemory_t.h"

EEDmac_t::EEDmac_t(const PS2Resources_t* PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),

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

void EEDmac_t::postResourcesInit()
{
	initChannels();
}

void EEDmac_t::initChannels()
{
	CHANNEL_VIF0 = std::make_shared<EEDmacChannel_VIF0_t>(getRoot()->Common->FIFO_VIF0);
	CHANNEL_VIF1 = std::make_shared<EEDmacChannel_VIF1_t>(getRoot()->Common->FIFO_VIF1);
	CHANNEL_GIF = std::make_shared<EEDmacChannel_GIF_t>(getRoot()->Common->FIFO_GIF);
	CHANNEL_fromIPU = std::make_shared<EEDmacChannel_fromIPU_t>(getRoot()->Common->FIFO_IPU);
	CHANNEL_toIPU = std::make_shared<EEDmacChannel_toIPU_t>(getRoot()->Common->FIFO_IPU);
	CHANNEL_SIF0 = std::make_shared<EEDmacChannel_SIF0_t>(getRoot()->Common->FIFO_SIF0);
	CHANNEL_SIF1 = std::make_shared<EEDmacChannel_SIF1_t>(getRoot()->Common->FIFO_SIF1);
	CHANNEL_SIF2 = std::make_shared<EEDmacChannel_SIF2_t>(getRoot()->Common->FIFO_SIF2);
	CHANNEL_fromSPR = std::make_shared<EEDmacChannel_fromSPR_t>();
	CHANNEL_toSPR = std::make_shared<EEDmacChannel_toSPR_t>();

	CHANNELS[0] = CHANNEL_VIF0;
	CHANNELS[1] = CHANNEL_VIF1;
	CHANNELS[2] = CHANNEL_GIF;
	CHANNELS[3] = CHANNEL_fromIPU;
	CHANNELS[4] = CHANNEL_toIPU;
	CHANNELS[5] = CHANNEL_SIF0;
	CHANNELS[6] = CHANNEL_SIF1;
	CHANNELS[7] = CHANNEL_SIF2;
	CHANNELS[8] = CHANNEL_fromSPR;
	CHANNELS[9] = CHANNEL_toSPR;
}
