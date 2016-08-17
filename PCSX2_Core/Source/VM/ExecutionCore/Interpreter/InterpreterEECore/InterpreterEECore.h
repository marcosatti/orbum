#pragma once

#include <memory>

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/Types/MIPSInstruction/MIPSInstruction_t.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/ExceptionHandler/ExceptionHandler.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/MMUHandler/MMUHandler.h"


class PS2Resources_t;
class VMMain;
class InterpreterEECore : public VMExecutionCoreComponent
{
public:
	InterpreterEECore(const VMMain *const vmMain);
	~InterpreterEECore();

	/*
	This is the "main loop" function called by the base interpreter component.
	*/
	void executionStep() override;

	// Component state functions
	const std::unique_ptr<ExceptionHandler> & getExceptionHandler() const;
	const std::unique_ptr<MMUHandler> & getMMUHandler() const;
	const MIPSInstruction_t & getInstruction() const;

private:

	// Component state functions
	/*
	The PS2 exception handler.
	*/
	const std::unique_ptr<ExceptionHandler> mExceptionHandler;

	/*
	The PS2 MMU handler. Translates PS2 virutal addresses into PS2 physical addresses, using a TLB.
	*/
	const std::unique_ptr<MMUHandler> mMMUHandler;

	/*
	The is used as a temporary holder for the current instruction, while the operation to perform is being determined.
	It is also used while an instruction is being performed.
	*/
	MIPSInstruction_t mInstruction;

	// EECore Instruction functions. The instructions are organised according to the EE Overview Manual starting from page 26 (which also means separate cpp files per category).
	// Note 1: there is no pipeline concept in PCSX2 - instructions that are meant for pipeline 1 (marked with "1" at the end of the mnemonic) are treated like normal instructions.
	// Note 2: Dots in mnemonics & function names are represented by the underscore character.
	// Note 3: Where exceptions are declared in the instruction information (ie: see EE Core Instruction Manual), some may be thrown in the instruction body itself (for example
	//         with integer overflows), while others may be thrown elsewhere in the emulator (such as the coprocessors being unacessible, which are defined when a read or write
	//         occurs in a subobject).

	/*
	Unknown instruction function - does nothing when executed. Used for any instructions with implementation index 0 (ie: reserved, unknown or otherwise).
	If the PCSX2_DEBUG macro is enabled, can be used to debug an unknown opcode by logging a message.
	Will increase PC by 4 regardless.
	*/
	void INSTRUCTION_UNKNOWN();

	/*
	Integer Add/Sub Instructions. See InterpreterEECore_INTEGER_ADD_SUB.cpp for implementations (31 instructions total).
	*/
	void ADD();
	void ADDI();
	void ADDIU();
	void ADDU();
	void DADD();
	void DADDI();
	void DADDIU();
	void DADDU();
	void DSUB();
	void DSUBU();
	void SUB();
	void SUBU();
	void PADDB();
	void PADDH();
	void PADDSB();
	void PADDSH();
	void PADDSW();
	void PADDUB();
	void PADDUH();
	void PADDUW();
	void PADDW();
	void PADSBH();
	void PSUBB();
	void PSUBH();
	void PSUBSB();
	void PSUBSH();
	void PSUBSW();
	void PSUBUB();
	void PSUBUH();
	void PSUBUW();
	void PSUBW();

	/*
	Integer Mult/Div Instructions. See InterpreterEECore_INTEGER_MULT_DIV.cpp for implementations (14 instructions total).
	*/
	void DIV();
	void DIV1();
	void DIVU();
	void DIVU1();
	void MULT();
	void MULT1();
	void MULTU();
	void MULTU1();
	void PDIVBW();
	void PDIVUW();
	void PDIVW();
	void PMULTH();
	void PMULTUW();
	void PMULTW();

	/*
	Integer Mult-Add Instructions. See InterpreterEECore_INTEGER_MULT_ADD.cpp for implementations (11 instructions total).
	*/
	void MADD();
	void MADD1();
	void MADDU();
	void MADDU1();
	void PHMADH();
	void PHMSBH();
	void PMADDH();
	void PMADDUW();
	void PMADDW();
	void PMSUBH();
	void PMSUBW();

	/*
	Floating-Point Instructions. See InterpreterEECore_FLOAT.cpp for implementations (10 instructions total).
	*/
	void ADD_S();
	void ADDA_S();
	void MADD_S();
	void MADDA_S();
	void MUL_S();
	void MULA_S();
	void MSUB_S();
	void MSUBA_S();
	void SUB_S();
	void SUBA_S();

	/*
	Shift Instructions. See InterpreterEECore_SHIFT.cpp for implementations (25 instructions total).
	*/
	void DSRA();
	void DSLL();
	void DSLL32();
	void DSLLV();
	void DSRA32();
	void DSRAV();
	void DSRL();
	void DSRL32();
	void DSRLV();
	void SLL();
	void SLLV();
	void SRA();
	void SRAV();
	void SRL();
	void SRLV();
	void PSLLH();
	void PSLLVW();
	void PSLLW();
	void PSRAH();
	void PSRAVW();
	void PSRAW();
	void PSRLH();
	void PSRLVW();
	void PSRLW();
	void QFSRV();

	/*
	Logical Instructions. See InterpreterEECore_LOGICAL.cpp for implementations (11 instructions total).
	*/
	void AND();
	void ANDI();
	void NOR();
	void OR();
	void ORI();
	void XOR();
	void XORI();
	void PAND();
	void PNOR();
	void POR();
	void PXOR();

	/*
	Logical Instructions. See InterpreterEECore_COMPARE.cpp for implementations (14 instructions total).
	*/
	void SLT(); // For some reason this is missing in the EE Overview Manual (v6)?? I guess it should be here however.
	void SLTI();
	void SLTIU();
	void SLTU();
	void PCEQB();
	void PCEQH();
	void PCEQW();
	void PCETB();
	void PCETH();
	void PCETW();
	void C_EQ_S();
	void C_F_S();
	void C_LE_S();
	void C_LT_S();

	/*
	Min/Max Instructions. See InterpreterEECore_MIN_MAX.cpp for implementations (6 instructions total).
	*/
	void PMAXH();
	void PMAXW();
	void PMINH();
	void PMINW();
	void MAX_S();
	void MIN_S();

	/*
	Data Format Conversion (DFC) Instructions. See InterpreterEECore_DFC.cpp for implementations (4 instructions total).
	*/
	void PEXT5();
	void PPAC5();
	void CVT_S_W();
	void CVT_W_S();

	/*
	Reordering Instructions. See InterpreterEECore_REORDERING.cpp for implementations (20 instructions total).
	*/
	void PCPYH();
	void PCPYLD();
	void PCPYUD();
	void PEXCH();
	void PEXCW();
	void PEXEH();
	void PEXEW();
	void PEXTLB();
	void PEXTLH();
	void PEXTLW();
	void PEXTUB();
	void PEXTUH();
	void PEXTUW();
	void PINTEH();
	void PINTH();
	void PPACB();
	void PPACH();
	void PPACW();
	void PREVH();
	void PROT3W();

	/*
	Others Instructions. See InterpreterEECore_OTHERS.cpp for implementations (7 instructions total).
	*/
	void PABSH();
	void PABSW();
	void PLZCW();
	void ABS_S();
	void NEG_S();
	void RSQRT_S();
	void SQRT_S();

	/*
	Register-Register Transfer Instructions. See InterpreterEECore_REG_TRANSFER.cpp for implementations (23 instructions total).
	*/
	void MFHI();
	void MFLO();
	void MOVN();
	void MOVZ();
	void MTHI();
	void MTLO();
	void MFHI1();
	void MFLO1();
	void MTHI1();
	void MTLO1();
	void PMFHI();
	void PMFHL_LH();
	void PMFHL_LW();
	void PMFHL_SH();
	void PMFHL_SLW();
	void PMFHL_UW();
	void PMFLO();
	void PMTHI();
	void PMTHL_LW();
	void PMTLO();
	void MFC1();
	void MOV_S();
	void MTC1();

	/*
	Load from Memory Instructions. See InterpreterEECore_LOAD_MEM.cpp for implementations (14 instructions total).
	*/
	void LB();
	void LBU();
	void LD();
	void LDL();
	void LDR();
	void LH();
	void LHU();
	void LUI();
	void LW();
	void LWL();
	void LWR();
	void LWU();
	void LQ();
	void LWC1();

	/*
	Store to Memory Instructions. See InterpreterEECore_STORE_MEM.cpp for implementations (14 instructions total).
	*/
	void SB();
	void SD();
	void SDL();
	void SDR();
	void SH();
	void SW();
	void SWL();
	void SWR();
	void SQ();
	void SWC1();

	/*
	Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index. See EECoreInstructionUtil for more details.
	*/
	void(InterpreterEECore::*const EECORE_INSTRUCTION_TABLE[Constants::NUMBER_EECORE_INSTRUCTIONS])() = {
		&InterpreterEECore::INSTRUCTION_UNKNOWN,
	};

};

