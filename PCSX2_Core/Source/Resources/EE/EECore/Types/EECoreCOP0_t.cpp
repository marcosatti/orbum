#include "stdafx.h"

#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

EECoreCOP0_t::EECoreCOP0_t() :
	Index(std::make_shared<EECoreCOP0Register_Index_t>()),
	Random(std::make_shared<EECoreCOP0Register_Random_t>()),
	EntryLo0(std::make_shared<EECoreCOP0Register_EntryLo0_t>()),
	EntryLo1(std::make_shared<EECoreCOP0Register_EntryLo1_t>()),
	Context(std::make_shared<EECoreCOP0Register_Context_t>()),
	PageMask(std::make_shared<EECoreCOP0Register_PageMask_t>()),
	Wired(std::make_shared<EECoreCOP0Register_Wired_t>()),
	Reserved7(std::make_shared<Register32_t>()),
	BadVAddr(std::make_shared<Register32_t>()),
	Count(std::make_shared<EECoreCOP0Register_Count_t>()),
	EntryHi(std::make_shared<EECoreCOP0Register_EntryHi_t>()),
	Cause(std::make_shared<EECoreCOP0Register_Cause_t>()),
	Compare(std::make_shared<Register32_t>()),
	Status(std::make_shared<EECoreCOP0Register_Status_t>()),
	EPC(std::make_shared<Register32_t>()),
	PRId(std::make_shared<EECoreCOP0Register_PRId_t>()),
	Config(std::make_shared<EECoreCOP0Register_Config_t>()),
	Reserved17(std::make_shared<Register32_t>()),
	Reserved18(std::make_shared<Register32_t>()),
	Reserved19(std::make_shared<Register32_t>()),
	Reserved20(std::make_shared<Register32_t>()),
	Reserved21(std::make_shared<Register32_t>()),
	Reserved22(std::make_shared<Register32_t>()),
	BadPAddr(std::make_shared<EECoreCOP0Register_BadPAddr_t>()),
	Reserved26(std::make_shared<Register32_t>()),
	Reserved27(std::make_shared<Register32_t>()),
	TagLo(std::make_shared<EECoreCOP0Register_TagLo_t>()),
	TagHi(std::make_shared<EECoreCOP0Register_TagHi_t>()),
	ErrorEPC(std::make_shared<Register32_t>()),
	Reserved31(std::make_shared<Register32_t>()),
	BPC(std::make_shared<EECoreCOP0Register_BPC_t>()),
	IAB(std::make_shared<Register32_t>()),
	IABM(std::make_shared<Register32_t>()),
	DAB(std::make_shared<Register32_t>()),
	DABM(std::make_shared<Register32_t>()),
	DVB(std::make_shared<Register32_t>()),
	DVBM(std::make_shared<Register32_t>()),
	PCCR(std::make_shared<EECoreCOP0Register_PCCR_t>()),
	PCR0(std::make_shared<EECoreCOP0Register_PCR0_t>()),
	PCR1(std::make_shared<EECoreCOP0Register_PCR1_t>()),
	Registers{ Index, Random, EntryLo0, EntryLo1, Context, PageMask, Wired, Reserved7,
		BadVAddr, Count, EntryHi, Compare, Status, Cause, EPC, PRId, Config, 
		Reserved17, Reserved18, Reserved19, Reserved20, Reserved21, Reserved22, 
		BadPAddr, BPC, PCCR, Reserved26, Reserved27, TagLo, TagHi, ErrorEPC, Reserved31 },
	PCRRegisters{ PCR0, PCR1 }
{
}

bool EECoreCOP0_t::isCoprocessorUsable() const
{
	// First check for kernel mode - the COP0 is always available in this mode. If not, then check that CU[bit 0] == 1 (ie: >0) in the status register.
	if (isOperatingKernelMode())
		return true;
	else if ((Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::CU) & 0x1) > 0)
		return true;
	else
		return false;
}

void EECoreCOP0_t::initalise()
{
	for (auto& reg : Registers)
		if (reg != nullptr) reg->initalise();

	for (auto& reg : PCRRegisters)
		if (reg != nullptr) reg->initalise();
}

bool EECoreCOP0_t::isOperatingUserMode() const
{
	const u32& KSU = Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::EXL);

	if (KSU == 2 && ERL == 0 && EXL == 0)
		return true;
	else
		return false;
}

bool EECoreCOP0_t::isOperatingSupervisorMode() const
{
	const u32& KSU = Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::EXL);

	if (KSU == 1 && ERL == 0 && EXL == 0)
		return true;
	else
		return false;
}

bool EECoreCOP0_t::isOperatingKernelMode() const
{
	const u32& KSU = Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::EXL);

	if (KSU == 0 || ERL == 1 || EXL == 1)
		return true;
	else
		return false;
}
