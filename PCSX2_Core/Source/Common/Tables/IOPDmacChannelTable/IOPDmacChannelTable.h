#pragma once

#include "Common/Global/Globals.h"

/*
Contains static channel properties for the IOP DMAC channels.
*/
class IOPDmacChannelTable
{
public:

	/*
	Define the DMA channel properties, as listed on IOP Users Manual page 42.
	*/
	enum class ChannelID_t
	{
		fromMDEC = 0,
		toMDEC = 1,
		GPU = 2,
		CDROM = 3,
		SPU2c1 = 4,
		PIO = 5,
		OTClear = 6,
		SPU2c2 = 7,
		DEV9 = 8, 
		SIF0 = 9, 
		SIF1 = 10, 
		fromSIO2 = 11, 
		toSIO2 = 12 
	};
	enum class Direction_t 
	{
		// Directions relative to channel FIFO. Sync'd to Dn_CHCR.TD.
		FROM = 0,
		TO = 1
	};
	enum class LogicalMode_t
	{
		// Do not change order! Sync'd to Dn_CHCR.SM order (needed in order to static_cast<LogicalMode_t>).
		NORMAL = 0,
		BLOCK = 1,
		LINKEDLIST = 2,
		RESERVED = 3
	};
	struct ChannelProperties_t
	{
		const char *   Mnemonic;
		ChannelID_t    ChannelID;
	};
	static constexpr ChannelProperties_t ChannelProperties[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS] =
	{
		{ "fromMDEC", ChannelID_t::fromMDEC },
		{ "toMDEC",   ChannelID_t::toMDEC   },
		{ "GPU",      ChannelID_t::GPU      },
		{ "CDROM",    ChannelID_t::CDROM    },
		{ "SPU2c1",   ChannelID_t::SPU2c1   },
		{ "PIO",      ChannelID_t::PIO      },
		{ "OTClear",  ChannelID_t::OTClear  },
		{ "SPU2c2",   ChannelID_t::SPU2c2   },
		{ "DEV9",     ChannelID_t::DEV9     },
		{ "SIF0",     ChannelID_t::SIF0     },
		{ "SIF1",     ChannelID_t::SIF1     },
		{ "fromSIO2", ChannelID_t::fromSIO2 },
		{ "toSIO2",   ChannelID_t::toSIO2   },
	};

	/*
	Returns the channel properties given the index.
	*/
	static const ChannelProperties_t * getChannelInfo(u32 index);

};

