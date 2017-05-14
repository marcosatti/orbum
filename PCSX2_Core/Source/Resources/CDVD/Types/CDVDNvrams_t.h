#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class HwordMemory_t;

/*
Contains information about the CDVD NVRAM state, used to store various data.
Undocumented - see PCSX2's CDVD.h/cpp.

There are 6 pieces of important information the NVRAM holds, in addition to the raw memory space it provides:
 - Config areas ("0"/"1"/"2"), accessed by blocks (a block is 16 bytes).
 - Console ID (8 bytes).
 - iLink ID (8 bytes).
 - Model Number (8 bytes).
 - Region Parameters (PStwo bios' only?) (8 bytes).
 - MAC (acronym for???) (PStwo bios' only?) (8 bytes).
While the memory space is always 1KB, the location of these special areas are different across bios versions (see .cpp file for locations/offsets).
Read/write virtual functions have been provided for these areas, that can be used to support different bios'.
The NVRAM is also exposed directly, needed by the CDVD system logic.

TODO: only valid for bios' v0.00 -> v1.70, look into others later.
*/
class CDVDNvram_t
{
public:
	/*
	Static NVRAM information:
	 - Magic values for the iLink data section (written to NVRAM upon initialisation by CDVD logic).
	*/
	static constexpr u8 ILINK_DATA_MAGIC[8] = { 0x00, 0xAC, 0xFF, 0xFF, 0xFF, 0xFF, 0xB9, 0x86 };

	CDVDNvram_t();
	virtual ~CDVDNvram_t() = default;

	/*
	NVRAM memory space.
	1KB of space total, Hword addressable.
	*/
	std::shared_ptr<HwordMemory_t> MainMemory;

	/*
	Sets the NVRAM config access paramters below, used for reading/writing to config areas.
	Common across all bios versions (not virutal).
	*/
	void setConfigAccessParams(const int readWrite, const int areaIndex, const int maxBlockIndex, const int blockIndex);

	/*
	Reads the next block (const System_t context, 16 bytes / 8 hwords) to the buffer given, based upon the config access parameters set.
	*/
	virtual void readConfigBlock(const System_t context, u16 * buffer) = 0;

	/*
	Writes the next block (const System_t context, 16 bytes / 8 hwords) from the buffer given, based upon the config access parameters set.
	*/
	virtual void writeConfigBlock(const System_t context, const u16 * buffer) = 0;

	/*
	Reads the console ID to the buffer given (const System_t context, 8 bytes / 4 hwords).
	*/
	virtual void readConsoleID(const System_t context, u16 * buffer) const = 0;

	/*
	Writes the console ID from the buffer given (const System_t context, 8 bytes / 4 hwords).
	*/
	virtual void writeConsoleID(const System_t context, const u16 * buffer) = 0;
	
	/*
	Reads the iLink ID to the buffer given (const System_t context, 8 bytes / 4 hwords).
	*/
	virtual void readILinkID(const System_t context, u16 * buffer) const = 0;

	/*
	Writes the iLink ID from the buffer given (const System_t context, 8 bytes / 4 hwords).
	*/
	virtual void writeILinkID(const System_t context, const u16 * buffer) = 0;

	/*
	Reads the model number to the buffer given (const System_t context, 8 bytes / 4 hwords).
	*/
	virtual void readModelNumber(const System_t context, u16 * buffer) const = 0;

	/*
	Writes the model number from of the buffer given (const System_t context, 8 bytes / 4 hwords).
	*/
	virtual void writeModelNumber(const System_t context, const u16 * buffer) = 0;

	/*
	Reads the region params to the buffer given (const System_t context, 8 bytes / 4 hwords).
	*/
	virtual void readRegionParams(const System_t context, u16 * buffer) const = 0;

	/*
	Writes the region params from of the buffer given (const System_t context, 8 bytes / 4 hwords).
	*/
	virtual void writeRegionParams(const System_t context, const u16 * buffer) = 0;

	/*
	Reads the MAC to the buffer given (const System_t context, 8 bytes / 4 hwords).
	*/
	virtual void readMAC(const System_t context, u16 * buffer) const = 0;

	/*
	Writes the MAC from of the buffer given (const System_t context, 8 bytes / 4 hwords).
	*/
	virtual void writeMAC(const System_t context, const u16 * buffer) = 0;

protected:
	/*
	Config access state variables including:
	 - Read or write status (0 = read, 1 = write).
	 - Current config area being accessed.
	 - Maximum block index allowed within config area (not really sure why this is a thing...).
	 - Current block index within config area.
	TODO: look into this... it kinda doesn't make a whole lot of sense.

	Block map:
	 - Config 0: 4 blocks (64B).
	 - Config 1: 2 blocks (32B).
	 - Config 2: 7 blocks (112B).
	*/
	int mConfigReadWrite;
	int mConfigAreaIndex;
	int mConfigMaxBlockIndex;
	int mConfigBlockIndex;
};

/*
Class representing the NVRAM for bios versions v0.00 <= x < 1.70.
*/
class CDVDNvram_000_t : public CDVDNvram_t
{
public:
	CDVDNvram_000_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Implementation of the NVRAM virtual functions.
	Contains magic size and offset values - see within functions for the values.
	*/
	void readConfigBlock(const System_t context, u16 * buffer) override;
	void writeConfigBlock(const System_t context, const u16 * buffer) override;
	void readConsoleID(const System_t context, u16 * buffer) const override;
	void writeConsoleID(const System_t context, const u16 * buffer) override;
	void readILinkID(const System_t context, u16 * buffer) const override;
	void writeILinkID(const System_t context, const u16 * buffer) override;
	void readModelNumber(const System_t context, u16 * buffer) const override;
	void writeModelNumber(const System_t context, const u16 * buffer) override;
	void readRegionParams(const System_t context, u16 * buffer) const override;
	void writeRegionParams(const System_t context, const u16 * buffer) override;
	void readMAC(const System_t context, u16 * buffer) const override;
	void writeMAC(const System_t context, const u16 * buffer) override;
};