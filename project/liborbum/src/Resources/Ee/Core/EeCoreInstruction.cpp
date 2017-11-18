#include "Resources/Ee/Core/EeCoreInstruction.hpp"

EeCoreInstruction::EeCoreInstruction(const uword value) :
	MipsInstruction(value)
{
	mInfo = EECoreInstructionTable::getInfo(this);
}

const EECoreInstructionTable::EECoreInstructionInfo_t * EeCoreInstruction::getInfo() const
{
	return mInfo;
}
