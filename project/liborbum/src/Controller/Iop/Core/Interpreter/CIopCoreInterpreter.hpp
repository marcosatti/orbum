#pragma once

#include "Common/Constants.hpp"

#include "Controller/Iop/Core/CIopCore.hpp"

#include "Resources/Iop/Core/IopCoreInstruction.hpp"

class Core;

// The IOP Interpreter. This is similar to a PS1 system - as such you can find resources on the internet for the PS1.
// The clock speed of the IOP is roughly 1/8th that of the EE Core (~36 MHz, increased from the original PSX clock speed of ~33.8 MHz).
// No official documentation, but there is resources available on the internet documenting the R3000 and other parts.
class CIopCoreInterpreter : public CIopCore
{
public:
	CIopCoreInterpreter(Core * core);

	/// Steps through the IOP Core state, executing instructions.
	int time_step(const int ticks_available) override;

	/// Unknown instruction function - does nothing when executed. Used for any instructions with implementation index 0 (ie: reserved, unknown or otherwise).
	/// If the BUILD_DEBUG macro is enabled, can be used to debug an unknown opcode by logging a message.
	void INSTRUCTION_UNKNOWN(const IopCoreInstruction inst);

	/// Computational (ALU) Instructions. See IOPInterpreter_ALU.cpp for implementations (31 instructions total).
	void ADD(const IopCoreInstruction inst);
	void ADDI(const IopCoreInstruction inst);
	void ADDIU(const IopCoreInstruction inst);
	void ADDU(const IopCoreInstruction inst); 
	void SUB(const IopCoreInstruction inst);
	void SUBU(const IopCoreInstruction inst);
	void DIV(const IopCoreInstruction inst);
	void DIVU(const IopCoreInstruction inst);
	void MULT(const IopCoreInstruction inst);
	void MULTU(const IopCoreInstruction inst);
	void SLL(const IopCoreInstruction inst);
	void SLLV(const IopCoreInstruction inst);
	void SRA(const IopCoreInstruction inst);
	void SRAV(const IopCoreInstruction inst);
	void SRL(const IopCoreInstruction inst);
	void SRLV(const IopCoreInstruction inst);
	void AND(const IopCoreInstruction inst);
	void ANDI(const IopCoreInstruction inst);
	void NOR(const IopCoreInstruction inst);
	void OR(const IopCoreInstruction inst);
	void ORI(const IopCoreInstruction inst);
	void XOR(const IopCoreInstruction inst);
	void XORI(const IopCoreInstruction inst);
	void SLT(const IopCoreInstruction inst);
	void SLTI(const IopCoreInstruction inst);
	void SLTIU(const IopCoreInstruction inst);
	void SLTU(const IopCoreInstruction inst);

	/// Load and Store from Memory Instructions. See IOPInterpreter_LOAD_STORE_MEM.cpp for implementations (14 instructions total).
	void LB(const IopCoreInstruction inst);
	void LBU(const IopCoreInstruction inst);
	void LH(const IopCoreInstruction inst);
	void LHU(const IopCoreInstruction inst);
	void LUI(const IopCoreInstruction inst);
	void LW(const IopCoreInstruction inst);
	void LWL(const IopCoreInstruction inst);
	void LWR(const IopCoreInstruction inst);
	void SB(const IopCoreInstruction inst);
	void SH(const IopCoreInstruction inst);
	void SW(const IopCoreInstruction inst);
	void SWL(const IopCoreInstruction inst);
	void SWR(const IopCoreInstruction inst);

	/// Special Data Transfer Instructions. See IOPInterpreter_SPECIAL_TRANSFER.cpp for implementations (26 instructions total).
	void MFC0(const IopCoreInstruction inst);
	void MTC0(const IopCoreInstruction inst);
	void MFHI(const IopCoreInstruction inst);
	void MFLO(const IopCoreInstruction inst);
	void MTHI(const IopCoreInstruction inst);
	void MTLO(const IopCoreInstruction inst);

	/// (Conditional) Branch and Jump Instructions. See IOPInterpreter_BRANCH_JUMP.cpp for implementations (26 instructions total).
	void BEQ(const IopCoreInstruction inst);
	void BGEZ(const IopCoreInstruction inst);
	void BGEZAL(const IopCoreInstruction inst);
	void BGTZ(const IopCoreInstruction inst);
	void BLEZ(const IopCoreInstruction inst);
	void BLTZ(const IopCoreInstruction inst);
	void BLTZAL(const IopCoreInstruction inst);
	void BNE(const IopCoreInstruction inst);
	void J(const IopCoreInstruction inst);
	void JR(const IopCoreInstruction inst);
	void JAL(const IopCoreInstruction inst);
	void JALR(const IopCoreInstruction inst);

	/// Others Instructions. See IOPInterpreter_OTHERS.cpp for implementations (9 instructions total).
	void BREAK(const IopCoreInstruction inst);
	void SYSCALL(const IopCoreInstruction inst);
	void TLBP(const IopCoreInstruction inst);
	void TLBR(const IopCoreInstruction inst);
	void TLBWI(const IopCoreInstruction inst);
	void TLBWR(const IopCoreInstruction inst);

	/// TODO: sort through.
	void LWC2(const IopCoreInstruction inst);
	void SWC2(const IopCoreInstruction inst);
	void CFC0(const IopCoreInstruction inst);
	void CTC0(const IopCoreInstruction inst);
	void RFE(const IopCoreInstruction inst);
	void RTPS(const IopCoreInstruction inst);
	void NCLIP(const IopCoreInstruction inst);
	void OP(const IopCoreInstruction inst);
	void DPCS(const IopCoreInstruction inst);
	void INTPL(const IopCoreInstruction inst);
	void MVMVA(const IopCoreInstruction inst);
	void NCDS(const IopCoreInstruction inst);
	void CDP(const IopCoreInstruction inst);
	void NCDT(const IopCoreInstruction inst);
	void NCCS(const IopCoreInstruction inst);
	void CC(const IopCoreInstruction inst);
	void NCS(const IopCoreInstruction inst);
	void NCT(const IopCoreInstruction inst);
	void SQR(const IopCoreInstruction inst);
	void DCPL(const IopCoreInstruction inst);
	void DPCT(const IopCoreInstruction inst);
	void AVSZ3(const IopCoreInstruction inst);
	void AVSZ4(const IopCoreInstruction inst);
	void RTPT(const IopCoreInstruction inst);
	void GPF(const IopCoreInstruction inst);
	void GPL(const IopCoreInstruction inst);
	void MFC2(const IopCoreInstruction inst);
	void CFC2(const IopCoreInstruction inst);
	void MTC2(const IopCoreInstruction inst);
	void CTC2(const IopCoreInstruction inst);

	/// Instruction Table. This table provides pointers to instruction implementations, which is accessed by the implementation index.
	/// See IOPCoreInstructionTable and "IOP Instruction Implementation Register.xlsm" for more details.
	void(CIopCoreInterpreter::* IOP_INSTRUCTION_TABLE[Constants::IOP::IOPCore::NUMBER_IOP_INSTRUCTIONS])(const IopCoreInstruction inst) =
	{
		&CIopCoreInterpreter::INSTRUCTION_UNKNOWN,
		&CIopCoreInterpreter::J,
		&CIopCoreInterpreter::JAL,
		&CIopCoreInterpreter::BEQ,
		&CIopCoreInterpreter::BNE,
		&CIopCoreInterpreter::BLEZ,
		&CIopCoreInterpreter::BGTZ,
		&CIopCoreInterpreter::ADDI,
		&CIopCoreInterpreter::ADDIU,
		&CIopCoreInterpreter::SLTI,
		&CIopCoreInterpreter::SLTIU,
		&CIopCoreInterpreter::ANDI,
		&CIopCoreInterpreter::ORI,
		&CIopCoreInterpreter::XORI,
		&CIopCoreInterpreter::LUI,
		&CIopCoreInterpreter::LB,
		&CIopCoreInterpreter::LH,
		&CIopCoreInterpreter::LWL,
		&CIopCoreInterpreter::LW,
		&CIopCoreInterpreter::LBU,
		&CIopCoreInterpreter::LHU,
		&CIopCoreInterpreter::LWR,
		&CIopCoreInterpreter::SB,
		&CIopCoreInterpreter::SH,
		&CIopCoreInterpreter::SWL,
		&CIopCoreInterpreter::SW,
		&CIopCoreInterpreter::SWR,
		&CIopCoreInterpreter::LWC2,
		&CIopCoreInterpreter::SWC2,
		&CIopCoreInterpreter::SLL,
		&CIopCoreInterpreter::SRL,
		&CIopCoreInterpreter::SRA,
		&CIopCoreInterpreter::SLLV,
		&CIopCoreInterpreter::SRLV,
		&CIopCoreInterpreter::SRAV,
		&CIopCoreInterpreter::JR,
		&CIopCoreInterpreter::JALR,
		&CIopCoreInterpreter::SYSCALL,
		&CIopCoreInterpreter::BREAK,
		&CIopCoreInterpreter::MFHI,
		&CIopCoreInterpreter::MTHI,
		&CIopCoreInterpreter::MFLO,
		&CIopCoreInterpreter::MTLO,
		&CIopCoreInterpreter::MULT,
		&CIopCoreInterpreter::MULTU,
		&CIopCoreInterpreter::DIV,
		&CIopCoreInterpreter::DIVU,
		&CIopCoreInterpreter::ADD,
		&CIopCoreInterpreter::ADDU,
		&CIopCoreInterpreter::SUB,
		&CIopCoreInterpreter::SUBU,
		&CIopCoreInterpreter::AND,
		&CIopCoreInterpreter::OR,
		&CIopCoreInterpreter::XOR,
		&CIopCoreInterpreter::NOR,
		&CIopCoreInterpreter::SLT,
		&CIopCoreInterpreter::SLTU,
		&CIopCoreInterpreter::BLTZ,
		&CIopCoreInterpreter::BGEZ,
		&CIopCoreInterpreter::BLTZAL,
		&CIopCoreInterpreter::BGEZAL,
		&CIopCoreInterpreter::MFC0,
		&CIopCoreInterpreter::CFC0,
		&CIopCoreInterpreter::MTC0,
		&CIopCoreInterpreter::CTC0,
		&CIopCoreInterpreter::RFE,
		&CIopCoreInterpreter::RTPS,
		&CIopCoreInterpreter::NCLIP,
		&CIopCoreInterpreter::OP,
		&CIopCoreInterpreter::DPCS,
		&CIopCoreInterpreter::INTPL,
		&CIopCoreInterpreter::MVMVA,
		&CIopCoreInterpreter::NCDS,
		&CIopCoreInterpreter::CDP,
		&CIopCoreInterpreter::NCDT,
		&CIopCoreInterpreter::NCCS,
		&CIopCoreInterpreter::CC,
		&CIopCoreInterpreter::NCS,
		&CIopCoreInterpreter::NCT,
		&CIopCoreInterpreter::SQR,
		&CIopCoreInterpreter::DCPL,
		&CIopCoreInterpreter::DPCT,
		&CIopCoreInterpreter::AVSZ3,
		&CIopCoreInterpreter::AVSZ4,
		&CIopCoreInterpreter::RTPT,
		&CIopCoreInterpreter::GPF,
		&CIopCoreInterpreter::GPL,
		&CIopCoreInterpreter::MFC2,
		&CIopCoreInterpreter::CFC2,
		&CIopCoreInterpreter::MTC2,
		&CIopCoreInterpreter::CTC2,
	};
};

