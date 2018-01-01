#pragma once

#include "Controller/CController.hpp"

#include "Resources/Ee/Vpu/Vu/VuUnits.hpp"
#include "Resources/Ee/Vpu/Vu/VuInstruction.hpp"

class Core;

/// The VU0/1 interpreter.
class CVuInterpreter : public CController
{
public:
	CVuInterpreter(Core * core);

	void handle_event(const ControllerEvent & event) const override;
	
	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us) const;

	/// Steps through the VU core state, executing one macro and one micro instruction.
	int time_step(const int ticks_available) const;

	//////////////////////////
	// Common Functionality //
	//////////////////////////

#if defined(BUILD_DEBUG)
	// Debug loop counter.
	mutable size_t DEBUG_LOOP_COUNTER = 0;
#endif

	///////////////////////////////
	// Instruction Functionality //
	///////////////////////////////

	/// Upper instruction functions. There are 59 instructions total.
	/// However, the 'bc' class instructions are split up into a base function and individual field x, y, z, w (0, 1, 2, 3) 
	/// functions, in order to support the instruction table lookup, and support the EE Core (COP2) function calls.
	/// Only the individual field functions are called from the instruction lookup, which call the base function with the field number parameter.
	/// See VU Users Manual page 35.
	void ABS(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADD(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDi(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDq(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void ADDbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDA(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDAi(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDAq(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDAbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void ADDAbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDAbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDAbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void ADDAbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUB(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBi(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBq(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void SUBbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBA(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBAi(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBAq(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBAbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void SUBAbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBAbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBAbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void SUBAbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void MUL(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULi(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULq(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void MULbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULA(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULAi(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULAq(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULAbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void MULAbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULAbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULAbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void MULAbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADD(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDi(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDq(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void MADDbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDA(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDAi(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDAq(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDAbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void MADDAbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDAbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDAbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void MADDAbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUB(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBi(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBq(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void MSUBbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBA(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBAi(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBAq(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBAbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void MSUBAbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBAbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBAbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void MSUBAbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void MAX(VuUnit_Base * unit, const VuInstruction inst) const;
	void MAXi(VuUnit_Base * unit, const VuInstruction inst) const;
	void MAXbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void MAXbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void MAXbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void MAXbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void MAXbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void MINI(VuUnit_Base * unit, const VuInstruction inst) const;
	void MINIi(VuUnit_Base * unit, const VuInstruction inst) const;
	void MINIbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const;
	void MINIbc_0(VuUnit_Base * unit, const VuInstruction inst) const;
	void MINIbc_1(VuUnit_Base * unit, const VuInstruction inst) const;
	void MINIbc_2(VuUnit_Base * unit, const VuInstruction inst) const;
	void MINIbc_3(VuUnit_Base * unit, const VuInstruction inst) const;
	void OPMULA(VuUnit_Base * unit, const VuInstruction inst) const;
	void OPMSUB(VuUnit_Base * unit, const VuInstruction inst) const;
	void NOP(VuUnit_Base * unit, const VuInstruction inst) const;
	void FTOI0(VuUnit_Base * unit, const VuInstruction inst) const;
	void FTOI4(VuUnit_Base * unit, const VuInstruction inst) const;
	void FTOI12(VuUnit_Base * unit, const VuInstruction inst) const;
	void FTOI15(VuUnit_Base * unit, const VuInstruction inst) const;
	void ITOF0(VuUnit_Base * unit, const VuInstruction inst) const;
	void ITOF4(VuUnit_Base * unit, const VuInstruction inst) const;
	void ITOF12(VuUnit_Base * unit, const VuInstruction inst) const;
	void ITOF15(VuUnit_Base * unit, const VuInstruction inst) const;
	void CLIP(VuUnit_Base * unit, const VuInstruction inst) const;

	/// Lower instruction functions. There are 69 instructions total.
	/// See VU Users Manual page 37.
	void DIV(VuUnit_Base * unit, const VuInstruction inst) const;
	void SQRT(VuUnit_Base * unit, const VuInstruction inst) const;
	void RSQRT(VuUnit_Base * unit, const VuInstruction inst) const;
	void IADD(VuUnit_Base * unit, const VuInstruction inst) const;
	void IADDI(VuUnit_Base * unit, const VuInstruction inst) const;
	void IADDIU(VuUnit_Base * unit, const VuInstruction inst) const;
	void IAND(VuUnit_Base * unit, const VuInstruction inst) const;
	void IOR(VuUnit_Base * unit, const VuInstruction inst) const;
	void ISUB(VuUnit_Base * unit, const VuInstruction inst) const;
	void ISUBIU(VuUnit_Base * unit, const VuInstruction inst) const;
	void MOVE(VuUnit_Base * unit, const VuInstruction inst) const;
	void MFIR(VuUnit_Base * unit, const VuInstruction inst) const;
	void MTIR(VuUnit_Base * unit, const VuInstruction inst) const;
	void MR32(VuUnit_Base * unit, const VuInstruction inst) const;
	void LQ(VuUnit_Base * unit, const VuInstruction inst) const;
	void LQD(VuUnit_Base * unit, const VuInstruction inst) const;
	void LQI(VuUnit_Base * unit, const VuInstruction inst) const;
	void SQ(VuUnit_Base * unit, const VuInstruction inst) const;
	void SQD(VuUnit_Base * unit, const VuInstruction inst) const;
	void SQI(VuUnit_Base * unit, const VuInstruction inst) const;
	void ILW(VuUnit_Base * unit, const VuInstruction inst) const;
	void ISW(VuUnit_Base * unit, const VuInstruction inst) const;
	void ILWR(VuUnit_Base * unit, const VuInstruction inst) const;
	void ISWR(VuUnit_Base * unit, const VuInstruction inst) const;
	void LOI(VuUnit_Base * unit, const VuInstruction inst) const;
	void RINIT(VuUnit_Base * unit, const VuInstruction inst) const;
	void RGET(VuUnit_Base * unit, const VuInstruction inst) const;
	void RNEXT(VuUnit_Base * unit, const VuInstruction inst) const;
	void RXOR(VuUnit_Base * unit, const VuInstruction inst) const;
	void WAITQ(VuUnit_Base * unit, const VuInstruction inst) const;
	void FSAND(VuUnit_Base * unit, const VuInstruction inst) const;
	void FSEQ(VuUnit_Base * unit, const VuInstruction inst) const;
	void FSOR(VuUnit_Base * unit, const VuInstruction inst) const;
	void FSSET(VuUnit_Base * unit, const VuInstruction inst) const;
	void FMAND(VuUnit_Base * unit, const VuInstruction inst) const;
	void FMEQ(VuUnit_Base * unit, const VuInstruction inst) const;
	void FMOR(VuUnit_Base * unit, const VuInstruction inst) const;
	void FCAND(VuUnit_Base * unit, const VuInstruction inst) const;
	void FCEQ(VuUnit_Base * unit, const VuInstruction inst) const;
	void FCOR(VuUnit_Base * unit, const VuInstruction inst) const;
	void FCSET(VuUnit_Base * unit, const VuInstruction inst) const;
	void FCGET(VuUnit_Base * unit, const VuInstruction inst) const;
	void IBEQ(VuUnit_Base * unit, const VuInstruction inst) const;
	void IBGEZ(VuUnit_Base * unit, const VuInstruction inst) const;
	void IBGTZ(VuUnit_Base * unit, const VuInstruction inst) const;
	void IBLEZ(VuUnit_Base * unit, const VuInstruction inst) const;
	void IBLTZ(VuUnit_Base * unit, const VuInstruction inst) const;
	void IBNE(VuUnit_Base * unit, const VuInstruction inst) const;
	void B(VuUnit_Base * unit, const VuInstruction inst) const;
	void BAL(VuUnit_Base * unit, const VuInstruction inst) const;
	void JR(VuUnit_Base * unit, const VuInstruction inst) const;
	void JALR(VuUnit_Base * unit, const VuInstruction inst) const;
	void MFP(VuUnit_Base * unit, const VuInstruction inst) const;
	void WAITP(VuUnit_Base * unit, const VuInstruction inst) const;
	void ESADD(VuUnit_Base * unit, const VuInstruction inst) const;
	void ERSADD(VuUnit_Base * unit, const VuInstruction inst) const;
	void ELENG(VuUnit_Base * unit, const VuInstruction inst) const;
	void ERLENG(VuUnit_Base * unit, const VuInstruction inst) const;
	void EATANxy(VuUnit_Base * unit, const VuInstruction inst) const;
	void EATANxz(VuUnit_Base * unit, const VuInstruction inst) const;
	void ESUM(VuUnit_Base * unit, const VuInstruction inst) const;
	void ERCPR(VuUnit_Base * unit, const VuInstruction inst) const;
	void ESQRT(VuUnit_Base * unit, const VuInstruction inst) const;
	void ERSQRT(VuUnit_Base * unit, const VuInstruction inst) const;
	void ESIN(VuUnit_Base * unit, const VuInstruction inst) const;
	void EATAN(VuUnit_Base * unit, const VuInstruction inst) const;
	void EEXP(VuUnit_Base * unit, const VuInstruction inst) const;
	void XGKICK(VuUnit_Base * unit, const VuInstruction inst) const;
	void XTOP(VuUnit_Base * unit, const VuInstruction inst) const;
	void XITOP(VuUnit_Base * unit, const VuInstruction inst) const;

	void(CVuInterpreter::* VU_INSTRUCTION_TABLE[Constants::EE::VPU::VU::NUMBER_VU_INSTRUCTIONS])(VuUnit_Base * unit, const VuInstruction inst) const =
	{
	};
};
