#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Tables/IOPDmacChannelTable/IOPDmacChannelTable.h"

/*
The IOP DMAC D_CHCR register.
Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
*/
class IOPDmacChannelRegister_CHCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 TD = 0;
		static constexpr u8 MAS = 1;
		static constexpr u8 CE = 2;
		static constexpr u8 SM = 3;
		static constexpr u8 ILinkUnk = 4;
		static constexpr u8 C_DWS = 5;
		static constexpr u8 C_CWS = 6;
		static constexpr u8 Start = 7;
		static constexpr u8 Force = 8;
		static constexpr u8 ForceSlice = 9;
		static constexpr u8 BusSnooping = 10;
		static constexpr u8 ILinkAR = 11;
	};

	IOPDmacChannelRegister_CHCR_t(const char * mnemonic);

	/*
	Returns the channel runtime logical mode its operating in.
	*/
	IOPDmacChannelTable::LogicalMode_t getLogicalMode() const;

	/*
	Gets the runtime direction. Useful for channels where it can be either way.
	*/
	IOPDmacChannelTable::Direction_t getDirection() const;

	/*
	Resets the chain mode state (variables below). Meant to be called on every finished tag transfer.
	*/
	void resetChainState();

	/*
	Tag exit flag. Within DMAC logic, set this to true when an exit tag is encountered, and use to check whether to exit from a DMA transfer. Reset this on a finished transfer.
	*/
	bool mTagExit;

	/*
	Tag IRQ flag. Within DMAC logic, set this to true when the IRQ flag is set, and use to check whether to interrupt on finishing the tag transfer. Reset this on a finished transfer.
	*/
	bool mTagIRQ;

	/*
	Chain mode transfer length. Set upon reading a tag and decremented on every unit transfered.
	*/
	size_t mTagTransferLength;
};

/*
The IOP DMAC D_BCR register.
Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
*/
class IOPDmacChannelRegister_BCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 BS = 0;
		static constexpr u8 BA = 1;
	};

	IOPDmacChannelRegister_BCR_t(const char * mnemonic);

	/*
	Upon writing, stores the transfer size to be used by the DMAC.
	*/
	void writeHword(const Context_t& context, size_t arrayIndex, u16 value) override;
	void writeWord(const Context_t & context, u32 value) override;

	/*
	Decrements the transfer size by 1.
	*/
	void decrement();

	/*
	Returns if the transfer size is finished.
	checkBS controls whether to check if both BS and BA are equal to 0 or just check if BS is equal to 0 (use in slice or burst mode respectively).
	*/
	bool isFinished(bool checkBS) const;

private:
	/*
	Internal transfer size parameters.
	The register value is not meant to change during the transfer.
	*/
	u16 mBS;
	u16 mBA;
};

/*
The DMAC D_MADR register, aka transfer address register.
Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
*/
class IOPDmacChannelRegister_MADR_t : public Register32_t
{
public:
	IOPDmacChannelRegister_MADR_t(const char * mnemonic);

	/*
	Increments or decrements the register by 0x4 (word), which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment();
	void decrement();
};

/*
The DMAC D_TADR register, aka transfer address register.
Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
*/
class IOPDmacChannelRegister_TADR_t : public Register32_t
{
public:
	IOPDmacChannelRegister_TADR_t(const char * mnemonic);

	/*
	Increments or decrements the register by 0x4, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment();
	void decrement();
};

/*
A base IOP TO DMAC D_CHCR register.
Sets the constant direction (TO) upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
*/
class IOPDmacChannelRegister_TO_CHCR_t : public IOPDmacChannelRegister_CHCR_t
{
public:
	explicit IOPDmacChannelRegister_TO_CHCR_t(const char * mnemonic);

	/*
	(IOP context only.) Upon writes, sets the correct direction (FROM).
	*/
	void writeWord(const Context_t& context, u32 value) override;
};

/*
A base IOP FROM DMAC D_CHCR register.
Sets the constant direction (FROM) upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
*/
class IOPDmacChannelRegister_FROM_CHCR_t : public IOPDmacChannelRegister_CHCR_t
{
public:
	explicit IOPDmacChannelRegister_FROM_CHCR_t(const char * mnemonic);

	/*
	(IOP context only.) Upon writes, sets the correct direction (FROM).
	*/
	void writeWord(const Context_t& context, u32 value) override;
};

/*
The IOP DMAC SIF1 CHCR register.
Sets the chain mode bit to 1 upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
*/
class IOPDmacChannelRegister_SIF1_CHCR_t : public IOPDmacChannelRegister_FROM_CHCR_t
{
public:
	explicit IOPDmacChannelRegister_SIF1_CHCR_t(const char * mnemonic);

	/*
	(IOP context only.) Upon writes, sets the chain mode bit (bit 10) to 1.
	*/
	void writeWord(const Context_t& context, u32 value) override;
};