#include "stdafx.h"

#include "Common/Types/Register/Register32_t.h"

#include "Resources/IOP/DMAC/IOPDmac_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"

IOPDmac_t::IOPDmac_t() :
	// Channels (defined on post resources initalisation).
	CHANNEL_fromMDEC(nullptr),
	CHANNEL_toMDEC(nullptr),
	CHANNEL_SIF2(nullptr),
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
	CHANNEL_13(nullptr),
	CHANNELS{ nullptr },

	PCR0(std::make_shared<IOPDmacRegister_PCR0_t>("IOP DMAC PCR0", false, false)),
	ICR0(std::make_shared<IOPDmacRegister_ICR0_t>("IOP DMAC ICR0", false, false)),
	PCR1(std::make_shared<IOPDmacRegister_PCR1_t>("IOP DMAC PCR1", false, false)),
	ICR1(std::make_shared<IOPDmacRegister_ICR1_t>("IOP DMAC ICR1", false, false, ICR0)),
	GCTRL(std::make_shared<Register32_t>("IOP DMAC GCTRL", false, false))
{
}
