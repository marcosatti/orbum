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

class DMAC_t : public PS2ResourcesSubobject
{
public:
	explicit DMAC_t(const PS2Resources_t *const PS2Resources);

	/*
	DMA Channels. See page 41 onwards of EE Users Manual.
	Each channel contains the set of registers defined on page 73 in the EE Users Manual.
	An array is also defined for use in iterations.
	*/
	std::shared_ptr<EEDmacChannel_VIF0_t>    DMAC_CHANNEL_VIF0;
	std::shared_ptr<EEDmacChannel_VIF1_t>    DMAC_CHANNEL_VIF1;
	std::shared_ptr<EEDmacChannel_GIF_t>     DMAC_CHANNEL_GIF;
	std::shared_ptr<EEDmacChannel_fromIPU_t> DMAC_CHANNEL_fromIPU;
	std::shared_ptr<EEDmacChannel_toIPU_t>   DMAC_CHANNEL_toIPU;
	std::shared_ptr<EEDmacChannel_SIF0_t>    DMAC_CHANNEL_SIF0;
	std::shared_ptr<EEDmacChannel_SIF1_t>    DMAC_CHANNEL_SIF1;
	std::shared_ptr<EEDmacChannel_SIF2_t>    DMAC_CHANNEL_SIF2;
	std::shared_ptr<EEDmacChannel_fromSPR_t> DMAC_CHANNEL_fromSPR;
	std::shared_ptr<EEDmacChannel_toSPR_t>   DMAC_CHANNEL_toSPR;
	std::shared_ptr<EEDmacChannel_t>         DMAC_CHANNELS[PS2Constants::EE::DMAC::NUMBER_DMAC_CHANNELS];

	/*
	DMAC common registers. Defined on page 63 of the EE Users Manual.
	*/
	// 0x1000E000
	std::shared_ptr<EEDmacRegister_CTRL_t>    DMAC_REGISTER_D_CTRL;
	std::shared_ptr<EEDmacRegister_STAT_t>    DMAC_REGISTER_D_STAT;
	std::shared_ptr<EEDmacRegister_PCR_t>     DMAC_REGISTER_D_PCR;
	std::shared_ptr<EEDmacRegister_SWQC_t>    DMAC_REGISTER_D_SQWC;
	std::shared_ptr<EEDmacRegister_RBSR_t>    DMAC_REGISTER_D_RBSR;
	std::shared_ptr<EEDmacRegister_RBOR_t>    DMAC_REGISTER_D_RBOR;
	std::shared_ptr<EEDmacRegister_STADR_t>   DMAC_REGISTER_D_STADR;
	std::shared_ptr<DeadMemory_t>         DMAC_MEMORY_e070;

	// 0x1000F500
	std::shared_ptr<Memory_t>        DMAC_MEMORY_F500;      // Register "Undocumented: F500" @ 0x1000F500 -> 0x1000F520.
	std::shared_ptr<EEDmacRegister_ENABLER_t> DMAC_REGISTER_D_ENABLER;
	std::shared_ptr<DeadMemory_t>         DMAC_MEMORY_F530;
	std::shared_ptr<EEDmacRegister_ENABLEW_t> DMAC_REGISTER_D_ENABLEW;
	std::shared_ptr<DeadMemory_t>         DMAC_MEMORY_F5A0;
};

