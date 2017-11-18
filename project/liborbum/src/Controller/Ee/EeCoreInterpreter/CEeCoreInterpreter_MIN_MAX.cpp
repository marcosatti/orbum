#include <algorithm>


#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"
#include "Resources/Ee/Core/EeCoreFpu.hpp"
#include "Resources/Ee/Core/EeCoreFpuRegisters.hpp"

void EECoreInterpreter_s::PMAXH()
{
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<s16>(source2Reg->read_uhword(i));
		s16 result = std::max(source2Val, source1Val); // Format parameters this way as std::max returns parameter 0 if they are equal, and value in Rt is returned according to docs if they are equal.
		destReg->write_uhword(i, result);
	}
}

void EECoreInterpreter_s::PMAXW()
{
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->read_uword(i));
		auto source2Val = static_cast<s32>(source2Reg->read_uword(i));
		s32 result = std::max(source2Val, source1Val); // Format parameters this way as std::max returns parameter 0 if they are equal, and value in Rt is returned according to docs if they are equal.
		destReg->write_uword(i, result);
	}
}

void EECoreInterpreter_s::PMINH()
{
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<s16>(source2Reg->read_uhword(i));
		s16 result = std::min(source1Val, source2Val); // Format parameters this way as std::min returns parameter 0 if they are equal, and value in Rs is returned according to docs if they are equal.
		destReg->write_uhword(i, result);
	}
}

void EECoreInterpreter_s::PMINW()
{
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->read_uword(i));
		auto source2Val = static_cast<s32>(source2Reg->read_uword(i));
		s32 result = std::min(source1Val, source2Val); // Format parameters this way as std::min returns parameter 0 if they are equal, and value in Rs is returned according to docs if they are equal.
		destReg->write_uword(i, result);
	}
}

void EECoreInterpreter_s::MAX_S()
{
	// Fd = MAX(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
		return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	CSR->clear_flags();
	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();
	f32 result = (source1Val >= source2Val) ? source1Val : source2Val; // Dont have to check for valid float as should already be valid from before.
	destReg->writeFloat(,result);
}

void EECoreInterpreter_s::MIN_S()
{
	// Fd = MIN(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
		return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	CSR->clear_flags();
	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();
	f32 result = (source1Val <= source2Val) ? source1Val : source2Val; // Dont have to check for valid float as should already be valid from before.
	destReg->writeFloat(,result);
}

