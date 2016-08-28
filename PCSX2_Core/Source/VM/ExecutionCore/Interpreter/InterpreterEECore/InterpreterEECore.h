#pragma once

#include <memory>

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/Types/MIPSInstruction/MIPSInstruction_t.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/ExceptionHandler/ExceptionHandler.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/MMUHandler/MMUHandler.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

using EECoreInstructionInfo_t = EECoreInstructionUtil::EECoreInstructionInfo_t;

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
	void checkExceptionQueue() const;
	void checkBranchDelaySlot() const;

private:

	// Component state functions

#if defined(BUILD_DEBUG)
	// Debug loop counter 
	u64 DEBUG_LOOP_COUNTER = 0;
#endif

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
	const EECoreInstructionInfo_t * mInstructionInfo;

	// EECore Instruction functions. The instructions are organised according to the EE Overview Manual starting from page 26 (which also means separate cpp files per category).
	// Note 1: there is no pipeline concept in PCSX2 - instructions that are meant for pipeline 1 (marked with "1" at the end of the mnemonic) are treated like normal instructions.
	// Note 2: Dots in mnemonics & function names are represented by the underscore character.

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
	void DIV_S();
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
	Compare Instructions. See InterpreterEECore_COMPARE.cpp for implementations (14 instructions total).
	*/
	void SLT(); // For some reason this is missing in the EE Overview Manual (v6)?? I guess it should be here however.
	void SLTI();
	void SLTIU();
	void SLTU();
	void PCEQB();
	void PCEQH();
	void PCEQW();
	void PCGTB();
	void PCGTH();
	void PCGTW();
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
	Others (ALU) Instructions. See InterpreterEECore_ALU_OTHERS.cpp for implementations (7 instructions total).
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
	void PMFHL(); // Calls one of the sub functions below.
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
	Store to Memory Instructions. See InterpreterEECore_STORE_MEM.cpp for implementations (10 instructions total).
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
	Special Data Transfer Instructions. See InterpreterEECore_SPECIAL_TRANSFER.cpp for implementations (26 instructions total).
	*/
	void MFSA();
	void MTSA();
	void MTSAB();
	void MTSAH();
	void MFBPC();
	void MFC0();
	void MFDAB();
	void MFDABM();
	void MFDVB();
	void MFDVBM();
	void MFIAB();
	void MFIABM();
	void MFPC();
	void MFPS();
	void MTBPC();
	void MTC0();
	void MTDAB();
	void MTDABM();
	void MTDVB();
	void MTDVBM();
	void MTIAB();
	void MTIABM();
	void MTPC();
	void MTPS();
	void CFC1();
	void CTC1();

	/*
	Conditional Branch and Jump Instructions. See InterpreterEECore_COND_BRANCH_JUMP.cpp for implementations (26 instructions total).
	*/
	void BEQ();
	void BEQL();
	void BGEZ();
	void BGEZL();
	void BGTZ();
	void BGTZL();
	void BLEZ();
	void BLEZL();
	void BLTZ();
	void BLTZL();
	void BNE();
	void BNEL();
	void BC0F();
	void BC0FL();
	void BC0T();
	void BC0TL();
	void BC1F();
	void BC1FL();
	void BC1T();
	void BC1TL();
	void BC2F();
	void BC2FL();
	void BC2T();
	void BC2TL();
	void J();
	void JR();

	/*
	Subroutine Call Instructions. See InterpreterEECore_CALL.cpp for implementations (6 instructions total).
	*/
	void BGEZAL();
	void BGEZALL();
	void BLTZAL();
	void BLTZALL();
	void JAL();
	void JALR();

	/*
	Break and Trap Instructions. See InterpreterEECore_BREAK_TRAP.cpp for implementations (15 instructions total).
	*/
	void BREAK();
	void SYSCALL();
	void TEQ();
	void TEQI();
	void TGE();
	void TGEI();
	void TGEIU();
	void TGEU();
	void TLT();
	void TLTI();
	void TLTIU();
	void TLTU();
	void TNE();
	void TNEI();
	void ERET();

	/*
	Others Instructions. See InterpreterEECore_OTHERS.cpp for implementations (9 instructions total). Includes the TLB instructions as they are missing in the overview manual...
	*/
	void SYNC_STYPE();
	void PREF();
	void DI();
	void EI();
	void CACHE();
	void TLBP();
	void TLBR();
	void TLBWI();
	void TLBWR();

	/*
	Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index. 
	See EECoreInstructionUtil and "EECore Instruction Implementation Register.xlsm" for more details.
	*/
	void(InterpreterEECore::*const EECORE_INSTRUCTION_TABLE[Constants::NUMBER_EECORE_INSTRUCTIONS])() = {
		&InterpreterEECore::INSTRUCTION_UNKNOWN,
		&InterpreterEECore::J,
		&InterpreterEECore::JAL,
		&InterpreterEECore::BEQ,
		&InterpreterEECore::BNE,
		&InterpreterEECore::BLEZ,
		&InterpreterEECore::BGTZ,
		&InterpreterEECore::ADDI,
		&InterpreterEECore::ADDIU,
		&InterpreterEECore::SLTI,
		&InterpreterEECore::SLTIU,
		&InterpreterEECore::ANDI,
		&InterpreterEECore::ORI,
		&InterpreterEECore::XORI,
		&InterpreterEECore::LUI,
		&InterpreterEECore::BEQL,
		&InterpreterEECore::BNEL,
		&InterpreterEECore::BLEZL,
		&InterpreterEECore::BGTZL,
		&InterpreterEECore::DADDI,
		&InterpreterEECore::DADDIU,
		&InterpreterEECore::LDL,
		&InterpreterEECore::LDR,
		&InterpreterEECore::LQ,
		&InterpreterEECore::SQ,
		&InterpreterEECore::LB,
		&InterpreterEECore::LH,
		&InterpreterEECore::LWL,
		&InterpreterEECore::LW,
		&InterpreterEECore::LBU,
		&InterpreterEECore::LHU,
		&InterpreterEECore::LWR,
		&InterpreterEECore::LWU,
		&InterpreterEECore::SB,
		&InterpreterEECore::SH,
		&InterpreterEECore::SWL,
		&InterpreterEECore::SW,
		&InterpreterEECore::SDL,
		&InterpreterEECore::SDR,
		&InterpreterEECore::SWR,
		&InterpreterEECore::CACHE,
		&InterpreterEECore::LWC1,
		&InterpreterEECore::PREF,
		&InterpreterEECore::INSTRUCTION_UNKNOWN, // &LQC2,
		&InterpreterEECore::LD,
		&InterpreterEECore::SWC1,
		&InterpreterEECore::INSTRUCTION_UNKNOWN, // &SQC2,
		&InterpreterEECore::SD,
		&InterpreterEECore::SLL,
		&InterpreterEECore::SRL,
		&InterpreterEECore::SRA,
		&InterpreterEECore::SLLV,
		&InterpreterEECore::SRLV,
		&InterpreterEECore::SRAV,
		&InterpreterEECore::JR,
		&InterpreterEECore::JALR,
		&InterpreterEECore::MOVZ,
		&InterpreterEECore::MOVN,
		&InterpreterEECore::SYSCALL,
		&InterpreterEECore::BREAK,
		&InterpreterEECore::SYNC_STYPE,
		&InterpreterEECore::MFHI,
		&InterpreterEECore::MTHI,
		&InterpreterEECore::MFLO,
		&InterpreterEECore::MTLO,
		&InterpreterEECore::DSLLV,
		&InterpreterEECore::DSRLV,
		&InterpreterEECore::DSRAV,
		&InterpreterEECore::MULT,
		&InterpreterEECore::MULTU,
		&InterpreterEECore::DIV,
		&InterpreterEECore::DIVU,
		&InterpreterEECore::ADD,
		&InterpreterEECore::ADDU,
		&InterpreterEECore::SUB,
		&InterpreterEECore::SUBU,
		&InterpreterEECore::AND,
		&InterpreterEECore::OR,
		&InterpreterEECore::XOR,
		&InterpreterEECore::NOR,
		&InterpreterEECore::MFSA,
		&InterpreterEECore::MTSA,
		&InterpreterEECore::SLT,
		&InterpreterEECore::SLTU,
		&InterpreterEECore::DADD,
		&InterpreterEECore::DADDU,
		&InterpreterEECore::DSUB,
		&InterpreterEECore::DSUBU,
		&InterpreterEECore::TGE,
		&InterpreterEECore::TGEU,
		&InterpreterEECore::TLT,
		&InterpreterEECore::TLTU,
		&InterpreterEECore::TEQ,
		&InterpreterEECore::TNE,
		&InterpreterEECore::DSLL,
		&InterpreterEECore::DSRL,
		&InterpreterEECore::DSRA,
		&InterpreterEECore::DSLL32,
		&InterpreterEECore::DSRL32,
		&InterpreterEECore::DSRA32,
		&InterpreterEECore::BLTZ,
		&InterpreterEECore::BGEZ,
		&InterpreterEECore::BLTZL,
		&InterpreterEECore::BGEZL,
		&InterpreterEECore::TGEI,
		&InterpreterEECore::TGEIU,
		&InterpreterEECore::TLTI,
		&InterpreterEECore::TLTIU,
		&InterpreterEECore::TEQI,
		&InterpreterEECore::TNEI,
		&InterpreterEECore::BLTZAL,
		&InterpreterEECore::BGEZAL,
		&InterpreterEECore::BLTZALL,
		&InterpreterEECore::BGEZALL,
		&InterpreterEECore::MTSAB,
		&InterpreterEECore::MTSAH,
		&InterpreterEECore::MADD,
		&InterpreterEECore::MADDU,
		&InterpreterEECore::PLZCW,
		&InterpreterEECore::MFHI1,
		&InterpreterEECore::MTHI1,
		&InterpreterEECore::MFLO1,
		&InterpreterEECore::MTLO1,
		&InterpreterEECore::MULT1,
		&InterpreterEECore::MULTU1,
		&InterpreterEECore::DIV1,
		&InterpreterEECore::DIVU1,
		&InterpreterEECore::MADD1,
		&InterpreterEECore::MADDU1,
		&InterpreterEECore::PMFHL,
		&InterpreterEECore::PMTHL_LW, // &PMTHL,
		&InterpreterEECore::PSLLH,
		&InterpreterEECore::PSRLH,
		&InterpreterEECore::PSRAH,
		&InterpreterEECore::PSLLW,
		&InterpreterEECore::PSRLW,
		&InterpreterEECore::PSRAW,
		&InterpreterEECore::PADDW,
		&InterpreterEECore::PSUBW,
		&InterpreterEECore::PCGTW,
		&InterpreterEECore::PMAXW,
		&InterpreterEECore::PADDH,
		&InterpreterEECore::PSUBH,
		&InterpreterEECore::PCGTH,
		&InterpreterEECore::PMAXH,
		&InterpreterEECore::PADDB,
		&InterpreterEECore::PSUBB,
		&InterpreterEECore::PCGTB,
		&InterpreterEECore::PADDSW,
		&InterpreterEECore::PSUBSW,
		&InterpreterEECore::PEXTLW,
		&InterpreterEECore::PPACW,
		&InterpreterEECore::PADDSH,
		&InterpreterEECore::PSUBSH,
		&InterpreterEECore::PEXTLH,
		&InterpreterEECore::PPACH,
		&InterpreterEECore::PADDSB,
		&InterpreterEECore::PSUBSB,
		&InterpreterEECore::PEXTLB,
		&InterpreterEECore::PPACB,
		&InterpreterEECore::PEXT5,
		&InterpreterEECore::PPAC5,
		&InterpreterEECore::PABSW,
		&InterpreterEECore::PCEQW,
		&InterpreterEECore::PMINW,
		&InterpreterEECore::PADSBH,
		&InterpreterEECore::PABSH,
		&InterpreterEECore::PCEQH,
		&InterpreterEECore::PMINH,
		&InterpreterEECore::PCEQB,
		&InterpreterEECore::PADDUW,
		&InterpreterEECore::PSUBUW,
		&InterpreterEECore::PEXTUW,
		&InterpreterEECore::PADDUH,
		&InterpreterEECore::PSUBUH,
		&InterpreterEECore::PEXTUH,
		&InterpreterEECore::PADDUB,
		&InterpreterEECore::PSUBUB,
		&InterpreterEECore::PEXTUB,
		&InterpreterEECore::QFSRV,
		&InterpreterEECore::PMADDW,
		&InterpreterEECore::PSLLVW,
		&InterpreterEECore::PSRLVW,
		&InterpreterEECore::PMSUBW,
		&InterpreterEECore::PMFHI,
		&InterpreterEECore::PMFLO,
		&InterpreterEECore::PINTH,
		&InterpreterEECore::PMULTW,
		&InterpreterEECore::PDIVW,
		&InterpreterEECore::PCPYLD,
		&InterpreterEECore::PMADDH,
		&InterpreterEECore::PHMADH,
		&InterpreterEECore::PAND,
		&InterpreterEECore::PXOR,
		&InterpreterEECore::PMSUBH,
		&InterpreterEECore::PHMSBH,
		&InterpreterEECore::PEXEH,
		&InterpreterEECore::PREVH,
		&InterpreterEECore::PMULTH,
		&InterpreterEECore::PDIVBW,
		&InterpreterEECore::PEXEW,
		&InterpreterEECore::PROT3W,
		&InterpreterEECore::PMADDUW,
		&InterpreterEECore::PSRAVW,
		&InterpreterEECore::PMTHI,
		&InterpreterEECore::PMTLO,
		&InterpreterEECore::PINTEH,
		&InterpreterEECore::PMULTUW,
		&InterpreterEECore::PDIVUW,
		&InterpreterEECore::PCPYUD,
		&InterpreterEECore::POR,
		&InterpreterEECore::PNOR,
		&InterpreterEECore::PEXCH,
		&InterpreterEECore::PCPYH,
		&InterpreterEECore::PEXCW,
		&InterpreterEECore::MFC0, // &MF0,
		&InterpreterEECore::MTC0, // &MT0,
		&InterpreterEECore::BC0F,
		&InterpreterEECore::BC0T,
		&InterpreterEECore::BC0FL,
		&InterpreterEECore::BC0TL,
		&InterpreterEECore::TLBR,
		&InterpreterEECore::TLBWI,
		&InterpreterEECore::TLBWR,
		&InterpreterEECore::TLBP,
		&InterpreterEECore::ERET,
		&InterpreterEECore::EI,
		&InterpreterEECore::DI,
		&InterpreterEECore::MFC1,
		&InterpreterEECore::CFC1,
		&InterpreterEECore::MTC1,
		&InterpreterEECore::CTC1,
		&InterpreterEECore::BC1F,
		&InterpreterEECore::BC1T,
		&InterpreterEECore::BC1FL,
		&InterpreterEECore::BC1TL,
		&InterpreterEECore::ADD_S, // &ADD,
		&InterpreterEECore::SUB_S, // &SUB,
		&InterpreterEECore::MUL_S, // &MUL,
		&InterpreterEECore::DIV_S, // &DIV,
		&InterpreterEECore::SQRT_S, // &SQRT,
		&InterpreterEECore::ABS_S, // &ABS,
		&InterpreterEECore::MOV_S, // &MOV,
		&InterpreterEECore::NEG_S, // &NEG,
		&InterpreterEECore::RSQRT_S, // &RSQRT,
		&InterpreterEECore::ADDA_S, // &ADDA,
		&InterpreterEECore::SUBA_S, // &SUBA,
		&InterpreterEECore::MULA_S, // &MULA,
		&InterpreterEECore::MADD_S, // &MADD,
		&InterpreterEECore::MSUB_S, // &MSUB,
		&InterpreterEECore::MADDA_S, // &MADDA,
		&InterpreterEECore::MSUBA_S, // &MSUBA,
		&InterpreterEECore::CVT_W_S, // &CVTW,
		&InterpreterEECore::MAX_S, // &MAX,
		&InterpreterEECore::MIN_S, // &MIN,
		&InterpreterEECore::C_F_S, // &C_F,
		&InterpreterEECore::C_EQ_S, // &C_EQ,
		&InterpreterEECore::C_LT_S, // &C_LT,
		&InterpreterEECore::C_LE_S, // &C_LE,
		&InterpreterEECore::CVT_S_W // &CVTS,
	};
};

