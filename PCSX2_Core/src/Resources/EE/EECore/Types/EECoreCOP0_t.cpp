#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

EECoreCOP0_t::EECoreCOP0_t() :
	Index(std::make_shared<EECoreCOP0Register_Index_t>("EECore COP0 Index", false, false)),
	Random(std::make_shared<EECoreCOP0Register_Random_t>("EECore COP0 Random", false, false)),
	EntryLo0(std::make_shared<EECoreCOP0Register_EntryLo0_t>("EECore COP0 EntryLo0", false, false)),
	EntryLo1(std::make_shared<EECoreCOP0Register_EntryLo1_t>("EECore COP0 EntryLo1", false, false)),
	Context(std::make_shared<EECoreCOP0Register_System_t>("EECore COP0 System", false, false)),
	PageMask(std::make_shared<EECoreCOP0Register_PageMask_t>("EECore COP0 PageMask", false, false)),
	Wired(std::make_shared<EECoreCOP0Register_Wired_t>("EECore COP0 Wired", false, false)),
	Reserved7(std::make_shared<Register32_t>("EECore COP0 Reserved7", false, false)),
	BadVAddr(std::make_shared<Register32_t>("EECore COP0 BadVAddr", false, false)),
	Count(std::make_shared<EECoreCOP0Register_Count_t>("EECore COP0 Count", false, false)),
	EntryHi(std::make_shared<EECoreCOP0Register_EntryHi_t>("EECore COP0 EntryHi", false, false)),
	Cause(std::make_shared<EECoreCOP0Register_Cause_t>("EECore COP0 Cause", false, false)),
	Compare(std::make_shared<Register32_t>("EECore COP0 Compare", false, false)),
	Status(std::make_shared<EECoreCOP0Register_Status_t>("EECore COP0 Status", false, false)),
	EPC(std::make_shared<Register32_t>("EECore COP0 EPC", false, false)),
	PRId(std::make_shared<EECoreCOP0Register_PRId_t>("EECore COP0 PRId", false, false)),
	Config(std::make_shared<EECoreCOP0Register_Config_t>("EECore COP0 Config", false, false)),
	Reserved17(std::make_shared<Register32_t>("EECore COP0 Reserved17", false, false)),
	Reserved18(std::make_shared<Register32_t>("EECore COP0 Reserved18", false, false)),
	Reserved19(std::make_shared<Register32_t>("EECore COP0 Reserved19", false, false)),
	Reserved20(std::make_shared<Register32_t>("EECore COP0 Reserved20", false, false)),
	Reserved21(std::make_shared<Register32_t>("EECore COP0 Reserved21", false, false)),
	Reserved22(std::make_shared<Register32_t>("EECore COP0 Reserved22", false, false)),
	BadPAddr(std::make_shared<EECoreCOP0Register_BadPAddr_t>("EECore COP0 BadPAddr", false, false)),
	Reserved26(std::make_shared<Register32_t>("EECore COP0 Reserved26", false, false)),
	Reserved27(std::make_shared<Register32_t>("EECore COP0 Reserved27", false, false)),
	TagLo(std::make_shared<EECoreCOP0Register_TagLo_t>("EECore COP0 TagLo", false, false)),
	TagHi(std::make_shared<EECoreCOP0Register_TagHi_t>("EECore COP0 TagHi", false, false)),
	ErrorEPC(std::make_shared<Register32_t>("EECore COP0 ErrorEPC", false, false)),
	Reserved31(std::make_shared<Register32_t>("EECore COP0 Reserved31", false, false)),
	BPC(std::make_shared<EECoreCOP0Register_BPC_t>("EECore COP0 BPC", false, false)),
	IAB(std::make_shared<Register32_t>("EECore COP0 IAB", false, false)),
	IABM(std::make_shared<Register32_t>("EECore COP0 IABM", false, false)),
	DAB(std::make_shared<Register32_t>("EECore COP0 DAB", false, false)),
	DABM(std::make_shared<Register32_t>("EECore COP0 DABM", false, false)),
	DVB(std::make_shared<Register32_t>("EECore COP0 DVB", false, false)),
	DVBM(std::make_shared<Register32_t>("EECore COP0 DVBM", false, false)),
	PCCR(std::make_shared<EECoreCOP0Register_PCCR_t>("EECore COP0 PCCR", false, false)),
	PCR0(std::make_shared<EECoreCOP0Register_PCR0_t>("EECore COP0 PCR0", false, false)),
	PCR1(std::make_shared<EECoreCOP0Register_PCR1_t>("EECore COP0 PCR1", false, false)),
	Registers{ Index, Random, EntryLo0, EntryLo1, Context, PageMask, Wired, Reserved7,
		BadVAddr, Count, EntryHi, Compare, Status, Cause, EPC, PRId, Config, 
		Reserved17, Reserved18, Reserved19, Reserved20, Reserved21, Reserved22, 
		BadPAddr, BPC, PCCR, Reserved26, Reserved27, TagLo, TagHi, ErrorEPC, Reserved31 },
	PCRRegisters{ PCR0, PCR1 }
{
}

bool EECoreCOP0_t::isCoprocessorUsable(const System_t context) const
{
	// First check for kernel mode - the COP0 is always available in this mode. If not, then check that CU[bit 0] == 1 (ie: >0) in the status register.
	if (getCPUOperatingContext(context) == MIPSCPUOperatingContext_t::Kernel)
		return true;
	else if ((Status->getFieldValue(context, EECoreCOP0Register_Status_t::Fields::CU) & 0x1) > 0)
		return true;
	else
		return false;
}

void EECoreCOP0_t::initialise()
{
	for (auto& reg : Registers)
		if (reg != nullptr) reg->initialise();

	for (auto& reg : PCRRegisters)
		if (reg != nullptr) reg->initialise();
}

MIPSCPUOperatingContext_t EECoreCOP0_t::getCPUOperatingContext(const System_t context) const
{
	const u32 KSU = Status->getFieldValue(context, EECoreCOP0Register_Status_t::Fields::KSU);
	const u32 ERL = Status->getFieldValue(context, EECoreCOP0Register_Status_t::Fields::ERL);
	const u32 EXL = Status->getFieldValue(context, EECoreCOP0Register_Status_t::Fields::EXL);

	if (KSU == 2 && ERL == 0 && EXL == 0)
		return MIPSCPUOperatingContext_t::User;
	else if (KSU == 0 || ERL == 1 || EXL == 1)
		return MIPSCPUOperatingContext_t::Kernel;
	else if (KSU == 1 && ERL == 0 && EXL == 0)
		return MIPSCPUOperatingContext_t::Supervisor;
	else
		throw std::runtime_error("EE COP0 could not determine CPU operating context! Please debug.");

}
