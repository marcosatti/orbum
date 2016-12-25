#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubcategory.h"
#include "PS2Constants/PS2Constants.h"

class Register32_t;
class IOPDmacChannel_t;
class IOPDmacChannel_fromMDEC_t;
class IOPDmacChannel_toMDEC_t;
class IOPDmacChannel_GPU_t;
class IOPDmacChannel_CDROM_t;
class IOPDmacChannel_SPU2c1_t;
class IOPDmacChannel_Channel5_t;
class IOPDmacChannel_OTClear_t;
class IOPDmacChannel_SPU2c2_t;
class IOPDmacChannel_DEV9_t;
class IOPDmacChannel_SIF0_t;
class IOPDmacChannel_SIF1_t;
class IOPDmacChannel_fromSIO2_t;
class IOPDmacChannel_toSIO2_t;

/*
IOP DMAC resources.
*/
class IOPDmac_t : public PS2ResourcesSubcategory
{
public:
	explicit IOPDmac_t(const PS2Resources_t * PS2Resources);
	
	/*
	IOP DMA Channels. 
	There are 12 channels in total.
	*/
	std::shared_ptr<IOPDmacChannel_fromMDEC_t> CHANNEL_fromMDEC;
	std::shared_ptr<IOPDmacChannel_toMDEC_t>   CHANNEL_toMDEC;
	std::shared_ptr<IOPDmacChannel_GPU_t>      CHANNEL_GPU;
	std::shared_ptr<IOPDmacChannel_CDROM_t>    CHANNEL_CDROM;
	std::shared_ptr<IOPDmacChannel_SPU2c1_t>   CHANNEL_SPU2c1;
	std::shared_ptr<IOPDmacChannel_Channel5_t> CHANNEL_5;
	std::shared_ptr<IOPDmacChannel_OTClear_t>  CHANNEL_OTClear;
	std::shared_ptr<IOPDmacChannel_SPU2c2_t>   CHANNEL_SPU2c2;
	std::shared_ptr<IOPDmacChannel_DEV9_t>     CHANNEL_DEV9;
	std::shared_ptr<IOPDmacChannel_SIF0_t>     CHANNEL_SIF0;
	std::shared_ptr<IOPDmacChannel_SIF1_t>     CHANNEL_SIF1;
	std::shared_ptr<IOPDmacChannel_fromSIO2_t> CHANNEL_fromSIO2;
	std::shared_ptr<IOPDmacChannel_toSIO2_t>   CHANNEL_toSIO2;
	std::shared_ptr<IOPDmacChannel_t> CHANNELS[PS2Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS];

	/*
	DMAC Common Registers.
	*/
	std::shared_ptr<Register32_t> PCR;  // Register "PCR (Primary Control Register)"    @ 0x1F8010F0 -> 0x1F8010F3.
	std::shared_ptr<Register32_t> ICR;  // Register "ICR (Interrupt Control Register)"  @ 0x1F8010F4 -> 0x1F8010F7.
	std::shared_ptr<Register32_t> PCR2; // Register "PCR2 (Primary Control Register)"   @ 0x1F801570 -> 0x1F801573.
	std::shared_ptr<Register32_t> ICR2; // Register "ICR  (Interrupt Control Register)" @ 0x1F801574 -> 0x1F801577.
};

