#pragma once

#include "Common/Global/Globals.h"

/*
Contains static channel properties for the IOP DMAC channels.
*/
class IOPDmacChannelTable
{
public:
	enum class Direction_t 
	{
		// Ordered according to Dn_CHCR.TD.
		FROM = 0,
		TO = 1
	};
	enum class LogicalMode_t
	{
		// Ordered according to Dn_CHCR.SM.
		NORMAL_BURST = 0,
		NORMAL_SLICE = 1,
		LINKEDLIST = 2,
		CHAIN = 3
	};
	struct ChannelProperties_t
	{
		const char * Mnemonic;
	};
	static constexpr ChannelProperties_t ChannelProperties[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS] =
	{
		{ "fromMDEC" },
		{ "toMDEC"   },
		{ "GPU"      },
		{ "CDROM"    },
		{ "SPU2c1"   },
		{ "PIO"      },
		{ "OTClear"  },
		{ "SPU2c2"   },
		{ "DEV9"     },
		{ "SIF0"     },
		{ "SIF1"     },
		{ "fromSIO2" },
		{ "toSIO2"   },
	};

	/*
	Returns the channel properties given the index.
	*/
	static const ChannelProperties_t * getChannelInfo(const int channelIndex);

};

