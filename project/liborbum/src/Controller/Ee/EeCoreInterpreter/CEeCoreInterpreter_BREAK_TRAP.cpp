
#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/PCRegister32_t.h"
#include "Common/Tables/EECoreSyscallTable.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"
#include "Resources/Ee/Core/EeCoreCop0.hpp"
#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"
#include "Resources/EE/EECore/Types/EECoreException_t.h"

void EECoreInterpreter_s::BREAK()
{
	// EXCEPTION(BREAKPOINT)
	handleException(EECoreException_t::EX_BREAK);
}

void EECoreInterpreter_s::SYSCALL()
{
#if DEBUG_LOG_EE_SYSCALLS
	// Debug print the syscall mnemonic.
	// The convention is to store the syscall number in register $v1 ($3), then use the syscall instruction (the 'code' field within the syscall instruction is apparently unused).
	// When the syscall number is loaded into $v1, it is done so through
	//   ADDIU $v1, $0, number.
	// If the 16-bit 'syscall number' above has the sign bit set (negative), the EE OS will first make it unsigned then call the handler with the (i) prefix... TODO: not sure what the differnece is.
	// The EE OS only defines handlers for syscall numbers 0 -> 127 (128 total). 
	ubyte index = mEECore->R5900->GPR[3]->read_ubyte(0);
	log(Debug, "EECore Syscall, number %d (%s) @ cycle = 0x%llX.", index, EECoreSyscallTable::getSyscallInfo(index)->mMnemonic, DEBUG_LOOP_COUNTER);
#endif

	// EXCEPTION(SYSCALL)
	handleException(EECoreException_t::EX_SYSTEMCALL);
}

void EECoreInterpreter_s::TEQ()
{
	// TRAP_EXCEPTION(Rs == Rt).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));
	auto source2Val = static_cast<s64>(source2Reg->read_udword(0));

	if (source1Val == source2Val)
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::TEQI()
{
	// TRAP_EXCEPTION(Rs == imm).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto imm = static_cast<s64>(mEECoreInstruction.getIImmS());

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));

	if (source1Val == imm)
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::TGE()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));
	auto source2Val = static_cast<s64>(source2Reg->read_udword(0));

	if (source1Val >= source2Val)
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::TGEI()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto imm = static_cast<s64>(mEECoreInstruction.getIImmS());

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));

	if (source1Val >= imm)
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::TGEIU()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto imm = static_cast<udword>(static_cast<s64>(mEECoreInstruction.getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	auto source1Val = static_cast<udword>(source1Reg->read_udword(0));

	if (source1Val >= imm)
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::TGEU()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<udword>(source1Reg->read_udword(0));
	auto source2Val = static_cast<udword>(source2Reg->read_udword(0));

	if (source1Val >= source2Val)
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::TLT()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));
	auto source2Val = static_cast<s64>(source2Reg->read_udword(0));

	if (source1Val < source2Val)
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::TLTI()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto imm = static_cast<s64>(mEECoreInstruction.getIImmS());

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));

	if (source1Val < imm)
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::TLTIU()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto imm = static_cast<udword>(static_cast<s64>(mEECoreInstruction.getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	auto source1Val = static_cast<udword>(source1Reg->read_udword(0));

	if (source1Reg->read_udword(0) < imm)
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::TLTU()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	if (source1Reg->read_udword(0) < source2Reg->read_udword(0))
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::TNE()
{
	// TRAP_EXCEPTION(Rs != Rt).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));
	auto source2Val = static_cast<s64>(source2Reg->read_udword(0));

	if (source1Val != source2Val)
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::TNEI()
{
	// TRAP_EXCEPTION(Rs != imm).
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto imm = static_cast<s64>(mEECoreInstruction.getIImmS());

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));

	if (source1Val != imm)
		handleException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter_s::ERET()
{
	// ERET is an outlier, where it does not cause a branch delay instruction to be executed - set the PC directly.
	// ERET(). No exceptions.
	if (mEECore->COP0->Status->getFieldValue(, EeCoreCop0Register_Status::ERL) > 0)
	{
		const uword pcValue = mEECore->COP0->ErrorEPC->read_uword() - static_cast<s32>(Constants::MIPS::SIZE_MIPS_INSTRUCTION);
		mEECore->R5900->PC->setPCValueAbsolute(, pcValue);
		mEECore->COP0->Status->setFieldValue(, EeCoreCop0Register_Status::ERL, 0);
	}
	else
	{
		const uword pcValue = mEECore->COP0->EPC->read_uword() - static_cast<s32>(Constants::MIPS::SIZE_MIPS_INSTRUCTION);
		mEECore->R5900->PC->setPCValueAbsolute(, pcValue);
		mEECore->COP0->Status->setFieldValue(, EeCoreCop0Register_Status::EXL, 0);
	}
}
