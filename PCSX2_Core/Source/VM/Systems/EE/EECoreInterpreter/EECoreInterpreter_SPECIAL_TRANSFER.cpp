#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register128_t.h"
#include "Common/Types/Register/Register32_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"

void EECoreInterpreter_s::MFSA()
{
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& sourceReg = mEECore->R5900->SA;

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::MTSA()
{
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& destReg = mEECore->R5900->SA;

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::MTSAB()
{
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& destReg = mEECore->R5900->SA;
	s16 imm = mEECoreInstruction.getIImmS();

	destReg->writeWord(getContext(), ((sourceReg->readWord(getContext(), 0) & 0xF) ^ (imm & 0xF)) * 8);
}

void EECoreInterpreter_s::MTSAH()
{
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& destReg = mEECore->R5900->SA;
	s16 imm = mEECoreInstruction.getIImmS();

	destReg->writeWord(getContext(), ((sourceReg->readWord(getContext(), 0) & 0x7) ^ (imm & 0x7)) * 16);
}

void EECoreInterpreter_s::MFBPC()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->COP0->BPC;

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::MFC0()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->COP0->Registers[mEECoreInstruction.getRRd()];

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::MFDAB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->COP0->DAB;

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::MFDABM()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->COP0->DABM;

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::MFDVB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->COP0->DVB;

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::MFDVBM()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->COP0->DVBM;

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::MFIAB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->COP0->IAB;

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::MFIABM()
{
	if (handleCOP0Usable())
		return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->COP0->IABM;

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::MFPC()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	u8 perfRegisterIndex = mEECoreInstruction.getRFunct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& sourceReg = mEECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::MFPS()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::MTBPC()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->COP0->BPC;

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::MTC0()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->COP0->Registers[mEECoreInstruction.getRRd()];

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::MTDAB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->COP0->DAB;

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::MTDABM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->COP0->DABM;

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::MTDVB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->COP0->DVB;

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::MTDVBM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->COP0->DVBM;

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::MTIAB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->COP0->IAB;

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::MTIABM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->COP0->IABM;

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::MTPC()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	u8 perfRegisterIndex = mEECoreInstruction.getRFunct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& destReg = mEECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::MTPS()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::CFC1()
{
	if (handleCOP1Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->FPU->FCR[mEECoreInstruction.getRRd()]; // Fs, can only be 0 or 31.

	destReg->writeDword(getContext(), 0, static_cast<u64>(sourceReg->readWord(getContext())));
}

void EECoreInterpreter_s::CTC1()
{
	if (handleCOP1Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->FPU->FCR[mEECoreInstruction.getRRd()];

	destReg->writeWord(getContext(), sourceReg->readWord(getContext(), 0));
}