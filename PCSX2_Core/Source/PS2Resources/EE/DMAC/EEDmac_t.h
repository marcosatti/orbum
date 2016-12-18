#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"

class EEDmacChannel_t;
class EEDmacChannel_VIF0_t;
class EEDmacChannel_VIF1_t;
class EEDmacChannel_GIF_t;
class EEDmacChannel_fromIPU_t;
class EEDmacChannel_toIPU_t;
class EEDmacChannel_SIF0_t;
class EEDmacChannel_SIF1_t;
class EEDmacChannel_SIF2_t;
class EEDmacChannel_fromSPR_t;
class EEDmacChannel_toSPR_t;

class EEDmacRegister_CTRL_t;
class EEDmacRegister_STAT_t;
class EEDmacRegister_PCR_t;
class EEDmacRegister_SWQC_t;
class EEDmacRegister_RBOR_t;
class EEDmacRegister_RBSR_t;
class EEDmacRegister_STADR_t;
class EEDmacRegister_ENABLEW_t;
class EEDmacRegister_ENABLER_t;

class Memory_t;
class ConstantMemory_t;


/*
EE DMAC Resources. See page 41 onwards of the EE Users Manual.
*/
class EEDmac_t : public PS2ResourcesSubobject
{
public:
	explicit EEDmac_t(const PS2Resources_t *const PS2Resources);

	/*
	DMA Channels. See page 42 of the EE Users Manual.
	Each channel contains the set of registers defined on page 73 in the EE Users Manual.
	An array is also defined for use in iterations.
	Initalised at runtime due to FIFO queue dependencies! See PS2Resources::initDMAChannelFifoQueues_EE().
	*/
	std::shared_ptr<EEDmacChannel_VIF0_t>    CHANNEL_VIF0;
	std::shared_ptr<EEDmacChannel_VIF1_t>    CHANNEL_VIF1;
	std::shared_ptr<EEDmacChannel_GIF_t>     CHANNEL_GIF;
	std::shared_ptr<EEDmacChannel_fromIPU_t> CHANNEL_fromIPU;
	std::shared_ptr<EEDmacChannel_toIPU_t>   CHANNEL_toIPU;
	std::shared_ptr<EEDmacChannel_SIF0_t>    CHANNEL_SIF0;
	std::shared_ptr<EEDmacChannel_SIF1_t>    CHANNEL_SIF1;
	std::shared_ptr<EEDmacChannel_SIF2_t>    CHANNEL_SIF2;
	std::shared_ptr<EEDmacChannel_fromSPR_t> CHANNEL_fromSPR;
	std::shared_ptr<EEDmacChannel_toSPR_t>   CHANNEL_toSPR;
	std::shared_ptr<EEDmacChannel_t>         CHANNELS[PS2Constants::EE::DMAC::NUMBER_DMAC_CHANNELS];

	/*
	DMAC common registers. Defined on page 63 of the EE Users Manual.
	*/
	std::shared_ptr<EEDmacRegister_CTRL_t>    CTRL;
	std::shared_ptr<EEDmacRegister_STAT_t>    STAT;
	std::shared_ptr<EEDmacRegister_PCR_t>     PCR;
	std::shared_ptr<EEDmacRegister_SWQC_t>    SQWC;
	std::shared_ptr<EEDmacRegister_RBSR_t>    RBSR;
	std::shared_ptr<EEDmacRegister_RBOR_t>    RBOR;
	std::shared_ptr<EEDmacRegister_STADR_t>   STADR;
	std::shared_ptr<ConstantMemory_t>         MEMORY_E070;
	std::shared_ptr<Memory_t>                 MEMORY_F500; // Memory "Undocumented: F500" @ 0x1000F500 -> 0x1000F51F.
	std::shared_ptr<EEDmacRegister_ENABLER_t> ENABLER;
	std::shared_ptr<ConstantMemory_t>         MEMORY_F530;
	std::shared_ptr<EEDmacRegister_ENABLEW_t> ENABLEW;
	std::shared_ptr<ConstantMemory_t>         MEMORY_F5A0;
};

