#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Register/BitfieldRegister32_t.h"
#include "Common/Tables/IOPDmacChannelTable.h"

/*
The IOP DMAC D_CHCR register.
Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
*/
class IOPDmacChannelRegister_CHCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int TD = 0;
		static constexpr int MAS = 1;
		static constexpr int CE = 2;
		static constexpr int SM = 3;
		static constexpr int ILinkUnk = 4;
		static constexpr int C_DWS = 5;
		static constexpr int C_CWS = 6;
		static constexpr int Start = 7;
		static constexpr int Force = 8;
		static constexpr int ForceSlice = 9;
		static constexpr int BusSnooping = 10;
		static constexpr int ILinkAR = 11;
	};

	IOPDmacChannelRegister_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Returns the channel runtime logical mode its operating in.
	*/
	IOPDmacChannelTable::LogicalMode_t getLogicalMode(const Context_t context);

	/*
	Gets the runtime direction. Useful for channels where it can be either way.
	*/
	IOPDmacChannelTable::Direction_t getDirection(const Context_t context);
	
	/*
	Resets the flags below when START = 1 is written.
	*/
	void writeWord(const Context_t context, const u32 value) override;

	/*
	DMA started flag. Used to indicate if a DMA transfer is in progress, in order for the DMAC to perform some initial and final checks.
	An example of the DMAC using this is to check for an initial invalid transfer length.
	Reset to false upon writing to this register.
	*/
	bool mDMAStarted;

	/*
	Tag exit flag. Within DMAC logic, set to true when an exit tag is encountered, and use to check whether to exit from a DMA transfer.
	Reset to false upon writing to this register.
	*/
	bool mTagExit;

	/*
	Tag IRQ flag. Within DMAC logic, set this to true when the IRQ flag is set, and use to check whether to interrupt on finishing the tag transfer. 
	Reset to false upon writing to this register.
	*/
	bool mTagIRQ;
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
		static constexpr int BS = 0;
		static constexpr int BA = 1;
	};

	IOPDmacChannelRegister_BCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Calculates the transfer size, based on the BCR register value.
	Call this before starting a DMA transfer, and then use the transfer length member directly.
	Parsing useBA = true means a block mode transfer size is calculated, otherwise, slice mode is calculated.
	*/
	void calculate(const Context_t context, const bool useBA);

	/*
	Transfer size.
	The register value is not meant to change during the transfer.
	Instead, the total length after calling calculate() is stored here.
	This is directly accessible to the IOP DMAC which manipulates this value.
	*/
	size_t mTransferLength;
};

/*
The DMAC D_MADR register, aka transfer address register.
Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
*/
class IOPDmacChannelRegister_MADR_t : public Register32_t
{
public:
	IOPDmacChannelRegister_MADR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Increments or decrements the register by a default of 0x4 (1 DMA unit) or the specified size.
	*/
	void increment(const Context_t context, const size_t amount = 0x4);
	void decrement(const Context_t context, const size_t amount = 0x4);
};

/*
The DMAC D_TADR register, aka transfer address register.
Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
*/
class IOPDmacChannelRegister_TADR_t : public Register32_t
{
public:
	IOPDmacChannelRegister_TADR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Increments or decrements the register by a default of 0x4 (1 DMA unit) or the specified size.
	*/
	void increment(const Context_t context, const size_t amount = 0x4);
	void decrement(const Context_t context, const size_t amount = 0x4);
};

/*
A base IOP TO DMAC D_CHCR register.
Sets the constant direction (TO) upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
*/
class IOPDmacChannelRegister_TO_CHCR_t : public IOPDmacChannelRegister_CHCR_t
{
public:
	IOPDmacChannelRegister_TO_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	(IOP context only.) Upon writes, sets the correct direction (FROM).
	*/
	void writeWord(const Context_t context, const u32 value) override;
};

/*
A base IOP FROM DMAC D_CHCR register.
Sets the constant direction (FROM) upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
*/
class IOPDmacChannelRegister_FROM_CHCR_t : public IOPDmacChannelRegister_CHCR_t
{
public:
	IOPDmacChannelRegister_FROM_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	(IOP context only.) Upon writes, sets the correct direction (FROM).
	*/
	void writeWord(const Context_t context, const u32 value) override;
};

/*
The IOP DMAC SIF0 CHCR register.
SIF0 requires access to the SBUS_F240 register (in the IOP, this is @ 0x1D000040), which is set on CHCR.Start becoming 1 or 0 (starting or finishing).
As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
TODO: Look into properly RE'ing the SBUS.
*/
class IOPDmacChannelRegister_SIF0_CHCR_t : public IOPDmacChannelRegister_TO_CHCR_t
{
public:
	IOPDmacChannelRegister_SIF0_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<Register32_t> & sbusF240);

	/*
	Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
	See PCSX2's "sif0.cpp".
	*/
	void setFieldValue(const Context_t context, const int fieldIndex, const u32 value) override;
	void writeWord(const Context_t context, const u32 value) override;

private:
	/*
	Reference to the SBUS_F240 register.
	*/
	std::shared_ptr<Register32_t> mSbusF240;

	/*
	Contains logic for updating the SBUS registers.
	One function for starting a transfer - a ending function should never be called as this is fixed in the TO direction.
	*/
	void handleSBUSUpdateStart(const Context_t context) const;
};

/*
The IOP DMAC SIF1 CHCR register.
Sets the chain mode bit to 1 upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
SIF1 requires access to the SBUS_F240 register (in the IOP, this is @ 0x1D000040), which is set on CHCR.Start becoming 1 or 0 (starting or finishing).
As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
TODO: Look into properly RE'ing the SBUS.
*/
class IOPDmacChannelRegister_SIF1_CHCR_t : public IOPDmacChannelRegister_FROM_CHCR_t
{
public:
	IOPDmacChannelRegister_SIF1_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<Register32_t> & sbusF240);

	/*
	(IOP context only.) Upon writes, sets the chain mode bit (bit 10) to 1.
	Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
	See PCSX2's "sif1.cpp".
	*/
	void setFieldValue(const Context_t context, const int fieldIndex, const u32 value) override;
	void writeWord(const Context_t context, const u32 value) override;

private:
	/*
	Reference to the SBUS_F240 register.
	*/
	std::shared_ptr<Register32_t> mSbusF240;

	/*
	Contains logic for updating the SBUS registers.
	One function for ending a transfer - a starting function should never be called as this is fixed in the FROM direction. 
	*/
	void handleSBUSUpdateFinish(const Context_t context) const;
};

/*
The SIF2 DMAC D_CHCR register, aka channel control register.
SIF2 requires access to the SBUS_F240 register (in the IOP, this is @ 0x1D000040), which is set on CHCR.Start becoming 1 or 0 (starting or finishing).
As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
TODO: Look into properly RE'ing the SBUS.
*/
class IOPDmacChannelRegister_SIF2_CHCR_t : public IOPDmacChannelRegister_CHCR_t
{
public:
	IOPDmacChannelRegister_SIF2_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<Register32_t> & sbusF240);

	/*
	Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required. 
	See PCSX2's "sif2.cpp".
	*/
	void setFieldValue(const Context_t context, const int fieldIndex, const u32 value) override;
	void writeWord(const Context_t context, const u32 value) override;

private:
	/*
	Reference to the SBUS_F240 register.
	*/
	std::shared_ptr<Register32_t> mSbusF240;

	/*
	Contains logic for updating the SBUS registers.
	One function for starting a transfer, and ending a transfer.
	*/
	void handleSBUSUpdateStart(const Context_t context) const;
	void handleSBUSUpdateFinish(const Context_t context) const;
};

