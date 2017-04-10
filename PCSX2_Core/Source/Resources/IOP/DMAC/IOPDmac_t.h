#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class BitfieldRegister32_t;
class IOPDmacChannel_t;
class IOPDmacChannel_fromMDEC_t;
class IOPDmacChannel_toMDEC_t;
class IOPDmacChannel_SIF2_t;
class IOPDmacChannel_CDROM_t;
class IOPDmacChannel_SPU2c1_t;
class IOPDmacChannel_PIO_t;
class IOPDmacChannel_OTClear_t;
class IOPDmacChannel_SPU2c2_t;
class IOPDmacChannel_DEV9_t;
class IOPDmacChannel_SIF0_t;
class IOPDmacChannel_SIF1_t;
class IOPDmacChannel_fromSIO2_t;
class IOPDmacChannel_toSIO2_t;
class IOPDmacChannel_CH13_t;
class IOPDmacRegister_PCR0_t; 
class IOPDmacRegister_ICR0_t;
class IOPDmacRegister_PCR1_t; 
class IOPDmacRegister_ICR1_t;
class Register32_t;

/*
IOP DMAC resources.
*/
class IOPDmac_t
{
public:
	IOPDmac_t();
	
	/*
	IOP DMA Channels. 
	There are 14 channels in total (to make it even), with the last one being undefined.
	*/
	std::shared_ptr<IOPDmacChannel_fromMDEC_t> CHANNEL_fromMDEC;
	std::shared_ptr<IOPDmacChannel_toMDEC_t>   CHANNEL_toMDEC;
	std::shared_ptr<IOPDmacChannel_SIF2_t>     CHANNEL_SIF2;
	std::shared_ptr<IOPDmacChannel_CDROM_t>    CHANNEL_CDROM;
	std::shared_ptr<IOPDmacChannel_SPU2c1_t>   CHANNEL_SPU2c1;
	std::shared_ptr<IOPDmacChannel_PIO_t>      CHANNEL_PIO;
	std::shared_ptr<IOPDmacChannel_OTClear_t>  CHANNEL_OTClear;
	std::shared_ptr<IOPDmacChannel_SPU2c2_t>   CHANNEL_SPU2c2;
	std::shared_ptr<IOPDmacChannel_DEV9_t>     CHANNEL_DEV9;
	std::shared_ptr<IOPDmacChannel_SIF0_t>     CHANNEL_SIF0;
	std::shared_ptr<IOPDmacChannel_SIF1_t>     CHANNEL_SIF1;
	std::shared_ptr<IOPDmacChannel_fromSIO2_t> CHANNEL_fromSIO2;
	std::shared_ptr<IOPDmacChannel_toSIO2_t>   CHANNEL_toSIO2;
	std::shared_ptr<IOPDmacChannel_CH13_t>     CHANNEL_13;
	std::shared_ptr<IOPDmacChannel_t> CHANNELS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS];

	/*
	DMAC Common Registers.
	*/
	std::shared_ptr<IOPDmacRegister_PCR0_t> PCR0;  // Register "PCR0 (Primary Control Register)"   @ 0x1F8010F0 -> 0x1F8010F3. Responsible for DMA channels 0 -> 6.
	std::shared_ptr<IOPDmacRegister_ICR0_t> ICR0;  // Register "ICR0 (Interrupt Control Register)" @ 0x1F8010F4 -> 0x1F8010F7. Responsible for DMA channels 0 -> 6.
	std::shared_ptr<IOPDmacRegister_PCR1_t> PCR1;  // Register "PCR1 (Primary Control Register)"   @ 0x1F801570 -> 0x1F801573. Responsible for DMA channels 7 -> 13. (Channel 13 is undefined.)
	std::shared_ptr<IOPDmacRegister_ICR1_t> ICR1;  // Register "ICR1 (Interrupt Control Register)" @ 0x1F801574 -> 0x1F801577. Responsible for DMA channels 7 -> 13. (Channel 13 is undefined.)
	std::shared_ptr<Register32_t>           GCTRL; // Register "GCTRL (Global Control Register)"   @ 0x1F801578 -> 0x1F80157B. From wisi and SP193's DMA docs.
};

