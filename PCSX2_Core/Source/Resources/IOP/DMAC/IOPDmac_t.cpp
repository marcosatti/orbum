#include "stdafx.h"

#include "Resources/IOP/DMAC/IOPDmac_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"

IOPDmac_t::IOPDmac_t() :
	// Channels.
	CHANNEL_fromMDEC(nullptr),
	CHANNEL_toMDEC(nullptr),
	CHANNEL_GPU(nullptr),
	CHANNEL_CDROM(nullptr),
	CHANNEL_SPU2c1(nullptr),
	CHANNEL_PIO(nullptr),
	CHANNEL_OTClear(nullptr),
	CHANNEL_SPU2c2(nullptr),
	CHANNEL_DEV9(nullptr),
	CHANNEL_SIF0(nullptr),
	CHANNEL_SIF1(nullptr),
	CHANNEL_fromSIO2(nullptr),
	CHANNEL_toSIO2(nullptr),

	PCR(std::make_shared<IOPDmacRegister_PCR_t>("IOP DMAC: PCR")),
	ICR(std::make_shared<IOPDmacRegister_ICR_t>("IOP DMAC: ICR")),
	PCR2(std::make_shared<IOPDmacRegister_PCR_t>("IOP DMAC: PCR2")),
	ICR2(std::make_shared<IOPDmacRegister_ICR_t>("IOP DMAC: ICR2")),
	PCRS{ PCR, PCR2 },
	ICRS{ ICR, ICR2 }
{
}
