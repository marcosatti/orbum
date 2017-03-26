#include "stdafx.h"

#include "Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"

using LogicalMode_t = IOPDmacChannelTable::LogicalMode_t;
using Direction_t = IOPDmacChannelTable::Direction_t;

IOPDmacChannelRegister_CHCR_t::IOPDmacChannelRegister_CHCR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, false, false),
	mTagExit(false),
	mTagIRQ(false),
	mTagTransferLength(0)
{
	registerField(Fields::TD, "TD", 0, 1, 0);
	registerField(Fields::MAS, "MAS", 1, 1, 0);
	registerField(Fields::CE, "CE", 8, 1, 0);
	registerField(Fields::SM, "SM", 9, 2, 0);
	registerField(Fields::ILinkUnk, "ILinkUnk", 11, 1, 0);
	registerField(Fields::C_DWS, "C_DWS", 16, 3, 0);
	registerField(Fields::C_CWS, "C_CWS", 20, 3, 0);
	registerField(Fields::Start, "Start", 24, 1, 0);
	registerField(Fields::Force, "Force", 28, 1, 0);
	registerField(Fields::ForceSlice, "ForceSlice", 29, 1, 0);
	registerField(Fields::BusSnooping, "BusSnooping", 30, 1, 0);
	registerField(Fields::ILinkAR, "ILinkAR", 31, 1, 0);
}

LogicalMode_t IOPDmacChannelRegister_CHCR_t::getLogicalMode() const
{
	return static_cast<LogicalMode_t>(getFieldValue(Fields::SM));
}

Direction_t IOPDmacChannelRegister_CHCR_t::getDirection() const
{
	return static_cast<Direction_t>(getFieldValue(Fields::TD));
}

void IOPDmacChannelRegister_CHCR_t::resetChainState()
{
	mTagExit = false;
	mTagIRQ = false;
	mTagTransferLength = 0;
}

IOPDmacChannelRegister_BCR_t::IOPDmacChannelRegister_BCR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, false, false),
	mBS(0),
	mBA(0)
{
	registerField(Fields::BS, "BS", 0, 16, 0);
	registerField(Fields::BA, "BA", 16, 16, 0);
}

void IOPDmacChannelRegister_BCR_t::writeHword(const Context_t context, size_t arrayIndex, u16 value)
{
	BitfieldRegister32_t::writeHword(context, arrayIndex, value);

	// Update the transfer size.
	mBS = static_cast<u16>(getFieldValue(Fields::BS));
	mBA = static_cast<u16>(getFieldValue(Fields::BA));
}

void IOPDmacChannelRegister_BCR_t::writeWord(const Context_t context, u32 value)
{
	BitfieldRegister32_t::writeWord(context, value);

	// Update the transfer size.
	mBS = static_cast<u16>(getFieldValue(Fields::BS));
	mBA = static_cast<u16>(getFieldValue(Fields::BA));
}

void IOPDmacChannelRegister_BCR_t::decrement()
{
	// If BS was set to 0 and we are in normal transfer mode (ie: transfer 0x10000 words), we rely on underflow to get us to the proper value (0xFFFF).
	mBS--;

	// Only decrement BA if there is blocks remaining, otherwise we are at the end of a transfer for chain/linked-list mode (there is no 0xFFFF thing like BS).
	if (mBS == 0 && mBA > 0)
		mBA--;
}

bool IOPDmacChannelRegister_BCR_t::isFinished(bool checkBS) const
{
	if (checkBS)
		return (mBS == 0 && mBA == 0);
	else
		return (mBS == 0);
}

IOPDmacChannelRegister_MADR_t::IOPDmacChannelRegister_MADR_t(const char* mnemonic) :
	Register32_t(mnemonic)
{
}

void IOPDmacChannelRegister_MADR_t::increment(const size_t amount)
{
	writeWord(RAW, readWord(RAW) + static_cast<u32>(amount));
}

void IOPDmacChannelRegister_MADR_t::decrement(const size_t amount)
{
	writeWord(RAW, readWord(RAW) - static_cast<u32>(amount));
}

IOPDmacChannelRegister_TADR_t::IOPDmacChannelRegister_TADR_t(const char* mnemonic) :
	Register32_t(mnemonic, false, false)
{
}

void IOPDmacChannelRegister_TADR_t::increment(const size_t amount)
{
	writeWord(RAW, readWord(RAW) + static_cast<u32>(amount));
}

void IOPDmacChannelRegister_TADR_t::decrement(const size_t amount)
{
	writeWord(RAW, readWord(RAW) - static_cast<u32>(amount));
}

IOPDmacChannelRegister_TO_CHCR_t::IOPDmacChannelRegister_TO_CHCR_t(const char* mnemonic) :
	IOPDmacChannelRegister_CHCR_t(mnemonic)
{
}

void IOPDmacChannelRegister_TO_CHCR_t::writeWord(const Context_t context, u32 value)
{
	if (context == IOP)
		value |= (1 << 0);

	IOPDmacChannelRegister_CHCR_t::writeWord(context, value);
}

IOPDmacChannelRegister_FROM_CHCR_t::IOPDmacChannelRegister_FROM_CHCR_t(const char* mnemonic) :
	IOPDmacChannelRegister_CHCR_t(mnemonic)
{
}

void IOPDmacChannelRegister_FROM_CHCR_t::writeWord(const Context_t context, u32 value)
{
	if (context == IOP)
		value &= ~(1 << 0);

	IOPDmacChannelRegister_CHCR_t::writeWord(context, value);
}

IOPDmacChannelRegister_SIF0_CHCR_t::IOPDmacChannelRegister_SIF0_CHCR_t(const char * mnemonic, const std::shared_ptr<Register32_t>& sbusF240) :
	IOPDmacChannelRegister_TO_CHCR_t(mnemonic),
	mSbusF240(sbusF240)
{
}

void IOPDmacChannelRegister_SIF0_CHCR_t::setFieldValue(const u8 & fieldIndex, const u32 & value)
{
	IOPDmacChannelRegister_TO_CHCR_t::setFieldValue(fieldIndex, value);

	// Only bother if its for the Start bit.
	if (fieldIndex == Fields::Start)
	{
		auto start = getFieldValue(Fields::Start);
		auto direction = getDirection();

		// Trigger update based on direction and if we are starting or stopping.
		// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
		if (start > 0 && direction == Direction_t::TO)
			handleSBUSUpdateStart();
		else if (start == 0 && direction == Direction_t::FROM)
			throw std::runtime_error("IOP SIF0 channel tried to start in the FROM direction! Not possible.");
	}
}

void IOPDmacChannelRegister_SIF0_CHCR_t::writeWord(const Context_t context, u32 value)
{
	IOPDmacChannelRegister_TO_CHCR_t::writeWord(context, value);

	auto start = getFieldValue(Fields::Start);
	auto direction = getDirection();

	// Trigger update based on direction and if we are starting or stopping.
	// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
	if (start > 0 && direction == Direction_t::TO)
		handleSBUSUpdateStart();
	else if (start == 0 && direction == Direction_t::FROM)
		throw std::runtime_error("IOP SIF0 channel tried to start in the FROM direction! Not possible.");
}

void IOPDmacChannelRegister_SIF0_CHCR_t::handleSBUSUpdateStart() const
{
	// Update 0x1D000040 (maps to Common->REGISTER_F240) with magic value.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) | 0x2000);
}

IOPDmacChannelRegister_SIF1_CHCR_t::IOPDmacChannelRegister_SIF1_CHCR_t(const char* mnemonic, const std::shared_ptr<Register32_t> & sbusF240) :
	IOPDmacChannelRegister_FROM_CHCR_t(mnemonic),
	mSbusF240(sbusF240)
{
}

void IOPDmacChannelRegister_SIF1_CHCR_t::setFieldValue(const u8 & fieldIndex, const u32 & value)
{
	IOPDmacChannelRegister_FROM_CHCR_t::setFieldValue(fieldIndex, value);

	// Only bother if its for the Start bit.
	if (fieldIndex == Fields::Start)
	{
		auto start = getFieldValue(Fields::Start);
		auto direction = getDirection();

		// Trigger update based on direction and if we are starting or stopping.
		// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
		if (start > 0 && direction == Direction_t::TO)
			throw std::runtime_error("IOP SIF1 channel tried to start in the TO direction! Not possible.");
		else if (start == 0 && direction == Direction_t::FROM)
			handleSBUSUpdateFinish();
	}
}

void IOPDmacChannelRegister_SIF1_CHCR_t::writeWord(const Context_t context, u32 value)
{
	if (context == IOP)
		value |= (1 << 10);

	IOPDmacChannelRegister_FROM_CHCR_t::writeWord(context, value);

	auto start = getFieldValue(Fields::Start);
	auto direction = getDirection();

	// Trigger update based on direction and if we are starting or stopping.
	// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
	if (start > 0 && direction == Direction_t::TO)
		throw std::runtime_error("IOP SIF1 channel tried to start in the TO direction! Not possible.");
	else if (start == 0 && direction == Direction_t::FROM)
		handleSBUSUpdateFinish();
}

void IOPDmacChannelRegister_SIF1_CHCR_t::handleSBUSUpdateFinish() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic values.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x40));
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x4000));
}

IOPDmacChannelRegister_SIF2_CHCR_t::IOPDmacChannelRegister_SIF2_CHCR_t(const char * mnemonic, const std::shared_ptr<Register32_t>& sbusF240) :
	IOPDmacChannelRegister_CHCR_t(mnemonic),
	mSbusF240(sbusF240)
{
}

void IOPDmacChannelRegister_SIF2_CHCR_t::setFieldValue(const u8 & fieldIndex, const u32 & value)
{
	IOPDmacChannelRegister_CHCR_t::setFieldValue(fieldIndex, value);

	// Only bother if its for the Start bit.
	if (fieldIndex == Fields::Start)
	{
		auto start = getFieldValue(Fields::Start);
		auto direction = getDirection();

		// Trigger update based on direction and if we are starting or stopping.
		// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
		if (start > 0 && direction == Direction_t::TO)
			handleSBUSUpdateStart();
		else if (start == 0 && direction == Direction_t::FROM)
			handleSBUSUpdateFinish();
	}
}

void IOPDmacChannelRegister_SIF2_CHCR_t::writeWord(const Context_t context, u32 value)
{
	IOPDmacChannelRegister_CHCR_t::writeWord(context, value);

	auto start = getFieldValue(Fields::Start);
	auto direction = getDirection();

	// Trigger update based on direction and if we are starting or stopping.
	// 2 triggers to consider: starting and direction = TO, stopping and direction = FROM.
	if (start > 0 && direction == Direction_t::TO)
		handleSBUSUpdateStart();
	else if (start == 0 && direction == Direction_t::FROM)
		handleSBUSUpdateFinish();
}

void IOPDmacChannelRegister_SIF2_CHCR_t::handleSBUSUpdateStart() const
{
	// Update 0x1D000040 (maps to Common->REGISTER_F240) with magic value.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) | 0x8000);
}

void IOPDmacChannelRegister_SIF2_CHCR_t::handleSBUSUpdateFinish() const
{
	// Update 0x1D000040 (maps to Common->REGISTER_F240) with magic values.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x80));
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x8000));
}

