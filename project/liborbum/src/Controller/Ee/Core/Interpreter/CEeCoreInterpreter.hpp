#pragma once

#include "Common/Constants.hpp"

#include "Controller/CController.hpp"
#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"

#include "Resources/Ee/Core/EeCoreInstruction.hpp"
#include "Resources/Ee/Core/EeCoreException.hpp"

class Core;

/// The EE Core interpreter. Implements the EE Core including the R5900, COP0, FPU (COP1), etc.
/// Needs a reference to the VU0 interpreter, which is called upon when any of the COP2 instructions starting with V* mnemonics are called.
/// This is done in order to avoid reimplementing the same function twice.
/// TODO: Finish documentation.
class CEeCoreInterpreter : public CController
{
public:
	CEeCoreInterpreter(Core * core);
	virtual ~CEeCoreInterpreter();

	void handle_event(const ControllerEvent & event) const override;
	
	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us) const;

	/// Steps through the EE Core state, executing instructions.
	int time_step(const int ticks_available) const;

	//////////////////////////
	// Common Functionality //
	//////////////////////////

#if defined(BUILD_DEBUG)
	/// Debug loop counter.
	mutable size_t DEBUG_LOOP_COUNTER = 0;
#endif

#if defined(BUILD_DEBUG)
	/// Prints debug information about interrupt sources.
	void debug_print_interrupt_info() const;
#endif

	///////////////////////////////
	// Instruction Functionality //
	///////////////////////////////

	/// Checks the COP0.Count register against the COP0.Compare register.
	/// If the Count value == Compare value, an interrupt is generated.
	void handle_count_update(const int cpi) const;

	/// The VU interpreter, used to call any COP2 instructions prefixed with V* as the mnemonic.
	/// TODO: Will change in future when VU's are implemented.
	CVuInterpreter c_vu_interpreter;

	/// Helper functions to check:
	///  - The usability conditions of COP0, 1, 2 (VU0).
	///  - No over or underflow will occur for signed 32/64 bit integers.
	/// Returns a bool indicating if the instruction should return early because of unavailablity.
	/// Return early from instruction = true, proceed with instruction = false.
	/// They will automatically set the exception state as well.
	bool handle_cop0_usable() const;
	bool handle_cop1_usable() const;
	bool handle_cop2_usable() const;
	bool handle_over_or_underflow_32(const sword & x, const sword & y) const;
	bool handle_over_or_underflow_64(const sdword & x, const sdword & y) const;

	/// EECore Instruction functions. The instructions are organised according to the EE Overview Manual starting from page 26 (which also means separate cpp files per category).
	/// Note 1: there is no true pipeline concept in PCSX2 - instructions that are meant for pipeline 1 (marked with "1" at the end of the mnemonic) are treated like normal instructions.
	/// Note 2: Dots in mnemonics & function names are represented by the underscore character.

	/// Unknown instruction...
	void INSTRUCTION_UNKNOWN(const EeCoreInstruction inst) const;

	/// Integer Add/Sub Instructions. See EECoreInterpreter_INTEGER_ADD_SUB.cpp for implementations (31 instructions total).
	void ADD(const EeCoreInstruction inst) const;
	void ADDI(const EeCoreInstruction inst) const;
	void ADDIU(const EeCoreInstruction inst) const;
	void ADDU(const EeCoreInstruction inst) const;
	void DADD(const EeCoreInstruction inst) const;
	void DADDI(const EeCoreInstruction inst) const;
	void DADDIU(const EeCoreInstruction inst) const;
	void DADDU(const EeCoreInstruction inst) const;
	void DSUB(const EeCoreInstruction inst) const;
	void DSUBU(const EeCoreInstruction inst) const;
	void SUB(const EeCoreInstruction inst) const;
	void SUBU(const EeCoreInstruction inst) const;
	void PADDB(const EeCoreInstruction inst) const;
	void PADDH(const EeCoreInstruction inst) const;
	void PADDSB(const EeCoreInstruction inst) const;
	void PADDSH(const EeCoreInstruction inst) const;
	void PADDSW(const EeCoreInstruction inst) const;
	void PADDUB(const EeCoreInstruction inst) const;
	void PADDUH(const EeCoreInstruction inst) const;
	void PADDUW(const EeCoreInstruction inst) const;
	void PADDW(const EeCoreInstruction inst) const;
	void PADSBH(const EeCoreInstruction inst) const;
	void PSUBB(const EeCoreInstruction inst) const;
	void PSUBH(const EeCoreInstruction inst) const;
	void PSUBSB(const EeCoreInstruction inst) const;
	void PSUBSH(const EeCoreInstruction inst) const;
	void PSUBSW(const EeCoreInstruction inst) const;
	void PSUBUB(const EeCoreInstruction inst) const;
	void PSUBUH(const EeCoreInstruction inst) const;
	void PSUBUW(const EeCoreInstruction inst) const;
	void PSUBW(const EeCoreInstruction inst) const;

	/// Integer Mult/Div Instructions. See EECoreInterpreter_INTEGER_MULT_DIV.cpp for implementations (14 instructions total).
	void DIV(const EeCoreInstruction inst) const;
	void DIV1(const EeCoreInstruction inst) const;
	void DIVU(const EeCoreInstruction inst) const;
	void DIVU1(const EeCoreInstruction inst) const;
	void MULT(const EeCoreInstruction inst) const;
	void MULT1(const EeCoreInstruction inst) const;
	void MULTU(const EeCoreInstruction inst) const;
	void MULTU1(const EeCoreInstruction inst) const;
	void PDIVBW(const EeCoreInstruction inst) const;
	void PDIVUW(const EeCoreInstruction inst) const;
	void PDIVW(const EeCoreInstruction inst) const;
	void PMULTH(const EeCoreInstruction inst) const;
	void PMULTUW(const EeCoreInstruction inst) const;
	void PMULTW(const EeCoreInstruction inst) const;

	/// Integer Mult-Add Instructions. See EECoreInterpreter_INTEGER_MULT_ADD.cpp for implementations (11 instructions total).
	void MADD(const EeCoreInstruction inst) const;
	void MADD1(const EeCoreInstruction inst) const;
	void MADDU(const EeCoreInstruction inst) const;
	void MADDU1(const EeCoreInstruction inst) const;
	void PHMADH(const EeCoreInstruction inst) const;
	void PHMSBH(const EeCoreInstruction inst) const;
	void PMADDH(const EeCoreInstruction inst) const;
	void PMADDUW(const EeCoreInstruction inst) const;
	void PMADDW(const EeCoreInstruction inst) const;
	void PMSUBH(const EeCoreInstruction inst) const;
	void PMSUBW(const EeCoreInstruction inst) const;

	/// Floating-Point Instructions. See EECoreInterpreter_FLOAT.cpp for implementations (10 instructions total).
	void ADD_S(const EeCoreInstruction inst) const;
	void ADDA_S(const EeCoreInstruction inst) const;
	void MADD_S(const EeCoreInstruction inst) const;
	void MADDA_S(const EeCoreInstruction inst) const;
	void MUL_S(const EeCoreInstruction inst) const;
	void MULA_S(const EeCoreInstruction inst) const;
	void DIV_S(const EeCoreInstruction inst) const;
	void MSUB_S(const EeCoreInstruction inst) const;
	void MSUBA_S(const EeCoreInstruction inst) const;
	void SUB_S(const EeCoreInstruction inst) const;
	void SUBA_S(const EeCoreInstruction inst) const;

	/// Shift Instructions. See EECoreInterpreter_SHIFT.cpp for implementations (25 instructions total).
	void DSRA(const EeCoreInstruction inst) const;
	void DSLL(const EeCoreInstruction inst) const;
	void DSLL32(const EeCoreInstruction inst) const;
	void DSLLV(const EeCoreInstruction inst) const;
	void DSRA32(const EeCoreInstruction inst) const;
	void DSRAV(const EeCoreInstruction inst) const;
	void DSRL(const EeCoreInstruction inst) const;
	void DSRL32(const EeCoreInstruction inst) const;
	void DSRLV(const EeCoreInstruction inst) const;
	void SLL(const EeCoreInstruction inst) const;
	void SLLV(const EeCoreInstruction inst) const;
	void SRA(const EeCoreInstruction inst) const;
	void SRAV(const EeCoreInstruction inst) const;
	void SRL(const EeCoreInstruction inst) const;
	void SRLV(const EeCoreInstruction inst) const;
	void PSLLH(const EeCoreInstruction inst) const;
	void PSLLVW(const EeCoreInstruction inst) const;
	void PSLLW(const EeCoreInstruction inst) const;
	void PSRAH(const EeCoreInstruction inst) const;
	void PSRAVW(const EeCoreInstruction inst) const;
	void PSRAW(const EeCoreInstruction inst) const;
	void PSRLH(const EeCoreInstruction inst) const;
	void PSRLVW(const EeCoreInstruction inst) const;
	void PSRLW(const EeCoreInstruction inst) const;
	void QFSRV(const EeCoreInstruction inst) const;

	/// Logical Instructions. See EECoreInterpreter_LOGICAL.cpp for implementations (11 instructions total).
	void AND(const EeCoreInstruction inst) const;
	void ANDI(const EeCoreInstruction inst) const;
	void NOR(const EeCoreInstruction inst) const;
	void OR(const EeCoreInstruction inst) const;
	void ORI(const EeCoreInstruction inst) const;
	void XOR(const EeCoreInstruction inst) const;
	void XORI(const EeCoreInstruction inst) const;
	void PAND(const EeCoreInstruction inst) const;
	void PNOR(const EeCoreInstruction inst) const;
	void POR(const EeCoreInstruction inst) const;
	void PXOR(const EeCoreInstruction inst) const;

	/// Compare Instructions. See EECoreInterpreter_COMPARE.cpp for implementations (14 instructions total).
	void SLT(const EeCoreInstruction inst) const; // For some reason this is missing in the EE Overview Manual (v6)?? I guess it should be here however.
	void SLTI(const EeCoreInstruction inst) const;
	void SLTIU(const EeCoreInstruction inst) const;
	void SLTU(const EeCoreInstruction inst) const;
	void PCEQB(const EeCoreInstruction inst) const;
	void PCEQH(const EeCoreInstruction inst) const;
	void PCEQW(const EeCoreInstruction inst) const;
	void PCGTB(const EeCoreInstruction inst) const;
	void PCGTH(const EeCoreInstruction inst) const;
	void PCGTW(const EeCoreInstruction inst) const;
	void C_EQ_S(const EeCoreInstruction inst) const;
	void C_F_S(const EeCoreInstruction inst) const;
	void C_LE_S(const EeCoreInstruction inst) const;
	void C_LT_S(const EeCoreInstruction inst) const;

	/// Min/Max Instructions. See EECoreInterpreter_MIN_MAX.cpp for implementations (6 instructions total).
	void PMAXH(const EeCoreInstruction inst) const;
	void PMAXW(const EeCoreInstruction inst) const;
	void PMINH(const EeCoreInstruction inst) const;
	void PMINW(const EeCoreInstruction inst) const;
	void MAX_S(const EeCoreInstruction inst) const;
	void MIN_S(const EeCoreInstruction inst) const;

	/// Data Format Conversion (DFC) Instructions. See EECoreInterpreter_DFC.cpp for implementations (4 instructions total).
	void PEXT5(const EeCoreInstruction inst) const;
	void PPAC5(const EeCoreInstruction inst) const;
	void CVT_S_W(const EeCoreInstruction inst) const;
	void CVT_W_S(const EeCoreInstruction inst) const;

	/// Reordering Instructions. See EECoreInterpreter_REORDERING.cpp for implementations (20 instructions total).
	void PCPYH(const EeCoreInstruction inst) const;
	void PCPYLD(const EeCoreInstruction inst) const;
	void PCPYUD(const EeCoreInstruction inst) const;
	void PEXCH(const EeCoreInstruction inst) const;
	void PEXCW(const EeCoreInstruction inst) const;
	void PEXEH(const EeCoreInstruction inst) const;
	void PEXEW(const EeCoreInstruction inst) const;
	void PEXTLB(const EeCoreInstruction inst) const;
	void PEXTLH(const EeCoreInstruction inst) const;
	void PEXTLW(const EeCoreInstruction inst) const;
	void PEXTUB(const EeCoreInstruction inst) const;
	void PEXTUH(const EeCoreInstruction inst) const;
	void PEXTUW(const EeCoreInstruction inst) const;
	void PINTEH(const EeCoreInstruction inst) const;
	void PINTH(const EeCoreInstruction inst) const;
	void PPACB(const EeCoreInstruction inst) const;
	void PPACH(const EeCoreInstruction inst) const;
	void PPACW(const EeCoreInstruction inst) const;
	void PREVH(const EeCoreInstruction inst) const;
	void PROT3W(const EeCoreInstruction inst) const;

	/// Others (ALU) Instructions. See EECoreInterpreter_ALU_OTHERS.cpp for implementations (7 instructions total).
	void PABSH(const EeCoreInstruction inst) const;
	void PABSW(const EeCoreInstruction inst) const;
	void PLZCW(const EeCoreInstruction inst) const;
	void ABS_S(const EeCoreInstruction inst) const;
	void NEG_S(const EeCoreInstruction inst) const;
	void RSQRT_S(const EeCoreInstruction inst) const;
	void SQRT_S(const EeCoreInstruction inst) const;

	/// Register-Register Transfer Instructions. See EECoreInterpreter_REG_TRANSFER.cpp for implementations (23 instructions total).
	void MFHI(const EeCoreInstruction inst) const;
	void MFLO(const EeCoreInstruction inst) const;
	void MOVN(const EeCoreInstruction inst) const;
	void MOVZ(const EeCoreInstruction inst) const;
	void MTHI(const EeCoreInstruction inst) const;
	void MTLO(const EeCoreInstruction inst) const;
	void MFHI1(const EeCoreInstruction inst) const;
	void MFLO1(const EeCoreInstruction inst) const;
	void MTHI1(const EeCoreInstruction inst) const;
	void MTLO1(const EeCoreInstruction inst) const;
	void PMFHI(const EeCoreInstruction inst) const;
	void PMFHL(const EeCoreInstruction inst) const; // Calls one of the sub functions below.
	void PMFHL_LH(const EeCoreInstruction inst) const;
	void PMFHL_LW(const EeCoreInstruction inst) const;
	void PMFHL_SH(const EeCoreInstruction inst) const;
	void PMFHL_SLW(const EeCoreInstruction inst) const;
	void PMFHL_UW(const EeCoreInstruction inst) const;
	void PMFLO(const EeCoreInstruction inst) const;
	void PMTHI(const EeCoreInstruction inst) const;
	void PMTHL_LW(const EeCoreInstruction inst) const;
	void PMTLO(const EeCoreInstruction inst) const;
	void MFC1(const EeCoreInstruction inst) const;
	void MOV_S(const EeCoreInstruction inst) const;
	void MTC1(const EeCoreInstruction inst) const;

	/// Load from Memory Instructions. See EECoreInterpreter_LOAD_MEM.cpp for implementations (14 instructions total).
	void LB(const EeCoreInstruction inst) const;
	void LBU(const EeCoreInstruction inst) const;
	void LD(const EeCoreInstruction inst) const;
	void LDL(const EeCoreInstruction inst) const;
	void LDR(const EeCoreInstruction inst) const;
	void LH(const EeCoreInstruction inst) const;
	void LHU(const EeCoreInstruction inst) const;
	void LUI(const EeCoreInstruction inst) const;
	void LW(const EeCoreInstruction inst) const;
	void LWL(const EeCoreInstruction inst) const;
	void LWR(const EeCoreInstruction inst) const;
	void LWU(const EeCoreInstruction inst) const;
	void LQ(const EeCoreInstruction inst) const;
	void LWC1(const EeCoreInstruction inst) const;

	/// Store to Memory Instructions. See EECoreInterpreter_STORE_MEM.cpp for implementations (10 instructions total).
	void SB(const EeCoreInstruction inst) const;
	void SD(const EeCoreInstruction inst) const;
	void SDL(const EeCoreInstruction inst) const;
	void SDR(const EeCoreInstruction inst) const;
	void SH(const EeCoreInstruction inst) const;
	void SW(const EeCoreInstruction inst) const;
	void SWL(const EeCoreInstruction inst) const;
	void SWR(const EeCoreInstruction inst) const;
	void SQ(const EeCoreInstruction inst) const;
	void SWC1(const EeCoreInstruction inst) const;

	/// Special Data Transfer Instructions. See EECoreInterpreter_SPECIAL_TRANSFER.cpp for implementations (26 instructions total).
	void MFSA(const EeCoreInstruction inst) const;
	void MTSA(const EeCoreInstruction inst) const;
	void MTSAB(const EeCoreInstruction inst) const;
	void MTSAH(const EeCoreInstruction inst) const;
	void MFBPC(const EeCoreInstruction inst) const;
	void MFC0(const EeCoreInstruction inst) const;
	void MFDAB(const EeCoreInstruction inst) const;
	void MFDABM(const EeCoreInstruction inst) const;
	void MFDVB(const EeCoreInstruction inst) const;
	void MFDVBM(const EeCoreInstruction inst) const;
	void MFIAB(const EeCoreInstruction inst) const;
	void MFIABM(const EeCoreInstruction inst) const;
	void MFPC(const EeCoreInstruction inst) const;
	void MFPS(const EeCoreInstruction inst) const;
	void MTBPC(const EeCoreInstruction inst) const;
	void MTC0(const EeCoreInstruction inst) const;
	void MTDAB(const EeCoreInstruction inst) const;
	void MTDABM(const EeCoreInstruction inst) const;
	void MTDVB(const EeCoreInstruction inst) const;
	void MTDVBM(const EeCoreInstruction inst) const;
	void MTIAB(const EeCoreInstruction inst) const;
	void MTIABM(const EeCoreInstruction inst) const;
	void MTPC(const EeCoreInstruction inst) const;
	void MTPS(const EeCoreInstruction inst) const;
	void CFC1(const EeCoreInstruction inst) const;
	void CTC1(const EeCoreInstruction inst) const;

	/// Conditional Branch and Jump Instructions. See EECoreInterpreter_COND_BRANCH_JUMP.cpp for implementations (22 instructions total).
	void BEQ(const EeCoreInstruction inst) const;
	void BEQL(const EeCoreInstruction inst) const;
	void BGEZ(const EeCoreInstruction inst) const;
	void BGEZL(const EeCoreInstruction inst) const;
	void BGTZ(const EeCoreInstruction inst) const;
	void BGTZL(const EeCoreInstruction inst) const;
	void BLEZ(const EeCoreInstruction inst) const;
	void BLEZL(const EeCoreInstruction inst) const;
	void BLTZ(const EeCoreInstruction inst) const;
	void BLTZL(const EeCoreInstruction inst) const;
	void BNE(const EeCoreInstruction inst) const;
	void BNEL(const EeCoreInstruction inst) const;
	void BC0F(const EeCoreInstruction inst) const;
	void BC0FL(const EeCoreInstruction inst) const;
	void BC0T(const EeCoreInstruction inst) const;
	void BC0TL(const EeCoreInstruction inst) const;
	void BC1F(const EeCoreInstruction inst) const;
	void BC1FL(const EeCoreInstruction inst) const;
	void BC1T(const EeCoreInstruction inst) const;
	void BC1TL(const EeCoreInstruction inst) const;
	void J(const EeCoreInstruction inst) const;
	void JR(const EeCoreInstruction inst) const;

	/// Subroutine Call Instructions. See EECoreInterpreter_CALL.cpp for implementations (6 instructions total).
	void BGEZAL(const EeCoreInstruction inst) const;
	void BGEZALL(const EeCoreInstruction inst) const;
	void BLTZAL(const EeCoreInstruction inst) const;
	void BLTZALL(const EeCoreInstruction inst) const;
	void JAL(const EeCoreInstruction inst) const;
	void JALR(const EeCoreInstruction inst) const;

	/// Break and Trap Instructions. See EECoreInterpreter_BREAK_TRAP.cpp for implementations (15 instructions total).
	void BREAK(const EeCoreInstruction inst) const;
	void SYSCALL(const EeCoreInstruction inst) const;
	void TEQ(const EeCoreInstruction inst) const;
	void TEQI(const EeCoreInstruction inst) const;
	void TGE(const EeCoreInstruction inst) const;
	void TGEI(const EeCoreInstruction inst) const;
	void TGEIU(const EeCoreInstruction inst) const;
	void TGEU(const EeCoreInstruction inst) const;
	void TLT(const EeCoreInstruction inst) const;
	void TLTI(const EeCoreInstruction inst) const;
	void TLTIU(const EeCoreInstruction inst) const;
	void TLTU(const EeCoreInstruction inst) const;
	void TNE(const EeCoreInstruction inst) const;
	void TNEI(const EeCoreInstruction inst) const;
	void ERET(const EeCoreInstruction inst) const;

	/// Others Instructions. See EECoreInterpreter_OTHERS.cpp for implementations (9 instructions total). Includes the TLB instructions as they are missing in the overview manual...
	void SYNC_STYPE(const EeCoreInstruction inst) const;
	void PREF(const EeCoreInstruction inst) const;
	void DI(const EeCoreInstruction inst) const;
	void EI(const EeCoreInstruction inst) const;
	void CACHE(const EeCoreInstruction inst) const;
	void TLBP(const EeCoreInstruction inst) const;
	void TLBR(const EeCoreInstruction inst) const;
	void TLBWI(const EeCoreInstruction inst) const;
	void TLBWR(const EeCoreInstruction inst) const;

	/// VU0 (attached as COP2) Macro Instructions. For reference, see VU Users Manual page 206 onwards. 
	/// In total there are 140 instructions, however, the instructions prefixed with V* are delegate functions to the VU0 system (see the VU system for implementation).
	/// The two exceptions to this is the VCALLMS/VCALLMSR instructions.
	/// For the EE Core, the first 12 instructions are implemented as pure COP2 instructions.
	/// ------------- Raw COP2 Instructions -------------
	void QMFC2(const EeCoreInstruction inst) const;
	void QMTC2(const EeCoreInstruction inst) const;
	void LQC2(const EeCoreInstruction inst) const;
	void SQC2(const EeCoreInstruction inst) const;
	void CFC2(const EeCoreInstruction inst) const;
	void CTC2(const EeCoreInstruction inst) const;
	void BC2F(const EeCoreInstruction inst) const;
	void BC2FL(const EeCoreInstruction inst) const;
	void BC2T(const EeCoreInstruction inst) const;
	void BC2TL(const EeCoreInstruction inst) const;
	void VCALLMS(const EeCoreInstruction inst) const;
	void VCALLMSR(const EeCoreInstruction inst) const;
	/// ------------- VU0 Delegate Instructions -------------
	void VABS(const EeCoreInstruction inst) const;
	void VADD(const EeCoreInstruction inst) const;
	void VADDi(const EeCoreInstruction inst) const;
	void VADDq(const EeCoreInstruction inst) const;
	void VADDbc_0(const EeCoreInstruction inst) const;
	void VADDbc_1(const EeCoreInstruction inst) const;
	void VADDbc_2(const EeCoreInstruction inst) const;
	void VADDbc_3(const EeCoreInstruction inst) const;
	void VADDA(const EeCoreInstruction inst) const;
	void VADDAi(const EeCoreInstruction inst) const;
	void VADDAq(const EeCoreInstruction inst) const;
	void VADDAbc_0(const EeCoreInstruction inst) const;
	void VADDAbc_1(const EeCoreInstruction inst) const;
	void VADDAbc_2(const EeCoreInstruction inst) const;
	void VADDAbc_3(const EeCoreInstruction inst) const;
	void VSUB(const EeCoreInstruction inst) const;
	void VSUBi(const EeCoreInstruction inst) const;
	void VSUBq(const EeCoreInstruction inst) const;
	void VSUBbc_0(const EeCoreInstruction inst) const;
	void VSUBbc_1(const EeCoreInstruction inst) const;
	void VSUBbc_2(const EeCoreInstruction inst) const;
	void VSUBbc_3(const EeCoreInstruction inst) const;
	void VSUBA(const EeCoreInstruction inst) const;
	void VSUBAi(const EeCoreInstruction inst) const;
	void VSUBAq(const EeCoreInstruction inst) const;
	void VSUBAbc_0(const EeCoreInstruction inst) const;
	void VSUBAbc_1(const EeCoreInstruction inst) const;
	void VSUBAbc_2(const EeCoreInstruction inst) const;
	void VSUBAbc_3(const EeCoreInstruction inst) const;
	void VMUL(const EeCoreInstruction inst) const;
	void VMULi(const EeCoreInstruction inst) const;
	void VMULq(const EeCoreInstruction inst) const;
	void VMULbc_0(const EeCoreInstruction inst) const;
	void VMULbc_1(const EeCoreInstruction inst) const;
	void VMULbc_2(const EeCoreInstruction inst) const;
	void VMULbc_3(const EeCoreInstruction inst) const;
	void VMULA(const EeCoreInstruction inst) const;
	void VMULAi(const EeCoreInstruction inst) const;
	void VMULAq(const EeCoreInstruction inst) const;
	void VMULAbc_0(const EeCoreInstruction inst) const;
	void VMULAbc_1(const EeCoreInstruction inst) const;
	void VMULAbc_2(const EeCoreInstruction inst) const;
	void VMULAbc_3(const EeCoreInstruction inst) const;
	void VMADD(const EeCoreInstruction inst) const;
	void VMADDi(const EeCoreInstruction inst) const;
	void VMADDq(const EeCoreInstruction inst) const;
	void VMADDbc_0(const EeCoreInstruction inst) const;
	void VMADDbc_1(const EeCoreInstruction inst) const;
	void VMADDbc_2(const EeCoreInstruction inst) const;
	void VMADDbc_3(const EeCoreInstruction inst) const;
	void VMADDA(const EeCoreInstruction inst) const;
	void VMADDAi(const EeCoreInstruction inst) const;
	void VMADDAq(const EeCoreInstruction inst) const;
	void VMADDAbc_0(const EeCoreInstruction inst) const;
	void VMADDAbc_1(const EeCoreInstruction inst) const;
	void VMADDAbc_2(const EeCoreInstruction inst) const;
	void VMADDAbc_3(const EeCoreInstruction inst) const;
	void VMSUB(const EeCoreInstruction inst) const;
	void VMSUBi(const EeCoreInstruction inst) const;
	void VMSUBq(const EeCoreInstruction inst) const;
	void VMSUBbc_0(const EeCoreInstruction inst) const;
	void VMSUBbc_1(const EeCoreInstruction inst) const;
	void VMSUBbc_2(const EeCoreInstruction inst) const;
	void VMSUBbc_3(const EeCoreInstruction inst) const;
	void VMSUBA(const EeCoreInstruction inst) const;
	void VMSUBAi(const EeCoreInstruction inst) const;
	void VMSUBAq(const EeCoreInstruction inst) const;
	void VMSUBAbc_0(const EeCoreInstruction inst) const;
	void VMSUBAbc_1(const EeCoreInstruction inst) const;
	void VMSUBAbc_2(const EeCoreInstruction inst) const;
	void VMSUBAbc_3(const EeCoreInstruction inst) const;
	void VMAX(const EeCoreInstruction inst) const;
	void VMAXi(const EeCoreInstruction inst) const;
	void VMAXbc_0(const EeCoreInstruction inst) const;
	void VMAXbc_1(const EeCoreInstruction inst) const;
	void VMAXbc_2(const EeCoreInstruction inst) const;
	void VMAXbc_3(const EeCoreInstruction inst) const;
	void VMINI(const EeCoreInstruction inst) const;
	void VMINIi(const EeCoreInstruction inst) const;
	void VMINIbc_0(const EeCoreInstruction inst) const;
	void VMINIbc_1(const EeCoreInstruction inst) const;
	void VMINIbc_2(const EeCoreInstruction inst) const;
	void VMINIbc_3(const EeCoreInstruction inst) const;
	void VOPMULA(const EeCoreInstruction inst) const;
	void VOPMSUB(const EeCoreInstruction inst) const;
	void VNOP(const EeCoreInstruction inst) const;
	void VFTOI0(const EeCoreInstruction inst) const;
	void VFTOI4(const EeCoreInstruction inst) const;
	void VFTOI12(const EeCoreInstruction inst) const;
	void VFTOI15(const EeCoreInstruction inst) const;
	void VITOF0(const EeCoreInstruction inst) const;
	void VITOF4(const EeCoreInstruction inst) const;
	void VITOF12(const EeCoreInstruction inst) const;
	void VITOF15(const EeCoreInstruction inst) const;
	void VCLIP(const EeCoreInstruction inst) const;
	void VDIV(const EeCoreInstruction inst) const;
	void VSQRT(const EeCoreInstruction inst) const;
	void VRSQRT(const EeCoreInstruction inst) const;
	void VIADD(const EeCoreInstruction inst) const;
	void VIADDI(const EeCoreInstruction inst) const;
	void VIAND(const EeCoreInstruction inst) const;
	void VIOR(const EeCoreInstruction inst) const;
	void VISUB(const EeCoreInstruction inst) const;
	void VMOVE(const EeCoreInstruction inst) const;
	void VMFIR(const EeCoreInstruction inst) const;
	void VMTIR(const EeCoreInstruction inst) const;
	void VMR32(const EeCoreInstruction inst) const;
	void VLQD(const EeCoreInstruction inst) const;
	void VLQI(const EeCoreInstruction inst) const;
	void VSQD(const EeCoreInstruction inst) const;
	void VSQI(const EeCoreInstruction inst) const;
	void VILWR(const EeCoreInstruction inst) const;
	void VISWR(const EeCoreInstruction inst) const;
	void VRINIT(const EeCoreInstruction inst) const;
	void VRGET(const EeCoreInstruction inst) const;
	void VRNEXT(const EeCoreInstruction inst) const;
	void VRXOR(const EeCoreInstruction inst) const;
	void VWAITQ(const EeCoreInstruction inst) const;

	/// Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index. 
	/// Sometimes there are differences in the instruction mnemonics within the manual. 
	/// Alternative names have been provided as comments against the array function used.
	void(CEeCoreInterpreter::* EECORE_INSTRUCTION_TABLE[Constants::EE::EECore::NUMBER_INSTRUCTIONS])(const EeCoreInstruction inst) const =
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

	/////////////////////////////
	// Exception Functionality //
	/////////////////////////////

	/// Handles a given exception by running the general exception handler (level 1 or 2) based on the exception properties defined.
	void handle_exception(const EeCoreException exception) const;

	/// Checks if any of the interrupt lines have an IRQ pending, and raises an interrupt exception.
	void handle_interrupt_check() const;

#if defined(BUILD_DEBUG)
	///  Debug for counting the number of exceptions handled.
	mutable size_t DEBUG_HANDLED_EXCEPTION_COUNT = 0;
#endif

	/// The level 1 or level 2 exception handler, which is called by the base handle_exception() function.
	/// They have been adapted from the code in the EE Core Users Manual page 91 & 92.
	void handle_exception_l1(const EeCoreException exception) const;
	void handle_exception_l2(const EeCoreException exception) const;

	///////////////////////
	// MMU Functionality //
	///////////////////////

	/// Internal types used within/to access MMU.
	enum MmuError { ADDRESS, TLB_REFILL, TLB_INVALID, TLB_MODIFIED };
	enum MmuAccess { READ, WRITE };

	/// Converts a given MmuError and MmuAccess to an EeCoreException and handles it (through handle_exception()).
	/// Also sets the required COP0 TLB information.
	/// Called internally from translate_vaddress().
	void handle_mmu_error(const uptr address, const MmuAccess access, const MmuError error, const sword tlb_entry_index) const;

	/// Performs a lookup from the given virtual address and access type.
	/// Returns if an error occured, indicating if the instruction that called should return early (error = true, no error = false).
	/// The physical address calculated is stored in physical_address.
	/// There are 4 associated stages (see diagram on EE Core Users Manual page 122):
	/// Stage 1 tests the operating context of the CPU and checks if the address is invalid.
	/// Stage 2 performs a TLB lookup and checks the ASID and G bits.
	/// Stage 3 tests the valid and dirty flags, and determines if the VPN is for the even or odd PFN.
	/// Stage 4 calculates the final physical address.
	bool translate_vaddress(const uptr virtual_address, const MmuAccess access, uptr & physical_address) const;
};