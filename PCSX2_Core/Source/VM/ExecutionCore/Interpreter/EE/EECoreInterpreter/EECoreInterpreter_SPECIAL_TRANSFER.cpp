#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "Common/Types/MIPSCoprocessor/COP0Registers_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"

void EECoreInterpreter::MFSA()
{
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& sourceReg = getResources()->EE->EECore->R5900->SA;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MTSA()
{
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& destReg = getResources()->EE->EECore->R5900->SA;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTSAB()
{
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->EE->EECore->R5900->SA;
	s16 imm = mInstruction.getIImmS();

	destReg->writeWordU(((sourceReg->readWordU(0) & 0xF) ^ (imm & 0xF)) * 8);
}

void EECoreInterpreter::MTSAH()
{
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->EE->EECore->R5900->SA;
	s16 imm = mInstruction.getIImmS();

	destReg->writeWordU(((sourceReg->readWordU(0) & 0x7) ^ (imm & 0x7)) * 16);
}

void EECoreInterpreter::MFBPC()
{
	if (!checkCOP0Usable())
        return;

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = getResources()->EE->EECore->COP0->BPC;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFC0()
{
	if (!checkCOP0Usable())
        return;

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = getResources()->EE->EECore->COP0->CPR[mInstruction.getRRd()];

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFDAB()
{
	if (!checkCOP0Usable())
        return;

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = getResources()->EE->EECore->COP0->DAB;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFDABM()
{
	if (!checkCOP0Usable())
        return;

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = getResources()->EE->EECore->COP0->DABM;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFDVB()
{
	if (!checkCOP0Usable())
        return;

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = getResources()->EE->EECore->COP0->DVB;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFDVBM()
{
	if (!checkCOP0Usable())
        return;

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = getResources()->EE->EECore->COP0->DVBM;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFIAB()
{
	if (!checkCOP0Usable())
        return;

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = getResources()->EE->EECore->COP0->IAB;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFIABM()
{
	if(!getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = getResources()->EE->EECore->COP0->IABM;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFPC()
{
	if (!checkCOP0Usable())
        return;

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	u8 perfRegisterIndex = mInstruction.getRFunct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& sourceReg = getResources()->EE->EECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFPS()
{
	if (!checkCOP0Usable())
        return;

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = getResources()->EE->EECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MTBPC()
{
	if (!checkCOP0Usable())
        return;

	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->COP0->BPC;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTC0()
{
	if (!checkCOP0Usable())
        return;

	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->COP0->CPR[mInstruction.getRRd()];

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTDAB()
{
	if (!checkCOP0Usable())
        return;

	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->COP0->DAB;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTDABM()
{
	if (!checkCOP0Usable())
        return;

	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->COP0->DABM;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTDVB()
{
	if (!checkCOP0Usable())
        return;

	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->COP0->DVB;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTDVBM()
{
	if (!checkCOP0Usable())
        return;

	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->COP0->DVBM;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTIAB()
{
	if (!checkCOP0Usable())
        return;

	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->COP0->IAB;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTIABM()
{
	if (!checkCOP0Usable())
        return;

	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->COP0->IABM;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTPC()
{
	if (!checkCOP0Usable())
        return;

	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	u8 perfRegisterIndex = mInstruction.getRFunct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& destReg = getResources()->EE->EECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTPS()
{
	if (!checkCOP0Usable())
        return;

	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::CFC1()
{
	if (!checkCOP1Usable())
        return;

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& sourceReg = getResources()->EE->EECore->FPU->FCR[mInstruction.getRRd()]; // Fs, can only be 0 or 31.

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::CTC1()
{
	if (!checkCOP1Usable())
        return;

	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->FPU->FCR[mInstruction.getRRd()];

	destReg->writeWordU(sourceReg->readWordU(0));
}