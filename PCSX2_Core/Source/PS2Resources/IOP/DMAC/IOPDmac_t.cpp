#include "stdafx.h"

#include "PS2Resources/IOP/DMAC/IOPDmac_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"

IOPDmac_t::IOPDmac_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Channels.
	CHANNEL_0(std::make_shared<IOPDmacChannel_t>(0)),
	CHANNEL_1(std::make_shared<IOPDmacChannel_t>(1)),
	CHANNEL_2(std::make_shared<IOPDmacChannel_t>(2)),
	CHANNEL_3(std::make_shared<IOPDmacChannel_t>(3)),
	CHANNEL_4(std::make_shared<IOPDmacChannel_t>(4)),
	CHANNEL_5(std::make_shared<IOPDmacChannel_t>(5)),
	CHANNEL_6(std::make_shared<IOPDmacChannel_t>(6)),
	CHANNEL_7(std::make_shared<IOPDmacChannel_t>(7)),
	CHANNEL_8(std::make_shared<IOPDmacChannel_t>(8)),
	CHANNEL_9(std::make_shared<IOPDmacChannel_t>(9)),
	CHANNEL_10(std::make_shared<IOPDmacChannel_t>(10)),
	CHANNEL_11(std::make_shared<IOPDmacChannel_t>(11)),
	CHANNEL_12(std::make_shared<IOPDmacChannel_t>(12)),
	CHANNELS{ CHANNEL_0, CHANNEL_1, CHANNEL_2, CHANNEL_3, CHANNEL_4, CHANNEL_5, CHANNEL_6, CHANNEL_7, CHANNEL_8, CHANNEL_9, CHANNEL_10, CHANNEL_11, CHANNEL_12 },

	PCR(std::make_shared<Register32_t>()),
	ICR(std::make_shared<Register32_t>()),
	PCR2(std::make_shared<Register32_t>()),
	ICR2(std::make_shared<Register32_t>())
{
}
