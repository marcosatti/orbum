
#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"
#include "Resources/Ee/Core/EeCoreFpu.hpp"
#include "Resources/Ee/Core/EeCoreFpuRegisters.hpp"

void EECoreInterpreter_s::SLT()
{
	// Rd = SignExtended<s64>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));
	auto source2Val = static_cast<s64>(source2Reg->read_udword(0));

	s64 result = (source1Val < source2Val) ? 1 : 0;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::SLTI()
{
	// Rd = SignExtended<s64>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto imm = static_cast<s64>(mEECoreInstruction.getIImmS());

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));

	s64 result = (source1Val < imm) ? 1 : 0;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::SLTIU()
{
	// Rd = SignExtended<udword>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto imm = static_cast<udword>(static_cast<s64>(mEECoreInstruction.getIImmS()));

	auto source1Val = static_cast<udword>(source1Reg->read_udword(0));

	udword result = (source1Val < imm) ? 1 : 0;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::SLTU()
{
	// Rd = SignExtended<udword>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	auto source1Val = static_cast<udword>(source1Reg->read_udword(0));
	auto source2Val = static_cast<udword>(source2Reg->read_udword(0));

	udword result = (source1Val < source2Val) ? 1 : 0;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::PCEQB()
{
	// Rd = SignExtended<ubyte>((Rs == Rt) ? 0xFF : 0x00)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		ubyte source1Val = source1Reg->read_ubyte(i);
		ubyte source2Val = source2Reg->read_ubyte(i);
		ubyte result = (source1Val == source2Val) ? 0xFF : 0x00;
		destReg->write_ubyte(i, result);
	}
}

void EECoreInterpreter_s::PCEQH()
{
	// Rd = SignExtended<uhword>((Rs == Rt) ? 0xFFFF : 0x0000)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		uhword source1Val = source1Reg->read_uhword(i);
		uhword source2Val = source2Reg->read_uhword(i);
		uhword result = (source1Val == source2Val) ? 0xFFFF : 0x0000;
		destReg->write_uhword(i, result);
	}
}

void EECoreInterpreter_s::PCEQW()
{
	// Rd = SignExtended<uword>((Rs == Rt) ? 0xFFFFFFFF : 0x00000000)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		uword source1Val = source1Reg->read_uword(i);
		uword source2Val = source2Reg->read_uword(i);
		uword result = (source1Val == source2Val) ? 0xFFFFFFFF : 0x00000000;
		destReg->write_uword(i, result);
	}
}

void EECoreInterpreter_s::PCGTB()
{
	// Rd = SignExtended<ubyte>((Rs > Rt) ? 0xFF : 0x00)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		ubyte source1Val = source1Reg->read_ubyte(i);
		ubyte source2Val = source2Reg->read_ubyte(i);
		ubyte result = (source1Val > source2Val) ? 0xFF : 0x00;
		destReg->write_ubyte(i, result);
	}
}

void EECoreInterpreter_s::PCGTH()
{
	// Rd = SignExtended<uhword>((Rs > Rt) ? 0xFFFF : 0x0000)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		uhword source1Val = source1Reg->read_uhword(i);
		uhword source2Val = source2Reg->read_uhword(i);
		uhword result = (source1Val > source2Val) ? 0xFFFF : 0x0000;
		destReg->write_uhword(i, result);
	}
}

void EECoreInterpreter_s::PCGTW()
{
	// Rd = SignExtended<uword>((Rs > Rt) ? 0xFFFFFFFF : 0x00000000)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		uword source1Val = source1Reg->read_uword(i);
		uword source2Val = source2Reg->read_uword(i);
		uword result = (source1Val > source2Val) ? 0xFFFFFFFF : 0x00000000;
		destReg->write_uword(i, result);
	}
}

void EECoreInterpreter_s::C_EQ_S()
{
	// (FCR[31] or CSR, C field) = (Fs == Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();

	if (source1Val == source2Val)
		CSR->setFieldValue(, EeCoreFpuRegister_Csr::C, 1);
	else
		CSR->setFieldValue(, EeCoreFpuRegister_Csr::C, 0);
}

void EECoreInterpreter_s::C_F_S()
{
	// TODO: Whats the point of this instruction? Docs say something about a comparison but it always sets the C field to 0 regardless...
	// (FCR[31] or CSR, C field) = 0
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
        return;

	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	CSR->setFieldValue(, EeCoreFpuRegister_Csr::C, 0);
}

void EECoreInterpreter_s::C_LE_S()
{
	// (FCR[31] or CSR, C field) = (Fs <= Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();

	if (source1Val <= source2Val)
		CSR->setFieldValue(, EeCoreFpuRegister_Csr::C, 1);
	else
		CSR->setFieldValue(, EeCoreFpuRegister_Csr::C, 0);
}

void EECoreInterpreter_s::C_LT_S()
{
	// (FCR[31] or CSR, C field) = (Fs < Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();

	if (source1Val < source2Val)
		CSR->setFieldValue(, EeCoreFpuRegister_Csr::C, 1);
	else
		CSR->setFieldValue(, EeCoreFpuRegister_Csr::C, 0);
}


