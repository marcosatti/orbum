#pragma once


#include "VM/Component Interfaces/VMInterpreterComponent.h"
#include "Common/PS2 Types/MIPSInstruction/MIPSInstruction_t.h"
#include <memory>

class PS2Resources_t;
class VMMain;
class InterpreterEECore : public VMInterpreterComponent
{
public:
	InterpreterEECore(const VMMain *const vmMain, const Interpreter *const interpreter);
	~InterpreterEECore();

	/*
	This is the "main loop" function called by the base interpreter component.
	*/
	void runInterpreterComponent() override;

private:

	// Component state functions

	/*
	The is used as a temporary holder for the current instruction, while the operation to perform is being determined.
	*/
	MIPSInstruction_t mInstruction;

	// Static R5900 Instruction functions. The instructions are organised according to the EE Overview Manual starting from page 26 (which also means separate cpp files per category).
	// Note: there is no pipeline concept in PCSX2 - instructions that are meant for pipeline 1 (marked with "1" at the end of the mnemonic) are treated like normal instructions.
	// Dots in mnemonics & function names are represented by the underscore character.

	/*
	Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index. See EECoreInstructionUtil for more details.
	*/
	static void(*const R5900_INSTRUCTION_TABLE[Constants::NUMBER_R5900_INSTRUCTIONS])(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);

	/*
	Unknown instruction function - does nothing when executed. Used for any instructions with implementation index 0 (ie: reserved, unknown or otherwise).
	If the PCSX2_DEBUG macro is enabled, can be used to debug an unknown opcode by logging a message.
	Will increase PC by 4 regardless.
	*/
	static void INSTRUCTION_UNKNOWN(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);

	/*
	Integer Add/Sub Instructions. See InterpreterR5900_INTEGER_ADD_SUB.cpp for implementations (31 instructions total).
	*/
	static void ADD(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void ADDI(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void ADDIU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void ADDU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DADD(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DADDI(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DADDIU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DADDU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DSUB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DSUBU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SUB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SUBU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PADDB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PADDH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PADDSB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PADDSH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PADDSW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PADDUB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PADDUH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PADDUW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PADDW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PADSBH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSUBB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSUBH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSUBSB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSUBSH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSUBSW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSUBUB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSUBUH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSUBUW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSUBW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);

	/*
	Integer Mult/Div Instructions. See InterpreterR5900_INTEGER_MULT_DIV.cpp for implementations (14 instructions total).
	*/
	static void DIV(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DIV1(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DIVU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DIVU1(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MULT(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MULT1(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MULTU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MULTU1(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PDIVBW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PDIVUW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PDIVW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PMULTH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PMULTUW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PMULTW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);

	/*
	Integer Mult-Add Instructions. See InterpreterR5900_INTEGER_MULT_ADD.cpp for implementations (11 instructions total).
	*/
	static void MADD(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MADD1(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MADDU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MADDU1(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PHMADH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PHMSBH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PMADDH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PMADDUW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PMADDW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PMSUBH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PMSUBW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);

	/*
	Floating-Point Instructions. See InterpreterR5900_FLOAT.cpp for implementations (10 instructions total).
	*/
	static void ADD_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void ADDA_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MADD_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MADDA_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MUL_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MULA_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MSUB_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MSUBA_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SUB_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SUBA_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);

	/*
	Shift Instructions. See InterpreterR5900_SHIFT.cpp for implementations (25 instructions total).
	*/
	static void DSRA(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DSLL(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DSLL32(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DSLLV(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DSRA32(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DSRAV(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DSRL(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DSRL32(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void DSRLV(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SLL(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SLLV(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SRA(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SRAV(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SRL(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SRLV(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSLLH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSLLVW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSLLW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSRAH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSRAVW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSRAW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSRLH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSRLVW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PSRLW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void QFSRV(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);

	/*
	Logical Instructions. See InterpreterR5900_LOGICAL.cpp for implementations (11 instructions total).
	*/
	static void AND(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void ANDI(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void NOR(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void OR(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void ORI(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void XOR(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void XORI(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PAND(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PNOR(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void POR(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PXOR(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);

	/*
	Logical Instructions. See InterpreterR5900_COMPARE.cpp for implementations (14 instructions total).
	*/
	static void SLT(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources); // For some reason this is missing in the EE Overview Manual (v6)?? I guess it should be here however.
	static void SLTI(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SLTIU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void SLTU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PCEQB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PCEQH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PCEQW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PCETB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PCETH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PCETW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void C_EQ_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void C_F_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void C_LE_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void C_LT_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);

	/*
	Min/Max Instructions. See InterpreterR5900_MIN_MAX.cpp for implementations (6 instructions total).
	*/
	static void PMAXH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PMAXW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PMINH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PMINW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MAX_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void MIN_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);

	/*
	Data Format Conversion (DFC) Instructions. See InterpreterR5900_DFC.cpp for implementations (4 instructions total).
	*/
	static void PEXT5(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void PPAC5(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void CVT_S_W(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
	static void CVT_W_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources);
};

