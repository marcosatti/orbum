#pragma once

#include "Common/Global/Globals.h"

/*
Contains static channel properties for the EE DMAC channels.
*/
class EEDmacChannelTable
{
public:

	/*
	Define the DMA channel properties, as listed on EE Users Manual page 42.
	*/
	enum class Direction_t
	{
		// Sync'd to Dn_CHCR.DIR order. This is relative from the FIFO queue's perspective.
		FROM = 0,
		TO = 1,
	};
	enum class PhysicalMode_t
	{
		SLICE,
		BURST
	};
	enum class LogicalMode_t
	{
		// Sync'd to Dn_CHCR.MOD order.
		NORMAL = 0,
		CHAIN = 1,
		INTERLEAVED = 2
	};
	struct ChannelProperties_t
	{
		const char *   Mnemonic;
		PhysicalMode_t PhysicalMode;
	};
	static constexpr ChannelProperties_t ChannelProperties[Constants::EE::DMAC::NUMBER_DMAC_CHANNELS] =
	{
		{ "VIF0",    PhysicalMode_t::SLICE },
		{ "VIF1",    PhysicalMode_t::SLICE },
		{ "GIF",     PhysicalMode_t::SLICE },
		{ "fromIPU", PhysicalMode_t::SLICE },
		{ "toIPU",   PhysicalMode_t::SLICE },
		{ "SIF0",    PhysicalMode_t::SLICE },
		{ "SIF1",    PhysicalMode_t::SLICE },
		{ "SIF2",    PhysicalMode_t::SLICE },
		{ "fromSPR", PhysicalMode_t::BURST },
		{ "toSPR",   PhysicalMode_t::BURST }
	};

	/*
	Returns the channel properties given the index.
	*/
	static const ChannelProperties_t * getChannelInfo(const u32 & index);

	/*
	Converts the D_CTRL.STS and STD fields to the proper channel id's.
	A return value of 0 means "Non-specified" for STS, "No stall control" for STD. 
	See EE Users Manual page 64.
	*/
	static constexpr int STS_MAP[4] = { 0, 5, 8, 3 };
	static constexpr int STD_MAP[4] = { 0, 1, 2, 6 };
	static int getSTSChannelIndex(const int STS);
	static int getSTDChannelIndex(const int STD);
};

