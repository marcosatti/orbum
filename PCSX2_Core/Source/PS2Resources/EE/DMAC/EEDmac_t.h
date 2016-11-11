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
class DeadMemory_t;

class EEDmac_t : public PS2ResourcesSubobject
{
public:
	explicit EEDmac_t(const PS2Resources_t *const PS2Resources);

	/*
	DMA Channels. See page 41 onwards of EE Users Manual.
	Each channel contains the set of registers defined on page 73 in the EE Users Manual.
	An array is also defined for use in iterations.
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
	std::shared_ptr<EEDmacRegister_CTRL_t>    REGISTER_CTRL;
	std::shared_ptr<EEDmacRegister_STAT_t>    REGISTER_STAT;
	std::shared_ptr<EEDmacRegister_PCR_t>     REGISTER_PCR;
	std::shared_ptr<EEDmacRegister_SWQC_t>    REGISTER_SQWC;
	std::shared_ptr<EEDmacRegister_RBSR_t>    REGISTER_RBSR;
	std::shared_ptr<EEDmacRegister_RBOR_t>    REGISTER_RBOR;
	std::shared_ptr<EEDmacRegister_STADR_t>   REGISTER_STADR;
	std::shared_ptr<DeadMemory_t>             MEMORY_e070;
	std::shared_ptr<Memory_t>                 MEMORY_F500;        // Memory "Undocumented: F500" @ 0x1000F500 -> 0x1000F520. Not in manual!
	std::shared_ptr<EEDmacRegister_ENABLER_t> REGISTER_ENABLER;
	std::shared_ptr<DeadMemory_t>             MEMORY_F530;
	std::shared_ptr<EEDmacRegister_ENABLEW_t> REGISTER_ENABLEW;
	std::shared_ptr<DeadMemory_t>             MEMORY_F5A0;
};

