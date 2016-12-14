#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"

class Register32_t;
class IOPDmacChannel_t;

/*
IOP DMAC resources.
*/
class IOPDmac_t : public PS2ResourcesSubobject
{
public:
	explicit IOPDmac_t(const PS2Resources_t *const PS2Resources);
	
	/*
	IOP DMA Channels. 
	There are 12 channels in total.
	*/
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_0;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_1;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_2;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_3;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_4;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_5;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_6;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_7;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_8;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_9;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_10;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_11;
	std::shared_ptr<IOPDmacChannel_t> CHANNEL_12;
	std::shared_ptr<IOPDmacChannel_t> CHANNELS[PS2Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS];

	/*
	DMAC Common Registers.
	*/
	std::shared_ptr<Register32_t> PCR;  // Register "PCR (Primary Control Register)"    @ 0x1F8010F0 -> 0x1F8010F3.
	std::shared_ptr<Register32_t> ICR;  // Register "ICR (Interrupt Control Register)"  @ 0x1F8010F4 -> 0x1F8010F7.
	std::shared_ptr<Register32_t> PCR2; // Register "PCR2 (Primary Control Register)"   @ 0x1F801570 -> 0x1F801573.
	std::shared_ptr<Register32_t> ICR2; // Register "ICR  (Interrupt Control Register)" @ 0x1F801574 -> 0x1F801577.
};

