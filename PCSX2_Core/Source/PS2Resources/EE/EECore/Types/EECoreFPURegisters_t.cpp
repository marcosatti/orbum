#include "stdafx.h"

#include "PS2Resources/EE/EECore/Types/EECoreFPURegisters_t.h"
#include "Common/Util/FPUUtil/FPUFlags_t.h"

FPURegister_IRR_t::FPURegister_IRR_t()
{
	registerField(Fields::Rev, "Rev", 0, 8, 0);
	registerField(Fields::Imp, "Imp", 8, 8, 0x2E);
}

FPURegister_CSR_t::FPURegister_CSR_t()
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

void FPURegister_CSR_t::setFieldValue(const u8& fieldIndex, const u32& value)
{
	// Check if the field index is for the non-sticky flags.
	// TODO: relies on fact that sticky flag indexes are offset by -4.
	if (fieldIndex >= Fields::U && fieldIndex <= Fields::I)
	{
		u32 oldStickyValue = getFieldValue(fieldIndex - 4);
		BitfieldRegister32_t::setFieldValue(fieldIndex - 4, oldStickyValue | value);
	}
}

void FPURegister_CSR_t::updateResultFlags(const FPUFlags_t & flags)
{
	setFieldValue(Fields::U, flags.UF ? 1 : 0);
	setFieldValue(Fields::O, flags.OF ? 1 : 0);
}

void FPURegister_CSR_t::clearFlags()
{
	setFieldValue(Fields::U, 0);
	setFieldValue(Fields::O, 0);
	setFieldValue(Fields::D, 0);
	setFieldValue(Fields::I, 0);
}
