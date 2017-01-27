#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/Register32_t.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"

#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"

void EECoreInterpreter::MFSA()
{
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];
	auto& sourceReg = mEECore->R5900->SA;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::MTSA()
{
	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& destReg = mEECore->R5900->SA;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter::MTSAB()
{
	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = mEECore->R5900->SA;
	s16 imm = mInstruction.getIImmS();

	destReg->writeWord(EE, ((sourceReg->readWord(EE, 0) & 0xF) ^ (imm & 0xF)) * 8);
}

void EECoreInterpreter::MTSAH()
{
	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = mEECore->R5900->SA;
	s16 imm = mInstruction.getIImmS();

	destReg->writeWord(EE, ((sourceReg->readWord(EE, 0) & 0x7) ^ (imm & 0x7)) * 16);
}

void EECoreInterpreter::MFBPC()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->BPC;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::MFC0()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->Registers[mInstruction.getRRd()];

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::MFDAB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->DAB;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::MFDABM()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->DABM;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::MFDVB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->DVB;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::MFDVBM()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->DVBM;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::MFIAB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->IAB;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::MFIABM()
{
	if (handleCOP0Usable())
		return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->IABM;

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::MFPC()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	u8 perfRegisterIndex = mInstruction.getRFunct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& sourceReg = mEECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::MFPS()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::MTBPC()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->BPC;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter::MTC0()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->Registers[mInstruction.getRRd()];

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter::MTDAB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->DAB;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter::MTDABM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->DABM;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter::MTDVB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->DVB;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter::MTDVBM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->DVBM;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter::MTIAB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->IAB;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter::MTIABM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->IABM;

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter::MTPC()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	u8 perfRegisterIndex = mInstruction.getRFunct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& destReg = mEECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter::MTPS()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}

void EECoreInterpreter::CFC1()
{
	if (handleCOP1Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = mEECore->FPU->FCR[mInstruction.getRRd()]; // Fs, can only be 0 or 31.

	destReg->writeDword(EE, 0, static_cast<u64>(sourceReg->readWord(EE)));
}

void EECoreInterpreter::CTC1()
{
	if (handleCOP1Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->FPU->FCR[mInstruction.getRRd()];

	destReg->writeWord(EE, sourceReg->readWord(EE, 0));
}