#include "stdafx.h"

#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"

#include "PS2Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"

EEDmacChannelRegister_CHCR_t::EEDmacChannelRegister_CHCR_t(const char * mnemonic) :
	BitfieldRegister32_t(mnemonic, false, false)
{
	registerField(Fields::DIR, "DIR", 0, 1, 0);
	registerField(Fields::MOD, "MOD", 2, 2, 0);
	registerField(Fields::ASP, "ASP", 4, 2, 0);
	registerField(Fields::TTE, "TTE", 6, 1, 0);
	registerField(Fields::TIE, "TIE", 7, 1, 0);
	registerField(Fields::STR, "STR", 8, 1, 0);
	registerField(Fields::TAG, "TAG", 16, 16, 0);
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

EEDmacChannelRegister_SIF0_CHCR_t::EEDmacChannelRegister_SIF0_CHCR_t(const char* mnemonic, const std::shared_ptr<Register32_t> & sbusF240) :
	EEDmacChannelRegister_CHCR_t(mnemonic),
	mSbusF240(sbusF240)
{
}

void EEDmacChannelRegister_SIF0_CHCR_t::setFieldValue(const u8& fieldIndex, const u32& value)
{
	// Only bother if its for the STR bit.
	if (fieldIndex == Fields::STR)
	{
		auto oldSTR = getFieldValue(Fields::STR);
		EEDmacChannelRegister_CHCR_t::setFieldValue(fieldIndex, value);
		auto newSTR = getFieldValue(Fields::STR);

		// Trigger update if (stopped -> started) or (started -> stopped). We can use XOR to check this.
		if (oldSTR ^ newSTR)
		{
			if (newSTR > 0)
				handleSBUSUpdateStart(); // Starting.
			else
				handleSBUSUpdateFinish(); // Stopping.
		}
	}
	else
	{
		EEDmacChannelRegister_CHCR_t::setFieldValue(fieldIndex, value);
	}
}

void EEDmacChannelRegister_SIF0_CHCR_t::writeWord(const Context_t& context, u32 value)
{
	auto oldSTR = getFieldValue(Fields::STR);
	EEDmacChannelRegister_CHCR_t::writeWord(context, value);
	auto newSTR = getFieldValue(Fields::STR);

	// Trigger update if (stopped -> started) or (started -> stopped). We can use XOR to check this.
	if (oldSTR ^ newSTR)
	{
		if (newSTR > 0)
			handleSBUSUpdateStart(); // Starting.
		else
			handleSBUSUpdateFinish(); // Stopping.
	}
}

void EEDmacChannelRegister_SIF0_CHCR_t::handleSBUSUpdateStart() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic value.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) | 0x2000);
}

void EEDmacChannelRegister_SIF0_CHCR_t::handleSBUSUpdateFinish() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic values.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x20));
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x2000));
}

EEDmacChannelRegister_SIF1_CHCR_t::EEDmacChannelRegister_SIF1_CHCR_t(const char* mnemonic, const std::shared_ptr<Register32_t> & sbusF240) :
	EEDmacChannelRegister_CHCR_t(mnemonic),
	mSbusF240(sbusF240)
{
}

void EEDmacChannelRegister_SIF1_CHCR_t::setFieldValue(const u8& fieldIndex, const u32& value)
{
	// Only bother if its for the STR bit.
	if (fieldIndex == Fields::STR)
	{
		auto oldSTR = getFieldValue(Fields::STR);
		EEDmacChannelRegister_CHCR_t::setFieldValue(fieldIndex, value);
		auto newSTR = getFieldValue(Fields::STR);

		// Trigger update if (stopped -> started) or (started -> stopped). We can use XOR to check this.
		if (oldSTR ^ newSTR)
		{
			if (newSTR > 0)
				handleSBUSUpdateStart(); // Starting.
			else
				handleSBUSUpdateFinish(); // Stopping.
		}
	}
	else
	{
		EEDmacChannelRegister_CHCR_t::setFieldValue(fieldIndex, value);
	}
}

void EEDmacChannelRegister_SIF1_CHCR_t::writeWord(const Context_t& context, u32 value)
{
	auto oldSTR = getFieldValue(Fields::STR);
	EEDmacChannelRegister_CHCR_t::writeWord(context, value);
	auto newSTR = getFieldValue(Fields::STR);

	// Trigger update if (stopped -> started) or (started -> stopped). We can use XOR to check this.
	if (oldSTR ^ newSTR)
	{
		if (newSTR > 0)
			handleSBUSUpdateStart(); // Starting.
		else
			handleSBUSUpdateFinish(); // Stopping.
	}
}

void EEDmacChannelRegister_SIF1_CHCR_t::handleSBUSUpdateStart() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic value.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) | 0x4000);
}

void EEDmacChannelRegister_SIF1_CHCR_t::handleSBUSUpdateFinish() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic values.
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x40));
	mSbusF240->writeWord(RAW, mSbusF240->readWord(RAW) & (~0x4000));
}

EEDmacChannelRegister_SIF2_CHCR_t::EEDmacChannelRegister_SIF2_CHCR_t(const char* mnemonic, const std::shared_ptr<Register32_t> & sbusF240) :
	EEDmacChannelRegister_CHCR_t(mnemonic),
	mSbusF240(sbusF240)
{
}

void EEDmacChannelRegister_SIF2_CHCR_t::setFieldValue(const u8& fieldIndex, const u32& value)
{
	// Only bother if its for the STR bit.
	if (fieldIndex == Fields::STR)
	{
		auto oldSTR = getFieldValue(Fields::STR);
		EEDmacChannelRegister_CHCR_t::setFieldValue(fieldIndex, value);
		auto newSTR = getFieldValue(Fields::STR);

		// Trigger update if (stopped -> started) or (started -> stopped). We can use XOR to check this.
		if (oldSTR ^ newSTR)
		{
			if (newSTR > 0)
				handleSBUSUpdateStart(); // Starting.
			else
				handleSBUSUpdateFinish(); // Stopping.
		}
	}
	else
	{
		EEDmacChannelRegister_CHCR_t::setFieldValue(fieldIndex, value);
	}
}

void EEDmacChannelRegister_SIF2_CHCR_t::writeWord(const Context_t& context, u32 value)
{
	auto oldSTR = getFieldValue(Fields::STR);
	EEDmacChannelRegister_CHCR_t::writeWord(context, value);
	auto newSTR = getFieldValue(Fields::STR);

	// Trigger update only if (stopped -> started) or (started -> stopped). We can use XOR to check this.
	if (oldSTR ^ newSTR)
	{
		if (newSTR > 0)
			handleSBUSUpdateStart(); // Starting.
		else
			handleSBUSUpdateFinish(); // Stopping.
	}
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
