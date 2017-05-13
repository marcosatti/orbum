#include "stdafx.h"

#include <algorithm>

#include "Common/Types/Memory/HwordMemory_t.h"

#include "Resources/CDVD/Types/CDVDNvrams_t.h"

CDVDNvram_t::CDVDNvram_t() :
	MainMemory(nullptr),
	mConfigReadWrite(0),
	mConfigAreaIndex(0),
	mConfigMaxBlockIndex(0),
	mConfigBlockIndex(0)
{
}

void CDVDNvram_t::setConfigAccessParams(const int readWrite, const int areaIndex, const int maxBlockIndex, const int blockIndex)
{
	mConfigReadWrite = readWrite;
	mConfigAreaIndex = areaIndex;
	mConfigMaxBlockIndex = maxBlockIndex;
	mConfigBlockIndex = blockIndex;
}

CDVDNvram_000_t::CDVDNvram_000_t(const char * mnemonic, const bool debugReads, const bool debugWrites)
{
	MainMemory = std::make_shared<HwordMemory_t>(mnemonic, debugReads, debugWrites, Constants::CDVD::SIZE_NVRAM);
}

void CDVDNvram_000_t::readConfigBlock(const System_t context, u16 * buffer)
{
	// Check for read mode (0), return magic values otherwise (TODO: check this, throws error for now).
	if (mConfigReadWrite == 0)
	{
		// Check if block is within bounds.
		if ( ((mConfigAreaIndex == 0) && (mConfigBlockIndex >= 4))
			|| ((mConfigAreaIndex == 1) && (mConfigBlockIndex >= 2))
			|| ((mConfigAreaIndex == 2) && (mConfigBlockIndex >= 7)) )
		{
			throw std::runtime_error("CDVD read config block was outside of bounds... What is meant to happen?");
		}

		// Check if block is within the max allowed parameter set.
		if (mConfigBlockIndex >= mConfigMaxBlockIndex)
		{
			throw std::runtime_error("CDVD read config block was outside of max block parameter set... What is meant to happen?");
		}

		// Ok to read a block.
		switch (mConfigAreaIndex)
		{
		case 0:
			MainMemory->read(context, buffer, 8, 0x280 / Constants::NUMBER_BYTES_IN_HWORD + mConfigBlockIndex * 8); break;
		case 1:
			MainMemory->read(context, buffer, 8, 0x300 / Constants::NUMBER_BYTES_IN_HWORD + mConfigBlockIndex * 8); break;
		case 2:
			MainMemory->read(context, buffer, 8, 0x200 / Constants::NUMBER_BYTES_IN_HWORD + mConfigBlockIndex * 8); break;
		default:
			throw std::runtime_error("CDVD read config block tried to read from invalid config area. Please fix.");
		}

		// Increment block index.
		mConfigBlockIndex++;
	}
	else
	{
		throw std::runtime_error("CDVD read config block was not in read mode... What is meant to happen?");
		// buffer[0] = 0x80;
		// std::fill(&buffer[1], &buffer[1] + 15, 0x00);
	}
}

void CDVDNvram_000_t::writeConfigBlock(const System_t context, const u16 * buffer)
{
	// Check for write mode (1), return magic values otherwise (TODO: check this, throws error for now).
	if (mConfigReadWrite == 1)
	{
		// Check if block is within bounds.
		if (((mConfigAreaIndex == 0) && (mConfigBlockIndex >= 4))
			|| ((mConfigAreaIndex == 1) && (mConfigBlockIndex >= 2))
			|| ((mConfigAreaIndex == 2) && (mConfigBlockIndex >= 7)))
		{
			throw std::runtime_error("CDVD read config block was outside of bounds... What is meant to happen?");
		}

		// Check if block is within the max allowed parameter set.
		if (mConfigBlockIndex >= mConfigMaxBlockIndex)
		{
			throw std::runtime_error("CDVD read config block was outside of max block parameter set... What is meant to happen?");
		}

		// Ok to read a block.
		switch (mConfigAreaIndex)
		{
		case 0:
			MainMemory->write(context, buffer, 8, 0x280 / Constants::NUMBER_BYTES_IN_HWORD + mConfigBlockIndex * 8); break;
		case 1:
			MainMemory->write(context, buffer, 8, 0x300 / Constants::NUMBER_BYTES_IN_HWORD + mConfigBlockIndex * 8); break;
		case 2:
			MainMemory->write(context, buffer, 8, 0x200 / Constants::NUMBER_BYTES_IN_HWORD + mConfigBlockIndex * 8); break;
		default:
			throw std::runtime_error("CDVD read config block tried to read from invalid config area. Please fix.");
		}

		// Increment block index.
		mConfigBlockIndex++;
	}
	else
	{
		throw std::runtime_error("CDVD read config block was not in write mode... What is meant to happen?");
		// buffer[0] = 0x80;
		// std::fill(&buffer[1], &buffer[1] + 15, 0x00);
	}
}

void CDVDNvram_000_t::readConsoleID(const System_t context, u16 * buffer) const
{
	MainMemory->read(context, buffer, 4, 0x1C8 / Constants::NUMBER_BYTES_IN_HWORD);
}

void CDVDNvram_000_t::writeConsoleID(const System_t context, const u16 * buffer)
{
	MainMemory->write(context, buffer, 4, 0x1C8 / Constants::NUMBER_BYTES_IN_HWORD);
}

void CDVDNvram_000_t::readILinkID(const System_t context, u16 * buffer) const
{
	MainMemory->read(context, buffer, 4, 0x1C0 / Constants::NUMBER_BYTES_IN_HWORD);
}

void CDVDNvram_000_t::writeILinkID(const System_t context, const u16 * buffer)
{
	MainMemory->write(context, buffer, 4, 0x1C0 / Constants::NUMBER_BYTES_IN_HWORD);
}

void CDVDNvram_000_t::readModelNumber(const System_t context, u16 * buffer) const
{
	MainMemory->read(context, buffer, 4, 0x1A0 / Constants::NUMBER_BYTES_IN_HWORD);
}

void CDVDNvram_000_t::writeModelNumber(const System_t context, const u16 * buffer)
{
	MainMemory->write(context, buffer, 4, 0x1A0 / Constants::NUMBER_BYTES_IN_HWORD);
}

void CDVDNvram_000_t::readRegionParams(const System_t context, u16 * buffer) const
{
	MainMemory->read(context, buffer, 4, 0x180 / Constants::NUMBER_BYTES_IN_HWORD);
}

void CDVDNvram_000_t::writeRegionParams(const System_t context, const u16 * buffer)
{
	MainMemory->write(context, buffer, 4, 0x180 / Constants::NUMBER_BYTES_IN_HWORD);
}

void CDVDNvram_000_t::readMAC(const System_t context, u16 * buffer) const
{
	MainMemory->read(context, buffer, 4, 0x198 / Constants::NUMBER_BYTES_IN_HWORD);
}

void CDVDNvram_000_t::writeMAC(const System_t context, const u16 * buffer)
{
	MainMemory->write(context, buffer, 4, 0x198 / Constants::NUMBER_BYTES_IN_HWORD);
}
