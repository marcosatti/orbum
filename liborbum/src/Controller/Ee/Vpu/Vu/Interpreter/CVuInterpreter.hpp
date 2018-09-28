#pragma once

#include "Controller/Ee/Vpu/Vu/CVu.hpp"
#include "Resources/Ee/Vpu/Vu/VuInstruction.hpp"
#include "Resources/Ee/Vpu/Vu/VuInstructionDecoder.hpp"
#include "Resources/Ee/Vpu/Vu/VuUnits.hpp"

class Core;

/// The VU0/1 interpreter.
class CVuInterpreter : public CVu
{
public:
    CVuInterpreter(Core* core);

    /// Steps through the VU core state, executing one macro and one micro instruction.
    int time_step(const int ticks_available) override;

    //////////////////////////
    // Common Functionality //
    //////////////////////////

#if defined(BUILD_DEBUG)
    // Debug loop counter.
    size_t DEBUG_LOOP_COUNTER = 0;
#endif

    ///////////////////////////////
    // Instruction Functionality //
    ///////////////////////////////

    /// Upper instruction functions. There are 59 instructions total.
    /// However, the 'bc' class instructions are split up into a base function and individual field x, y, z, w (0, 1, 2, 3)
    /// functions, in order to support the instruction table lookup, and support the EE Core (COP2) function calls.
    /// Only the individual field functions are called from the instruction lookup, which call the base function with the field number parameter.
    /// See VU Users Manual page 35.
    void ABS(VuUnit_Base* unit, const VuInstruction inst);
    void ADD(VuUnit_Base* unit, const VuInstruction inst);
    void ADDi(VuUnit_Base* unit, const VuInstruction inst);
    void ADDq(VuUnit_Base* unit, const VuInstruction inst);
    void ADDbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void ADDbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void ADDbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void ADDbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void ADDbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void ADDA(VuUnit_Base* unit, const VuInstruction inst);
    void ADDAi(VuUnit_Base* unit, const VuInstruction inst);
    void ADDAq(VuUnit_Base* unit, const VuInstruction inst);
    void ADDAbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void ADDAbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void ADDAbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void ADDAbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void ADDAbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void SUB(VuUnit_Base* unit, const VuInstruction inst);
    void SUBi(VuUnit_Base* unit, const VuInstruction inst);
    void SUBq(VuUnit_Base* unit, const VuInstruction inst);
    void SUBbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void SUBbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void SUBbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void SUBbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void SUBbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void SUBA(VuUnit_Base* unit, const VuInstruction inst);
    void SUBAi(VuUnit_Base* unit, const VuInstruction inst);
    void SUBAq(VuUnit_Base* unit, const VuInstruction inst);
    void SUBAbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void SUBAbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void SUBAbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void SUBAbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void SUBAbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void MUL(VuUnit_Base* unit, const VuInstruction inst);
    void MULi(VuUnit_Base* unit, const VuInstruction inst);
    void MULq(VuUnit_Base* unit, const VuInstruction inst);
    void MULbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void MULbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void MULbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void MULbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void MULbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void MULA(VuUnit_Base* unit, const VuInstruction inst);
    void MULAi(VuUnit_Base* unit, const VuInstruction inst);
    void MULAq(VuUnit_Base* unit, const VuInstruction inst);
    void MULAbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void MULAbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void MULAbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void MULAbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void MULAbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void MADD(VuUnit_Base* unit, const VuInstruction inst);
    void MADDi(VuUnit_Base* unit, const VuInstruction inst);
    void MADDq(VuUnit_Base* unit, const VuInstruction inst);
    void MADDbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void MADDbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void MADDbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void MADDbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void MADDbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void MADDA(VuUnit_Base* unit, const VuInstruction inst);
    void MADDAi(VuUnit_Base* unit, const VuInstruction inst);
    void MADDAq(VuUnit_Base* unit, const VuInstruction inst);
    void MADDAbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void MADDAbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void MADDAbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void MADDAbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void MADDAbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void MSUB(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBi(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBq(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void MSUBbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBA(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBAi(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBAq(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBAbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void MSUBAbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBAbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBAbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void MSUBAbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void MAX(VuUnit_Base* unit, const VuInstruction inst);
    void MAXi(VuUnit_Base* unit, const VuInstruction inst);
    void MAXbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void MAXbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void MAXbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void MAXbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void MAXbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void MINI(VuUnit_Base* unit, const VuInstruction inst);
    void MINIi(VuUnit_Base* unit, const VuInstruction inst);
    void MINIbc(VuUnit_Base* unit, const VuInstruction inst, const int idx);
    void MINIbc_0(VuUnit_Base* unit, const VuInstruction inst);
    void MINIbc_1(VuUnit_Base* unit, const VuInstruction inst);
    void MINIbc_2(VuUnit_Base* unit, const VuInstruction inst);
    void MINIbc_3(VuUnit_Base* unit, const VuInstruction inst);
    void OPMULA(VuUnit_Base* unit, const VuInstruction inst);
    void OPMSUB(VuUnit_Base* unit, const VuInstruction inst);
    void NOP(VuUnit_Base* unit, const VuInstruction inst);
    void FTOI0(VuUnit_Base* unit, const VuInstruction inst);
    void FTOI4(VuUnit_Base* unit, const VuInstruction inst);
    void FTOI12(VuUnit_Base* unit, const VuInstruction inst);
    void FTOI15(VuUnit_Base* unit, const VuInstruction inst);
    void ITOF0(VuUnit_Base* unit, const VuInstruction inst);
    void ITOF4(VuUnit_Base* unit, const VuInstruction inst);
    void ITOF12(VuUnit_Base* unit, const VuInstruction inst);
    void ITOF15(VuUnit_Base* unit, const VuInstruction inst);
    void CLIP(VuUnit_Base* unit, const VuInstruction inst);

    /// Lower instruction functions. There are 69 instructions total.
    /// See VU Users Manual page 37.
    void DIV(VuUnit_Base* unit, const VuInstruction inst);
    void SQRT(VuUnit_Base* unit, const VuInstruction inst);
    void RSQRT(VuUnit_Base* unit, const VuInstruction inst);
    void IADD(VuUnit_Base* unit, const VuInstruction inst);
    void IADDI(VuUnit_Base* unit, const VuInstruction inst);
    void IADDIU(VuUnit_Base* unit, const VuInstruction inst);
    void IAND(VuUnit_Base* unit, const VuInstruction inst);
    void IOR(VuUnit_Base* unit, const VuInstruction inst);
    void ISUB(VuUnit_Base* unit, const VuInstruction inst);
    void ISUBIU(VuUnit_Base* unit, const VuInstruction inst);
    void MOVE(VuUnit_Base* unit, const VuInstruction inst);
    void MFIR(VuUnit_Base* unit, const VuInstruction inst);
    void MTIR(VuUnit_Base* unit, const VuInstruction inst);
    void MR32(VuUnit_Base* unit, const VuInstruction inst);
    void LQ(VuUnit_Base* unit, const VuInstruction inst);
    void LQD(VuUnit_Base* unit, const VuInstruction inst);
    void LQI(VuUnit_Base* unit, const VuInstruction inst);
    void SQ(VuUnit_Base* unit, const VuInstruction inst);
    void SQD(VuUnit_Base* unit, const VuInstruction inst);
    void SQI(VuUnit_Base* unit, const VuInstruction inst);
    void ILW(VuUnit_Base* unit, const VuInstruction inst);
    void ISW(VuUnit_Base* unit, const VuInstruction inst);
    void ILWR(VuUnit_Base* unit, const VuInstruction inst);
    void ISWR(VuUnit_Base* unit, const VuInstruction inst);
    void LOI(VuUnit_Base* unit, const VuInstruction inst);
    void RINIT(VuUnit_Base* unit, const VuInstruction inst);
    void RGET(VuUnit_Base* unit, const VuInstruction inst);
    void RNEXT(VuUnit_Base* unit, const VuInstruction inst);
    void RXOR(VuUnit_Base* unit, const VuInstruction inst);
    void WAITQ(VuUnit_Base* unit, const VuInstruction inst);
    void FSAND(VuUnit_Base* unit, const VuInstruction inst);
    void FSEQ(VuUnit_Base* unit, const VuInstruction inst);
    void FSOR(VuUnit_Base* unit, const VuInstruction inst);
    void FSSET(VuUnit_Base* unit, const VuInstruction inst);
    void FMAND(VuUnit_Base* unit, const VuInstruction inst);
    void FMEQ(VuUnit_Base* unit, const VuInstruction inst);
    void FMOR(VuUnit_Base* unit, const VuInstruction inst);
    void FCAND(VuUnit_Base* unit, const VuInstruction inst);
    void FCEQ(VuUnit_Base* unit, const VuInstruction inst);
    void FCOR(VuUnit_Base* unit, const VuInstruction inst);
    void FCSET(VuUnit_Base* unit, const VuInstruction inst);
    void FCGET(VuUnit_Base* unit, const VuInstruction inst);
    void IBEQ(VuUnit_Base* unit, const VuInstruction inst);
    void IBGEZ(VuUnit_Base* unit, const VuInstruction inst);
    void IBGTZ(VuUnit_Base* unit, const VuInstruction inst);
    void IBLEZ(VuUnit_Base* unit, const VuInstruction inst);
    void IBLTZ(VuUnit_Base* unit, const VuInstruction inst);
    void IBNE(VuUnit_Base* unit, const VuInstruction inst);
    void B(VuUnit_Base* unit, const VuInstruction inst);
    void BAL(VuUnit_Base* unit, const VuInstruction inst);
    void JR(VuUnit_Base* unit, const VuInstruction inst);
    void JALR(VuUnit_Base* unit, const VuInstruction inst);
    void MFP(VuUnit_Base* unit, const VuInstruction inst);
    void WAITP(VuUnit_Base* unit, const VuInstruction inst);
    void ESADD(VuUnit_Base* unit, const VuInstruction inst);
    void ERSADD(VuUnit_Base* unit, const VuInstruction inst);
    void ELENG(VuUnit_Base* unit, const VuInstruction inst);
    void ERLENG(VuUnit_Base* unit, const VuInstruction inst);
    void EATANxy(VuUnit_Base* unit, const VuInstruction inst);
    void EATANxz(VuUnit_Base* unit, const VuInstruction inst);
    void ESUM(VuUnit_Base* unit, const VuInstruction inst);
    void ERCPR(VuUnit_Base* unit, const VuInstruction inst);
    void ESQRT(VuUnit_Base* unit, const VuInstruction inst);
    void ERSQRT(VuUnit_Base* unit, const VuInstruction inst);
    void ESIN(VuUnit_Base* unit, const VuInstruction inst);
    void EATAN(VuUnit_Base* unit, const VuInstruction inst);
    void EEXP(VuUnit_Base* unit, const VuInstruction inst);
    void XGKICK(VuUnit_Base* unit, const VuInstruction inst);
    void XTOP(VuUnit_Base* unit, const VuInstruction inst);
    void XITOP(VuUnit_Base* unit, const VuInstruction inst);

    void (CVuInterpreter::*VU_INSTRUCTION_TABLE[Constants::EE::VPU::VU::NUMBER_VU_INSTRUCTIONS])(VuUnit_Base* unit, const VuInstruction inst) =
    {
        &CVuInterpreter::ABS,
        &CVuInterpreter::ADD,
        &CVuInterpreter::ADDi,
        &CVuInterpreter::ADDq,
        &CVuInterpreter::ADDbc_0,
        &CVuInterpreter::ADDbc_1,
        &CVuInterpreter::ADDbc_2,
        &CVuInterpreter::ADDbc_3,
        &CVuInterpreter::ADDA,
        &CVuInterpreter::ADDAi,
        &CVuInterpreter::ADDAq,
        &CVuInterpreter::ADDAbc_0,
        &CVuInterpreter::ADDAbc_1,
        &CVuInterpreter::ADDAbc_2,
        &CVuInterpreter::ADDAbc_3,
        &CVuInterpreter::SUB,
        &CVuInterpreter::SUBi,
        &CVuInterpreter::SUBq,
        &CVuInterpreter::SUBbc_0,
        &CVuInterpreter::SUBbc_1,
        &CVuInterpreter::SUBbc_2,
        &CVuInterpreter::SUBbc_3,
        &CVuInterpreter::SUBA,
        &CVuInterpreter::SUBAi,
        &CVuInterpreter::SUBAq,
        &CVuInterpreter::SUBAbc_0,
        &CVuInterpreter::SUBAbc_1,
        &CVuInterpreter::SUBAbc_2,
        &CVuInterpreter::SUBAbc_3,
        &CVuInterpreter::MUL,
        &CVuInterpreter::MULi,
        &CVuInterpreter::MULq,
        &CVuInterpreter::MULbc_0,
        &CVuInterpreter::MULbc_1,
        &CVuInterpreter::MULbc_2,
        &CVuInterpreter::MULbc_3,
        &CVuInterpreter::MULA,
        &CVuInterpreter::MULAi,
        &CVuInterpreter::MULAq,
        &CVuInterpreter::MULAbc_0,
        &CVuInterpreter::MULAbc_1,
        &CVuInterpreter::MULAbc_2,
        &CVuInterpreter::MULAbc_3,
        &CVuInterpreter::MADD,
        &CVuInterpreter::MADDi,
        &CVuInterpreter::MADDq,
        &CVuInterpreter::MADDbc_0,
        &CVuInterpreter::MADDbc_1,
        &CVuInterpreter::MADDbc_2,
        &CVuInterpreter::MADDbc_3,
        &CVuInterpreter::MADDA,
        &CVuInterpreter::MADDAi,
        &CVuInterpreter::MADDAq,
        &CVuInterpreter::MADDAbc_0,
        &CVuInterpreter::MADDAbc_1,
        &CVuInterpreter::MADDAbc_2,
        &CVuInterpreter::MADDAbc_3,
        &CVuInterpreter::MSUB,
        &CVuInterpreter::MSUBi,
        &CVuInterpreter::MSUBq,
        &CVuInterpreter::MSUBbc_0,
        &CVuInterpreter::MSUBbc_1,
        &CVuInterpreter::MSUBbc_2,
        &CVuInterpreter::MSUBbc_3,
        &CVuInterpreter::MSUBA,
        &CVuInterpreter::MSUBAi,
        &CVuInterpreter::MSUBAq,
        &CVuInterpreter::MSUBAbc_0,
        &CVuInterpreter::MSUBAbc_1,
        &CVuInterpreter::MSUBAbc_2,
        &CVuInterpreter::MSUBAbc_3,
        &CVuInterpreter::MAX,
        &CVuInterpreter::MAXi,
        &CVuInterpreter::MAXbc_0,
        &CVuInterpreter::MAXbc_1,
        &CVuInterpreter::MAXbc_2,
        &CVuInterpreter::MAXbc_3,
        &CVuInterpreter::MINI,
        &CVuInterpreter::MINIi,
        &CVuInterpreter::MINIbc_0,
        &CVuInterpreter::MINIbc_1,
        &CVuInterpreter::MINIbc_2,
        &CVuInterpreter::MINIbc_3,
        &CVuInterpreter::OPMULA,
        &CVuInterpreter::OPMSUB,
        &CVuInterpreter::NOP,
        &CVuInterpreter::FTOI0,
        &CVuInterpreter::FTOI4,
        &CVuInterpreter::FTOI12,
        &CVuInterpreter::FTOI15,
        &CVuInterpreter::ITOF0,
        &CVuInterpreter::ITOF4,
        &CVuInterpreter::ITOF12,
        &CVuInterpreter::ITOF15,
        &CVuInterpreter::CLIP,
        &CVuInterpreter::DIV,
        &CVuInterpreter::SQRT,
        &CVuInterpreter::RSQRT,
        &CVuInterpreter::IADD,
        &CVuInterpreter::IADDI,
        &CVuInterpreter::IADDIU,
        &CVuInterpreter::IAND,
        &CVuInterpreter::IOR,
        &CVuInterpreter::ISUB,
        &CVuInterpreter::ISUBIU,
        &CVuInterpreter::MOVE,
        &CVuInterpreter::MFIR,
        &CVuInterpreter::MTIR,
        &CVuInterpreter::MR32,
        &CVuInterpreter::LQ,
        &CVuInterpreter::LQD,
        &CVuInterpreter::LQI,
        &CVuInterpreter::SQ,
        &CVuInterpreter::SQD,
        &CVuInterpreter::SQI,
        &CVuInterpreter::ILW,
        &CVuInterpreter::ISW,
        &CVuInterpreter::ILWR,
        &CVuInterpreter::ISWR,
        &CVuInterpreter::RINIT,
        &CVuInterpreter::RGET,
        &CVuInterpreter::RNEXT,
        &CVuInterpreter::RXOR,
        &CVuInterpreter::WAITQ,
        &CVuInterpreter::FSAND,
        &CVuInterpreter::FSEQ,
        &CVuInterpreter::FSOR,
        &CVuInterpreter::FSSET,
        &CVuInterpreter::FMAND,
        &CVuInterpreter::FMEQ,
        &CVuInterpreter::FMOR,
        &CVuInterpreter::FCAND,
        &CVuInterpreter::FCEQ,
        &CVuInterpreter::FCOR,
        &CVuInterpreter::FCSET,
        &CVuInterpreter::FCGET,
        &CVuInterpreter::IBEQ,
        &CVuInterpreter::IBGEZ,
        &CVuInterpreter::IBGTZ,
        &CVuInterpreter::IBLEZ,
        &CVuInterpreter::IBLTZ,
        &CVuInterpreter::IBNE,
        &CVuInterpreter::B,
        &CVuInterpreter::BAL,
        &CVuInterpreter::JR,
        &CVuInterpreter::JALR,
        &CVuInterpreter::MFP,
        &CVuInterpreter::WAITP,
        &CVuInterpreter::ESADD,
        &CVuInterpreter::ERSADD,
        &CVuInterpreter::ELENG,
        &CVuInterpreter::ERLENG,
        &CVuInterpreter::EATANxy,
        &CVuInterpreter::EATANxz,
        &CVuInterpreter::ESUM,
        &CVuInterpreter::ERCPR,
        &CVuInterpreter::ESQRT,
        &CVuInterpreter::ERSQRT,
        &CVuInterpreter::ESIN,
        &CVuInterpreter::EATAN,
        &CVuInterpreter::EEXP,
        &CVuInterpreter::XGKICK,
        &CVuInterpreter::XTOP,
        &CVuInterpreter::XITOP
    };

private:
    bool check_data_hazard(VuUnit_Base* unit, const VuInstructionDecoder& decoder) const;
    
    int execute_upper_instruction(VuUnit_Base* unit, VuInstruction inst, MipsInstructionInfo info, const VuInstructionDecoder& decoder);
    int execute_lower_instruction(VuUnit_Base* unit, VuInstruction inst, MipsInstructionInfo info, const VuInstructionDecoder& decoder);
};
