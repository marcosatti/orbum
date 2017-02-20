#pragma once

#include <memory>

#include "Common/Tables/EECoreExceptionsTable/EECoreExceptionsTable.h"
#include "Common/Tables/EECoreInstructionTable/EECoreInstructionTable.h"

#include "VM/Types/VMSystem_s.h"

#include "Resources/EE/EECore/Types/EECoreInstruction_t.h"
#include "Resources/EE/EECore/Types/EECoreException_t.h"

using ExceptionProperties_t = EECoreExceptionsTable::ExceptionProperties_t;

class VM;
class VUInterpreter_s;
class EECore_t;
class VuUnit_VU0_t;
class PhysicalMMU_t;

/*
The EE Core interpreter. Implements the EE Core including the R5900, COP0, FPU (COP1), etc.

Needs a reference to the VU0 interpreter, which is called upon when any of the COP2 instructions starting with V* mnemonics are called.
This is done in order to avoid reimplementing the same function twice.

TODO: Finish documentation.
*/
class EECoreInterpreter_s : public VMSystem_s
{
public:
	explicit EECoreInterpreter_s(VM * vm, const std::shared_ptr<VUInterpreter_s> & vuInterpreter);
	virtual ~EECoreInterpreter_s();

	/*
	Initalisation.
	*/
	void initalise() override;

	/*
	This is the "main loop" function called by the base interpreter component, and sub-functions it calls.
	*/
	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:

	//////////////////////////
	// Common Functionality //
	//////////////////////////

	/*
	Resources.
	*/
	std::shared_ptr<EECore_t> mEECore;
	std::shared_ptr<PhysicalMMU_t> mPhysicalMMU;
	std::shared_ptr<VuUnit_VU0_t> mVU0;

#if defined(BUILD_DEBUG)
	// Debug loop counter.
	u64 DEBUG_LOOP_COUNTER = 0;
#endif

	///////////////////////////////
	// Instruction Functionality //
	///////////////////////////////

#if defined(BUILD_DEBUG)
	// SYNC instruction counter.
	u64 DEBUG_INSTRUCTION_SYNC = 0;
#endif

	/*
	Checks the COP0.Count register against the COP0.Compare register.
	If the Count value == Compare value, an interrupt is generated.
	*/
	void handleCountEventCheck() const;

	/*
	The is used as a temporary holder for the current instruction, while the operation to perform is being determined.
	It is also used while an instruction is being performed.
	*/
	EECoreInstruction_t mInstruction;
	const EECoreInstructionInfo_t * mInstructionInfo;

	/*
	The VU interpreter reference, used to call any COP2 instructions prefixed with V* as the mnemonic.
	*/
	std::shared_ptr<VUInterpreter_s> mVU0Interpreter;

	/*
	Helper functions to check:
	 - The usability conditions of COP0, 1, 2 (VU0).
	 - No over or underflow will occur for signed 32/64 bit integers.
	Returns a bool indicating if the instruction should return early because of unavailablity.
	Return early from instruction = true, proceed with instruction = false.
	They will automatically set the exception state as well.
	*/
	bool handleCOP0Usable();
	bool handleCOP1Usable();
	bool handleCOP2Usable();
	bool handleOverOrUnderflow32(const s32 & x, const s32 & y);
	bool handleOverOrUnderflow64(const s64 & x, const s64 & y);

	// EECore Instruction functions. The instructions are organised according to the EE Overview Manual starting from page 26 (which also means separate cpp files per category).
	// Note 1: there is no true pipeline concept in PCSX2 - instructions that are meant for pipeline 1 (marked with "1" at the end of the mnemonic) are treated like normal instructions.
	// Note 2: Dots in mnemonics & function names are represented by the underscore character.

	/*
	Unknown instruction function - does nothing when executed. Used for any instructions with implementation index 0 (ie: reserved, unknown or otherwise).
	On a debug build, can be used to debug an unknown opcode by logging a message.
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
	Conditional Branch and Jump Instructions. See EECoreInterpreter_COND_BRANCH_JUMP.cpp for implementations (22 instructions total).
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
	VU0 (attached as COP2) Macro Instructions. For reference, see VU Users Manual page 206 onwards. 
	In total there are 140 instructions, however, the instructions prefixed with V* are delegate functions to the VU0 system (see the VU system for implementation).
	The two exceptions to this is the VCALLMS/VCALLMSR instructions.
	For the EE Core, the first 12 instructions are implemented as pure COP2 instructions.
	*/
	// ------------- Raw COP2 Instructions -------------
	void QMFC2();
	void QMTC2();
	void LQC2();
	void SQC2();
	void CFC2();
	void CTC2();
	void BC2F();
	void BC2FL();
	void BC2T();
	void BC2TL();
	void VCALLMS();
	void VCALLMSR();
	// ------------- VU0 Delegate Instructions -------------
	void VABS();
	void VADD();
	void VADDi();
	void VADDq();
	void VADDbc_0();
	void VADDbc_1();
	void VADDbc_2();
	void VADDbc_3();
	void VADDA();
	void VADDAi();
	void VADDAq();
	void VADDAbc_0();
	void VADDAbc_1();
	void VADDAbc_2();
	void VADDAbc_3();
	void VSUB();
	void VSUBi();
	void VSUBq();
	void VSUBbc_0();
	void VSUBbc_1();
	void VSUBbc_2();
	void VSUBbc_3();
	void VSUBA();
	void VSUBAi();
	void VSUBAq();
	void VSUBAbc_0();
	void VSUBAbc_1();
	void VSUBAbc_2();
	void VSUBAbc_3();
	void VMUL();
	void VMULi();
	void VMULq();
	void VMULbc_0();
	void VMULbc_1();
	void VMULbc_2();
	void VMULbc_3();
	void VMULA();
	void VMULAi();
	void VMULAq();
	void VMULAbc_0();
	void VMULAbc_1();
	void VMULAbc_2();
	void VMULAbc_3();
	void VMADD();
	void VMADDi();
	void VMADDq();
	void VMADDbc_0();
	void VMADDbc_1();
	void VMADDbc_2();
	void VMADDbc_3();
	void VMADDA();
	void VMADDAi();
	void VMADDAq();
	void VMADDAbc_0();
	void VMADDAbc_1();
	void VMADDAbc_2();
	void VMADDAbc_3();
	void VMSUB();
	void VMSUBi();
	void VMSUBq();
	void VMSUBbc_0();
	void VMSUBbc_1();
	void VMSUBbc_2();
	void VMSUBbc_3();
	void VMSUBA();
	void VMSUBAi();
	void VMSUBAq();
	void VMSUBAbc_0();
	void VMSUBAbc_1();
	void VMSUBAbc_2();
	void VMSUBAbc_3();
	void VMAX();
	void VMAXi();
	void VMAXbc_0();
	void VMAXbc_1();
	void VMAXbc_2();
	void VMAXbc_3();
	void VMINI();
	void VMINIi();
	void VMINIbc_0();
	void VMINIbc_1();
	void VMINIbc_2();
	void VMINIbc_3();
	void VOPMULA();
	void VOPMSUB();
	void VNOP();
	void VFTOI0();
	void VFTOI4();
	void VFTOI12();
	void VFTOI15();
	void VITOF0();
	void VITOF4();
	void VITOF12();
	void VITOF15();
	void VCLIP();
	void VDIV();
	void VSQRT();
	void VRSQRT();
	void VIADD();
	void VIADDI();
	void VIAND();
	void VIOR();
	void VISUB();
	void VMOVE();
	void VMFIR();
	void VMTIR();
	void VMR32();
	void VLQD();
	void VLQI();
	void VSQD();
	void VSQI();
	void VILWR();
	void VISWR();
	void VRINIT();
	void VRGET();
	void VRNEXT();
	void VRXOR();
	void VWAITQ();

	/*
	Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index. 
	See EECoreInstructionTable and "EECore Instruction Implementation Register.xlsm" for more details.

	Sometimes there are differences in the instruction mnemonics within the manual. 
	Alternative names have been provided as comments against the array function used.
	*/
	void(EECoreInterpreter_s::* EECORE_INSTRUCTION_TABLE[Constants::EE::EECore::NUMBER_EECORE_INSTRUCTIONS])() =
	{
		&EECoreInterpreter_s::INSTRUCTION_UNKNOWN,
		&EECoreInterpreter_s::J,
		&EECoreInterpreter_s::JAL,
		&EECoreInterpreter_s::BEQ,
		&EECoreInterpreter_s::BNE,
		&EECoreInterpreter_s::BLEZ,
		&EECoreInterpreter_s::BGTZ,
		&EECoreInterpreter_s::ADDI,
		&EECoreInterpreter_s::ADDIU,
		&EECoreInterpreter_s::SLTI,
		&EECoreInterpreter_s::SLTIU,
		&EECoreInterpreter_s::ANDI,
		&EECoreInterpreter_s::ORI,
		&EECoreInterpreter_s::XORI,
		&EECoreInterpreter_s::LUI,
		&EECoreInterpreter_s::BEQL,
		&EECoreInterpreter_s::BNEL,
		&EECoreInterpreter_s::BLEZL,
		&EECoreInterpreter_s::BGTZL,
		&EECoreInterpreter_s::DADDI,
		&EECoreInterpreter_s::DADDIU,
		&EECoreInterpreter_s::LDL,
		&EECoreInterpreter_s::LDR,
		&EECoreInterpreter_s::LQ,
		&EECoreInterpreter_s::SQ,
		&EECoreInterpreter_s::LB,
		&EECoreInterpreter_s::LH,
		&EECoreInterpreter_s::LWL,
		&EECoreInterpreter_s::LW,
		&EECoreInterpreter_s::LBU,
		&EECoreInterpreter_s::LHU,
		&EECoreInterpreter_s::LWR,
		&EECoreInterpreter_s::LWU,
		&EECoreInterpreter_s::SB,
		&EECoreInterpreter_s::SH,
		&EECoreInterpreter_s::SWL,
		&EECoreInterpreter_s::SW,
		&EECoreInterpreter_s::SDL,
		&EECoreInterpreter_s::SDR,
		&EECoreInterpreter_s::SWR,
		&EECoreInterpreter_s::CACHE,
		&EECoreInterpreter_s::LWC1,
		&EECoreInterpreter_s::PREF,
		&EECoreInterpreter_s::LQC2,
		&EECoreInterpreter_s::LD,
		&EECoreInterpreter_s::SWC1,
		&EECoreInterpreter_s::LQC2,
		&EECoreInterpreter_s::SD,
		&EECoreInterpreter_s::SLL,
		&EECoreInterpreter_s::SRL,
		&EECoreInterpreter_s::SRA,
		&EECoreInterpreter_s::SLLV,
		&EECoreInterpreter_s::SRLV,
		&EECoreInterpreter_s::SRAV,
		&EECoreInterpreter_s::JR,
		&EECoreInterpreter_s::JALR,
		&EECoreInterpreter_s::MOVZ,
		&EECoreInterpreter_s::MOVN,
		&EECoreInterpreter_s::SYSCALL,
		&EECoreInterpreter_s::BREAK,
		&EECoreInterpreter_s::SYNC_STYPE,
		&EECoreInterpreter_s::MFHI,
		&EECoreInterpreter_s::MTHI,
		&EECoreInterpreter_s::MFLO,
		&EECoreInterpreter_s::MTLO,
		&EECoreInterpreter_s::DSLLV,
		&EECoreInterpreter_s::DSRLV,
		&EECoreInterpreter_s::DSRAV,
		&EECoreInterpreter_s::MULT,
		&EECoreInterpreter_s::MULTU,
		&EECoreInterpreter_s::DIV,
		&EECoreInterpreter_s::DIVU,
		&EECoreInterpreter_s::ADD,
		&EECoreInterpreter_s::ADDU,
		&EECoreInterpreter_s::SUB,
		&EECoreInterpreter_s::SUBU,
		&EECoreInterpreter_s::AND,
		&EECoreInterpreter_s::OR,
		&EECoreInterpreter_s::XOR,
		&EECoreInterpreter_s::NOR,
		&EECoreInterpreter_s::MFSA,
		&EECoreInterpreter_s::MTSA,
		&EECoreInterpreter_s::SLT,
		&EECoreInterpreter_s::SLTU,
		&EECoreInterpreter_s::DADD,
		&EECoreInterpreter_s::DADDU,
		&EECoreInterpreter_s::DSUB,
		&EECoreInterpreter_s::DSUBU,
		&EECoreInterpreter_s::TGE,
		&EECoreInterpreter_s::TGEU,
		&EECoreInterpreter_s::TLT,
		&EECoreInterpreter_s::TLTU,
		&EECoreInterpreter_s::TEQ,
		&EECoreInterpreter_s::TNE,
		&EECoreInterpreter_s::DSLL,
		&EECoreInterpreter_s::DSRL,
		&EECoreInterpreter_s::DSRA,
		&EECoreInterpreter_s::DSLL32,
		&EECoreInterpreter_s::DSRL32,
		&EECoreInterpreter_s::DSRA32,
		&EECoreInterpreter_s::BLTZ,
		&EECoreInterpreter_s::BGEZ,
		&EECoreInterpreter_s::BLTZL,
		&EECoreInterpreter_s::BGEZL,
		&EECoreInterpreter_s::TGEI,
		&EECoreInterpreter_s::TGEIU,
		&EECoreInterpreter_s::TLTI,
		&EECoreInterpreter_s::TLTIU,
		&EECoreInterpreter_s::TEQI,
		&EECoreInterpreter_s::TNEI,
		&EECoreInterpreter_s::BLTZAL,
		&EECoreInterpreter_s::BGEZAL,
		&EECoreInterpreter_s::BLTZALL,
		&EECoreInterpreter_s::BGEZALL,
		&EECoreInterpreter_s::MTSAB,
		&EECoreInterpreter_s::MTSAH,
		&EECoreInterpreter_s::MADD,
		&EECoreInterpreter_s::MADDU,
		&EECoreInterpreter_s::PLZCW,
		&EECoreInterpreter_s::MFHI1,
		&EECoreInterpreter_s::MTHI1,
		&EECoreInterpreter_s::MFLO1,
		&EECoreInterpreter_s::MTLO1,
		&EECoreInterpreter_s::MULT1,
		&EECoreInterpreter_s::MULTU1,
		&EECoreInterpreter_s::DIV1,
		&EECoreInterpreter_s::DIVU1,
		&EECoreInterpreter_s::MADD1,
		&EECoreInterpreter_s::MADDU1,
		&EECoreInterpreter_s::PMFHL,
		&EECoreInterpreter_s::PMTHL_LW, // &PMTHL,
		&EECoreInterpreter_s::PSLLH,
		&EECoreInterpreter_s::PSRLH,
		&EECoreInterpreter_s::PSRAH,
		&EECoreInterpreter_s::PSLLW,
		&EECoreInterpreter_s::PSRLW,
		&EECoreInterpreter_s::PSRAW,
		&EECoreInterpreter_s::PADDW,
		&EECoreInterpreter_s::PSUBW,
		&EECoreInterpreter_s::PCGTW,
		&EECoreInterpreter_s::PMAXW,
		&EECoreInterpreter_s::PADDH,
		&EECoreInterpreter_s::PSUBH,
		&EECoreInterpreter_s::PCGTH,
		&EECoreInterpreter_s::PMAXH,
		&EECoreInterpreter_s::PADDB,
		&EECoreInterpreter_s::PSUBB,
		&EECoreInterpreter_s::PCGTB,
		&EECoreInterpreter_s::PADDSW,
		&EECoreInterpreter_s::PSUBSW,
		&EECoreInterpreter_s::PEXTLW,
		&EECoreInterpreter_s::PPACW,
		&EECoreInterpreter_s::PADDSH,
		&EECoreInterpreter_s::PSUBSH,
		&EECoreInterpreter_s::PEXTLH,
		&EECoreInterpreter_s::PPACH,
		&EECoreInterpreter_s::PADDSB,
		&EECoreInterpreter_s::PSUBSB,
		&EECoreInterpreter_s::PEXTLB,
		&EECoreInterpreter_s::PPACB,
		&EECoreInterpreter_s::PEXT5,
		&EECoreInterpreter_s::PPAC5,
		&EECoreInterpreter_s::PABSW,
		&EECoreInterpreter_s::PCEQW,
		&EECoreInterpreter_s::PMINW,
		&EECoreInterpreter_s::PADSBH,
		&EECoreInterpreter_s::PABSH,
		&EECoreInterpreter_s::PCEQH,
		&EECoreInterpreter_s::PMINH,
		&EECoreInterpreter_s::PCEQB,
		&EECoreInterpreter_s::PADDUW,
		&EECoreInterpreter_s::PSUBUW,
		&EECoreInterpreter_s::PEXTUW,
		&EECoreInterpreter_s::PADDUH,
		&EECoreInterpreter_s::PSUBUH,
		&EECoreInterpreter_s::PEXTUH,
		&EECoreInterpreter_s::PADDUB,
		&EECoreInterpreter_s::PSUBUB,
		&EECoreInterpreter_s::PEXTUB,
		&EECoreInterpreter_s::QFSRV,
		&EECoreInterpreter_s::PMADDW,
		&EECoreInterpreter_s::PSLLVW,
		&EECoreInterpreter_s::PSRLVW,
		&EECoreInterpreter_s::PMSUBW,
		&EECoreInterpreter_s::PMFHI,
		&EECoreInterpreter_s::PMFLO,
		&EECoreInterpreter_s::PINTH,
		&EECoreInterpreter_s::PMULTW,
		&EECoreInterpreter_s::PDIVW,
		&EECoreInterpreter_s::PCPYLD,
		&EECoreInterpreter_s::PMADDH,
		&EECoreInterpreter_s::PHMADH,
		&EECoreInterpreter_s::PAND,
		&EECoreInterpreter_s::PXOR,
		&EECoreInterpreter_s::PMSUBH,
		&EECoreInterpreter_s::PHMSBH,
		&EECoreInterpreter_s::PEXEH,
		&EECoreInterpreter_s::PREVH,
		&EECoreInterpreter_s::PMULTH,
		&EECoreInterpreter_s::PDIVBW,
		&EECoreInterpreter_s::PEXEW,
		&EECoreInterpreter_s::PROT3W,
		&EECoreInterpreter_s::PMADDUW,
		&EECoreInterpreter_s::PSRAVW,
		&EECoreInterpreter_s::PMTHI,
		&EECoreInterpreter_s::PMTLO,
		&EECoreInterpreter_s::PINTEH,
		&EECoreInterpreter_s::PMULTUW,
		&EECoreInterpreter_s::PDIVUW,
		&EECoreInterpreter_s::PCPYUD,
		&EECoreInterpreter_s::POR,
		&EECoreInterpreter_s::PNOR,
		&EECoreInterpreter_s::PEXCH,
		&EECoreInterpreter_s::PCPYH,
		&EECoreInterpreter_s::PEXCW,
		&EECoreInterpreter_s::MFC0, // &MF0,
		&EECoreInterpreter_s::MTC0, // &MT0,
		&EECoreInterpreter_s::BC0F,
		&EECoreInterpreter_s::BC0T,
		&EECoreInterpreter_s::BC0FL,
		&EECoreInterpreter_s::BC0TL,
		&EECoreInterpreter_s::TLBR,
		&EECoreInterpreter_s::TLBWI,
		&EECoreInterpreter_s::TLBWR,
		&EECoreInterpreter_s::TLBP,
		&EECoreInterpreter_s::ERET,
		&EECoreInterpreter_s::EI,
		&EECoreInterpreter_s::DI,
		&EECoreInterpreter_s::MFC1,
		&EECoreInterpreter_s::CFC1,
		&EECoreInterpreter_s::MTC1,
		&EECoreInterpreter_s::CTC1,
		&EECoreInterpreter_s::BC1F,
		&EECoreInterpreter_s::BC1T,
		&EECoreInterpreter_s::BC1FL,
		&EECoreInterpreter_s::BC1TL,
		&EECoreInterpreter_s::ADD_S, // &ADD,
		&EECoreInterpreter_s::SUB_S, // &SUB,
		&EECoreInterpreter_s::MUL_S, // &MUL,
		&EECoreInterpreter_s::DIV_S, // &DIV,
		&EECoreInterpreter_s::SQRT_S, // &SQRT,
		&EECoreInterpreter_s::ABS_S, // &ABS,
		&EECoreInterpreter_s::MOV_S, // &MOV,
		&EECoreInterpreter_s::NEG_S, // &NEG,
		&EECoreInterpreter_s::RSQRT_S, // &RSQRT,
		&EECoreInterpreter_s::ADDA_S, // &ADDA,
		&EECoreInterpreter_s::SUBA_S, // &SUBA,
		&EECoreInterpreter_s::MULA_S, // &MULA,
		&EECoreInterpreter_s::MADD_S, // &MADD,
		&EECoreInterpreter_s::MSUB_S, // &MSUB,
		&EECoreInterpreter_s::MADDA_S, // &MADDA,
		&EECoreInterpreter_s::MSUBA_S, // &MSUBA,
		&EECoreInterpreter_s::CVT_W_S, // &CVTW,
		&EECoreInterpreter_s::MAX_S, // &MAX,
		&EECoreInterpreter_s::MIN_S, // &MIN,
		&EECoreInterpreter_s::C_F_S, // &C_F,
		&EECoreInterpreter_s::C_EQ_S, // &C_EQ,
		&EECoreInterpreter_s::C_LT_S, // &C_LT,
		&EECoreInterpreter_s::C_LE_S, // &C_LE,
		&EECoreInterpreter_s::CVT_S_W, // &CVTS,
		&EECoreInterpreter_s::QMFC2,
		&EECoreInterpreter_s::CFC2,
		&EECoreInterpreter_s::QMTC2,
		&EECoreInterpreter_s::CTC2,
		&EECoreInterpreter_s::BC2F,
		&EECoreInterpreter_s::BC2T,
		&EECoreInterpreter_s::BC2FL,
		&EECoreInterpreter_s::BC2TL,
		&EECoreInterpreter_s::VADDbc_0,
		&EECoreInterpreter_s::VADDbc_1,
		&EECoreInterpreter_s::VADDbc_2,
		&EECoreInterpreter_s::VADDbc_3,
		&EECoreInterpreter_s::VSUBbc_0,
		&EECoreInterpreter_s::VSUBbc_1,
		&EECoreInterpreter_s::VSUBbc_2,
		&EECoreInterpreter_s::VSUBbc_3,
		&EECoreInterpreter_s::VMADDbc_0,
		&EECoreInterpreter_s::VMADDbc_1,
		&EECoreInterpreter_s::VMADDbc_2,
		&EECoreInterpreter_s::VMADDbc_3,
		&EECoreInterpreter_s::VMSUBbc_0,
		&EECoreInterpreter_s::VMSUBbc_1,
		&EECoreInterpreter_s::VMSUBbc_2,
		&EECoreInterpreter_s::VMSUBbc_3,
		&EECoreInterpreter_s::VMAXbc_0,
		&EECoreInterpreter_s::VMAXbc_1,
		&EECoreInterpreter_s::VMAXbc_2,
		&EECoreInterpreter_s::VMAXbc_3,
		&EECoreInterpreter_s::VMINIbc_0,
		&EECoreInterpreter_s::VMINIbc_1,
		&EECoreInterpreter_s::VMINIbc_2,
		&EECoreInterpreter_s::VMINIbc_3,
		&EECoreInterpreter_s::VMULbc_0,
		&EECoreInterpreter_s::VMULbc_1,
		&EECoreInterpreter_s::VMULbc_2,
		&EECoreInterpreter_s::VMULbc_3,
		&EECoreInterpreter_s::VMULq,
		&EECoreInterpreter_s::VMAXi,
		&EECoreInterpreter_s::VMULi,
		&EECoreInterpreter_s::VMINIi,
		&EECoreInterpreter_s::VADDq,
		&EECoreInterpreter_s::VMADDq,
		&EECoreInterpreter_s::VADDi,
		&EECoreInterpreter_s::VMADDi,
		&EECoreInterpreter_s::VSUBq,
		&EECoreInterpreter_s::VMSUBq,
		&EECoreInterpreter_s::VSUBi,
		&EECoreInterpreter_s::VMSUBi,
		&EECoreInterpreter_s::VADD,
		&EECoreInterpreter_s::VMADD,
		&EECoreInterpreter_s::VMUL,
		&EECoreInterpreter_s::VMAX,
		&EECoreInterpreter_s::VSUB,
		&EECoreInterpreter_s::VMSUB,
		&EECoreInterpreter_s::VOPMSUB,
		&EECoreInterpreter_s::VMINI,
		&EECoreInterpreter_s::VIADD,
		&EECoreInterpreter_s::VISUB,
		&EECoreInterpreter_s::VIADDI,
		&EECoreInterpreter_s::VIAND,
		&EECoreInterpreter_s::VIOR,
		&EECoreInterpreter_s::VCALLMS,
		&EECoreInterpreter_s::VCALLMSR,
		&EECoreInterpreter_s::VADDAbc_0,
		&EECoreInterpreter_s::VSUBAbc_0,
		&EECoreInterpreter_s::VMADDAbc_0,
		&EECoreInterpreter_s::VMSUBAbc_0,
		&EECoreInterpreter_s::VITOF0,
		&EECoreInterpreter_s::VFTOI0,
		&EECoreInterpreter_s::VMULAbc_0,
		&EECoreInterpreter_s::VMULAq,
		&EECoreInterpreter_s::VADDAq,
		&EECoreInterpreter_s::VSUBAq,
		&EECoreInterpreter_s::VADDA,
		&EECoreInterpreter_s::VSUBA,
		&EECoreInterpreter_s::VMOVE,
		&EECoreInterpreter_s::VLQI,
		&EECoreInterpreter_s::VDIV,
		&EECoreInterpreter_s::VMTIR,
		&EECoreInterpreter_s::VRNEXT,
		&EECoreInterpreter_s::VADDAbc_1,
		&EECoreInterpreter_s::VSUBAbc_1,
		&EECoreInterpreter_s::VMADDAbc_1,
		&EECoreInterpreter_s::VMSUBAbc_1,
		&EECoreInterpreter_s::VITOF4,
		&EECoreInterpreter_s::VFTOI4,
		&EECoreInterpreter_s::VMULAbc_1,
		&EECoreInterpreter_s::VABS,
		&EECoreInterpreter_s::VMADDAq,
		&EECoreInterpreter_s::VMSUBAq,
		&EECoreInterpreter_s::VMADDA,
		&EECoreInterpreter_s::VMSUBA,
		&EECoreInterpreter_s::VMR32,
		&EECoreInterpreter_s::VSQI,
		&EECoreInterpreter_s::VSQRT,
		&EECoreInterpreter_s::VMFIR,
		&EECoreInterpreter_s::VRGET,
		&EECoreInterpreter_s::VADDAbc_2,
		&EECoreInterpreter_s::VSUBAbc_2,
		&EECoreInterpreter_s::VMADDAbc_2,
		&EECoreInterpreter_s::VMSUBAbc_2,
		&EECoreInterpreter_s::VITOF12,
		&EECoreInterpreter_s::VFTOI12,
		&EECoreInterpreter_s::VMULAbc_2,
		&EECoreInterpreter_s::VMULAi,
		&EECoreInterpreter_s::VADDAi,
		&EECoreInterpreter_s::VSUBAi,
		&EECoreInterpreter_s::VMULA,
		&EECoreInterpreter_s::VOPMULA,
		&EECoreInterpreter_s::VLQD,
		&EECoreInterpreter_s::VRSQRT,
		&EECoreInterpreter_s::VILWR,
		&EECoreInterpreter_s::VRINIT,
		&EECoreInterpreter_s::VADDAbc_3,
		&EECoreInterpreter_s::VSUBAbc_3,
		&EECoreInterpreter_s::VMADDAbc_3,
		&EECoreInterpreter_s::VMSUBAbc_3,
		&EECoreInterpreter_s::VITOF15,
		&EECoreInterpreter_s::VFTOI15,
		&EECoreInterpreter_s::VMULAbc_3,
		&EECoreInterpreter_s::VCLIP,
		&EECoreInterpreter_s::VMADDAi,
		&EECoreInterpreter_s::VMSUBAi,
		&EECoreInterpreter_s::VNOP,
		&EECoreInterpreter_s::VSQD,
		&EECoreInterpreter_s::VWAITQ,
		&EECoreInterpreter_s::VISWR,
		&EECoreInterpreter_s::VRXOR
	};

	/////////////////////////////
	// Exception Functionality //
	/////////////////////////////

	/*
	Handles a given exception by running the general exception handler (level 1 or 2) based on the exception properties defined.
	*/
	void handleException(const EECoreException_t & exception);

	/*
	Checks if any of the interrupt lines have an IRQ pending, and raises an interrupt exception.
	*/
	void handleInterruptCheck();

#if defined(BUILD_DEBUG)
	// Debug for counting the number of exceptions handled.
	u64 DEBUG_HANDLED_EXCEPTION_COUNT = 0;
#endif

	/*
	Temp state variables.
	*/
	EECoreException_t mException;
	const ExceptionProperties_t * mExceptionProperties;

	/*
	The level 1 or level 2 exception handler, which is called by the base handleException() function.
	They have been adapted from the code in the EE Core Users Manual page 91 & 92.
	*/
	void handleException_L1() const;
	void handleException_L2() const;

	///////////////////////
	// MMU Functionality //
	///////////////////////

	/*
	Internal types used within/to access MMU.
	*/
	enum MMUError_t { ADDRESS, TLB_REFILL, TLB_INVALID, TLB_MODIFIED };
	enum MMUAccess_t { READ, WRITE };

	/*
	Converts a given MMUError_t and MMUAccess_t to an EECoreException_t and handles it (through handleException()).
	Also sets the required COP0 TLB information.
	Called internally from getPhysicalAddress().
	*/
	void handleMMUError(const u32 & virtualAddress, const MMUAccess_t & access, const MMUError_t & error, const s32 & tlbEntryIndex);

	/*
	Performs a lookup from the given virtual address and access type.
	Returns if an error occured, indicating if the instruction that called should return early (error = true, no error = false).
	The physical address calculated is stored in physicalAddress.
	
	There are 4 associated stages (see diagram on EE Core Users Manual page 122):
	Stage 1 tests the operating context of the CPU and checks if the address is invalid.
	Stage 2 performs a TLB lookup and checks the ASID and G bits.
	Stage 3 tests the valid and dirty flags, and determines if the VPN is for the even or odd PFN.
	Stage 4 calculates the final physical address.
	*/
	bool getPhysicalAddress(const u32 & virtualAddress, const MMUAccess_t & access, u32 & physicalAddress);
};