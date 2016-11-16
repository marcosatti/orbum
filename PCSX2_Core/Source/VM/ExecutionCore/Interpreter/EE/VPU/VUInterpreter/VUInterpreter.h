#pragma once

#include "Common/Global/Globals.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"

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

	/*
	Context of which VU this system is processing.
	*/
	const u32 mVUUnitIndex;

	/*
	Upper instruction functions. There are 59 instructions total.
	See VU Users Manual page 35.
	*/
	void ABS();
	void ADD();
	void ADDi();
	void ADDq();
	void ADDbc();
	void ADDA();
	void ADDAi();
	void ADDAq();
	void ADDAbc();
	void SUB();
	void SUBi();
	void SUBq();
	void SUBbc();
	void SUBA();
	void SUBAi();
	void SUBAq();
	void SUBAbc();
	void MUL();
	void MULi();
	void MULq();
	void MULbc();
	void MULA();
	void MULAi();
	void MULAq();
	void MULAbc();
	void MADD();
	void MADDi();
	void MADDq();
	void MADDbc();
	void MADDA();
	void MADDAi();
	void MADDAq();
	void MADDAbc();
	void MSUB();
	void MSUBi();
	void MSUBq();
	void MSUBbc();
	void MSUBA();
	void MSUBAi();
	void MSUBAq();
	void MSUBAbc();
	void MAX();
	void MAXi();
	void MAXbc();
	void MINI();
	void MINIi();
	void MINIbc();
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

};