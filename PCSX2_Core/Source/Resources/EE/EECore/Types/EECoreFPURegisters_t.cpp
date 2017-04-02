#include "stdafx.h"

#include "Common/Util/FPUUtil/FPUFlags_t.h"

#include "Resources/EE/EECore/Types/EECoreFPURegisters_t.h"

EECoreFPURegister_IRR_t::EECoreFPURegister_IRR_t()
{
	registerField(Fields::Rev, "Rev", 0, 8, 0);
	registerField(Fields::Imp, "Imp", 8, 8, 0x2E);
}

EECoreFPURegister_CSR_t::EECoreFPURegister_CSR_t()
{
	registerField(Fields::SU, "SU", 3, 1, 0);
	registerField(Fields::SO, "SO", 4, 1, 0);
	registerField(Fields::SD, "SD", 5, 1, 0);
	registerField(Fields::SI, "SI", 6, 1, 0);
	registerField(Fields::U, "U", 14, 1, 0);
	registerField(Fields::O, "O", 15, 1, 0);
	registerField(Fields::D, "D", 16, 1, 0);
	registerField(Fields::I, "I", 17, 1, 0);
	registerField(Fields::C, "C", 23, 1, 0);
}

void EECoreFPURegister_CSR_t::setFieldValueSticky(const System_t context, const int fieldIndex, const u32 value)
{
	// Check if the field index is for the non-sticky flags.
	// TODO: relies on fact that sticky flag indexes are offset by -4.
	if (fieldIndex >= Fields::U && fieldIndex <= Fields::I)
	{
		u32 oldStickyValue = getFieldValue(context, fieldIndex - 4);
		setFieldValue(context, fieldIndex - 4, oldStickyValue | value);
	}
	else
	{
		throw std::runtime_error("CSR set field sticky was called with invalid field.");
	}
}

void EECoreFPURegister_CSR_t::updateResultFlags(const System_t context, const FPUFlags_t & flags)
{
	setFieldValueSticky(context, Fields::U, flags.UF ? 1 : 0);
	setFieldValueSticky(context, Fields::O, flags.OF ? 1 : 0);
}

void EECoreFPURegister_CSR_t::clearFlags(const System_t context)
{
	setFieldValueSticky(context, Fields::U, 0);
	setFieldValueSticky(context, Fields::O, 0);
	setFieldValueSticky(context, Fields::D, 0);
	setFieldValueSticky(context, Fields::I, 0);
}
