#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class Register32_t;

/*
A base type representing an IOP DMAC Channel.
*/
class IOPDmacChannel_t
{
public:
	explicit IOPDmacChannel_t(const u32 & channelID);

	/*
	The ID of this channel.
	*/
	const u32 mChannelID;

	/*
	IOP DMAC Channel Registers.
	*/
	std::shared_ptr<Register32_t> MADR;
	std::shared_ptr<Register32_t> BCR;
	std::shared_ptr<Register32_t> CHCR;
	std::shared_ptr<Register32_t> TADR;
};