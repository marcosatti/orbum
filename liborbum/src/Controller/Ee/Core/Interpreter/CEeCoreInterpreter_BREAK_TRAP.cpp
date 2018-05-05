#include <boost/format.hpp>

#include "Core.hpp"
#include "Utilities/Utilities.hpp"
#include "Common/Options.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::BREAK(const EeCoreInstruction inst)
{
	// EXCEPTION(BREAKPOINT)
	handle_exception(EeCoreException::EX_BREAK);
}

void CEeCoreInterpreter::SYSCALL(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
#if DEBUG_LOG_EE_SYSCALLS
	// Debug print the syscall mnemonic.
	// The convention is to store the syscall number in register $v1 ($3), then use the syscall instruction (the 'code' field within the syscall instruction is apparently unused).
	// When the syscall number is loaded into $v1, it is done so through
	//   ADDIU $v1, $0, number.
	// If the 16-bit 'syscall number' above has the sign bit set (negative), the EE OS will first make it unsigned then call the handler with the (i) prefix... TODO: not sure what the differnece is.
	// The EE OS only defines handlers for syscall numbers 0 -> 127 (128 total). 
	int index = static_cast<int>(r.ee.core.r5900.gpr[3]->read_ubyte(0));
	BOOST_LOG(Core::get_logger()) << 
		boost::format("EECore Syscall, number %d @ cycle = 0x%llX.") 
		% index 
		% DEBUG_LOOP_COUNTER;
#endif

	// EXCEPTION(SYSCALL)
	handle_exception(EeCoreException::EX_SYSTEMCALL);
}

void CEeCoreInterpreter::TEQ(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs == Rt).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
	auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));

	if (val_source1 == val_source2)
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::TEQI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs == imm).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto imm = static_cast<sdword>(inst.s_imm());

	auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

	if (val_source1 == imm)
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::TGE(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
	auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));

	if (val_source1 >= val_source2)
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::TGEI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs >= imm).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto imm = static_cast<sdword>(inst.s_imm());

	auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

	if (val_source1 >= imm)
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::TGEIU(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs >= imm).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto imm = static_cast<udword>(static_cast<sdword>(inst.s_imm())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	auto val_source1 = static_cast<udword>(reg_source1.read_udword(0));

	if (val_source1 >= imm)
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::TGEU(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<udword>(reg_source1.read_udword(0));
	auto val_source2 = static_cast<udword>(reg_source2.read_udword(0));

	if (val_source1 >= val_source2)
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::TLT(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs < Rt).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
	auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));

	if (val_source1 < val_source2)
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::TLTI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs < imm).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto imm = static_cast<sdword>(inst.s_imm());

	auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

	if (val_source1 < imm)
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::TLTIU(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs < imm).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto imm = static_cast<udword>(static_cast<sdword>(inst.s_imm())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	auto val_source1 = static_cast<udword>(reg_source1.read_udword(0));

	if (reg_source1.read_udword(0) < imm)
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::TLTU(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs < Rt).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	if (reg_source1.read_udword(0) < reg_source2.read_udword(0))
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::TNE(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs != Rt).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
	auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));

	if (val_source1 != val_source2)
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::TNEI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TRAP_EXCEPTION(Rs != imm).
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto imm = static_cast<sdword>(inst.s_imm());

	auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

	if (val_source1 != imm)
		handle_exception(EeCoreException::EX_TRAP);
}

void CEeCoreInterpreter::ERET(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// ERET is an outlier, where it does not cause a branch delay instruction to be executed - set the PC directly.
	// ERET(). No exceptions.
	if (r.ee.core.cop0.status.extract_field(EeCoreCop0Register_Status::ERL) > 0)
	{
		const uptr pc_address = r.ee.core.cop0.errorepc.read_uword() - static_cast<sword>(Constants::MIPS::SIZE_MIPS_INSTRUCTION);
		r.ee.core.r5900.pc.write_uword(pc_address);
		r.ee.core.cop0.status.insert_field(EeCoreCop0Register_Status::ERL, 0);
	}
	else
	{
		const uptr pc_address = r.ee.core.cop0.epc.read_uword() - static_cast<sword>(Constants::MIPS::SIZE_MIPS_INSTRUCTION);
		r.ee.core.r5900.pc.write_uword(pc_address);
		r.ee.core.cop0.status.insert_field(EeCoreCop0Register_Status::EXL, 0);
	}

	// Force a flush of all irq lines - we could be in the state
	// where the EE core is the only component left running, and
	// the next loop could cause an errornous interrupt to occur.
	// Since all components are constantly updating their interrupt
	// status, we don't really loose out on anything. ERET should 
	// be the last instruction executed before interrupts can occur 
	// again.
	r.ee.core.cop0.cause.clear_all_irq();

    // Flush translation caches (context change).
    translation_cache_data.flush();
    translation_cache_inst.flush();
}
