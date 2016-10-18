#pragma once

#include <memory>

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/PS2Resources/Types/MIPSInstruction/MIPSInstruction_t.h"
#include "Common/PS2Constants/PS2Constants.h"

class PS2Resources_t;
class VMMain;
class IOPMMUHandler;
class IOPExceptionHandler;
struct MIPSInstructionInfo_t;

/*
The IOP Interpreter. This is identical to a PS1 system.
The clock speed of the IOP is roughly 1/8th that of the EE Core (~36 MHz, increased from the original PSX clock speed of ~33.8 MHz).

No official documentation, but there is resources available on the internet documenting the R3000 and other parts.
*/
class IOPInterpreter : public VMExecutionCoreComponent
{
public:
	explicit IOPInterpreter(VMMain* const vmMain);

	/*
	See VMExecutionCoreComponent for documentation.
	*/
	std::vector<ClockSource_t> mClockSources;
	const std::vector<ClockSource_t> & getClockSources() override;

	/*
	Initalisation.
	*/
	void initalise() override;

	/*
	This is the "main loop" function called by the base interpreter component, and sub-functions it calls.
	*/
	s64 executionStep(const ClockSource_t & clockSource) override;
	void checkBranchDelaySlot() const;
	s64 executeInstruction();

	// Component state functions
	const std::unique_ptr<IOPExceptionHandler> & getExceptionHandler() const;
	const std::unique_ptr<IOPMMUHandler> & getMMUHandler() const;
	MIPSInstruction_t & getInstruction();

private:
#if defined(BUILD_DEBUG)
	// Debug loop counter 
	u64 DEBUG_LOOP_COUNTER = 0;
#endif

	/*
	The IOP exception handler.
	*/
	const std::unique_ptr<IOPExceptionHandler> mExceptionHandler;

	/*
	The IOP MMU handler. Translates PS2 virutal addresses into PS2 physical addresses, using a TLB.
	*/
	const std::unique_ptr<IOPMMUHandler> mMMUHandler;

	/*
	The is used as a temporary holder for the current instruction, while the operation to perform is being determined.
	It is also used while an instruction is being performed.
	*/
	MIPSInstruction_t mInstruction;
	const MIPSInstructionInfo_t * mInstructionInfo;

	// IOP Instruction funtionality.

	/*
	Unknown instruction function - does nothing when executed. Used for any instructions with implementation index 0 (ie: reserved, unknown or otherwise).
	If the BUILD_DEBUG macro is enabled, can be used to debug an unknown opcode by logging a message.
	*/
	void INSTRUCTION_UNKNOWN();

	/*
	Computational (ALU) Instructions. See IOPInterpreter_ALU.cpp for implementations (31 instructions total).
	*/
	void ADD();
	void ADDI();
	void ADDIU();
	void ADDU(); 
	void SUB();
	void SUBU();
	void DIV();
	void DIVU();
	void MULT();
	void MULTU();
	void SLL();
	void SLLV();
	void SRA();
	void SRAV();
	void SRL();
	void SRLV();
	void AND();
	void ANDI();
	void NOR();
	void OR();
	void ORI();
	void XOR();
	void XORI();
	void SLT();
	void SLTI();
	void SLTIU();
	void SLTU();

	/*
	Load and Store from Memory Instructions. See IOPInterpreter_LOAD_STORE_MEM.cpp for implementations (14 instructions total).
	*/
	void LB();
	void LBU();
	void LH();
	void LHU();
	void LUI();
	void LW();
	void LWL();
	void LWR();
	void SB();
	void SH();
	void SW();
	void SWL();
	void SWR();


	/*
	Special Data Transfer Instructions. See IOPInterpreter_SPECIAL_TRANSFER.cpp for implementations (26 instructions total).
	*/
	void MFC0();
	void MTC0();
	void MFHI();
	void MFLO();
	void MTHI();
	void MTLO();

	/*
	(Conditional) Branch and Jump Instructions. See IOPInterpreter_BRANCH_JUMP.cpp for implementations (26 instructions total).
	*/
	void BEQ();
	void BGEZ();
	void BGEZAL();
	void BGTZ();
	void BLEZ();
	void BLTZ();
	void BLTZAL();
	void BNE();
	void J();
	void JR();
	void JAL();
	void JALR();

	/*
	Others Instructions. See IOPInterpreter_OTHERS.cpp for implementations (9 instructions total).
	*/
	void BREAK();
	void SYSCALL();
	void TLBP();
	void TLBR();
	void TLBWI();
	void TLBWR();

	/*
	TODO: sort through.
	*/
	void LWC2();
	void SWC2();
	void CFC0();
	void CTC0();
	void RFE();
	void RTPS();
	void NCLIP();
	void OP();
	void DPCS();
	void INTPL();
	void MVMVA();
	void NCDS();
	void CDP();
	void NCDT();
	void NCCS();
	void CC();
	void NCS();
	void NCT();
	void SQR();
	void DCPL();
	void DPCT();
	void AVSZ3();
	void AVSZ4();
	void RTPT();
	void GPF();
	void GPL();
	void MFC2();
	void CFC2();
	void MTC2();
	void CTC2();

	/*
	Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index.
	See IOPInstructionTable and "IOP Instruction Implementation Register.xlsm" for more details.
	*/
	void(IOPInterpreter::*const IOP_INSTRUCTION_TABLE[PS2Constants::IOP::NUMBER_IOP_INSTRUCTIONS])() =
	{
		&IOPInterpreter::INSTRUCTION_UNKNOWN,
		&IOPInterpreter::J,
		&IOPInterpreter::JAL,
		&IOPInterpreter::BEQ,
		&IOPInterpreter::BNE,
		&IOPInterpreter::BLEZ,
		&IOPInterpreter::BGTZ,
		&IOPInterpreter::ADDI,
		&IOPInterpreter::ADDIU,
		&IOPInterpreter::SLTI,
		&IOPInterpreter::SLTIU,
		&IOPInterpreter::ANDI,
		&IOPInterpreter::ORI,
		&IOPInterpreter::XORI,
		&IOPInterpreter::LUI,
		&IOPInterpreter::LB,
		&IOPInterpreter::LH,
		&IOPInterpreter::LWL,
		&IOPInterpreter::LW,
		&IOPInterpreter::LBU,
		&IOPInterpreter::LHU,
		&IOPInterpreter::LWR,
		&IOPInterpreter::SB,
		&IOPInterpreter::SH,
		&IOPInterpreter::SWL,
		&IOPInterpreter::SW,
		&IOPInterpreter::SWR,
		&IOPInterpreter::LWC2,
		&IOPInterpreter::SWC2,
		&IOPInterpreter::SLL,
		&IOPInterpreter::SRL,
		&IOPInterpreter::SRA,
		&IOPInterpreter::SLLV,
		&IOPInterpreter::SRLV,
		&IOPInterpreter::SRAV,
		&IOPInterpreter::JR,
		&IOPInterpreter::JALR,
		&IOPInterpreter::SYSCALL,
		&IOPInterpreter::BREAK,
		&IOPInterpreter::MFHI,
		&IOPInterpreter::MTHI,
		&IOPInterpreter::MFLO,
		&IOPInterpreter::MTLO,
		&IOPInterpreter::MULT,
		&IOPInterpreter::MULTU,
		&IOPInterpreter::DIV,
		&IOPInterpreter::DIVU,
		&IOPInterpreter::ADD,
		&IOPInterpreter::ADDU,
		&IOPInterpreter::SUB,
		&IOPInterpreter::SUBU,
		&IOPInterpreter::AND,
		&IOPInterpreter::OR,
		&IOPInterpreter::XOR,
		&IOPInterpreter::NOR,
		&IOPInterpreter::SLT,
		&IOPInterpreter::SLTU,
		&IOPInterpreter::BLTZ,
		&IOPInterpreter::BGEZ,
		&IOPInterpreter::BLTZAL,
		&IOPInterpreter::BGEZAL,
		&IOPInterpreter::MFC0,
		&IOPInterpreter::CFC0,
		&IOPInterpreter::MTC0,
		&IOPInterpreter::CTC0,
		&IOPInterpreter::RFE,
		&IOPInterpreter::RTPS,
		&IOPInterpreter::NCLIP,
		&IOPInterpreter::OP,
		&IOPInterpreter::DPCS,
		&IOPInterpreter::INTPL,
		&IOPInterpreter::MVMVA,
		&IOPInterpreter::NCDS,
		&IOPInterpreter::CDP,
		&IOPInterpreter::NCDT,
		&IOPInterpreter::NCCS,
		&IOPInterpreter::CC,
		&IOPInterpreter::NCS,
		&IOPInterpreter::NCT,
		&IOPInterpreter::SQR,
		&IOPInterpreter::DCPL,
		&IOPInterpreter::DPCT,
		&IOPInterpreter::AVSZ3,
		&IOPInterpreter::AVSZ4,
		&IOPInterpreter::RTPT,
		&IOPInterpreter::GPF,
		&IOPInterpreter::GPL,
		&IOPInterpreter::MFC2,
		&IOPInterpreter::CFC2,
		&IOPInterpreter::MTC2,
		&IOPInterpreter::CTC2,
	};
};

