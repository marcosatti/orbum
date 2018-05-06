#pragma once

#include "Common/Constants.hpp"

/// Contains static channel properties for the EE DMAC channels.
/// See EE Users Manual page 42.
struct EeDmacConstants
{

	enum class PhysicalMode
	{
		SLICE,
		BURST
	};

	struct EeDmacChannelInfo
	{
		PhysicalMode physical_mode;
	};

	static constexpr EeDmacChannelInfo EEDMAC_CHANNEL_TABLE[Constants::EE::DMAC::NUMBER_DMAC_CHANNELS] =
	{
		{ PhysicalMode::SLICE },
		{ PhysicalMode::SLICE },
		{ PhysicalMode::SLICE },
		{ PhysicalMode::SLICE },
		{ PhysicalMode::SLICE },
		{ PhysicalMode::SLICE },
		{ PhysicalMode::SLICE },
		{ PhysicalMode::SLICE },
		{ PhysicalMode::BURST },
		{ PhysicalMode::BURST }
	};

	/// Converts the D_CTRL.STS and STD fields to the proper channel id's.
	/// A return value of 0 means "Non-specified" for STS, "No stall control" for STD. 
	/// See EE Users Manual page 64.
	static constexpr int STS_MAP[4] = { 0, 5, 8, 3 };
	static constexpr int STD_MAP[4] = { 0, 1, 2, 6 };

	static constexpr const char * MNEMONICS[Constants::EE::DMAC::NUMBER_DMAC_CHANNELS] =
	{
		"VIF0",
		"VIF1",
		"GIF",
		"fromIPU",
		"toIPU",
		"SIF0",
		"SIF1",
		"SIF2",
		"fromSPR",
		"toSPR"
	};
};

