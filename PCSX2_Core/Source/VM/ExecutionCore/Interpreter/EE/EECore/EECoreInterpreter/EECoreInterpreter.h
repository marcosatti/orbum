#pragma once

#include <memory>

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/PS2Resources/Types/MIPSInstruction/MIPSInstruction_t.h"
#include "Common/Tables/EECoreInstructionTable/EECoreInstructionTable.h"
#include "Common/PS2Constants/PS2Constants.h"

class PS2Resources_t;
class VMMain;
class EECoreMMUHandler;
class EECoreExceptionHandler;
struct MIPSInstructionInfo_t;

/*
The EE Core interpreter.

This also acts as the control for synchronisation across components, as this is the fastest clocked device in the PS2 (294 MHz).
Each time executionStep() is run, PS2Resources->Clock->updateClocks() is also run, which updates other clock sources such as the BUSCLK.

TODO: Finish documentation.
*/

class EECoreInterpreter : public VMExecutionCoreComponent
{
public:
	explicit EECoreInterpreter(VMMain * vmMain);
	~EECoreInterpreter();

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
	u32 executeInstruction();

	/*
	Checks the COP0.Count register against the COP0.Compare register.
	If the Count value >= Compare value, an exception is generated.
	*/
	void checkCountTimerEvent() const;

	// Component state functions
	const std::unique_ptr<EECoreExceptionHandler> & getExceptionHandler() const;
	const std::unique_ptr<EECoreMMUHandler> & getMMUHandler() const;
	MIPSInstruction_t & getInstruction();

private:

	// Component state functions

#if defined(BUILD_DEBUG)
	// Debug loop counter 
	u64 DEBUG_LOOP_COUNTER = 0;
	// SYNC counter
	u64 DEBUG_INSTRUCTION_SYNC = 0;
#endif

	/*
	The EECore exception handler.
	*/
	const std::unique_ptr<EECoreExceptionHandler> mExceptionHandler;

	/*
	The EECore MMU handler. Translates PS2 virutal addresses into PS2 physical addresses, using a TLB.
	*/
	const std::unique_ptr<EECoreMMUHandler> mMMUHandler;

	/*
	The is used as a temporary holder for the current instruction, while the operation to perform is being determined.
	It is also used while an instruction is being performed.
	*/
	MIPSInstruction_t mInstruction;
	const MIPSInstructionInfo_t * mInstructionInfo;

	// EECore Instruction functions. The instructions are organised according to the EE Overview Manual starting from page 26 (which also means separate cpp files per category).
	// Note 1: there is no pipeline concept in PCSX2 - instructions that are meant for pipeline 1 (marked with "1" at the end of the mnemonic) are treated like normal instructions.
	// Note 2: Dots in mnemonics & function names are represented by the underscore character.

	/*
	Unknown instruction function - does nothing when executed. Used for any instructions with implementation index 0 (ie: reserved, unknown or otherwise).
	If the BUILD_DEBUG macro is enabled, can be used to debug an unknown opcode by logging a message.
	*/
	void INSTRUCTION_UNKNOWN();

	/*
	Integer Add/Sub Instructions. See EECoreInterpreter_INTEGER_ADD_SUB.cpp for implementations (31 instructions total).
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
	Integer Mult/Div Instructions. See EECoreInterpreter_INTEGER_MULT_DIV.cpp for implementations (14 instructions total).
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
	Integer Mult-Add Instructions. See EECoreInterpreter_INTEGER_MULT_ADD.cpp for implementations (11 instructions total).
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
	Floating-Point Instructions. See EECoreInterpreter_FLOAT.cpp for implementations (10 instructions total).
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
	Shift Instructions. See EECoreInterpreter_SHIFT.cpp for implementations (25 instructions total).
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
	Logical Instructions. See EECoreInterpreter_LOGICAL.cpp for implementations (11 instructions total).
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
	Compare Instructions. See EECoreInterpreter_COMPARE.cpp for implementations (14 instructions total).
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
	Min/Max Instructions. See EECoreInterpreter_MIN_MAX.cpp for implementations (6 instructions total).
	*/
	void PMAXH();
	void PMAXW();
	void PMINH();
	void PMINW();
	void MAX_S();
	void MIN_S();

	/*
	Data Format Conversion (DFC) Instructions. See EECoreInterpreter_DFC.cpp for implementations (4 instructions total).
	*/
	void PEXT5();
	void PPAC5();
	void CVT_S_W();
	void CVT_W_S();

	/*
	Reordering Instructions. See EECoreInterpreter_REORDERING.cpp for implementations (20 instructions total).
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
	Others (ALU) Instructions. See EECoreInterpreter_ALU_OTHERS.cpp for implementations (7 instructions total).
	*/
	void PABSH();
	void PABSW();
	void PLZCW();
	void ABS_S();
	void NEG_S();
	void RSQRT_S();
	void SQRT_S();

	/*
	Register-Register Transfer Instructions. See EECoreInterpreter_REG_TRANSFER.cpp for implementations (23 instructions total).
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
	Load from Memory Instructions. See EECoreInterpreter_LOAD_MEM.cpp for implementations (14 instructions total).
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
	Store to Memory Instructions. See EECoreInterpreter_STORE_MEM.cpp for implementations (10 instructions total).
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
	Special Data Transfer Instructions. See EECoreInterpreter_SPECIAL_TRANSFER.cpp for implementations (26 instructions total).
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
	Conditional Branch and Jump Instructions. See EECoreInterpreter_COND_BRANCH_JUMP.cpp for implementations (26 instructions total).
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
	Subroutine Call Instructions. See EECoreInterpreter_CALL.cpp for implementations (6 instructions total).
	*/
	void BGEZAL();
	void BGEZALL();
	void BLTZAL();
	void BLTZALL();
	void JAL();
	void JALR();

	/*
	Break and Trap Instructions. See EECoreInterpreter_BREAK_TRAP.cpp for implementations (15 instructions total).
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
	Others Instructions. See EECoreInterpreter_OTHERS.cpp for implementations (9 instructions total). Includes the TLB instructions as they are missing in the overview manual...
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
	See EECoreInstructionTable and "EECore Instruction Implementation Register.xlsm" for more details.

	Sometimes there are differences in the instruction mnemonics within the manual. 
	Alternative names have been provided as comments against the array function used.
	*/
	// TODO: surely there is an easier way.. reasearch how to initalise static arrays outside of the header file. I'm sure I'm missing something completely obvious here..
	void(EECoreInterpreter::*const EECORE_INSTRUCTION_TABLE[PS2Constants::EE::EECore::NUMBER_EECORE_INSTRUCTIONS])() =
	{
		&EECoreInterpreter::INSTRUCTION_UNKNOWN,
		&EECoreInterpreter::J,
		&EECoreInterpreter::JAL,
		&EECoreInterpreter::BEQ,
		&EECoreInterpreter::BNE,
		&EECoreInterpreter::BLEZ,
		&EECoreInterpreter::BGTZ,
		&EECoreInterpreter::ADDI,
		&EECoreInterpreter::ADDIU,
		&EECoreInterpreter::SLTI,
		&EECoreInterpreter::SLTIU,
		&EECoreInterpreter::ANDI,
		&EECoreInterpreter::ORI,
		&EECoreInterpreter::XORI,
		&EECoreInterpreter::LUI,
		&EECoreInterpreter::BEQL,
		&EECoreInterpreter::BNEL,
		&EECoreInterpreter::BLEZL,
		&EECoreInterpreter::BGTZL,
		&EECoreInterpreter::DADDI,
		&EECoreInterpreter::DADDIU,
		&EECoreInterpreter::LDL,
		&EECoreInterpreter::LDR,
		&EECoreInterpreter::LQ,
		&EECoreInterpreter::SQ,
		&EECoreInterpreter::LB,
		&EECoreInterpreter::LH,
		&EECoreInterpreter::LWL,
		&EECoreInterpreter::LW,
		&EECoreInterpreter::LBU,
		&EECoreInterpreter::LHU,
		&EECoreInterpreter::LWR,
		&EECoreInterpreter::LWU,
		&EECoreInterpreter::SB,
		&EECoreInterpreter::SH,
		&EECoreInterpreter::SWL,
		&EECoreInterpreter::SW,
		&EECoreInterpreter::SDL,
		&EECoreInterpreter::SDR,
		&EECoreInterpreter::SWR,
		&EECoreInterpreter::CACHE,
		&EECoreInterpreter::LWC1,
		&EECoreInterpreter::PREF,
		&EECoreInterpreter::INSTRUCTION_UNKNOWN, // &LQC2,
		&EECoreInterpreter::LD,
		&EECoreInterpreter::SWC1,
		&EECoreInterpreter::INSTRUCTION_UNKNOWN, // &SQC2,
		&EECoreInterpreter::SD,
		&EECoreInterpreter::SLL,
		&EECoreInterpreter::SRL,
		&EECoreInterpreter::SRA,
		&EECoreInterpreter::SLLV,
		&EECoreInterpreter::SRLV,
		&EECoreInterpreter::SRAV,
		&EECoreInterpreter::JR,
		&EECoreInterpreter::JALR,
		&EECoreInterpreter::MOVZ,
		&EECoreInterpreter::MOVN,
		&EECoreInterpreter::SYSCALL,
		&EECoreInterpreter::BREAK,
		&EECoreInterpreter::SYNC_STYPE,
		&EECoreInterpreter::MFHI,
		&EECoreInterpreter::MTHI,
		&EECoreInterpreter::MFLO,
		&EECoreInterpreter::MTLO,
		&EECoreInterpreter::DSLLV,
		&EECoreInterpreter::DSRLV,
		&EECoreInterpreter::DSRAV,
		&EECoreInterpreter::MULT,
		&EECoreInterpreter::MULTU,
		&EECoreInterpreter::DIV,
		&EECoreInterpreter::DIVU,
		&EECoreInterpreter::ADD,
		&EECoreInterpreter::ADDU,
		&EECoreInterpreter::SUB,
		&EECoreInterpreter::SUBU,
		&EECoreInterpreter::AND,
		&EECoreInterpreter::OR,
		&EECoreInterpreter::XOR,
		&EECoreInterpreter::NOR,
		&EECoreInterpreter::MFSA,
		&EECoreInterpreter::MTSA,
		&EECoreInterpreter::SLT,
		&EECoreInterpreter::SLTU,
		&EECoreInterpreter::DADD,
		&EECoreInterpreter::DADDU,
		&EECoreInterpreter::DSUB,
		&EECoreInterpreter::DSUBU,
		&EECoreInterpreter::TGE,
		&EECoreInterpreter::TGEU,
		&EECoreInterpreter::TLT,
		&EECoreInterpreter::TLTU,
		&EECoreInterpreter::TEQ,
		&EECoreInterpreter::TNE,
		&EECoreInterpreter::DSLL,
		&EECoreInterpreter::DSRL,
		&EECoreInterpreter::DSRA,
		&EECoreInterpreter::DSLL32,
		&EECoreInterpreter::DSRL32,
		&EECoreInterpreter::DSRA32,
		&EECoreInterpreter::BLTZ,
		&EECoreInterpreter::BGEZ,
		&EECoreInterpreter::BLTZL,
		&EECoreInterpreter::BGEZL,
		&EECoreInterpreter::TGEI,
		&EECoreInterpreter::TGEIU,
		&EECoreInterpreter::TLTI,
		&EECoreInterpreter::TLTIU,
		&EECoreInterpreter::TEQI,
		&EECoreInterpreter::TNEI,
		&EECoreInterpreter::BLTZAL,
		&EECoreInterpreter::BGEZAL,
		&EECoreInterpreter::BLTZALL,
		&EECoreInterpreter::BGEZALL,
		&EECoreInterpreter::MTSAB,
		&EECoreInterpreter::MTSAH,
		&EECoreInterpreter::MADD,
		&EECoreInterpreter::MADDU,
		&EECoreInterpreter::PLZCW,
		&EECoreInterpreter::MFHI1,
		&EECoreInterpreter::MTHI1,
		&EECoreInterpreter::MFLO1,
		&EECoreInterpreter::MTLO1,
		&EECoreInterpreter::MULT1,
		&EECoreInterpreter::MULTU1,
		&EECoreInterpreter::DIV1,
		&EECoreInterpreter::DIVU1,
		&EECoreInterpreter::MADD1,
		&EECoreInterpreter::MADDU1,
		&EECoreInterpreter::PMFHL,
		&EECoreInterpreter::PMTHL_LW, // &PMTHL,
		&EECoreInterpreter::PSLLH,
		&EECoreInterpreter::PSRLH,
		&EECoreInterpreter::PSRAH,
		&EECoreInterpreter::PSLLW,
		&EECoreInterpreter::PSRLW,
		&EECoreInterpreter::PSRAW,
		&EECoreInterpreter::PADDW,
		&EECoreInterpreter::PSUBW,
		&EECoreInterpreter::PCGTW,
		&EECoreInterpreter::PMAXW,
		&EECoreInterpreter::PADDH,
		&EECoreInterpreter::PSUBH,
		&EECoreInterpreter::PCGTH,
		&EECoreInterpreter::PMAXH,
		&EECoreInterpreter::PADDB,
		&EECoreInterpreter::PSUBB,
		&EECoreInterpreter::PCGTB,
		&EECoreInterpreter::PADDSW,
		&EECoreInterpreter::PSUBSW,
		&EECoreInterpreter::PEXTLW,
		&EECoreInterpreter::PPACW,
		&EECoreInterpreter::PADDSH,
		&EECoreInterpreter::PSUBSH,
		&EECoreInterpreter::PEXTLH,
		&EECoreInterpreter::PPACH,
		&EECoreInterpreter::PADDSB,
		&EECoreInterpreter::PSUBSB,
		&EECoreInterpreter::PEXTLB,
		&EECoreInterpreter::PPACB,
		&EECoreInterpreter::PEXT5,
		&EECoreInterpreter::PPAC5,
		&EECoreInterpreter::PABSW,
		&EECoreInterpreter::PCEQW,
		&EECoreInterpreter::PMINW,
		&EECoreInterpreter::PADSBH,
		&EECoreInterpreter::PABSH,
		&EECoreInterpreter::PCEQH,
		&EECoreInterpreter::PMINH,
		&EECoreInterpreter::PCEQB,
		&EECoreInterpreter::PADDUW,
		&EECoreInterpreter::PSUBUW,
		&EECoreInterpreter::PEXTUW,
		&EECoreInterpreter::PADDUH,
		&EECoreInterpreter::PSUBUH,
		&EECoreInterpreter::PEXTUH,
		&EECoreInterpreter::PADDUB,
		&EECoreInterpreter::PSUBUB,
		&EECoreInterpreter::PEXTUB,
		&EECoreInterpreter::QFSRV,
		&EECoreInterpreter::PMADDW,
		&EECoreInterpreter::PSLLVW,
		&EECoreInterpreter::PSRLVW,
		&EECoreInterpreter::PMSUBW,
		&EECoreInterpreter::PMFHI,
		&EECoreInterpreter::PMFLO,
		&EECoreInterpreter::PINTH,
		&EECoreInterpreter::PMULTW,
		&EECoreInterpreter::PDIVW,
		&EECoreInterpreter::PCPYLD,
		&EECoreInterpreter::PMADDH,
		&EECoreInterpreter::PHMADH,
		&EECoreInterpreter::PAND,
		&EECoreInterpreter::PXOR,
		&EECoreInterpreter::PMSUBH,
		&EECoreInterpreter::PHMSBH,
		&EECoreInterpreter::PEXEH,
		&EECoreInterpreter::PREVH,
		&EECoreInterpreter::PMULTH,
		&EECoreInterpreter::PDIVBW,
		&EECoreInterpreter::PEXEW,
		&EECoreInterpreter::PROT3W,
		&EECoreInterpreter::PMADDUW,
		&EECoreInterpreter::PSRAVW,
		&EECoreInterpreter::PMTHI,
		&EECoreInterpreter::PMTLO,
		&EECoreInterpreter::PINTEH,
		&EECoreInterpreter::PMULTUW,
		&EECoreInterpreter::PDIVUW,
		&EECoreInterpreter::PCPYUD,
		&EECoreInterpreter::POR,
		&EECoreInterpreter::PNOR,
		&EECoreInterpreter::PEXCH,
		&EECoreInterpreter::PCPYH,
		&EECoreInterpreter::PEXCW,
		&EECoreInterpreter::MFC0, // &MF0,
		&EECoreInterpreter::MTC0, // &MT0,
		&EECoreInterpreter::BC0F,
		&EECoreInterpreter::BC0T,
		&EECoreInterpreter::BC0FL,
		&EECoreInterpreter::BC0TL,
		&EECoreInterpreter::TLBR,
		&EECoreInterpreter::TLBWI,
		&EECoreInterpreter::TLBWR,
		&EECoreInterpreter::TLBP,
		&EECoreInterpreter::ERET,
		&EECoreInterpreter::EI,
		&EECoreInterpreter::DI,
		&EECoreInterpreter::MFC1,
		&EECoreInterpreter::CFC1,
		&EECoreInterpreter::MTC1,
		&EECoreInterpreter::CTC1,
		&EECoreInterpreter::BC1F,
		&EECoreInterpreter::BC1T,
		&EECoreInterpreter::BC1FL,
		&EECoreInterpreter::BC1TL,
		&EECoreInterpreter::ADD_S, // &ADD,
		&EECoreInterpreter::SUB_S, // &SUB,
		&EECoreInterpreter::MUL_S, // &MUL,
		&EECoreInterpreter::DIV_S, // &DIV,
		&EECoreInterpreter::SQRT_S, // &SQRT,
		&EECoreInterpreter::ABS_S, // &ABS,
		&EECoreInterpreter::MOV_S, // &MOV,
		&EECoreInterpreter::NEG_S, // &NEG,
		&EECoreInterpreter::RSQRT_S, // &RSQRT,
		&EECoreInterpreter::ADDA_S, // &ADDA,
		&EECoreInterpreter::SUBA_S, // &SUBA,
		&EECoreInterpreter::MULA_S, // &MULA,
		&EECoreInterpreter::MADD_S, // &MADD,
		&EECoreInterpreter::MSUB_S, // &MSUB,
		&EECoreInterpreter::MADDA_S, // &MADDA,
		&EECoreInterpreter::MSUBA_S, // &MSUBA,
		&EECoreInterpreter::CVT_W_S, // &CVTW,
		&EECoreInterpreter::MAX_S, // &MAX,
		&EECoreInterpreter::MIN_S, // &MIN,
		&EECoreInterpreter::C_F_S, // &C_F,
		&EECoreInterpreter::C_EQ_S, // &C_EQ,
		&EECoreInterpreter::C_LT_S, // &C_LT,
		&EECoreInterpreter::C_LE_S, // &C_LE,
		&EECoreInterpreter::CVT_S_W // &CVTS,
	};
};

