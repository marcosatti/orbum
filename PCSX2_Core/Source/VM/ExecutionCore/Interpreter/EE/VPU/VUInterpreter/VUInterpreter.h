#pragma once

#include "Common/Global/Globals.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "PS2Constants/PS2Constants.h"
#include "PS2Resources/EE/VPU/VU/Types/VUInstruction_t.h"

class VUInterpreter : public VMExecutionCoreComponent
{
public:
	explicit VUInterpreter(VMMain * vmMain, u32 vuUnitIndex);
	~VUInterpreter();

	/*
	See VMExecutionCoreComponent for documentation.
	*/
	std::vector<ClockSource_t> mClockSources;
	const std::vector<ClockSource_t> & getClockSources() override;

	/*
	TODO: implement.
	*/
	s64 executionStep(const ClockSource_t & clockSource) override;

private:
	// The EE Core delegates the COP2 instructions with the V* prefix to the VUInterpreter system, to avoid writing duplicate code.
	// Need to allow it access to the individual instruction functions below.
	friend class EECoreInterpreter;

	/*
	Context of which VU this system is processing.
	*/
	const u32 mVUUnitIndex;

	/*
	Temporary holder for the current instruction, while the operation to perform is being determined.
	It is also used while an instruction is being performed.
	TODO: make thread safe, need to make sure if COP2 (macro) instruction is running it doesnt interfere with micro instruction running.
	*/
	VUInstruction_t mInstruction;

	/*
	Upper instruction functions. There are 59 instructions total.
	However, the 'bc' class instructions are split up into a base function and individual field x, y, z, w (0, 1, 2, 3) 
	 functions, in order to support the instruction table lookup, and support the EE Core (COP2) function calls.
	Only the individual field functions are called from the instruction lookup, which call the base function with the field number parameter.
	See VU Users Manual page 35.
	*/
	void ABS();
	void ADD();
	void ADDi();
	void ADDq();
	void ADDbc(const u8 & idx);
	void ADDbc_0();
	void ADDbc_1();
	void ADDbc_2();
	void ADDbc_3();
	void ADDA();
	void ADDAi();
	void ADDAq();
	void ADDAbc(const u8 & idx);
	void ADDAbc_0();
	void ADDAbc_1();
	void ADDAbc_2();
	void ADDAbc_3();
	void SUB();
	void SUBi();
	void SUBq();
	void SUBbc(const u8 & idx);
	void SUBbc_0();
	void SUBbc_1();
	void SUBbc_2();
	void SUBbc_3();
	void SUBA();
	void SUBAi();
	void SUBAq();
	void SUBAbc(const u8 & idx);
	void SUBAbc_0();
	void SUBAbc_1();
	void SUBAbc_2();
	void SUBAbc_3();
	void MUL();
	void MULi();
	void MULq();
	void MULbc(const u8 & idx);
	void MULbc_0();
	void MULbc_1();
	void MULbc_2();
	void MULbc_3();
	void MULA();
	void MULAi();
	void MULAq();
	void MULAbc(const u8 & idx);
	void MULAbc_0();
	void MULAbc_1();
	void MULAbc_2();
	void MULAbc_3();
	void MADD();
	void MADDi();
	void MADDq();
	void MADDbc(const u8 & idx);
	void MADDbc_0();
	void MADDbc_1();
	void MADDbc_2();
	void MADDbc_3();
	void MADDA();
	void MADDAi();
	void MADDAq();
	void MADDAbc(const u8 & idx);
	void MADDAbc_0();
	void MADDAbc_1();
	void MADDAbc_2();
	void MADDAbc_3();
	void MSUB();
	void MSUBi();
	void MSUBq();
	void MSUBbc(const u8 & idx);
	void MSUBbc_0();
	void MSUBbc_1();
	void MSUBbc_2();
	void MSUBbc_3();
	void MSUBA();
	void MSUBAi();
	void MSUBAq();
	void MSUBAbc(const u8 & idx);
	void MSUBAbc_0();
	void MSUBAbc_1();
	void MSUBAbc_2();
	void MSUBAbc_3();
	void MAX();
	void MAXi();
	void MAXbc(const u8 & idx);
	void MAXbc_0();
	void MAXbc_1();
	void MAXbc_2();
	void MAXbc_3();
	void MINI();
	void MINIi();
	void MINIbc(const u8 & idx);
	void MINIbc_0();
	void MINIbc_1();
	void MINIbc_2();
	void MINIbc_3();
	void OPMULA();
	void OPMSUB();
	void NOP();
	void FTOI0();
	void FTOI4();
	void FTOI12();
	void FTOI15();
	void ITOF0();
	void ITOF4();
	void ITOF12();
	void ITOF15();
	void CLIP();

	/*
	Lower instruction functions. There are 69 instructions total.
	See VU Users Manual page 37.
	*/
	void DIV();
	void SQRT();
	void RSQRT();
	void IADD();
	void IADDI();
	void IADDIU();
	void IAND();
	void IOR();
	void ISUB();
	void ISUBIU();
	void MOVE();
	void MFIR();
	void MTIR();
	void MR32();
	void LQ();
	void LQD();
	void LQI();
	void SQ();
	void SQD();
	void SQI();
	void ILW();
	void ISW();
	void ILWR();
	void ISWR();
	void LOI();
	void RINIT();
	void RGET();
	void RNEXT();
	void RXOR();
	void WAITQ();
	void FSAND();
	void FSEQ();
	void FSOR();
	void FSSET();
	void FMAND();
	void FMEQ();
	void FMOR();
	void FCAND();
	void FCEQ();
	void FCOR();
	void FCSET();
	void FCGET();
	void IBEQ();
	void IBGEZ();
	void IBGTZ();
	void IBLEZ();
	void IBLTZ();
	void IBNE();
	void B();
	void BAL();
	void JR();
	void JALR();
	void MFP();
	void WAITP();
	void ESADD();
	void ERSADD();
	void ELENG();
	void ERLENG();
	void EATANxy();
	void EATANxz();
	void ESUM();
	void ERCPR();
	void ESQRT();
	void ERSQRT();
	void ESIN();
	void EATAN();
	void EEXP();
	void XGKICK();
	void XTOP();
	void XITOP();

	/*
	Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index.
	See VUInstructionTable and "VU Instruction Implementation Register.xlsm" for more details.
	
	As mentioned above, the 'bc' class instructions are split up into the individual fields for x, y, z, w (0, 1, 2, 3) and listed instead of a generic bc-type instruction.
	*/
	void(VUInterpreter::*const VU_INSTRUCTION_TABLE[PS2Constants::EE::VPU::VU::NUMBER_VU_INSTRUCTIONS])() =
	{
	};
};
