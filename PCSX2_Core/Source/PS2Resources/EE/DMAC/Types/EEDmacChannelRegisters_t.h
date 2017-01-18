#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Types/Registers/Register32_t.h"

/*
The DMAC D_CHCR register, aka channel control register.
Needs a reference to a slice count variable that is reset when the STR bit is set to 1.
*/
class EEDmacChannelRegister_CHCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 DIR = 0;
		static constexpr u8 MOD = 1;
		static constexpr u8 ASP = 2;
		static constexpr u8 TTE = 3;
		static constexpr u8 TIE = 4;
		static constexpr u8 STR = 5;
		static constexpr u8 TAG = 6;
	};

	EEDmacChannelRegister_CHCR_t(const char * mnemonic);
};

/*
The DMAC D_MADR register, aka transfer address register.
*/
class EEDmacChannelRegister_MADR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	EEDmacChannelRegister_MADR_t(const char * mnemonic);

	/*
	Increments ADDR by 0x10, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment();
};

/*
The DMAC D_QWC register, aka quadword count register (holds remaining transfer qword count).
*/
class EEDmacChannelRegister_QWC_t : public Register32_t
{
public:
	EEDmacChannelRegister_QWC_t(const char * mnemonic);

	/*
	Decrements the QWC counter by 1. Should be called when a data unit has been transferred.
	*/
	void decrement();
};

/*
The DMAC D_TADR register, aka tag address register.
*/
class EEDmacChannelRegister_TADR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	EEDmacChannelRegister_TADR_t(const char * mnemonic);

	/*
	Increments ADDR by 0x10, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment();
};

/*
The DMAC D_ASR0/1 register, aka tag address save register.
*/
class EEDmacChannelRegister_ASR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ADDR = 0;
		static constexpr u8 SPR = 1;
	};

	EEDmacChannelRegister_ASR_t(const char * mnemonic);
};

/*
The DMAC D_SADR register, aka SPR (scratchpad ram) transfer address register.
*/
class EEDmacChannelRegister_SADR_t : public Register32_t
{
public:
	EEDmacChannelRegister_SADR_t(const char * mnemonic);

	/*
	Increments ADDR by 0x10, which is the size of 1 DMA transfer (used when one transfer has completed).
	*/
	void increment();
};

/*
The SIF0 DMAC D_CHCR register, aka channel control register.
SIF0 requires access to the SBUS_F240 register (in the EE, this is @ 0x1000F240), which is set on CHCR.STR becoming 1 or 0 (starting or finishing).
As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
TODO: Look into properly RE'ing the SBUS.
*/
class EEDmacChannelRegister_SIF0_CHCR_t : public EEDmacChannelRegister_CHCR_t
{
public:
	EEDmacChannelRegister_SIF0_CHCR_t(const char * mnemonic, std::shared_ptr<Register32_t> & sbusF240);

	/*
	Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
	See PCSX2's "sif0.cpp".
	*/
	void setFieldValue(const u8& fieldIndex, const u32& value) override;
	void writeWord(const Context_t& context, u32 value) override;

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

/*
The SIF1 DMAC D_CHCR register, aka channel control register.
SIF1 requires access to the SBUS_F240 register (in the EE, this is @ 0x1000F240), which is set on CHCR.STR becoming 1 or 0 (starting or finishing).
As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
TODO: Look into properly RE'ing the SBUS.
*/
class EEDmacChannelRegister_SIF1_CHCR_t : public EEDmacChannelRegister_CHCR_t
{
public:
	EEDmacChannelRegister_SIF1_CHCR_t(const char * mnemonic, std::shared_ptr<Register32_t> & sbusF240);

	/*
	Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
	See PCSX2's "sif1.cpp".
	*/
	void setFieldValue(const u8& fieldIndex, const u32& value) override;
	void writeWord(const Context_t& context, u32 value) override;

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

/*
The SIF2 DMAC D_CHCR register, aka channel control register.
SIF2 requires access to the SBUS_F240 register (in the EE, this is @ 0x1000F240), which is set on CHCR.STR becoming 1 or 0 (starting or finishing).
As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
TODO: Look into properly RE'ing the SBUS.
*/
class EEDmacChannelRegister_SIF2_CHCR_t : public EEDmacChannelRegister_CHCR_t
{
public:
	EEDmacChannelRegister_SIF2_CHCR_t(const char * mnemonic, std::shared_ptr<Register32_t> & sbusF240);

	/*
	Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
	See PCSX2's "sif2.cpp".
	*/
	void setFieldValue(const u8& fieldIndex, const u32& value) override;
	void writeWord(const Context_t& context, u32 value) override;

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

