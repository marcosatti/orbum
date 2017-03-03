#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Tables/IOPDmacChannelTable/IOPDmacChannelTable.h"

/*
The IOP DMAC D_CHCR register.
Based off the PSX docs.
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
};

/*
The IOP DMAC D_BCR register.
Based of the nocash PSX docs.
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
	checkBS controls whether to check if both BS and BA are equal to 0 or just check if BS is equal to 0 (use in linked-list/chain or normal modes respectively).
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
The DMAC D_MADR register, aka transfer address register.
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