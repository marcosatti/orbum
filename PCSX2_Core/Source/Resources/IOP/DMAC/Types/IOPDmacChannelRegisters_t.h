#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"
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
		static constexpr int BS = 0;
		static constexpr int BA = 1;
	};

	IOPDmacChannelRegister_BCR_t(const char * mnemonic);

	/*
	Upon writing, stores the transfer size to be used by the DMAC.
	*/
	void writeHword(const Context_t context, size_t arrayIndex, u16 value) override;
	void writeWord(const Context_t context, u32 value) override;

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
	Increments or decrements the register by a default of 0x4 (1 DMA unit) or the specified size.
	*/
	void increment(const size_t amount = 0x4);
	void decrement(const size_t amount = 0x4);
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
	Increments or decrements the register by a default of 0x4 (1 DMA unit) or the specified size.
	*/
	void increment(const size_t amount = 0x4);
	void decrement(const size_t amount = 0x4);
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
	void writeWord(const Context_t context, u32 value) override;
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
	void writeWord(const Context_t context, u32 value) override;
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
	explicit IOPDmacChannelRegister_SIF0_CHCR_t(const char * mnemonic, const std::shared_ptr<Register32_t> & sbusF240);

	/*
	Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
	See PCSX2's "sif0.cpp".
	*/
	void setFieldValue(const int fieldIndex, const u32 value) override;
	void writeWord(const Context_t context, u32 value) override;

private:
	/*
	Reference to the SBUS_F240 register.
	*/
	std::shared_ptr<Register32_t> mSbusF240;

	/*
	Contains logic for updating the SBUS registers.
	One function for starting a transfer - a ending function should never be called as this is fixed in the TO direction.
	*/
	void handleSBUSUpdateStart() const;
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
	explicit IOPDmacChannelRegister_SIF1_CHCR_t(const char * mnemonic, const std::shared_ptr<Register32_t> & sbusF240);

	/*
	(IOP context only.) Upon writes, sets the chain mode bit (bit 10) to 1.
	Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
	See PCSX2's "sif1.cpp".
	*/
	void setFieldValue(const int fieldIndex, const u32 value) override;
	void writeWord(const Context_t context, u32 value) override;

private:
	/*
	Reference to the SBUS_F240 register.
	*/
	std::shared_ptr<Register32_t> mSbusF240;

	/*
	Contains logic for updating the SBUS registers.
	One function for ending a transfer - a starting function should never be called as this is fixed in the FROM direction. 
	*/
	void handleSBUSUpdateFinish() const;
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
	IOPDmacChannelRegister_SIF2_CHCR_t(const char * mnemonic, const std::shared_ptr<Register32_t> & sbusF240);

	/*
	Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required. 
	See PCSX2's "sif2.cpp".
	*/
	void setFieldValue(const int fieldIndex, const u32 value) override;
	void writeWord(const Context_t context, u32 value) override;

private:
	/*
	Reference to the SBUS_F240 register.
	*/
	std::shared_ptr<Register32_t> mSbusF240;

	/*
	Contains logic for updating the SBUS registers.
	One function for starting a transfer, and ending a transfer.
	*/
	void handleSBUSUpdateStart() const;
	void handleSBUSUpdateFinish() const;
};

