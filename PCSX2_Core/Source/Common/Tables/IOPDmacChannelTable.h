#pragma once

#include "Common/Global/Globals.h"

class IOPDmacChannel_t;

/*
Contains static channel properties for the IOP DMAC channels.
See wisi and SP193's IOP DMAC docs.
*/
struct IOPDmacChannelTable
{
	enum class Direction_t 
	{
		// Ordered according to Dn_CHCR.TD. Relative to FIFO's perspective.
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
	struct IOPDmacChannelInfo_t
	{
		const char * mMnemonic;
	};
	static constexpr IOPDmacChannelInfo_t IOPDMAC_CHANNEL_TABLE[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS] =
	{
		{ "fromMDEC" },
		{ "toMDEC"   },
		{ "SIF2/GPU" },
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
	static const IOPDmacChannelInfo_t * getChannelInfo(const IOPDmacChannel_t * channel);
};

