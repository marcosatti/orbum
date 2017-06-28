#include "Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"

using LogicalMode_t = IOPDmacChannelTable::LogicalMode_t;
using Direction_t = IOPDmacChannelTable::Direction_t;

IOPDmacChannelRegister_CHCR_t::IOPDmacChannelRegister_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites),
	mDMAStarted(false),
	mTagExit(false),
	mTagIRQ(false)
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

LogicalMode_t IOPDmacChannelRegister_CHCR_t::getLogicalMode(const Context_t context) 
{
	return static_cast<LogicalMode_t>(getFieldValue(context, Fields::SM));
}

Direction_t IOPDmacChannelRegister_CHCR_t::getDirection(const Context_t context)
{
	return static_cast<Direction_t>(getFieldValue(context, Fields::TD));
}

void IOPDmacChannelRegister_CHCR_t::writeWord(const Context_t context, const u32 value)
{
	auto startOld = getFieldValue(context, Fields::Start);

	BitfieldRegister32_t::writeWord(context, value);

	auto startNew = getFieldValue(context, Fields::Start);

	// Reset DMA flags on suspended -> start.
	if ((startOld == 0) && (startNew != 0))
	{
		mDMAStarted = false;
		mTagExit = false;
		mTagIRQ = false;
	}
}

IOPDmacChannelRegister_BCR_t::IOPDmacChannelRegister_BCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites),
	mTransferLength(0)
{
	registerField(Fields::BS, "BS", 0, 16, 0);
	registerField(Fields::BA, "BA", 16, 16, 0);
}

void IOPDmacChannelRegister_BCR_t::writeHword(const Context_t context, const size_t arrayIndex, const u16 value)
{
	BitfieldRegister32_t::writeHword(context, arrayIndex, value);

	// Update the transfer size.
	// When BS = 0, it is interpreted as 0x10000 (see wisi and sp193's IOP DMAC docs).
	// Wben BA = 0, just use 1 in its place (0 implies it is being used in a burst context).
	// TODO: I'm actually not sure if when BA = 0, does it mean 0x10000 (same as BS). Wouldn't think so...
	u16 BS = static_cast<u16>(getFieldValue(context, Fields::BS));
	u16 BA = static_cast<u16>(getFieldValue(context, Fields::BA));
	BA = (BA > 0) ? BA : 1;

	if (BS == 0)
		mTransferLength = BA * 0x10000;
	else
		mTransferLength = BA * BS;

	if (mTransferLength == 0)
		log(Debug, "IOP DMA BCR register's transfer size set is 0 - please check!");
}

void IOPDmacChannelRegister_BCR_t::writeWord(const Context_t context, const u32 value)
{
	BitfieldRegister32_t::writeWord(context, value);

	// Update the transfer size.
	// When BS = 0, it is interpreted as 0x10000 (see wisi and sp193's IOP DMAC docs).
	u16 BS = static_cast<u16>(getFieldValue(context, Fields::BS));
	u16 BA = static_cast<u16>(getFieldValue(context, Fields::BA));
	if (BS == 0)
		mTransferLength = BA * 0x10000;
	else
		mTransferLength = BA * BS;
		
	if (mTransferLength == 0)
		log(Debug, "IOP DMA BCR register's transfer size set is 0 - please check!");
}

IOPDmacChannelRegister_MADR_t::IOPDmacChannelRegister_MADR_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	Register32_t(mnemonic, debugReads, debugWrites)
{
}

void IOPDmacChannelRegister_MADR_t::increment(const Context_t context, const size_t amount)
{
	writeWord(context, readWord(context) + static_cast<u32>(amount));
}

void IOPDmacChannelRegister_MADR_t::decrement(const Context_t context, const size_t amount)
{
	writeWord(context, readWord(context) - static_cast<u32>(amount));
}

IOPDmacChannelRegister_TADR_t::IOPDmacChannelRegister_TADR_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	Register32_t(mnemonic, debugReads, debugWrites)
{
}

void IOPDmacChannelRegister_TADR_t::increment(const Context_t context, const size_t amount)
{
	writeWord(context, readWord(context) + static_cast<u32>(amount));
}

void IOPDmacChannelRegister_TADR_t::decrement(const Context_t context, const size_t amount)
{
	writeWord(context, readWord(context) - static_cast<u32>(amount));
}

IOPDmacChannelRegister_TO_CHCR_t::IOPDmacChannelRegister_TO_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	IOPDmacChannelRegister_CHCR_t(mnemonic, debugReads, debugWrites)
{
}

void IOPDmacChannelRegister_TO_CHCR_t::writeWord(const Context_t context, const u32 value)
{
	u32 temp = value;
	if (context == Context_t::IOPCore)
		temp |= (1 << 0);

	IOPDmacChannelRegister_CHCR_t::writeWord(context, temp);
}

IOPDmacChannelRegister_FROM_CHCR_t::IOPDmacChannelRegister_FROM_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	IOPDmacChannelRegister_CHCR_t(mnemonic, debugReads, debugWrites)
{
}

void IOPDmacChannelRegister_FROM_CHCR_t::writeWord(const Context_t context, const u32 value)
{
	u32 temp = value;
	if (context == Context_t::IOPCore)
		temp &= ~(1 << 0);

	IOPDmacChannelRegister_CHCR_t::writeWord(context, temp);
}

IOPDmacChannelRegister_SIF0_CHCR_t::IOPDmacChannelRegister_SIF0_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<Register32_t>& sbusF240) :
	IOPDmacChannelRegister_TO_CHCR_t(mnemonic, debugReads, debugWrites),
	mSbusF240(sbusF240)
{
}

void IOPDmacChannelRegister_SIF0_CHCR_t::setFieldValue(const Context_t context, const int fieldIndex, const u32 value)
{
	IOPDmacChannelRegister_TO_CHCR_t::setFieldValue(context, fieldIndex, value);

	// Only bother if its for the Start bit.
	if (fieldIndex == Fields::Start)
	{
		auto start = getFieldValue(context, Fields::Start);
		auto direction = getDirection(context);

		// Trigger SBUS update.
		if (start > 0 && direction == Direction_t::TO)
			handleSBUSUpdateStart(context);
	}
}

void IOPDmacChannelRegister_SIF0_CHCR_t::writeWord(const Context_t context, const u32 value)
{
	IOPDmacChannelRegister_TO_CHCR_t::writeWord(context, value);

	auto start = getFieldValue(context, Fields::Start);
	auto direction = getDirection(context);

	// Trigger SBUS update.
	if (start > 0 && direction == Direction_t::TO)
		handleSBUSUpdateStart(context);
}

void IOPDmacChannelRegister_SIF0_CHCR_t::handleSBUSUpdateStart(const Context_t context) const
{
	// Update 0x1D000040 (maps to Common->REGISTER_F240) with magic value.
	mSbusF240->writeWord(context, mSbusF240->readWord(context) | 0x2000);
}

IOPDmacChannelRegister_SIF1_CHCR_t::IOPDmacChannelRegister_SIF1_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<Register32_t> & sbusF240) :
	IOPDmacChannelRegister_FROM_CHCR_t(mnemonic, debugReads, debugWrites),
	mSbusF240(sbusF240)
{
}

void IOPDmacChannelRegister_SIF1_CHCR_t::setFieldValue(const Context_t context, const int fieldIndex, const u32 value)
{
	IOPDmacChannelRegister_FROM_CHCR_t::setFieldValue(context, fieldIndex, value);

	// Only bother if its for the Start bit.
	if (fieldIndex == Fields::Start)
	{
		auto start = getFieldValue(context, Fields::Start);
		auto direction = getDirection(context);

		// Trigger SBUS update.
		if (start == 0 && direction == Direction_t::FROM)
			handleSBUSUpdateFinish(context);
	}
}

void IOPDmacChannelRegister_SIF1_CHCR_t::writeWord(const Context_t context, const u32 value)
{
	u32 temp = value;
	if (context == Context_t::IOPCore)
		temp |= (1 << 10);

	IOPDmacChannelRegister_FROM_CHCR_t::writeWord(context, temp);

	auto start = getFieldValue(context, Fields::Start);
	auto direction = getDirection(context);

	// Trigger SBUS update.
	if (start == 0 && direction == Direction_t::FROM)
		handleSBUSUpdateFinish(context);
}

void IOPDmacChannelRegister_SIF1_CHCR_t::handleSBUSUpdateFinish(const Context_t context) const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic values.
	mSbusF240->writeWord(context, mSbusF240->readWord(context) & (~0x40));
	mSbusF240->writeWord(context, mSbusF240->readWord(context) & (~0x4000));
}

IOPDmacChannelRegister_SIF2_CHCR_t::IOPDmacChannelRegister_SIF2_CHCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<Register32_t>& sbusF240) :
	IOPDmacChannelRegister_CHCR_t(mnemonic, debugReads, debugWrites),
	mSbusF240(sbusF240)
{
}

void IOPDmacChannelRegister_SIF2_CHCR_t::setFieldValue(const Context_t context, const int fieldIndex, const u32 value)
{
	IOPDmacChannelRegister_CHCR_t::setFieldValue(context, fieldIndex, value);

	// Only bother if its for the Start bit.
	if (fieldIndex == Fields::Start)
	{
		auto start = getFieldValue(context, Fields::Start);
		auto direction = getDirection(context);

		// Trigger SBUS update.
		if (start > 0 && direction == Direction_t::TO)
			handleSBUSUpdateStart(context);
		else if (start == 0 && direction == Direction_t::FROM)
			handleSBUSUpdateFinish(context);
	}
}

void IOPDmacChannelRegister_SIF2_CHCR_t::writeWord(const Context_t context, const u32 value)
{
	IOPDmacChannelRegister_CHCR_t::writeWord(context, value);

	auto start = getFieldValue(context, Fields::Start);
	auto direction = getDirection(context);

	// Trigger SBUS update.
	if (start > 0 && direction == Direction_t::TO)
		handleSBUSUpdateStart(context);
	else if (start == 0 && direction == Direction_t::FROM)
		handleSBUSUpdateFinish(context);
}

void IOPDmacChannelRegister_SIF2_CHCR_t::handleSBUSUpdateStart(const Context_t context) const
{
	// Update 0x1D000040 (maps to Common->REGISTER_F240) with magic value.
	mSbusF240->writeWord(context, mSbusF240->readWord(context) | 0x8000);
}

void IOPDmacChannelRegister_SIF2_CHCR_t::handleSBUSUpdateFinish(const Context_t context) const
{
	// Update 0x1D000040 (maps to Common->REGISTER_F240) with magic values.
	mSbusF240->writeWord(context, mSbusF240->readWord(context) & (~0x80));
	mSbusF240->writeWord(context, mSbusF240->readWord(context) & (~0x8000));
}

