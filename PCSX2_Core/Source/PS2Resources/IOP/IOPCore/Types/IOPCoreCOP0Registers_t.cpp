#include "stdafx.h"

#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

IOPCoreCOP0Register_Context_t::IOPCoreCOP0Register_Context_t()
{
	registerField(Fields::BadVPN2, "BadVPN2", 2, 19, 0);
	registerField(Fields::PTEBase, "PTEBase", 21, 11, 0);
}

IOPCoreCOP0Register_Status_t::IOPCoreCOP0Register_Status_t() :
	BitfieldRegister32_t("IOP COP0 Status")
{
	registerField(Fields::IEc, "IEc", 0, 1, 0);
	registerField(Fields::KUc, "KUc", 1, 1, 0);
	registerField(Fields::IEp, "IEp", 2, 1, 0);
	registerField(Fields::KUp, "KUp", 3, 1, 0);
	registerField(Fields::IEo, "IEo", 4, 1, 0);
	registerField(Fields::KUo, "KUo", 5, 1, 0);
	registerField(Fields::IM, "IM", 8, 8, 0);
	registerField(Fields::IsC, "IsC", 16, 1, 0);
	registerField(Fields::SwC, "SwC", 17, 1, 0);
	registerField(Fields::PZ, "PZ", 18, 1, 0);
	registerField(Fields::CM, "CM", 19, 1, 0);
	registerField(Fields::PE, "PE", 20, 1, 0);
	registerField(Fields::TS, "TS", 21, 1, 0);
	registerField(Fields::BEV, "BEV", 22, 1, 1);
	registerField(Fields::RE, "RE", 25, 1, 0);
	registerField(Fields::CU, "CU", 28, 4, 0);
}

void IOPCoreCOP0Register_Status_t::pushExceptionStack()
{
	// New status = shift (KU|IP)(c|p) bits left by 2 then make (KU|IP)c bits = 0.
	u32 statusValue = readWord(Context_t::RAW);
	writeWord(Context_t::RAW, (statusValue & (~0x3F)) | ((statusValue & 0xF) << 2));
}

void IOPCoreCOP0Register_Status_t::popExceptionStack()
{
	// New status = shift (KU|IP)(p|o) bits right by 2. Leave old bits unchanged after.
	u32 statusValue = readWord(Context_t::RAW);
	writeWord(Context_t::RAW, (statusValue & (~0xF)) | ((statusValue & 0x3C) >> 2));
}

bool IOPCoreCOP0Register_Status_t::isExceptionsMasked() const
{
	return false;
}

bool IOPCoreCOP0Register_Status_t::isInterruptsMasked() const
{
	return !(getFieldValue(Fields::IEc) > 0);
}

bool IOPCoreCOP0Register_Status_t::isIRQMasked(u8 irq) const
{
	return !((getFieldValue(Fields::IM) & (1 << irq)) > 0);
}

IOPCoreCOP0Register_Cause_t::IOPCoreCOP0Register_Cause_t()
{
	registerField(Fields::ExcCode, "ExcCode", 2, 5, 0);
	registerField(Fields::IP, "IP", 8, 8, 0);
	registerField(Fields::CE, "CE", 28, 2, 0);
	registerField(Fields::BD, "BD", 31, 1, 0);
}

void IOPCoreCOP0Register_Cause_t::clearIP()
{
	setFieldValue(Fields::IP, 0);
}

void IOPCoreCOP0Register_Cause_t::setIRQLine(u8 irq)
{
	auto temp = getFieldValue(Fields::IP) | (1 << irq);
	setFieldValue(Fields::IP, temp);
}

void IOPCoreCOP0Register_Cause_t::clearIRQLine(u8 irq)
{
	auto temp = (getFieldValue(Fields::IP) & (~(1 << irq))) & 0xFF; // 0xFF mask to strip off any other bits as a safety precaution.
	setFieldValue(Fields::IP, temp);
}

IOPCoreCOP0Register_PRId_t::IOPCoreCOP0Register_PRId_t()
{
	registerField(Fields::Rev, "Rev", 0, 8, 0x1F); // Same as old PCSX2.
	registerField(Fields::Imp, "Imp", 8, 8, 0x00);
}
