#pragma once

#include <memory>

#include "Common/Global/Globals.h"

#include "VM/Types/VMSystem_t.h"

#include "Resources/IOP/IOPCore/Types/IOPCoreException_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreInstruction_t.h"

class VM;
class IOPCore_t;
class ByteMMU_t;
struct MIPSInstructionInfo_t;

/*
The IOP Interpreter. This is similar to a PS1 system - as such you can find resources on the internet for the PS1.
The clock speed of the IOP is roughly 1/8th that of the EE Core (~36 MHz, increased from the original PSX clock speed of ~33.8 MHz).

No official documentation, but there is resources available on the internet documenting the R3000 and other parts.
*/
class IOPCoreInterpreter_s : public VMSystem_t
{
public:
	IOPCoreInterpreter_s(VM * vm);
	virtual ~IOPCoreInterpreter_s() = default;

	/*
	Initialisation.
	*/
	void initialise() override;

	/*
	This is the "main loop" function called by the base interpreter component, and sub-functions it calls.
	*/
	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:
	// UnitTest friend classes (use non-macro defined friend statements to remove the dependency on the GoogleTestLibrary). 
	// "FRIEND_TEST(Foo, Bar)" equivilant to "friend class Foo_Bar_Test".
	friend class TEST_IOPCoreInterpreter_s_MIPS_INSTRUCTION_IMPLEMENTATIONS_Test;

	//////////////////////////
	// Common Functionality //
	//////////////////////////

	/*
	Resources.
	*/
	std::shared_ptr<IOPCore_t> mIOPCore;
	std::shared_ptr<ByteMMU_t> mByteMMU;

#if defined(BUILD_DEBUG)
	// Debug loop counter 
	u64 DEBUG_LOOP_COUNTER = 0;
#endif

#if defined(BUILD_DEBUG)
	/*
	Prints debug information about interrupt sources.
	*/
	void printInterruptInfo() const;
#endif

	///////////////////////////////
	// Instruction Functionality //
	///////////////////////////////

	/*
	The is used as a temporary holder for the current instruction, while the operation to perform is being determined.
	It is also used while an instruction is being performed.
	*/
	IOPCoreInstruction_t mIOPCoreInstruction;

	/*
	Helper functions to check for: 
	 - The usability conditions of COP0.
	 - No over or underflow will occur for signed 32 bit integers.
	Returns a bool indicating if the instruction should return early because of unavailablity.
	Return early from instruction = true, proceed with instruction = false.
	They will automatically set the exception state as well.
	*/
	bool handleCOP0Usable();
	bool handleOverOrUnderflow32(const s32 & x, const s32 & y);

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
	See IOPCoreInstructionTable and "IOP Instruction Implementation Register.xlsm" for more details.
	*/
	void(IOPCoreInterpreter_s::* IOP_INSTRUCTION_TABLE[Constants::IOP::IOPCore::NUMBER_IOP_INSTRUCTIONS])() =
	{
		&IOPCoreInterpreter_s::INSTRUCTION_UNKNOWN,
		&IOPCoreInterpreter_s::J,
		&IOPCoreInterpreter_s::JAL,
		&IOPCoreInterpreter_s::BEQ,
		&IOPCoreInterpreter_s::BNE,
		&IOPCoreInterpreter_s::BLEZ,
		&IOPCoreInterpreter_s::BGTZ,
		&IOPCoreInterpreter_s::ADDI,
		&IOPCoreInterpreter_s::ADDIU,
		&IOPCoreInterpreter_s::SLTI,
		&IOPCoreInterpreter_s::SLTIU,
		&IOPCoreInterpreter_s::ANDI,
		&IOPCoreInterpreter_s::ORI,
		&IOPCoreInterpreter_s::XORI,
		&IOPCoreInterpreter_s::LUI,
		&IOPCoreInterpreter_s::LB,
		&IOPCoreInterpreter_s::LH,
		&IOPCoreInterpreter_s::LWL,
		&IOPCoreInterpreter_s::LW,
		&IOPCoreInterpreter_s::LBU,
		&IOPCoreInterpreter_s::LHU,
		&IOPCoreInterpreter_s::LWR,
		&IOPCoreInterpreter_s::SB,
		&IOPCoreInterpreter_s::SH,
		&IOPCoreInterpreter_s::SWL,
		&IOPCoreInterpreter_s::SW,
		&IOPCoreInterpreter_s::SWR,
		&IOPCoreInterpreter_s::LWC2,
		&IOPCoreInterpreter_s::SWC2,
		&IOPCoreInterpreter_s::SLL,
		&IOPCoreInterpreter_s::SRL,
		&IOPCoreInterpreter_s::SRA,
		&IOPCoreInterpreter_s::SLLV,
		&IOPCoreInterpreter_s::SRLV,
		&IOPCoreInterpreter_s::SRAV,
		&IOPCoreInterpreter_s::JR,
		&IOPCoreInterpreter_s::JALR,
		&IOPCoreInterpreter_s::SYSCALL,
		&IOPCoreInterpreter_s::BREAK,
		&IOPCoreInterpreter_s::MFHI,
		&IOPCoreInterpreter_s::MTHI,
		&IOPCoreInterpreter_s::MFLO,
		&IOPCoreInterpreter_s::MTLO,
		&IOPCoreInterpreter_s::MULT,
		&IOPCoreInterpreter_s::MULTU,
		&IOPCoreInterpreter_s::DIV,
		&IOPCoreInterpreter_s::DIVU,
		&IOPCoreInterpreter_s::ADD,
		&IOPCoreInterpreter_s::ADDU,
		&IOPCoreInterpreter_s::SUB,
		&IOPCoreInterpreter_s::SUBU,
		&IOPCoreInterpreter_s::AND,
		&IOPCoreInterpreter_s::OR,
		&IOPCoreInterpreter_s::XOR,
		&IOPCoreInterpreter_s::NOR,
		&IOPCoreInterpreter_s::SLT,
		&IOPCoreInterpreter_s::SLTU,
		&IOPCoreInterpreter_s::BLTZ,
		&IOPCoreInterpreter_s::BGEZ,
		&IOPCoreInterpreter_s::BLTZAL,
		&IOPCoreInterpreter_s::BGEZAL,
		&IOPCoreInterpreter_s::MFC0,
		&IOPCoreInterpreter_s::CFC0,
		&IOPCoreInterpreter_s::MTC0,
		&IOPCoreInterpreter_s::CTC0,
		&IOPCoreInterpreter_s::RFE,
		&IOPCoreInterpreter_s::RTPS,
		&IOPCoreInterpreter_s::NCLIP,
		&IOPCoreInterpreter_s::OP,
		&IOPCoreInterpreter_s::DPCS,
		&IOPCoreInterpreter_s::INTPL,
		&IOPCoreInterpreter_s::MVMVA,
		&IOPCoreInterpreter_s::NCDS,
		&IOPCoreInterpreter_s::CDP,
		&IOPCoreInterpreter_s::NCDT,
		&IOPCoreInterpreter_s::NCCS,
		&IOPCoreInterpreter_s::CC,
		&IOPCoreInterpreter_s::NCS,
		&IOPCoreInterpreter_s::NCT,
		&IOPCoreInterpreter_s::SQR,
		&IOPCoreInterpreter_s::DCPL,
		&IOPCoreInterpreter_s::DPCT,
		&IOPCoreInterpreter_s::AVSZ3,
		&IOPCoreInterpreter_s::AVSZ4,
		&IOPCoreInterpreter_s::RTPT,
		&IOPCoreInterpreter_s::GPF,
		&IOPCoreInterpreter_s::GPL,
		&IOPCoreInterpreter_s::MFC2,
		&IOPCoreInterpreter_s::CFC2,
		&IOPCoreInterpreter_s::MTC2,
		&IOPCoreInterpreter_s::CTC2,
	};

	/////////////////////////////
	// Exception Functionality //
	/////////////////////////////

	/*
	Handles a given exception by running the general exception handler based on the exception properties defined.
	*/
	void handleException(const IOPCoreException_t & exception);

	/*
	Checks if any of the interrupt lines have an IRQ pending, and raises an interrupt exception.
	*/
	void handleInterruptCheck();

#if defined(BUILD_DEBUG)
	// Debug for counting the number of exceptions handled.
	u64 DEBUG_HANDLED_EXCEPTION_COUNT = 0;
#endif

	///////////////////////
	// MMU Functionality //
	///////////////////////

	/*
	Internal types used within/to access MMU.
	*/
	enum MMUAccess_t { READ, WRITE };

	/*
	Performs a lookup from the given virtual address and access type.
	Returns if an error occured, indicating if the instruction that called should return early (error = true, no error = false).
	The physical address calculated is stored in physicalAddress.

	The IOP Core has no TLB - all virtual addresses are directly converted to physical addresses based on kernel segments.
	Currently if the CPU is not in a kernel context or an MMU error occurs, a runtime_error exception will be thrown.
	TODO: investigate into user mode. I think the original PSX had no TLB...
	*/
	bool getPhysicalAddress(const u32 virtualAddress, const MMUAccess_t access, u32 & physicalAddress);
};

