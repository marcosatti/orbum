#include "stdafx.h"

#include "PS2Resources/IOP/DMAC/IOPDmac_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"

IOPDmac_t::IOPDmac_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Channels.
	CHANNEL_fromMDEC(std::make_shared<IOPDmacChannel_fromMDEC_t>()),
	CHANNEL_toMDEC(std::make_shared<IOPDmacChannel_toMDEC_t>()),
	CHANNEL_GPU(std::make_shared<IOPDmacChannel_GPU_t>()),
	CHANNEL_CDROM(std::make_shared<IOPDmacChannel_CDROM_t>()),
	CHANNEL_SPU2c1(std::make_shared<IOPDmacChannel_SPU2c1_t>()),
	CHANNEL_5(std::make_shared<IOPDmacChannel_Channel5_t>()),
	CHANNEL_OTClear(std::make_shared<IOPDmacChannel_OTClear_t>()),
	CHANNEL_SPU2c2(std::make_shared<IOPDmacChannel_SPU2c2_t>()),
	CHANNEL_DEV9(std::make_shared<IOPDmacChannel_DEV9_t>()),
	CHANNEL_SIF0(std::make_shared<IOPDmacChannel_SIF0_t>()),
	CHANNEL_SIF1(std::make_shared<IOPDmacChannel_SIF1_t>()),
	CHANNEL_fromSIO2(std::make_shared<IOPDmacChannel_fromSIO2_t>()),
	CHANNEL_toSIO2(std::make_shared<IOPDmacChannel_toSIO2_t>()),
	CHANNELS{ CHANNEL_fromMDEC, CHANNEL_toMDEC, CHANNEL_GPU, CHANNEL_CDROM, CHANNEL_SPU2c1, CHANNEL_5, CHANNEL_OTClear,
	          CHANNEL_SPU2c2, CHANNEL_DEV9, CHANNEL_SIF0, CHANNEL_SIF1, CHANNEL_fromSIO2, CHANNEL_toSIO2 },

	PCR(std::make_shared<Register32_t>()),
	ICR(std::make_shared<Register32_t>()),
	PCR2(std::make_shared<Register32_t>()),
	ICR2(std::make_shared<Register32_t>())
{
}
