#pragma once

#include "Common/Constants.hpp"

#include "Controller/Ee/Core/CEeCore.hpp" 
#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"

#include "Resources/Ee/Core/EeCoreInstruction.hpp"

class Core;

/// The EE Core interpreter. Implements the EE Core including the R5900, COP0, FPU (COP1), etc.
/// Needs a reference to the VU0 interpreter, which is called upon when any of the COP2 instructions starting with V* mnemonics are called.
/// This is done in order to avoid reimplementing the same function twice.
/// TODO: Finish documentation.
class CEeCoreInterpreter : public CEeCore
{
public:
	CEeCoreInterpreter(Core * core);

	/// Steps through the EE Core state, executing instructions.
	int time_step(const int ticks_available) override;

	/// The VU interpreter, used to call any COP2 instructions prefixed with V* as the mnemonic.
	/// TODO: Will change in future when VU's are implemented.
	CVuInterpreter c_vu_interpreter;

	/// EECore Instruction functions. The instructions are organised according to the EE Overview Manual starting from page 26 (which also means separate cpp files per category).
	/// Note 1: there is no true pipeline concept in PCSX2 - instructions that are meant for pipeline 1 (marked with "1" at the end of the mnemonic) are treated like normal instructions.
	/// Note 2: Dots in mnemonics & function names are represented by the underscore character.

	/// Unknown instruction...
	void INSTRUCTION_UNKNOWN(const EeCoreInstruction inst);

	/// Integer Add/Sub Instructions. See EECoreInterpreter_INTEGER_ADD_SUB.cpp for implementations (31 instructions total).
	void ADD(const EeCoreInstruction inst);
	void ADDI(const EeCoreInstruction inst);
	void ADDIU(const EeCoreInstruction inst);
	void ADDU(const EeCoreInstruction inst);
	void DADD(const EeCoreInstruction inst);
	void DADDI(const EeCoreInstruction inst);
	void DADDIU(const EeCoreInstruction inst);
	void DADDU(const EeCoreInstruction inst);
	void DSUB(const EeCoreInstruction inst);
	void DSUBU(const EeCoreInstruction inst);
	void SUB(const EeCoreInstruction inst);
	void SUBU(const EeCoreInstruction inst);
	void PADDB(const EeCoreInstruction inst);
	void PADDH(const EeCoreInstruction inst);
	void PADDSB(const EeCoreInstruction inst);
	void PADDSH(const EeCoreInstruction inst);
	void PADDSW(const EeCoreInstruction inst);
	void PADDUB(const EeCoreInstruction inst);
	void PADDUH(const EeCoreInstruction inst);
	void PADDUW(const EeCoreInstruction inst);
	void PADDW(const EeCoreInstruction inst);
	void PADSBH(const EeCoreInstruction inst);
	void PSUBB(const EeCoreInstruction inst);
	void PSUBH(const EeCoreInstruction inst);
	void PSUBSB(const EeCoreInstruction inst);
	void PSUBSH(const EeCoreInstruction inst);
	void PSUBSW(const EeCoreInstruction inst);
	void PSUBUB(const EeCoreInstruction inst);
	void PSUBUH(const EeCoreInstruction inst);
	void PSUBUW(const EeCoreInstruction inst);
	void PSUBW(const EeCoreInstruction inst);

	/// Integer Mult/Div Instructions. See EECoreInterpreter_INTEGER_MULT_DIV.cpp for implementations (14 instructions total).
	void DIV(const EeCoreInstruction inst);
	void DIV1(const EeCoreInstruction inst);
	void DIVU(const EeCoreInstruction inst);
	void DIVU1(const EeCoreInstruction inst);
	void MULT(const EeCoreInstruction inst);
	void MULT1(const EeCoreInstruction inst);
	void MULTU(const EeCoreInstruction inst);
	void MULTU1(const EeCoreInstruction inst);
	void PDIVBW(const EeCoreInstruction inst);
	void PDIVUW(const EeCoreInstruction inst);
	void PDIVW(const EeCoreInstruction inst);
	void PMULTH(const EeCoreInstruction inst);
	void PMULTUW(const EeCoreInstruction inst);
	void PMULTW(const EeCoreInstruction inst);

	/// Integer Mult-Add Instructions. See EECoreInterpreter_INTEGER_MULT_ADD.cpp for implementations (11 instructions total).
	void MADD(const EeCoreInstruction inst);
	void MADD1(const EeCoreInstruction inst);
	void MADDU(const EeCoreInstruction inst);
	void MADDU1(const EeCoreInstruction inst);
	void PHMADH(const EeCoreInstruction inst);
	void PHMSBH(const EeCoreInstruction inst);
	void PMADDH(const EeCoreInstruction inst);
	void PMADDUW(const EeCoreInstruction inst);
	void PMADDW(const EeCoreInstruction inst);
	void PMSUBH(const EeCoreInstruction inst);
	void PMSUBW(const EeCoreInstruction inst);

	/// Floating-Point Instructions. See EECoreInterpreter_FLOAT.cpp for implementations (10 instructions total).
	void ADD_S(const EeCoreInstruction inst);
	void ADDA_S(const EeCoreInstruction inst);
	void MADD_S(const EeCoreInstruction inst);
	void MADDA_S(const EeCoreInstruction inst);
	void MUL_S(const EeCoreInstruction inst);
	void MULA_S(const EeCoreInstruction inst);
	void DIV_S(const EeCoreInstruction inst);
	void MSUB_S(const EeCoreInstruction inst);
	void MSUBA_S(const EeCoreInstruction inst);
	void SUB_S(const EeCoreInstruction inst);
	void SUBA_S(const EeCoreInstruction inst);

	/// Shift Instructions. See EECoreInterpreter_SHIFT.cpp for implementations (25 instructions total).
	void DSRA(const EeCoreInstruction inst);
	void DSLL(const EeCoreInstruction inst);
	void DSLL32(const EeCoreInstruction inst);
	void DSLLV(const EeCoreInstruction inst);
	void DSRA32(const EeCoreInstruction inst);
	void DSRAV(const EeCoreInstruction inst);
	void DSRL(const EeCoreInstruction inst);
	void DSRL32(const EeCoreInstruction inst);
	void DSRLV(const EeCoreInstruction inst);
	void SLL(const EeCoreInstruction inst);
	void SLLV(const EeCoreInstruction inst);
	void SRA(const EeCoreInstruction inst);
	void SRAV(const EeCoreInstruction inst);
	void SRL(const EeCoreInstruction inst);
	void SRLV(const EeCoreInstruction inst);
	void PSLLH(const EeCoreInstruction inst);
	void PSLLVW(const EeCoreInstruction inst);
	void PSLLW(const EeCoreInstruction inst);
	void PSRAH(const EeCoreInstruction inst);
	void PSRAVW(const EeCoreInstruction inst);
	void PSRAW(const EeCoreInstruction inst);
	void PSRLH(const EeCoreInstruction inst);
	void PSRLVW(const EeCoreInstruction inst);
	void PSRLW(const EeCoreInstruction inst);
	void QFSRV(const EeCoreInstruction inst);

	/// Logical Instructions. See EECoreInterpreter_LOGICAL.cpp for implementations (11 instructions total).
	void AND(const EeCoreInstruction inst);
	void ANDI(const EeCoreInstruction inst);
	void NOR(const EeCoreInstruction inst);
	void OR(const EeCoreInstruction inst);
	void ORI(const EeCoreInstruction inst);
	void XOR(const EeCoreInstruction inst);
	void XORI(const EeCoreInstruction inst);
	void PAND(const EeCoreInstruction inst);
	void PNOR(const EeCoreInstruction inst);
	void POR(const EeCoreInstruction inst);
	void PXOR(const EeCoreInstruction inst);

	/// Compare Instructions. See EECoreInterpreter_COMPARE.cpp for implementations (14 instructions total).
	void SLT(const EeCoreInstruction inst); // For some reason this is missing in the EE Overview Manual (v6)?? I guess it should be here however.
	void SLTI(const EeCoreInstruction inst);
	void SLTIU(const EeCoreInstruction inst);
	void SLTU(const EeCoreInstruction inst);
	void PCEQB(const EeCoreInstruction inst);
	void PCEQH(const EeCoreInstruction inst);
	void PCEQW(const EeCoreInstruction inst);
	void PCGTB(const EeCoreInstruction inst);
	void PCGTH(const EeCoreInstruction inst);
	void PCGTW(const EeCoreInstruction inst);
	void C_EQ_S(const EeCoreInstruction inst);
	void C_F_S(const EeCoreInstruction inst);
	void C_LE_S(const EeCoreInstruction inst);
	void C_LT_S(const EeCoreInstruction inst);

	/// Min/Max Instructions. See EECoreInterpreter_MIN_MAX.cpp for implementations (6 instructions total).
	void PMAXH(const EeCoreInstruction inst);
	void PMAXW(const EeCoreInstruction inst);
	void PMINH(const EeCoreInstruction inst);
	void PMINW(const EeCoreInstruction inst);
	void MAX_S(const EeCoreInstruction inst);
	void MIN_S(const EeCoreInstruction inst);

	/// Data Format Conversion (DFC) Instructions. See EECoreInterpreter_DFC.cpp for implementations (4 instructions total).
	void PEXT5(const EeCoreInstruction inst);
	void PPAC5(const EeCoreInstruction inst);
	void CVT_S_W(const EeCoreInstruction inst);
	void CVT_W_S(const EeCoreInstruction inst);

	/// Reordering Instructions. See EECoreInterpreter_REORDERING.cpp for implementations (20 instructions total).
	void PCPYH(const EeCoreInstruction inst);
	void PCPYLD(const EeCoreInstruction inst);
	void PCPYUD(const EeCoreInstruction inst);
	void PEXCH(const EeCoreInstruction inst);
	void PEXCW(const EeCoreInstruction inst);
	void PEXEH(const EeCoreInstruction inst);
	void PEXEW(const EeCoreInstruction inst);
	void PEXTLB(const EeCoreInstruction inst);
	void PEXTLH(const EeCoreInstruction inst);
	void PEXTLW(const EeCoreInstruction inst);
	void PEXTUB(const EeCoreInstruction inst);
	void PEXTUH(const EeCoreInstruction inst);
	void PEXTUW(const EeCoreInstruction inst);
	void PINTEH(const EeCoreInstruction inst);
	void PINTH(const EeCoreInstruction inst);
	void PPACB(const EeCoreInstruction inst);
	void PPACH(const EeCoreInstruction inst);
	void PPACW(const EeCoreInstruction inst);
	void PREVH(const EeCoreInstruction inst);
	void PROT3W(const EeCoreInstruction inst);

	/// Others (ALU) Instructions. See EECoreInterpreter_ALU_OTHERS.cpp for implementations (7 instructions total).
	void PABSH(const EeCoreInstruction inst);
	void PABSW(const EeCoreInstruction inst);
	void PLZCW(const EeCoreInstruction inst);
	void ABS_S(const EeCoreInstruction inst);
	void NEG_S(const EeCoreInstruction inst);
	void RSQRT_S(const EeCoreInstruction inst);
	void SQRT_S(const EeCoreInstruction inst);

	/// Register-Register Transfer Instructions. See EECoreInterpreter_REG_TRANSFER.cpp for implementations (23 instructions total).
	void MFHI(const EeCoreInstruction inst);
	void MFLO(const EeCoreInstruction inst);
	void MOVN(const EeCoreInstruction inst);
	void MOVZ(const EeCoreInstruction inst);
	void MTHI(const EeCoreInstruction inst);
	void MTLO(const EeCoreInstruction inst);
	void MFHI1(const EeCoreInstruction inst);
	void MFLO1(const EeCoreInstruction inst);
	void MTHI1(const EeCoreInstruction inst);
	void MTLO1(const EeCoreInstruction inst);
	void PMFHI(const EeCoreInstruction inst);
	void PMFHL(const EeCoreInstruction inst); // Calls one of the sub functions below.
	void PMFHL_LH(const EeCoreInstruction inst);
	void PMFHL_LW(const EeCoreInstruction inst);
	void PMFHL_SH(const EeCoreInstruction inst);
	void PMFHL_SLW(const EeCoreInstruction inst);
	void PMFHL_UW(const EeCoreInstruction inst);
	void PMFLO(const EeCoreInstruction inst);
	void PMTHI(const EeCoreInstruction inst);
	void PMTHL_LW(const EeCoreInstruction inst);
	void PMTLO(const EeCoreInstruction inst);
	void MFC1(const EeCoreInstruction inst);
	void MOV_S(const EeCoreInstruction inst);
	void MTC1(const EeCoreInstruction inst);

	/// Load from Memory Instructions. See EECoreInterpreter_LOAD_MEM.cpp for implementations (14 instructions total).
	void LB(const EeCoreInstruction inst);
	void LBU(const EeCoreInstruction inst);
	void LD(const EeCoreInstruction inst);
	void LDL(const EeCoreInstruction inst);
	void LDR(const EeCoreInstruction inst);
	void LH(const EeCoreInstruction inst);
	void LHU(const EeCoreInstruction inst);
	void LUI(const EeCoreInstruction inst);
	void LW(const EeCoreInstruction inst);
	void LWL(const EeCoreInstruction inst);
	void LWR(const EeCoreInstruction inst);
	void LWU(const EeCoreInstruction inst);
	void LQ(const EeCoreInstruction inst);
	void LWC1(const EeCoreInstruction inst);

	/// Store to Memory Instructions. See EECoreInterpreter_STORE_MEM.cpp for implementations (10 instructions total).
	void SB(const EeCoreInstruction inst);
	void SD(const EeCoreInstruction inst);
	void SDL(const EeCoreInstruction inst);
	void SDR(const EeCoreInstruction inst);
	void SH(const EeCoreInstruction inst);
	void SW(const EeCoreInstruction inst);
	void SWL(const EeCoreInstruction inst);
	void SWR(const EeCoreInstruction inst);
	void SQ(const EeCoreInstruction inst);
	void SWC1(const EeCoreInstruction inst);

	/// Special Data Transfer Instructions. See EECoreInterpreter_SPECIAL_TRANSFER.cpp for implementations (26 instructions total).
	void MFSA(const EeCoreInstruction inst);
	void MTSA(const EeCoreInstruction inst);
	void MTSAB(const EeCoreInstruction inst);
	void MTSAH(const EeCoreInstruction inst);
	void MFBPC(const EeCoreInstruction inst);
	void MFC0(const EeCoreInstruction inst);
	void MFDAB(const EeCoreInstruction inst);
	void MFDABM(const EeCoreInstruction inst);
	void MFDVB(const EeCoreInstruction inst);
	void MFDVBM(const EeCoreInstruction inst);
	void MFIAB(const EeCoreInstruction inst);
	void MFIABM(const EeCoreInstruction inst);
	void MFPC(const EeCoreInstruction inst);
	void MFPS(const EeCoreInstruction inst);
	void MTBPC(const EeCoreInstruction inst);
	void MTC0(const EeCoreInstruction inst);
	void MTDAB(const EeCoreInstruction inst);
	void MTDABM(const EeCoreInstruction inst);
	void MTDVB(const EeCoreInstruction inst);
	void MTDVBM(const EeCoreInstruction inst);
	void MTIAB(const EeCoreInstruction inst);
	void MTIABM(const EeCoreInstruction inst);
	void MTPC(const EeCoreInstruction inst);
	void MTPS(const EeCoreInstruction inst);
	void CFC1(const EeCoreInstruction inst);
	void CTC1(const EeCoreInstruction inst);

	/// Conditional Branch and Jump Instructions. See EECoreInterpreter_COND_BRANCH_JUMP.cpp for implementations (22 instructions total).
	void BEQ(const EeCoreInstruction inst);
	void BEQL(const EeCoreInstruction inst);
	void BGEZ(const EeCoreInstruction inst);
	void BGEZL(const EeCoreInstruction inst);
	void BGTZ(const EeCoreInstruction inst);
	void BGTZL(const EeCoreInstruction inst);
	void BLEZ(const EeCoreInstruction inst);
	void BLEZL(const EeCoreInstruction inst);
	void BLTZ(const EeCoreInstruction inst);
	void BLTZL(const EeCoreInstruction inst);
	void BNE(const EeCoreInstruction inst);
	void BNEL(const EeCoreInstruction inst);
	void BC0F(const EeCoreInstruction inst);
	void BC0FL(const EeCoreInstruction inst);
	void BC0T(const EeCoreInstruction inst);
	void BC0TL(const EeCoreInstruction inst);
	void BC1F(const EeCoreInstruction inst);
	void BC1FL(const EeCoreInstruction inst);
	void BC1T(const EeCoreInstruction inst);
	void BC1TL(const EeCoreInstruction inst);
	void J(const EeCoreInstruction inst);
	void JR(const EeCoreInstruction inst);

	/// Subroutine Call Instructions. See EECoreInterpreter_CALL.cpp for implementations (6 instructions total).
	void BGEZAL(const EeCoreInstruction inst);
	void BGEZALL(const EeCoreInstruction inst);
	void BLTZAL(const EeCoreInstruction inst);
	void BLTZALL(const EeCoreInstruction inst);
	void JAL(const EeCoreInstruction inst);
	void JALR(const EeCoreInstruction inst);

	/// Break and Trap Instructions. See EECoreInterpreter_BREAK_TRAP.cpp for implementations (15 instructions total).
	void BREAK(const EeCoreInstruction inst);
	void SYSCALL(const EeCoreInstruction inst);
	void TEQ(const EeCoreInstruction inst);
	void TEQI(const EeCoreInstruction inst);
	void TGE(const EeCoreInstruction inst);
	void TGEI(const EeCoreInstruction inst);
	void TGEIU(const EeCoreInstruction inst);
	void TGEU(const EeCoreInstruction inst);
	void TLT(const EeCoreInstruction inst);
	void TLTI(const EeCoreInstruction inst);
	void TLTIU(const EeCoreInstruction inst);
	void TLTU(const EeCoreInstruction inst);
	void TNE(const EeCoreInstruction inst);
	void TNEI(const EeCoreInstruction inst);
	void ERET(const EeCoreInstruction inst);

	/// Others Instructions. See EECoreInterpreter_OTHERS.cpp for implementations (9 instructions total). Includes the TLB instructions as they are missing in the overview manual...
	void SYNC_STYPE(const EeCoreInstruction inst);
	void PREF(const EeCoreInstruction inst);
	void DI(const EeCoreInstruction inst);
	void EI(const EeCoreInstruction inst);
	void CACHE(const EeCoreInstruction inst);
	void TLBP(const EeCoreInstruction inst);
	void TLBR(const EeCoreInstruction inst);
	void TLBWI(const EeCoreInstruction inst);
	void TLBWR(const EeCoreInstruction inst);

	/// VU0 (attached as COP2) Macro Instructions. For reference, see VU Users Manual page 206 onwards. 
	/// In total there are 140 instructions, however, the instructions prefixed with V* are delegate functions to the VU0 system (see the VU system for implementation).
	/// The two exceptions to this is the VCALLMS/VCALLMSR instructions.
	/// For the EE Core, the first 12 instructions are implemented as pure COP2 instructions.
	/// ------------- Raw COP2 Instructions -------------
	void QMFC2(const EeCoreInstruction inst);
	void QMTC2(const EeCoreInstruction inst);
	void LQC2(const EeCoreInstruction inst);
	void SQC2(const EeCoreInstruction inst);
	void CFC2(const EeCoreInstruction inst);
	void CTC2(const EeCoreInstruction inst);
	void BC2F(const EeCoreInstruction inst);
	void BC2FL(const EeCoreInstruction inst);
	void BC2T(const EeCoreInstruction inst);
	void BC2TL(const EeCoreInstruction inst);
	void VCALLMS(const EeCoreInstruction inst);
	void VCALLMSR(const EeCoreInstruction inst);
	/// ------------- VU0 Delegate Instructions -------------
	void VABS(const EeCoreInstruction inst);
	void VADD(const EeCoreInstruction inst);
	void VADDi(const EeCoreInstruction inst);
	void VADDq(const EeCoreInstruction inst);
	void VADDbc_0(const EeCoreInstruction inst);
	void VADDbc_1(const EeCoreInstruction inst);
	void VADDbc_2(const EeCoreInstruction inst);
	void VADDbc_3(const EeCoreInstruction inst);
	void VADDA(const EeCoreInstruction inst);
	void VADDAi(const EeCoreInstruction inst);
	void VADDAq(const EeCoreInstruction inst);
	void VADDAbc_0(const EeCoreInstruction inst);
	void VADDAbc_1(const EeCoreInstruction inst);
	void VADDAbc_2(const EeCoreInstruction inst);
	void VADDAbc_3(const EeCoreInstruction inst);
	void VSUB(const EeCoreInstruction inst);
	void VSUBi(const EeCoreInstruction inst);
	void VSUBq(const EeCoreInstruction inst);
	void VSUBbc_0(const EeCoreInstruction inst);
	void VSUBbc_1(const EeCoreInstruction inst);
	void VSUBbc_2(const EeCoreInstruction inst);
	void VSUBbc_3(const EeCoreInstruction inst);
	void VSUBA(const EeCoreInstruction inst);
	void VSUBAi(const EeCoreInstruction inst);
	void VSUBAq(const EeCoreInstruction inst);
	void VSUBAbc_0(const EeCoreInstruction inst);
	void VSUBAbc_1(const EeCoreInstruction inst);
	void VSUBAbc_2(const EeCoreInstruction inst);
	void VSUBAbc_3(const EeCoreInstruction inst);
	void VMUL(const EeCoreInstruction inst);
	void VMULi(const EeCoreInstruction inst);
	void VMULq(const EeCoreInstruction inst);
	void VMULbc_0(const EeCoreInstruction inst);
	void VMULbc_1(const EeCoreInstruction inst);
	void VMULbc_2(const EeCoreInstruction inst);
	void VMULbc_3(const EeCoreInstruction inst);
	void VMULA(const EeCoreInstruction inst);
	void VMULAi(const EeCoreInstruction inst);
	void VMULAq(const EeCoreInstruction inst);
	void VMULAbc_0(const EeCoreInstruction inst);
	void VMULAbc_1(const EeCoreInstruction inst);
	void VMULAbc_2(const EeCoreInstruction inst);
	void VMULAbc_3(const EeCoreInstruction inst);
	void VMADD(const EeCoreInstruction inst);
	void VMADDi(const EeCoreInstruction inst);
	void VMADDq(const EeCoreInstruction inst);
	void VMADDbc_0(const EeCoreInstruction inst);
	void VMADDbc_1(const EeCoreInstruction inst);
	void VMADDbc_2(const EeCoreInstruction inst);
	void VMADDbc_3(const EeCoreInstruction inst);
	void VMADDA(const EeCoreInstruction inst);
	void VMADDAi(const EeCoreInstruction inst);
	void VMADDAq(const EeCoreInstruction inst);
	void VMADDAbc_0(const EeCoreInstruction inst);
	void VMADDAbc_1(const EeCoreInstruction inst);
	void VMADDAbc_2(const EeCoreInstruction inst);
	void VMADDAbc_3(const EeCoreInstruction inst);
	void VMSUB(const EeCoreInstruction inst);
	void VMSUBi(const EeCoreInstruction inst);
	void VMSUBq(const EeCoreInstruction inst);
	void VMSUBbc_0(const EeCoreInstruction inst);
	void VMSUBbc_1(const EeCoreInstruction inst);
	void VMSUBbc_2(const EeCoreInstruction inst);
	void VMSUBbc_3(const EeCoreInstruction inst);
	void VMSUBA(const EeCoreInstruction inst);
	void VMSUBAi(const EeCoreInstruction inst);
	void VMSUBAq(const EeCoreInstruction inst);
	void VMSUBAbc_0(const EeCoreInstruction inst);
	void VMSUBAbc_1(const EeCoreInstruction inst);
	void VMSUBAbc_2(const EeCoreInstruction inst);
	void VMSUBAbc_3(const EeCoreInstruction inst);
	void VMAX(const EeCoreInstruction inst);
	void VMAXi(const EeCoreInstruction inst);
	void VMAXbc_0(const EeCoreInstruction inst);
	void VMAXbc_1(const EeCoreInstruction inst);
	void VMAXbc_2(const EeCoreInstruction inst);
	void VMAXbc_3(const EeCoreInstruction inst);
	void VMINI(const EeCoreInstruction inst);
	void VMINIi(const EeCoreInstruction inst);
	void VMINIbc_0(const EeCoreInstruction inst);
	void VMINIbc_1(const EeCoreInstruction inst);
	void VMINIbc_2(const EeCoreInstruction inst);
	void VMINIbc_3(const EeCoreInstruction inst);
	void VOPMULA(const EeCoreInstruction inst);
	void VOPMSUB(const EeCoreInstruction inst);
	void VNOP(const EeCoreInstruction inst);
	void VFTOI0(const EeCoreInstruction inst);
	void VFTOI4(const EeCoreInstruction inst);
	void VFTOI12(const EeCoreInstruction inst);
	void VFTOI15(const EeCoreInstruction inst);
	void VITOF0(const EeCoreInstruction inst);
	void VITOF4(const EeCoreInstruction inst);
	void VITOF12(const EeCoreInstruction inst);
	void VITOF15(const EeCoreInstruction inst);
	void VCLIP(const EeCoreInstruction inst);
	void VDIV(const EeCoreInstruction inst);
	void VSQRT(const EeCoreInstruction inst);
	void VRSQRT(const EeCoreInstruction inst);
	void VIADD(const EeCoreInstruction inst);
	void VIADDI(const EeCoreInstruction inst);
	void VIAND(const EeCoreInstruction inst);
	void VIOR(const EeCoreInstruction inst);
	void VISUB(const EeCoreInstruction inst);
	void VMOVE(const EeCoreInstruction inst);
	void VMFIR(const EeCoreInstruction inst);
	void VMTIR(const EeCoreInstruction inst);
	void VMR32(const EeCoreInstruction inst);
	void VLQD(const EeCoreInstruction inst);
	void VLQI(const EeCoreInstruction inst);
	void VSQD(const EeCoreInstruction inst);
	void VSQI(const EeCoreInstruction inst);
	void VILWR(const EeCoreInstruction inst);
	void VISWR(const EeCoreInstruction inst);
	void VRINIT(const EeCoreInstruction inst);
	void VRGET(const EeCoreInstruction inst);
	void VRNEXT(const EeCoreInstruction inst);
	void VRXOR(const EeCoreInstruction inst);
	void VWAITQ(const EeCoreInstruction inst);

	/// Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index. 
	/// Sometimes there are differences in the instruction mnemonics within the manual. 
	/// Alternative names have been provided as comments against the array function used.
	void(CEeCoreInterpreter::* EECORE_INSTRUCTION_TABLE[Constants::EE::EECore::NUMBER_INSTRUCTIONS])(const EeCoreInstruction inst) =
	{
		&CEeCoreInterpreter::INSTRUCTION_UNKNOWN,
		&CEeCoreInterpreter::J,
		&CEeCoreInterpreter::JAL,
		&CEeCoreInterpreter::BEQ,
		&CEeCoreInterpreter::BNE,
		&CEeCoreInterpreter::BLEZ,
		&CEeCoreInterpreter::BGTZ,
		&CEeCoreInterpreter::ADDI,
		&CEeCoreInterpreter::ADDIU,
		&CEeCoreInterpreter::SLTI,
		&CEeCoreInterpreter::SLTIU,
		&CEeCoreInterpreter::ANDI,
		&CEeCoreInterpreter::ORI,
		&CEeCoreInterpreter::XORI,
		&CEeCoreInterpreter::LUI,
		&CEeCoreInterpreter::BEQL,
		&CEeCoreInterpreter::BNEL,
		&CEeCoreInterpreter::BLEZL,
		&CEeCoreInterpreter::BGTZL,
		&CEeCoreInterpreter::DADDI,
		&CEeCoreInterpreter::DADDIU,
		&CEeCoreInterpreter::LDL,
		&CEeCoreInterpreter::LDR,
		&CEeCoreInterpreter::LQ,
		&CEeCoreInterpreter::SQ,
		&CEeCoreInterpreter::LB,
		&CEeCoreInterpreter::LH,
		&CEeCoreInterpreter::LWL,
		&CEeCoreInterpreter::LW,
		&CEeCoreInterpreter::LBU,
		&CEeCoreInterpreter::LHU,
		&CEeCoreInterpreter::LWR,
		&CEeCoreInterpreter::LWU,
		&CEeCoreInterpreter::SB,
		&CEeCoreInterpreter::SH,
		&CEeCoreInterpreter::SWL,
		&CEeCoreInterpreter::SW,
		&CEeCoreInterpreter::SDL,
		&CEeCoreInterpreter::SDR,
		&CEeCoreInterpreter::SWR,
		&CEeCoreInterpreter::CACHE,
		&CEeCoreInterpreter::LWC1,
		&CEeCoreInterpreter::PREF,
		&CEeCoreInterpreter::LQC2,
		&CEeCoreInterpreter::LD,
		&CEeCoreInterpreter::SWC1,
		&CEeCoreInterpreter::LQC2,
		&CEeCoreInterpreter::SD,
		&CEeCoreInterpreter::SLL,
		&CEeCoreInterpreter::SRL,
		&CEeCoreInterpreter::SRA,
		&CEeCoreInterpreter::SLLV,
		&CEeCoreInterpreter::SRLV,
		&CEeCoreInterpreter::SRAV,
		&CEeCoreInterpreter::JR,
		&CEeCoreInterpreter::JALR,
		&CEeCoreInterpreter::MOVZ,
		&CEeCoreInterpreter::MOVN,
		&CEeCoreInterpreter::SYSCALL,
		&CEeCoreInterpreter::BREAK,
		&CEeCoreInterpreter::SYNC_STYPE,
		&CEeCoreInterpreter::MFHI,
		&CEeCoreInterpreter::MTHI,
		&CEeCoreInterpreter::MFLO,
		&CEeCoreInterpreter::MTLO,
		&CEeCoreInterpreter::DSLLV,
		&CEeCoreInterpreter::DSRLV,
		&CEeCoreInterpreter::DSRAV,
		&CEeCoreInterpreter::MULT,
		&CEeCoreInterpreter::MULTU,
		&CEeCoreInterpreter::DIV,
		&CEeCoreInterpreter::DIVU,
		&CEeCoreInterpreter::ADD,
		&CEeCoreInterpreter::ADDU,
		&CEeCoreInterpreter::SUB,
		&CEeCoreInterpreter::SUBU,
		&CEeCoreInterpreter::AND,
		&CEeCoreInterpreter::OR,
		&CEeCoreInterpreter::XOR,
		&CEeCoreInterpreter::NOR,
		&CEeCoreInterpreter::MFSA,
		&CEeCoreInterpreter::MTSA,
		&CEeCoreInterpreter::SLT,
		&CEeCoreInterpreter::SLTU,
		&CEeCoreInterpreter::DADD,
		&CEeCoreInterpreter::DADDU,
		&CEeCoreInterpreter::DSUB,
		&CEeCoreInterpreter::DSUBU,
		&CEeCoreInterpreter::TGE,
		&CEeCoreInterpreter::TGEU,
		&CEeCoreInterpreter::TLT,
		&CEeCoreInterpreter::TLTU,
		&CEeCoreInterpreter::TEQ,
		&CEeCoreInterpreter::TNE,
		&CEeCoreInterpreter::DSLL,
		&CEeCoreInterpreter::DSRL,
		&CEeCoreInterpreter::DSRA,
		&CEeCoreInterpreter::DSLL32,
		&CEeCoreInterpreter::DSRL32,
		&CEeCoreInterpreter::DSRA32,
		&CEeCoreInterpreter::BLTZ,
		&CEeCoreInterpreter::BGEZ,
		&CEeCoreInterpreter::BLTZL,
		&CEeCoreInterpreter::BGEZL,
		&CEeCoreInterpreter::TGEI,
		&CEeCoreInterpreter::TGEIU,
		&CEeCoreInterpreter::TLTI,
		&CEeCoreInterpreter::TLTIU,
		&CEeCoreInterpreter::TEQI,
		&CEeCoreInterpreter::TNEI,
		&CEeCoreInterpreter::BLTZAL,
		&CEeCoreInterpreter::BGEZAL,
		&CEeCoreInterpreter::BLTZALL,
		&CEeCoreInterpreter::BGEZALL,
		&CEeCoreInterpreter::MTSAB,
		&CEeCoreInterpreter::MTSAH,
		&CEeCoreInterpreter::MADD,
		&CEeCoreInterpreter::MADDU,
		&CEeCoreInterpreter::PLZCW,
		&CEeCoreInterpreter::MFHI1,
		&CEeCoreInterpreter::MTHI1,
		&CEeCoreInterpreter::MFLO1,
		&CEeCoreInterpreter::MTLO1,
		&CEeCoreInterpreter::MULT1,
		&CEeCoreInterpreter::MULTU1,
		&CEeCoreInterpreter::DIV1,
		&CEeCoreInterpreter::DIVU1,
		&CEeCoreInterpreter::MADD1,
		&CEeCoreInterpreter::MADDU1,
		&CEeCoreInterpreter::PMFHL,
		&CEeCoreInterpreter::PMTHL_LW, // &PMTHL,
		&CEeCoreInterpreter::PSLLH,
		&CEeCoreInterpreter::PSRLH,
		&CEeCoreInterpreter::PSRAH,
		&CEeCoreInterpreter::PSLLW,
		&CEeCoreInterpreter::PSRLW,
		&CEeCoreInterpreter::PSRAW,
		&CEeCoreInterpreter::PADDW,
		&CEeCoreInterpreter::PSUBW,
		&CEeCoreInterpreter::PCGTW,
		&CEeCoreInterpreter::PMAXW,
		&CEeCoreInterpreter::PADDH,
		&CEeCoreInterpreter::PSUBH,
		&CEeCoreInterpreter::PCGTH,
		&CEeCoreInterpreter::PMAXH,
		&CEeCoreInterpreter::PADDB,
		&CEeCoreInterpreter::PSUBB,
		&CEeCoreInterpreter::PCGTB,
		&CEeCoreInterpreter::PADDSW,
		&CEeCoreInterpreter::PSUBSW,
		&CEeCoreInterpreter::PEXTLW,
		&CEeCoreInterpreter::PPACW,
		&CEeCoreInterpreter::PADDSH,
		&CEeCoreInterpreter::PSUBSH,
		&CEeCoreInterpreter::PEXTLH,
		&CEeCoreInterpreter::PPACH,
		&CEeCoreInterpreter::PADDSB,
		&CEeCoreInterpreter::PSUBSB,
		&CEeCoreInterpreter::PEXTLB,
		&CEeCoreInterpreter::PPACB,
		&CEeCoreInterpreter::PEXT5,
		&CEeCoreInterpreter::PPAC5,
		&CEeCoreInterpreter::PABSW,
		&CEeCoreInterpreter::PCEQW,
		&CEeCoreInterpreter::PMINW,
		&CEeCoreInterpreter::PADSBH,
		&CEeCoreInterpreter::PABSH,
		&CEeCoreInterpreter::PCEQH,
		&CEeCoreInterpreter::PMINH,
		&CEeCoreInterpreter::PCEQB,
		&CEeCoreInterpreter::PADDUW,
		&CEeCoreInterpreter::PSUBUW,
		&CEeCoreInterpreter::PEXTUW,
		&CEeCoreInterpreter::PADDUH,
		&CEeCoreInterpreter::PSUBUH,
		&CEeCoreInterpreter::PEXTUH,
		&CEeCoreInterpreter::PADDUB,
		&CEeCoreInterpreter::PSUBUB,
		&CEeCoreInterpreter::PEXTUB,
		&CEeCoreInterpreter::QFSRV,
		&CEeCoreInterpreter::PMADDW,
		&CEeCoreInterpreter::PSLLVW,
		&CEeCoreInterpreter::PSRLVW,
		&CEeCoreInterpreter::PMSUBW,
		&CEeCoreInterpreter::PMFHI,
		&CEeCoreInterpreter::PMFLO,
		&CEeCoreInterpreter::PINTH,
		&CEeCoreInterpreter::PMULTW,
		&CEeCoreInterpreter::PDIVW,
		&CEeCoreInterpreter::PCPYLD,
		&CEeCoreInterpreter::PMADDH,
		&CEeCoreInterpreter::PHMADH,
		&CEeCoreInterpreter::PAND,
		&CEeCoreInterpreter::PXOR,
		&CEeCoreInterpreter::PMSUBH,
		&CEeCoreInterpreter::PHMSBH,
		&CEeCoreInterpreter::PEXEH,
		&CEeCoreInterpreter::PREVH,
		&CEeCoreInterpreter::PMULTH,
		&CEeCoreInterpreter::PDIVBW,
		&CEeCoreInterpreter::PEXEW,
		&CEeCoreInterpreter::PROT3W,
		&CEeCoreInterpreter::PMADDUW,
		&CEeCoreInterpreter::PSRAVW,
		&CEeCoreInterpreter::PMTHI,
		&CEeCoreInterpreter::PMTLO,
		&CEeCoreInterpreter::PINTEH,
		&CEeCoreInterpreter::PMULTUW,
		&CEeCoreInterpreter::PDIVUW,
		&CEeCoreInterpreter::PCPYUD,
		&CEeCoreInterpreter::POR,
		&CEeCoreInterpreter::PNOR,
		&CEeCoreInterpreter::PEXCH,
		&CEeCoreInterpreter::PCPYH,
		&CEeCoreInterpreter::PEXCW,
		&CEeCoreInterpreter::MFC0, // &MF0,
		&CEeCoreInterpreter::MTC0, // &MT0,
		&CEeCoreInterpreter::BC0F,
		&CEeCoreInterpreter::BC0T,
		&CEeCoreInterpreter::BC0FL,
		&CEeCoreInterpreter::BC0TL,
		&CEeCoreInterpreter::TLBR,
		&CEeCoreInterpreter::TLBWI,
		&CEeCoreInterpreter::TLBWR,
		&CEeCoreInterpreter::TLBP,
		&CEeCoreInterpreter::ERET,
		&CEeCoreInterpreter::EI,
		&CEeCoreInterpreter::DI,
		&CEeCoreInterpreter::MFC1,
		&CEeCoreInterpreter::CFC1,
		&CEeCoreInterpreter::MTC1,
		&CEeCoreInterpreter::CTC1,
		&CEeCoreInterpreter::BC1F,
		&CEeCoreInterpreter::BC1T,
		&CEeCoreInterpreter::BC1FL,
		&CEeCoreInterpreter::BC1TL,
		&CEeCoreInterpreter::ADD_S, // &ADD,
		&CEeCoreInterpreter::SUB_S, // &SUB,
		&CEeCoreInterpreter::MUL_S, // &MUL,
		&CEeCoreInterpreter::DIV_S, // &DIV,
		&CEeCoreInterpreter::SQRT_S, // &SQRT,
		&CEeCoreInterpreter::ABS_S, // &ABS,
		&CEeCoreInterpreter::MOV_S, // &MOV,
		&CEeCoreInterpreter::NEG_S, // &NEG,
		&CEeCoreInterpreter::RSQRT_S, // &RSQRT,
		&CEeCoreInterpreter::ADDA_S, // &ADDA,
		&CEeCoreInterpreter::SUBA_S, // &SUBA,
		&CEeCoreInterpreter::MULA_S, // &MULA,
		&CEeCoreInterpreter::MADD_S, // &MADD,
		&CEeCoreInterpreter::MSUB_S, // &MSUB,
		&CEeCoreInterpreter::MADDA_S, // &MADDA,
		&CEeCoreInterpreter::MSUBA_S, // &MSUBA,
		&CEeCoreInterpreter::CVT_W_S, // &CVTW,
		&CEeCoreInterpreter::MAX_S, // &MAX,
		&CEeCoreInterpreter::MIN_S, // &MIN,
		&CEeCoreInterpreter::C_F_S, // &C_F,
		&CEeCoreInterpreter::C_EQ_S, // &C_EQ,
		&CEeCoreInterpreter::C_LT_S, // &C_LT,
		&CEeCoreInterpreter::C_LE_S, // &C_LE,
		&CEeCoreInterpreter::CVT_S_W, // &CVTS,
		&CEeCoreInterpreter::QMFC2,
		&CEeCoreInterpreter::CFC2,
		&CEeCoreInterpreter::QMTC2,
		&CEeCoreInterpreter::CTC2,
		&CEeCoreInterpreter::BC2F,
		&CEeCoreInterpreter::BC2T,
		&CEeCoreInterpreter::BC2FL,
		&CEeCoreInterpreter::BC2TL,
		&CEeCoreInterpreter::VADDbc_0,
		&CEeCoreInterpreter::VADDbc_1,
		&CEeCoreInterpreter::VADDbc_2,
		&CEeCoreInterpreter::VADDbc_3,
		&CEeCoreInterpreter::VSUBbc_0,
		&CEeCoreInterpreter::VSUBbc_1,
		&CEeCoreInterpreter::VSUBbc_2,
		&CEeCoreInterpreter::VSUBbc_3,
		&CEeCoreInterpreter::VMADDbc_0,
		&CEeCoreInterpreter::VMADDbc_1,
		&CEeCoreInterpreter::VMADDbc_2,
		&CEeCoreInterpreter::VMADDbc_3,
		&CEeCoreInterpreter::VMSUBbc_0,
		&CEeCoreInterpreter::VMSUBbc_1,
		&CEeCoreInterpreter::VMSUBbc_2,
		&CEeCoreInterpreter::VMSUBbc_3,
		&CEeCoreInterpreter::VMAXbc_0,
		&CEeCoreInterpreter::VMAXbc_1,
		&CEeCoreInterpreter::VMAXbc_2,
		&CEeCoreInterpreter::VMAXbc_3,
		&CEeCoreInterpreter::VMINIbc_0,
		&CEeCoreInterpreter::VMINIbc_1,
		&CEeCoreInterpreter::VMINIbc_2,
		&CEeCoreInterpreter::VMINIbc_3,
		&CEeCoreInterpreter::VMULbc_0,
		&CEeCoreInterpreter::VMULbc_1,
		&CEeCoreInterpreter::VMULbc_2,
		&CEeCoreInterpreter::VMULbc_3,
		&CEeCoreInterpreter::VMULq,
		&CEeCoreInterpreter::VMAXi,
		&CEeCoreInterpreter::VMULi,
		&CEeCoreInterpreter::VMINIi,
		&CEeCoreInterpreter::VADDq,
		&CEeCoreInterpreter::VMADDq,
		&CEeCoreInterpreter::VADDi,
		&CEeCoreInterpreter::VMADDi,
		&CEeCoreInterpreter::VSUBq,
		&CEeCoreInterpreter::VMSUBq,
		&CEeCoreInterpreter::VSUBi,
		&CEeCoreInterpreter::VMSUBi,
		&CEeCoreInterpreter::VADD,
		&CEeCoreInterpreter::VMADD,
		&CEeCoreInterpreter::VMUL,
		&CEeCoreInterpreter::VMAX,
		&CEeCoreInterpreter::VSUB,
		&CEeCoreInterpreter::VMSUB,
		&CEeCoreInterpreter::VOPMSUB,
		&CEeCoreInterpreter::VMINI,
		&CEeCoreInterpreter::VIADD,
		&CEeCoreInterpreter::VISUB,
		&CEeCoreInterpreter::VIADDI,
		&CEeCoreInterpreter::VIAND,
		&CEeCoreInterpreter::VIOR,
		&CEeCoreInterpreter::VCALLMS,
		&CEeCoreInterpreter::VCALLMSR,
		&CEeCoreInterpreter::VADDAbc_0,
		&CEeCoreInterpreter::VSUBAbc_0,
		&CEeCoreInterpreter::VMADDAbc_0,
		&CEeCoreInterpreter::VMSUBAbc_0,
		&CEeCoreInterpreter::VITOF0,
		&CEeCoreInterpreter::VFTOI0,
		&CEeCoreInterpreter::VMULAbc_0,
		&CEeCoreInterpreter::VMULAq,
		&CEeCoreInterpreter::VADDAq,
		&CEeCoreInterpreter::VSUBAq,
		&CEeCoreInterpreter::VADDA,
		&CEeCoreInterpreter::VSUBA,
		&CEeCoreInterpreter::VMOVE,
		&CEeCoreInterpreter::VLQI,
		&CEeCoreInterpreter::VDIV,
		&CEeCoreInterpreter::VMTIR,
		&CEeCoreInterpreter::VRNEXT,
		&CEeCoreInterpreter::VADDAbc_1,
		&CEeCoreInterpreter::VSUBAbc_1,
		&CEeCoreInterpreter::VMADDAbc_1,
		&CEeCoreInterpreter::VMSUBAbc_1,
		&CEeCoreInterpreter::VITOF4,
		&CEeCoreInterpreter::VFTOI4,
		&CEeCoreInterpreter::VMULAbc_1,
		&CEeCoreInterpreter::VABS,
		&CEeCoreInterpreter::VMADDAq,
		&CEeCoreInterpreter::VMSUBAq,
		&CEeCoreInterpreter::VMADDA,
		&CEeCoreInterpreter::VMSUBA,
		&CEeCoreInterpreter::VMR32,
		&CEeCoreInterpreter::VSQI,
		&CEeCoreInterpreter::VSQRT,
		&CEeCoreInterpreter::VMFIR,
		&CEeCoreInterpreter::VRGET,
		&CEeCoreInterpreter::VADDAbc_2,
		&CEeCoreInterpreter::VSUBAbc_2,
		&CEeCoreInterpreter::VMADDAbc_2,
		&CEeCoreInterpreter::VMSUBAbc_2,
		&CEeCoreInterpreter::VITOF12,
		&CEeCoreInterpreter::VFTOI12,
		&CEeCoreInterpreter::VMULAbc_2,
		&CEeCoreInterpreter::VMULAi,
		&CEeCoreInterpreter::VADDAi,
		&CEeCoreInterpreter::VSUBAi,
		&CEeCoreInterpreter::VMULA,
		&CEeCoreInterpreter::VOPMULA,
		&CEeCoreInterpreter::VLQD,
		&CEeCoreInterpreter::VRSQRT,
		&CEeCoreInterpreter::VILWR,
		&CEeCoreInterpreter::VRINIT,
		&CEeCoreInterpreter::VADDAbc_3,
		&CEeCoreInterpreter::VSUBAbc_3,
		&CEeCoreInterpreter::VMADDAbc_3,
		&CEeCoreInterpreter::VMSUBAbc_3,
		&CEeCoreInterpreter::VITOF15,
		&CEeCoreInterpreter::VFTOI15,
		&CEeCoreInterpreter::VMULAbc_3,
		&CEeCoreInterpreter::VCLIP,
		&CEeCoreInterpreter::VMADDAi,
		&CEeCoreInterpreter::VMSUBAi,
		&CEeCoreInterpreter::VNOP,
		&CEeCoreInterpreter::VSQD,
		&CEeCoreInterpreter::VWAITQ,
		&CEeCoreInterpreter::VISWR,
		&CEeCoreInterpreter::VRXOR
	};
};