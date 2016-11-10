#pragma once

#include "PS2Constants/PS2Constants.h"

class EEDmacTable
{
public:

	/*
	Define the DMA channel properties, as listed on EE Users Manual page 42.
	*/
	enum class ChannelID_t
	{
		VIF0 = 0,
		VIF1 = 1,
		GIF = 2,
		fromIPU = 3,
		toIPU = 4,
		SIF0 = 5,
		SIF1 = 6,
		SIF2 = 7,
		fromSPR = 8, // From scratchpad ram.
		toSPR = 9  // To scratchpad ram.
	};
	enum class Direction_t
	{
		// Do not change order! Sync'd to Dn_CHCR.DIR order (needed in order to static_cast<Direction_t>), 
		//  except for BOTH in which case the direction is determined at runtime.
		FROM = 0,
		TO = 1,
		BOTH = 2
	};
	enum class PhysicalMode_t
	{
		SLICE = 0,
		BURST = 1
	};
	enum class ChainMode_t
	{
		SOURCE = 0,
		DEST = 1, // Destination.
		NONE = 2
	};
	struct ChannelProperties_t
	{
		const char *   Mnemonic;
		ChannelID_t    ChannelID;
		Direction_t    Direction;
		PhysicalMode_t PhysicalMode;
		ChainMode_t    ChainMode;
	};
	static constexpr ChannelProperties_t ChannelProperties[PS2Constants::EE::DMAC::NUMBER_DMAC_CHANNELS] =
	{
		{ "VIF0",    ChannelID_t::VIF0,    Direction_t::TO,   PhysicalMode_t::SLICE, ChainMode_t::SOURCE },
		{ "VIF1",    ChannelID_t::VIF1,    Direction_t::BOTH, PhysicalMode_t::SLICE, ChainMode_t::SOURCE },
		{ "GIF",     ChannelID_t::GIF,     Direction_t::TO,   PhysicalMode_t::SLICE, ChainMode_t::SOURCE },
		{ "fromIPU", ChannelID_t::fromIPU, Direction_t::FROM, PhysicalMode_t::SLICE, ChainMode_t::NONE },
		{ "toIPU",   ChannelID_t::toIPU,   Direction_t::TO,   PhysicalMode_t::SLICE, ChainMode_t::SOURCE },
		{ "SIF0",    ChannelID_t::SIF0,    Direction_t::FROM, PhysicalMode_t::SLICE, ChainMode_t::DEST },
		{ "SIF1",    ChannelID_t::SIF1,    Direction_t::TO,   PhysicalMode_t::SLICE, ChainMode_t::SOURCE },
		{ "SIF2",    ChannelID_t::SIF2,    Direction_t::BOTH, PhysicalMode_t::SLICE, ChainMode_t::NONE },
		{ "fromSPR", ChannelID_t::fromSPR, Direction_t::FROM, PhysicalMode_t::BURST, ChainMode_t::DEST },
		{ "toSPR",   ChannelID_t::toSPR,   Direction_t::TO,   PhysicalMode_t::BURST, ChainMode_t::SOURCE }
	};

	/*
	Returns the channel properties given the index.
	*/
	static const ChannelProperties_t * getChannelInfo(u32 index);

	/*
	Converts the D_CTRL.STS and STD fields to the proper channel id's.
	A return value of 0 means "Non-specified" for STS, "No stall control" for STD. 
	See EE Users Manual page 64.
	*/
	static constexpr u8 STS_MAP[4] = { 0, 5, 8, 3 };
	static constexpr u8 STD_MAP[4] = { 0, 1, 2, 6 };
	static const u8 & getSTSChannelIndex(const u8 & STS);
	static const u8 & getSTDChannelIndex(const u8 & STD);
};

