#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/Register32_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"

void EECoreInterpreter_s::MFSA()
{
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];
	auto& sourceReg = mEECore->R5900->SA;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::MTSA()
{
	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& destReg = mEECore->R5900->SA;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter_s::MTSAB()
{
	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = mEECore->R5900->SA;
	s16 imm = mInstruction.getIImmS();

	destReg->writeWord(EE, ((sourceReg->readWord(EE, 0) & 0xF) ^ (imm & 0xF)) * 8);
}

void EECoreInterpreter_s::MTSAH()
{
	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = mEECore->R5900->SA;
	s16 imm = mInstruction.getIImmS();

	destReg->writeWord(EE, ((sourceReg->readWord(EE, 0) & 0x7) ^ (imm & 0x7)) * 16);
}

void EECoreInterpreter_s::MFBPC()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->BPC;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::MFC0()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->Registers[mInstruction.getRRd()];

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::MFDAB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->DAB;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::MFDABM()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->DABM;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::MFDVB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->DVB;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::MFDVBM()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->DVBM;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::MFIAB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->IAB;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::MFIABM()
{
	if (handleCOP0Usable())
		return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->IABM;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::MFPC()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	u8 perfRegisterIndex = mInstruction.getRFunct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& sourceReg = mEECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::MFPS()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::MTBPC()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->BPC;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter_s::MTC0()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->Registers[mInstruction.getRRd()];

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter_s::MTDAB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->DAB;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter_s::MTDABM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->DABM;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter_s::MTDVB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->DVB;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter_s::MTDVBM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->DVBM;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter_s::MTIAB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->IAB;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter_s::MTIABM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->IABM;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter_s::MTPC()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	u8 perfRegisterIndex = mInstruction.getRFunct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& destReg = mEECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter_s::MTPS()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter_s::CFC1()
{
	if (handleCOP1Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->FPU->FCR[mInstruction.getRRd()]; // Fs, can only be 0 or 31.

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter_s::CTC1()
{
	if (handleCOP1Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->FPU->FCR[mInstruction.getRRd()];

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}