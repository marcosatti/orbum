#include "stdafx.h"

#include "Common/Types/Registers/BitfieldRegister32_t.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/Common/Common_t.h"
#include "PS2Resources/IOP/DMAC/IOPDmac_t.h"
#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"
#include "PS2Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"

IOPDmac_t::IOPDmac_t(const PS2Resources_t* PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),

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

void IOPDmac_t::postResourcesInit()
{
	CHANNEL_fromMDEC = std::make_shared<IOPDmacChannel_fromMDEC_t>(getRoot()->Common->FIFO_DEBUG);
	CHANNEL_toMDEC = std::make_shared<IOPDmacChannel_toMDEC_t>(getRoot()->Common->FIFO_DEBUG);
	CHANNEL_GPU = std::make_shared<IOPDmacChannel_GPU_t>(getRoot()->Common->FIFO_DEBUG);
	CHANNEL_CDROM = std::make_shared<IOPDmacChannel_CDROM_t>(getRoot()->Common->FIFO_DEBUG);
	CHANNEL_SPU2c1 = std::make_shared<IOPDmacChannel_SPU2c1_t>(getRoot()->Common->FIFO_DEBUG);
	CHANNEL_PIO = std::make_shared<IOPDmacChannel_PIO_t>(getRoot()->Common->FIFO_DEBUG);
	CHANNEL_OTClear = std::make_shared<IOPDmacChannel_OTClear_t>(getRoot()->Common->FIFO_DEBUG);
	CHANNEL_SPU2c2 = std::make_shared<IOPDmacChannel_SPU2c2_t>(getRoot()->Common->FIFO_DEBUG);
	CHANNEL_DEV9 = std::make_shared<IOPDmacChannel_DEV9_t>(getRoot()->Common->FIFO_DEBUG);
	CHANNEL_SIF0 = std::make_shared<IOPDmacChannel_SIF0_t>(getRoot()->Common->FIFO_SIF0);
	CHANNEL_SIF1 = std::make_shared<IOPDmacChannel_SIF1_t>(getRoot()->Common->FIFO_SIF1);
	CHANNEL_fromSIO2 = std::make_shared<IOPDmacChannel_fromSIO2_t>(getRoot()->Common->FIFO_DEBUG);
	CHANNEL_toSIO2 = std::make_shared<IOPDmacChannel_toSIO2_t>(getRoot()->Common->FIFO_DEBUG);

	CHANNELS[0] = CHANNEL_fromMDEC;
	CHANNELS[1] = CHANNEL_toMDEC;
	CHANNELS[2] = CHANNEL_GPU;
	CHANNELS[3] = CHANNEL_CDROM;
	CHANNELS[4] = CHANNEL_SPU2c1;
	CHANNELS[5] = CHANNEL_PIO;
	CHANNELS[6] = CHANNEL_OTClear;
	CHANNELS[7] = CHANNEL_SPU2c2;
	CHANNELS[8] = CHANNEL_DEV9;
	CHANNELS[9] = CHANNEL_SIF0;
	CHANNELS[10] = CHANNEL_SIF1;
	CHANNELS[11] = CHANNEL_fromSIO2;
	CHANNELS[12] = CHANNEL_toSIO2;
	CHANNELS[13] = nullptr; // CH 13 undefined, just to keep number of channels even (total 14).
}
