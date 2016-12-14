#include "stdafx.h"

#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"
#include "Common/Types/Registers/Register32_t.h"

IOPDmacChannel_t::IOPDmacChannel_t(const u32 & channelID) :
	mChannelID(channelID),
	MADR(std::make_shared<Register32_t>()),
	BCR(std::make_shared<Register32_t>()),
	CHCR(std::make_shared<Register32_t>()),
	TADR(std::make_shared<Register32_t>())
{
}