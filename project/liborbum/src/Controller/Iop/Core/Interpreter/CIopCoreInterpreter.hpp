#pragma once

#include "Common/Constants.hpp"

#include "Controller/CController.hpp"

#include "Resources/Iop/Core/IopCoreException.hpp"
#include "Resources/Iop/Core/IopCoreInstruction.hpp"

class Core;

// The IOP Interpreter. This is similar to a PS1 system - as such you can find resources on the internet for the PS1.
// The clock speed of the IOP is roughly 1/8th that of the EE Core (~36 MHz, increased from the original PSX clock speed of ~33.8 MHz).
// No official documentation, but there is resources available on the internet documenting the R3000 and other parts.
class CIopCoreInterpreter : public CController
{
public:
	CIopCoreInterpreter(Core * core);
	virtual ~CIopCoreInterpreter();

	void handle_event(const ControllerEvent & event) const override;

	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us) const;
	
	/// Steps through the IOP Core state, executing instructions.
	int time_step(const int ticks_available) const;

	//////////////////////////
	// Common Functionality //
	//////////////////////////

#if defined(BUILD_DEBUG)
	// Debug loop counter 
	mutable size_t DEBUG_LOOP_COUNTER = 0;
#endif

#if defined(BUILD_DEBUG)
	/// Prints debug information about interrupt sources.
	void debug_print_interrupt_info() const;
#endif

	///////////////////////////////
	// Instruction Functionality //
	///////////////////////////////

	/// Helper functions to check for: 
	///  - The usability conditions of COP0.
	///  - No over or underflow will occur for signed 32 bit integers.
	/// Returns a bool indicating if the instruction should return early because of unavailablity.
	/// Return early from instruction = true, proceed with instruction = false.
	/// They will automatically set the exception state as well.
	bool handle_cop0_usable() const;
	bool handle_over_or_underflow_32(const sword & x, const sword & y) const;

	/// Unknown instruction function - does nothing when executed. Used for any instructions with implementation index 0 (ie: reserved, unknown or otherwise).
	/// If the BUILD_DEBUG macro is enabled, can be used to debug an unknown opcode by logging a message.
	void INSTRUCTION_UNKNOWN(const IopCoreInstruction inst) const;

	/// Computational (ALU) Instructions. See IOPInterpreter_ALU.cpp for implementations (31 instructions total).
	void ADD(const IopCoreInstruction inst) const;
	void ADDI(const IopCoreInstruction inst) const;
	void ADDIU(const IopCoreInstruction inst) const;
	void ADDU(const IopCoreInstruction inst) const; 
	void SUB(const IopCoreInstruction inst) const;
	void SUBU(const IopCoreInstruction inst) const;
	void DIV(const IopCoreInstruction inst) const;
	void DIVU(const IopCoreInstruction inst) const;
	void MULT(const IopCoreInstruction inst) const;
	void MULTU(const IopCoreInstruction inst) const;
	void SLL(const IopCoreInstruction inst) const;
	void SLLV(const IopCoreInstruction inst) const;
	void SRA(const IopCoreInstruction inst) const;
	void SRAV(const IopCoreInstruction inst) const;
	void SRL(const IopCoreInstruction inst) const;
	void SRLV(const IopCoreInstruction inst) const;
	void AND(const IopCoreInstruction inst) const;
	void ANDI(const IopCoreInstruction inst) const;
	void NOR(const IopCoreInstruction inst) const;
	void OR(const IopCoreInstruction inst) const;
	void ORI(const IopCoreInstruction inst) const;
	void XOR(const IopCoreInstruction inst) const;
	void XORI(const IopCoreInstruction inst) const;
	void SLT(const IopCoreInstruction inst) const;
	void SLTI(const IopCoreInstruction inst) const;
	void SLTIU(const IopCoreInstruction inst) const;
	void SLTU(const IopCoreInstruction inst) const;

	/// Load and Store from Memory Instructions. See IOPInterpreter_LOAD_STORE_MEM.cpp for implementations (14 instructions total).
	void LB(const IopCoreInstruction inst) const;
	void LBU(const IopCoreInstruction inst) const;
	void LH(const IopCoreInstruction inst) const;
	void LHU(const IopCoreInstruction inst) const;
	void LUI(const IopCoreInstruction inst) const;
	void LW(const IopCoreInstruction inst) const;
	void LWL(const IopCoreInstruction inst) const;
	void LWR(const IopCoreInstruction inst) const;
	void SB(const IopCoreInstruction inst) const;
	void SH(const IopCoreInstruction inst) const;
	void SW(const IopCoreInstruction inst) const;
	void SWL(const IopCoreInstruction inst) const;
	void SWR(const IopCoreInstruction inst) const;

	/// Special Data Transfer Instructions. See IOPInterpreter_SPECIAL_TRANSFER.cpp for implementations (26 instructions total).
	void MFC0(const IopCoreInstruction inst) const;
	void MTC0(const IopCoreInstruction inst) const;
	void MFHI(const IopCoreInstruction inst) const;
	void MFLO(const IopCoreInstruction inst) const;
	void MTHI(const IopCoreInstruction inst) const;
	void MTLO(const IopCoreInstruction inst) const;

	/// (Conditional) Branch and Jump Instructions. See IOPInterpreter_BRANCH_JUMP.cpp for implementations (26 instructions total).
	void BEQ(const IopCoreInstruction inst) const;
	void BGEZ(const IopCoreInstruction inst) const;
	void BGEZAL(const IopCoreInstruction inst) const;
	void BGTZ(const IopCoreInstruction inst) const;
	void BLEZ(const IopCoreInstruction inst) const;
	void BLTZ(const IopCoreInstruction inst) const;
	void BLTZAL(const IopCoreInstruction inst) const;
	void BNE(const IopCoreInstruction inst) const;
	void J(const IopCoreInstruction inst) const;
	void JR(const IopCoreInstruction inst) const;
	void JAL(const IopCoreInstruction inst) const;
	void JALR(const IopCoreInstruction inst) const;

	/// Others Instructions. See IOPInterpreter_OTHERS.cpp for implementations (9 instructions total).
	void BREAK(const IopCoreInstruction inst) const;
	void SYSCALL(const IopCoreInstruction inst) const;
	void TLBP(const IopCoreInstruction inst) const;
	void TLBR(const IopCoreInstruction inst) const;
	void TLBWI(const IopCoreInstruction inst) const;
	void TLBWR(const IopCoreInstruction inst) const;

	/// TODO: sort through.
	void LWC2(const IopCoreInstruction inst) const;
	void SWC2(const IopCoreInstruction inst) const;
	void CFC0(const IopCoreInstruction inst) const;
	void CTC0(const IopCoreInstruction inst) const;
	void RFE(const IopCoreInstruction inst) const;
	void RTPS(const IopCoreInstruction inst) const;
	void NCLIP(const IopCoreInstruction inst) const;
	void OP(const IopCoreInstruction inst) const;
	void DPCS(const IopCoreInstruction inst) const;
	void INTPL(const IopCoreInstruction inst) const;
	void MVMVA(const IopCoreInstruction inst) const;
	void NCDS(const IopCoreInstruction inst) const;
	void CDP(const IopCoreInstruction inst) const;
	void NCDT(const IopCoreInstruction inst) const;
	void NCCS(const IopCoreInstruction inst) const;
	void CC(const IopCoreInstruction inst) const;
	void NCS(const IopCoreInstruction inst) const;
	void NCT(const IopCoreInstruction inst) const;
	void SQR(const IopCoreInstruction inst) const;
	void DCPL(const IopCoreInstruction inst) const;
	void DPCT(const IopCoreInstruction inst) const;
	void AVSZ3(const IopCoreInstruction inst) const;
	void AVSZ4(const IopCoreInstruction inst) const;
	void RTPT(const IopCoreInstruction inst) const;
	void GPF(const IopCoreInstruction inst) const;
	void GPL(const IopCoreInstruction inst) const;
	void MFC2(const IopCoreInstruction inst) const;
	void CFC2(const IopCoreInstruction inst) const;
	void MTC2(const IopCoreInstruction inst) const;
	void CTC2(const IopCoreInstruction inst) const;

	/// Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index.
	/// See IOPCoreInstructionTable and "IOP Instruction Implementation Register.xlsm" for more details.
	void(CIopCoreInterpreter::* IOP_INSTRUCTION_TABLE[Constants::IOP::IOPCore::NUMBER_IOP_INSTRUCTIONS])(const IopCoreInstruction inst) const =
	{
		&CIopCoreInterpreter::INSTRUCTION_UNKNOWN,
		&CIopCoreInterpreter::J,
		&CIopCoreInterpreter::JAL,
		&CIopCoreInterpreter::BEQ,
		&CIopCoreInterpreter::BNE,
		&CIopCoreInterpreter::BLEZ,
		&CIopCoreInterpreter::BGTZ,
		&CIopCoreInterpreter::ADDI,
		&CIopCoreInterpreter::ADDIU,
		&CIopCoreInterpreter::SLTI,
		&CIopCoreInterpreter::SLTIU,
		&CIopCoreInterpreter::ANDI,
		&CIopCoreInterpreter::ORI,
		&CIopCoreInterpreter::XORI,
		&CIopCoreInterpreter::LUI,
		&CIopCoreInterpreter::LB,
		&CIopCoreInterpreter::LH,
		&CIopCoreInterpreter::LWL,
		&CIopCoreInterpreter::LW,
		&CIopCoreInterpreter::LBU,
		&CIopCoreInterpreter::LHU,
		&CIopCoreInterpreter::LWR,
		&CIopCoreInterpreter::SB,
		&CIopCoreInterpreter::SH,
		&CIopCoreInterpreter::SWL,
		&CIopCoreInterpreter::SW,
		&CIopCoreInterpreter::SWR,
		&CIopCoreInterpreter::LWC2,
		&CIopCoreInterpreter::SWC2,
		&CIopCoreInterpreter::SLL,
		&CIopCoreInterpreter::SRL,
		&CIopCoreInterpreter::SRA,
		&CIopCoreInterpreter::SLLV,
		&CIopCoreInterpreter::SRLV,
		&CIopCoreInterpreter::SRAV,
		&CIopCoreInterpreter::JR,
		&CIopCoreInterpreter::JALR,
		&CIopCoreInterpreter::SYSCALL,
		&CIopCoreInterpreter::BREAK,
		&CIopCoreInterpreter::MFHI,
		&CIopCoreInterpreter::MTHI,
		&CIopCoreInterpreter::MFLO,
		&CIopCoreInterpreter::MTLO,
		&CIopCoreInterpreter::MULT,
		&CIopCoreInterpreter::MULTU,
		&CIopCoreInterpreter::DIV,
		&CIopCoreInterpreter::DIVU,
		&CIopCoreInterpreter::ADD,
		&CIopCoreInterpreter::ADDU,
		&CIopCoreInterpreter::SUB,
		&CIopCoreInterpreter::SUBU,
		&CIopCoreInterpreter::AND,
		&CIopCoreInterpreter::OR,
		&CIopCoreInterpreter::XOR,
		&CIopCoreInterpreter::NOR,
		&CIopCoreInterpreter::SLT,
		&CIopCoreInterpreter::SLTU,
		&CIopCoreInterpreter::BLTZ,
		&CIopCoreInterpreter::BGEZ,
		&CIopCoreInterpreter::BLTZAL,
		&CIopCoreInterpreter::BGEZAL,
		&CIopCoreInterpreter::MFC0,
		&CIopCoreInterpreter::CFC0,
		&CIopCoreInterpreter::MTC0,
		&CIopCoreInterpreter::CTC0,
		&CIopCoreInterpreter::RFE,
		&CIopCoreInterpreter::RTPS,
		&CIopCoreInterpreter::NCLIP,
		&CIopCoreInterpreter::OP,
		&CIopCoreInterpreter::DPCS,
		&CIopCoreInterpreter::INTPL,
		&CIopCoreInterpreter::MVMVA,
		&CIopCoreInterpreter::NCDS,
		&CIopCoreInterpreter::CDP,
		&CIopCoreInterpreter::NCDT,
		&CIopCoreInterpreter::NCCS,
		&CIopCoreInterpreter::CC,
		&CIopCoreInterpreter::NCS,
		&CIopCoreInterpreter::NCT,
		&CIopCoreInterpreter::SQR,
		&CIopCoreInterpreter::DCPL,
		&CIopCoreInterpreter::DPCT,
		&CIopCoreInterpreter::AVSZ3,
		&CIopCoreInterpreter::AVSZ4,
		&CIopCoreInterpreter::RTPT,
		&CIopCoreInterpreter::GPF,
		&CIopCoreInterpreter::GPL,
		&CIopCoreInterpreter::MFC2,
		&CIopCoreInterpreter::CFC2,
		&CIopCoreInterpreter::MTC2,
		&CIopCoreInterpreter::CTC2,
	};

	/////////////////////////////
	// Exception Functionality //
	/////////////////////////////

	/// Handles a given exception by running the general exception handler based on the exception properties defined.
	void handle_exception(const IopCoreException exception) const;

	/// Checks if any of the interrupt lines have an IRQ pending, and raises an interrupt exception.
	void handle_interrupt_check() const;

#if defined(BUILD_DEBUG)
	// Debug for counting the number of exceptions handled.
	mutable size_t DEBUG_HANDLED_EXCEPTION_COUNT = 0;
#endif

	///////////////////////
	// MMU Functionality //
	///////////////////////

	/// Internal types used within/to access MMU.
	enum MmuAccess { READ, WRITE };

	/// Performs a lookup from the given virtual address and access type.
	/// Returns if an error occured, indicating if the instruction that called should return early (error = true, no error = false).
	/// The physical address calculated is stored in physical_address.
	/// The IOP Core has no TLB - all virtual addresses are directly converted to physical addresses based on kernel segments.
	/// Currently if the CPU is not in a kernel context or an MMU error occurs, a runtime_error exception will be thrown.
	bool translate_vaddress(const uptr virtual_address, const MmuAccess access, uptr & physical_address) const;
};

