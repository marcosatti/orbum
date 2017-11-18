#include "Resources/Ee/Vpu/VifcodeInstruction.hpp"

VifcodeInstruction::VifcodeInstruction(const uword value) :
	MipsInstruction(value)
{
	mInstructionInfo = VIFcodeTable::getInfo(this);
}

const VIFcodeTable::VIFcodeInstructionInfo_t * VifcodeInstruction::get_instruction_info() const
{
	return mInstructionInfo;
}
