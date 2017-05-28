#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Register/BitfieldRegister32_t.h"
#include "Common/Types/Register/Register32_t.h"
#include "Common/Tables/EEDmacChannelTable.h"

/*
The DMAC D_CHCR register, aka channel control register.
*/
class EEDmacChannelRegister_CHCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int DIR = 0;
		static constexpr int MOD = 1;
		static constexpr int ASP = 2;
		static constexpr int TTE = 3;
		static constexpr int TIE = 4;
		static constexpr int STR = 5;
		static constexpr int TAG = 6;
	};

	EEDmacChannelRegister_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Returns the channel runtime logical mode its operating in.
	*/
	EEDmacChannelTable::LogicalMode_t getLogicalMode(const Context_t context);

	/*
	Returns the runtime direction. Useful for channels where it can be either way.
	*/
	EEDmacChannelTable::Direction_t getDirection(const Context_t context);

	/*
	Resets the chain mode state (variables below). Meant to be called on every finished tag transfer.
	*/
	void resetChainState();

	/*
	Tag exit flag. Within DMAC logic, set this to true when an exit tag is encountered, and use to check whether to exit from a DMA transfer. Reset this on a finished transfer.
	TODO: I feel like this should be done from within the TAG field... but I can't see a way when considering both the source and dest tag id's.
	*/
	bool mTagExit;

	/*
	Tag stall control flag. Within DMAC logic, set this to true when an stall control tag is encountered, and use to check whether to update STADR or skip a cycle. Reset this on a finished transfer.
	TODO: I feel like this should be done from within the TAG field... but I can't see a way when considering both the source and dest tag id's.
	*/
	bool mTagStallControl;

	/*
	Tag IRQ flag. Within DMAC logic, set this to true when the IRQ flag is set, and use to check whether to interrupt on finishing the tag transfer. Reset this on a finished transfer.
	TODO: I feel like this should be done from within the TAG field... but I can't see a way when considering both the source and dest tag id's.
	*/
	bool mTagIRQ;
};

/*
The DMAC D_MADR register, aka transfer address register.
*/
class EEDmacChannelRegister_MADR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int ADDR = 0;
		static constexpr int SPR = 1;
	};

	EEDmacChannelRegister_MADR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Increments ADDR by 0x10, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment(const Context_t context);
};

/*
The DMAC D_QWC register, aka quadword count register (holds remaining transfer qword count).
*/
class EEDmacChannelRegister_QWC_t : public Register32_t
{
public:
	EEDmacChannelRegister_QWC_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Decrements the QWC counter by 1. Should be called when a data unit has been transferred.
	*/
	void decrement(const Context_t context);
};

/*
The DMAC D_TADR register, aka tag address register.
*/
class EEDmacChannelRegister_TADR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int ADDR = 0;
		static constexpr int SPR = 1;
	};

	EEDmacChannelRegister_TADR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Increments ADDR by 0x10, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment(const Context_t context);
};

/*
The DMAC D_ASR0/1 register, aka tag address save register.
*/
class EEDmacChannelRegister_ASR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int ADDR = 0;
		static constexpr int SPR = 1;
	};

	EEDmacChannelRegister_ASR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The DMAC D_SADR register, aka SPR (scratchpad ram) transfer address register.
*/
class EEDmacChannelRegister_SADR_t : public Register32_t
{
public:
	EEDmacChannelRegister_SADR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Increments ADDR by 0x10, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment(const Context_t context);
};

/*
A base EE TO DMAC D_CHCR register, aka channel control register.
Sets the constant direction (TO) upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
*/
class EEDmacChannelRegister_TO_CHCR_t : public EEDmacChannelRegister_CHCR_t
{
public:
	EEDmacChannelRegister_TO_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	(EE context only.) Upon writes, sets the correct direction (FROM).
	*/
	void writeWord(const Context_t context, const u32 value) override;
};

/*
A base EE FROM DMAC D_CHCR register, aka channel control register.
Sets the constant direction (FROM) upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
*/
class EEDmacChannelRegister_FROM_CHCR_t : public EEDmacChannelRegister_CHCR_t
{
public:
	EEDmacChannelRegister_FROM_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	(EE context only.) Upon writes, sets the correct direction (FROM).
	*/
	void writeWord(const Context_t context, const u32 value) override;
};

/*
The SIF0 DMAC D_CHCR register, aka channel control register.
SIF0 requires access to the SBUS_F240 register (in the EE, this is @ 0x1000F240), which is set on CHCR.STR becoming 1 or 0 (starting or finishing).
As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
TODO: Look into properly RE'ing the SBUS.
TODO: SIF0 direction is IOP -> EE, so need to move the SBUS start update into the IOP side.
*/
class EEDmacChannelRegister_SIF0_CHCR_t : public EEDmacChannelRegister_FROM_CHCR_t
{
public:
	EEDmacChannelRegister_SIF0_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<Register32_t> & sbusF240);

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
	One function for ending a transfer - a starting function should never be called as this is fixed in the FROM direction.
	*/
	void handleSBUSUpdateFinish(const Context_t context) const;
};

/*
The SIF1 DMAC D_CHCR register, aka channel control register.
SIF1 requires access to the SBUS_F240 register (in the EE, this is @ 0x1000F240), which is set on CHCR.STR becoming 1 or 0 (starting or finishing).
As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
TODO: Look into properly RE'ing the SBUS.
*/
class EEDmacChannelRegister_SIF1_CHCR_t : public EEDmacChannelRegister_TO_CHCR_t
{
public:
	EEDmacChannelRegister_SIF1_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<Register32_t> & sbusF240);

	/*
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
	One function for starting a transfer - a ending function should never be called as this is fixed in the TO direction.
	*/
	void handleSBUSUpdateStart(const Context_t context) const;
};

/*
The SIF2 DMAC D_CHCR register, aka channel control register.
SIF2 requires access to the SBUS_F240 register (in the EE, this is @ 0x1000F240), which is set on CHCR.STR becoming 1 or 0 (starting or finishing).
As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
TODO: Look into properly RE'ing the SBUS.
*/
class EEDmacChannelRegister_SIF2_CHCR_t : public EEDmacChannelRegister_CHCR_t
{
public:
	EEDmacChannelRegister_SIF2_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<Register32_t> & sbusF240);

	/*
	Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required. See PCSX2's "sif2.cpp".
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

