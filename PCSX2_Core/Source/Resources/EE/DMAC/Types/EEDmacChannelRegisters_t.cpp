#include "stdafx.h"

#include "Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"

using LogicalMode_t = EEDmacChannelTable::LogicalMode_t;
using Direction_t = EEDmacChannelTable::Direction_t;

EEDmacChannelRegister_CHCR_t::EEDmacChannelRegister_CHCR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, false, false),
	mTagExit(false),
	mTagStallControl(false),
	mTagIRQ(false)
{
	registerField(Fields::DIR, "DIR", 0, 1, 0);
	registerField(Fields::MOD, "MOD", 2, 2, 0);
	registerField(Fields::ASP, "ASP", 4, 2, 0);
	registerField(Fields::TTE, "TTE", 6, 1, 0);
	registerField(Fields::TIE, "TIE", 7, 1, 0);
	registerField(Fields::STR, "STR", 8, 1, 0);
	registerField(Fields::TAG, "TAG", 16, 16, 0);
}

EEDmacChannelTable::LogicalMode_t EEDmacChannelRegister_CHCR_t::getLogicalMode() const
{
	return static_cast<EEDmacChannelTable::LogicalMode_t>(getFieldValue(Fields::MOD));
}

EEDmacChannelTable::Direction_t EEDmacChannelRegister_CHCR_t::getDirection() const
{
	return static_cast<EEDmacChannelTable::Direction_t>(getFieldValue(Fields::DIR));
}

void EEDmacChannelRegister_CHCR_t::resetChainState()
{
	mTagExit = false;
	mTagStallControl = false;
	mTagIRQ = false;
}

EEDmacChannelRegister_MADR_t::EEDmacChannelRegister_MADR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, false, false)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

void EEDmacChannelRegister_MADR_t::increment()
{
	setFieldValue(Fields::ADDR, getFieldValue(Fields::ADDR) + 0x10);
}

EEDmacChannelRegister_QWC_t::EEDmacChannelRegister_QWC_t(const char * mnemonic) :
	Register32_t(mnemonic, false, false)
{
}

void EEDmacChannelRegister_QWC_t::decrement()
{
	writeWord(RAW, readWord(RAW) - 1);
}

EEDmacChannelRegister_TADR_t::EEDmacChannelRegister_TADR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, false, false)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

void EEDmacChannelRegister_TADR_t::increment()
{
	setFieldValue(Fields::ADDR, getFieldValue(Fields::ADDR) + 0x10);
}

EEDmacChannelRegister_ASR_t::EEDmacChannelRegister_ASR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, false, false)
{
	registerField(Fields::ADDR, "ADDR", 0, 31, 0);
	registerField(Fields::SPR, "SPR", 31, 1, 0);
}

EEDmacChannelRegister_SADR_t::EEDmacChannelRegister_SADR_t(const char * mnemonic) :
	Register32_t(mnemonic, false, false)
{
}

void EEDmacChannelRegister_SADR_t::increment()
{
	writeWord(RAW, readWord(RAW) + 0x10);
}

EEDmacChannelRegister_TO_CHCR_t::EEDmacChannelRegister_TO_CHCR_t(const char* mnemonic) :
	EEDmacChannelRegister_CHCR_t(mnemonic)
{
}

void EEDmacChannelRegister_TO_CHCR_t::writeWord(const Context_t context, u32 value)
{
	if (context == EE)
		value |= (1 << 0);

	EEDmacChannelRegister_CHCR_t::writeWord(context, value);
}

EEDmacChannelRegister_FROM_CHCR_t::EEDmacChannelRegister_FROM_CHCR_t(const char* mnemonic) :
	EEDmacChannelRegister_CHCR_t(mnemonic)
{
}

void EEDmacChannelRegister_FROM_CHCR_t::writeWord(const Context_t context, u32 value)
{
	if (context == EE)
		value &= ~(1 << 0);

	EEDmacChannelRegister_CHCR_t::writeWord(context, value);
}

EEDmacChannelRegister_SIF0_CHCR_t::EEDmacChannelRegister_SIF0_CHCR_t(const char* mnemonic, const std::shared_ptr<Register32_t> & sbusF240) :
	EEDmacChannelRegister_FROM_CHCR_t(mnemonic),
	mSbusF240(sbusF240)
{
}

void EEDmacChannelRegister_SIF0_CHCR_t::setFieldValue(const u8& fieldIndex, const u32& value)
{
	EEDmacChannelRegister_FROM_CHCR_t::setFieldValue(fieldIndex, value);

	// Only bother if its for the STR bit.
	if (fieldIndex == Fields::STR)
	{
		auto start = getFieldValue(Fields::STR);
		auto direction = getDirection();

		// Trigger update based on direction and if we are starting or stopping.
		// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
		if (start > 0 && direction == Direction_t::TO)
			throw std::runtime_error("EE SIF0 channel tried to start in the TO direction! Not possible.");
		else if (start == 0 && direction == Direction_t::FROM)
			handleSBUSUpdateFinish();
	}
}

void EEDmacChannelRegister_SIF0_CHCR_t::writeWord(const Context_t context, u32 value)
{
	EEDmacChannelRegister_FROM_CHCR_t::writeWord(context, value);

	auto start = getFieldValue(Fields::STR);
	auto direction = getDirection();

	// Trigger update based on direction and if we are starting or stopping.
	// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
	if (start > 0 && direction == Direction_t::TO)
		throw std::runtime_error("EE SIF0 channel tried to start in the TO direction! Not possible.");
	else if (start == 0 && direction == Direction_t::FROM)
		handleSBUSUpdateFinish();
}

void EEDmacChannelRegister_SIF0_CHCR_t::handleSBUSUpdateFinish() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic values.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x20));
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x2000));
}

EEDmacChannelRegister_SIF1_CHCR_t::EEDmacChannelRegister_SIF1_CHCR_t(const char* mnemonic, const std::shared_ptr<Register32_t> & sbusF240) :
	EEDmacChannelRegister_TO_CHCR_t(mnemonic),
	mSbusF240(sbusF240)
{
}

void EEDmacChannelRegister_SIF1_CHCR_t::setFieldValue(const u8& fieldIndex, const u32& value)
{
	EEDmacChannelRegister_TO_CHCR_t::setFieldValue(fieldIndex, value);

	// Only bother if its for the STR bit.
	if (fieldIndex == Fields::STR)
	{
		auto start = getFieldValue(Fields::STR);
		auto direction = getDirection();

		// Trigger update based on direction and if we are starting or stopping.
		// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
		if (start > 0 && direction == Direction_t::TO)
			handleSBUSUpdateStart();
		else if (start == 0 && direction == Direction_t::FROM)
			throw std::runtime_error("EE SIF1 channel tried to start in the FROM direction! Not possible.");
	}
}

void EEDmacChannelRegister_SIF1_CHCR_t::writeWord(const Context_t context, u32 value)
{
	EEDmacChannelRegister_TO_CHCR_t::writeWord(context, value);

	auto start = getFieldValue(Fields::STR);
	auto direction = getDirection();

	// Trigger update based on direction and if we are starting or stopping.
	// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
	if (start > 0 && direction == Direction_t::TO)
		handleSBUSUpdateStart();
	else if (start == 0 && direction == Direction_t::FROM)
		throw std::runtime_error("EE SIF1 channel tried to start in the FROM direction! Not possible.");
}

void EEDmacChannelRegister_SIF1_CHCR_t::handleSBUSUpdateStart() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic value.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) | 0x4000);
}

EEDmacChannelRegister_SIF2_CHCR_t::EEDmacChannelRegister_SIF2_CHCR_t(const char* mnemonic, const std::shared_ptr<Register32_t> & sbusF240) :
	EEDmacChannelRegister_CHCR_t(mnemonic),
	mSbusF240(sbusF240)
{
}

void EEDmacChannelRegister_SIF2_CHCR_t::setFieldValue(const u8& fieldIndex, const u32& value)
{
	EEDmacChannelRegister_CHCR_t::setFieldValue(fieldIndex, value);

	// Only bother if its for the STR bit.
	if (fieldIndex == Fields::STR)
	{
		auto str = getFieldValue(Fields::STR);
		auto direction = getDirection();

		// Trigger update based on direction and if we are starting or stopping.
		// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
		if (str > 0 && direction == Direction_t::TO)
			handleSBUSUpdateStart();
		else if (str == 0 && direction == Direction_t::FROM)
			handleSBUSUpdateFinish();
	}
}

void EEDmacChannelRegister_SIF2_CHCR_t::writeWord(const Context_t context, u32 value)
{
	EEDmacChannelRegister_CHCR_t::writeWord(context, value);
	
	auto str = getFieldValue(Fields::STR);
	auto direction = getDirection();

	// Trigger update based on direction and if we are starting or stopping.
	// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
	if (str > 0 && direction == Direction_t::TO)
		handleSBUSUpdateStart();
	else if (str == 0 && direction == Direction_t::FROM)
		handleSBUSUpdateFinish();
}

void EEDmacChannelRegister_SIF2_CHCR_t::handleSBUSUpdateStart() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic value.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) | 0x8000);
}

void EEDmacChannelRegister_SIF2_CHCR_t::handleSBUSUpdateFinish() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic values.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x80));
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x8000));
}
