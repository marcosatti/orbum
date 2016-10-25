#include "stdafx.h"

#include "Common/PS2Resources/EE/EECore/EECoreCOP0/EECoreCOP0_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreCOP0/Types/EECore_COP0_Registers_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"

EECoreCOP0_t::EECoreCOP0_t(const PS2Resources_t* const PS2Resources) : 
	PS2ResourcesSubobject(PS2Resources),
	Index(std::make_shared<EECore_COP0RegisterIndex_t>()),
	Random(std::make_shared<EECore_COP0RegisterRandom_t>()),
	EntryLo0(std::make_shared<EECore_COP0RegisterEntryLo0_t>()),
	EntryLo1(std::make_shared<EECore_COP0RegisterEntryLo1_t>()),
	Context(std::make_shared<EECore_COP0RegisterContext_t>()),
	PageMask(std::make_shared<EECore_COP0RegisterPageMask_t>()),
	Wired(std::make_shared<EECore_COP0RegisterWired_t>()),
	Reserved7(std::make_shared<COP0RegisterReserved_t>()),
	BadVAddr(std::make_shared<EECore_COP0RegisterBadVAddr_t>()),
	Count(std::make_shared<EECore_COP0RegisterCount_t>()),
	EntryHi(std::make_shared<EECore_COP0RegisterEntryHi_t>()),
	Cause(std::make_shared<EECore_COP0RegisterCause_t>()),
	Compare(std::make_shared<EECore_COP0RegisterCompare_t>(Cause)),
	Status(std::make_shared<EECore_COP0RegisterStatus_t>()),
	EPC(std::make_shared<COP0RegisterEPC_t>()),
	PRId(std::make_shared<EECore_COP0RegisterPRId_t>()),
	Config(std::make_shared<EECore_COP0RegisterConfig_t>()),
	Reserved17(std::make_shared<COP0RegisterReserved_t>()),
	Reserved18(std::make_shared<COP0RegisterReserved_t>()),
	Reserved19(std::make_shared<COP0RegisterReserved_t>()),
	Reserved20(std::make_shared<COP0RegisterReserved_t>()),
	Reserved21(std::make_shared<COP0RegisterReserved_t>()),
	Reserved22(std::make_shared<COP0RegisterReserved_t>()),
	BadPAddr(std::make_shared<EECore_COP0RegisterBadPAddr_t>()),
	Reserved26(std::make_shared<COP0RegisterReserved_t>()),
	Reserved27(std::make_shared<COP0RegisterReserved_t>()),
	TagLo(std::make_shared<EECore_COP0RegisterTagLo_t>()),
	TagHi(std::make_shared<EECore_COP0RegisterTagHi_t>()),
	ErrorEPC(std::make_shared<EECore_COP0RegisterErrorEPC_t>()),
	Reserved31(std::make_shared<COP0RegisterReserved_t>()),
	BPC(std::make_shared<EECore_COP0RegisterBPC_t>()),
	IAB(std::make_shared<EECore_COP0RegisterIAB_t>()),
	IABM(std::make_shared<EECore_COP0RegisterIABM_t>()),
	DAB(std::make_shared<EECore_COP0RegisterDAB_t>()),
	DABM(std::make_shared<EECore_COP0RegisterDABM_t>()),
	DVB(std::make_shared<EECore_COP0RegisterDVB_t>()),
	DVBM(std::make_shared<EECore_COP0RegisterDVBM_t>()),
	PCCR(std::make_shared<EECore_COP0RegisterPCCR_t>()),
	PCR0(std::make_shared<EECore_COP0RegisterPCR0_t>()),
	PCR1(std::make_shared<EECore_COP0RegisterPCR1_t>()),
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
	else if ((Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::CU) & 0x1) > 0)
		return true;
	else
		return false;
}

void EECoreCOP0_t::initalise()
{
	for (auto& reg : Registers)
	{
		if (reg != nullptr)
			reg->initaliseAllFields();
	}
}

bool EECoreCOP0_t::isOperatingUserMode() const
{
	const u32& KSU = Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::EXL);

	if (KSU == 2 && ERL == 0 && EXL == 0)
		return true;
	else
		return false;
}

bool EECoreCOP0_t::isOperatingSupervisorMode() const
{
	const u32& KSU = Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::EXL);

	if (KSU == 1 && ERL == 0 && EXL == 0)
		return true;
	else
		return false;
}

bool EECoreCOP0_t::isOperatingKernelMode() const
{
	const u32& KSU = Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::EXL);

	if (KSU == 0 || ERL == 1 || EXL == 1)
		return true;
	else
		return false;
}
