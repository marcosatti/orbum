#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class BitfieldRegister32_t;
class IOPDmacChannel_t;
class IOPDmacChannel_fromMDEC_t;
class IOPDmacChannel_toMDEC_t;
class IOPDmacChannel_GPU_t;
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
class IOPDmacRegister_PCR_t; 
class IOPDmacRegister_ICR_t;

/*
IOP DMAC resources.
*/
class IOPDmac_t
{
public:
	explicit IOPDmac_t();
	
	/*
	IOP DMA Channels. 
	There are 12 channels in total.
	*/
	std::shared_ptr<IOPDmacChannel_fromMDEC_t> CHANNEL_fromMDEC;
	std::shared_ptr<IOPDmacChannel_toMDEC_t>   CHANNEL_toMDEC;
	std::shared_ptr<IOPDmacChannel_GPU_t>      CHANNEL_GPU;
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
	std::shared_ptr<IOPDmacChannel_t> CHANNELS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS];

	/*
	DMAC Common Registers.
	*/
	std::shared_ptr<IOPDmacRegister_PCR_t> PCR;  // Register "PCR (Primary Control Register)"    @ 0x1F8010F0 -> 0x1F8010F3. Responsible for DMA channels 0 -> 6.
	std::shared_ptr<IOPDmacRegister_ICR_t> ICR;  // Register "ICR (Interrupt Control Register)"  @ 0x1F8010F4 -> 0x1F8010F7. Responsible for DMA channels 0 -> 6.
	std::shared_ptr<IOPDmacRegister_PCR_t> PCR2; // Register "PCR2 (Primary Control Register)"   @ 0x1F801570 -> 0x1F801573. Responsible for DMA channels 7 -> 12.
	std::shared_ptr<IOPDmacRegister_ICR_t> ICR2; // Register "ICR  (Interrupt Control Register)" @ 0x1F801574 -> 0x1F801577. Responsible for DMA channels 7 -> 12.
	std::shared_ptr<IOPDmacRegister_PCR_t> PCRS[Constants::IOP::DMAC::NUMBER_PCR_REGISTERS]; // Array of PCR registers needed for iterations.
	std::shared_ptr<IOPDmacRegister_ICR_t> ICRS[Constants::IOP::DMAC::NUMBER_ICR_REGISTERS]; // Array of PCR registers needed for iterations.
};

