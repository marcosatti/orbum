
#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"
#include "Resources/Ee/Core/EeCoreCop0.hpp"
#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"
#include "Resources/Ee/Core/EeCoreFpu.hpp"

void EECoreInterpreter_s::MFSA()
{
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& sourceReg = mEECore->R5900->SA;

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::MTSA()
{
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->SA;

	destReg->write_uword(sourceReg->read_uword(0));
}

void EECoreInterpreter_s::MTSAB()
{
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->SA;
	s16 imm = mEECoreInstruction.getIImmS();

	destReg->write_uword(((sourceReg->read_uword(0) & 0xF) ^ (imm & 0xF)) * 8);
}

void EECoreInterpreter_s::MTSAH()
{
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->SA;
	s16 imm = mEECoreInstruction.getIImmS();

	destReg->write_uword(((sourceReg->read_uword(0) & 0x7) ^ (imm & 0x7)) * 16);
}

void EECoreInterpreter_s::MFBPC()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->COP0->BPC;

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::MFC0()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->COP0->Registers[mEECoreInstruction.getRRd()];

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::MFDAB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->COP0->DAB;

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::MFDABM()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->COP0->DABM;

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::MFDVB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->COP0->DVB;

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::MFDVBM()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->COP0->DVBM;

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::MFIAB()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->COP0->IAB;

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::MFIABM()
{
	if (handleCOP0Usable())
		return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->COP0->IABM;

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::MFPC()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	ubyte perfRegisterIndex = mEECoreInstruction.funct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& sourceReg = mEECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::MFPS()
{
	if (handleCOP0Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::MTBPC()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->COP0->BPC;

	destReg->write_uword(sourceReg->read_uword(0));
}

void EECoreInterpreter_s::MTC0()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->COP0->Registers[mEECoreInstruction.getRRd()];

	destReg->write_uword(sourceReg->read_uword(0));
}

void EECoreInterpreter_s::MTDAB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->COP0->DAB;

	destReg->write_uword(sourceReg->read_uword(0));
}

void EECoreInterpreter_s::MTDABM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->COP0->DABM;

	destReg->write_uword(sourceReg->read_uword(0));
}

void EECoreInterpreter_s::MTDVB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->COP0->DVB;

	destReg->write_uword(sourceReg->read_uword(0));
}

void EECoreInterpreter_s::MTDVBM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->COP0->DVBM;

	destReg->write_uword(sourceReg->read_uword(0));
}

void EECoreInterpreter_s::MTIAB()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->COP0->IAB;

	destReg->write_uword(sourceReg->read_uword(0));
}

void EECoreInterpreter_s::MTIABM()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->COP0->IABM;

	destReg->write_uword(sourceReg->read_uword(0));
}

void EECoreInterpreter_s::MTPC()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	ubyte perfRegisterIndex = mEECoreInstruction.funct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& destReg = mEECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->write_uword(sourceReg->read_uword(0));
}

void EECoreInterpreter_s::MTPS()
{
	if (handleCOP0Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->write_uword(sourceReg->read_uword(0));
}

void EECoreInterpreter_s::CFC1()
{
	if (handleCOP1Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->FPU->FCR[mEECoreInstruction.getRRd()]; // Fs, can only be 0 or 31.

	destReg->write_udword(0, static_cast<udword>(sourceReg->read_uword()));
}

void EECoreInterpreter_s::CTC1()
{
	if (handleCOP1Usable())
        return;

	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->FPU->FCR[mEECoreInstruction.getRRd()];

	destReg->write_uword(sourceReg->read_uword(0));
}