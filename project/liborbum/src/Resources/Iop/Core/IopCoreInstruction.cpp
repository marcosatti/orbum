#include "Resources/Iop/Core/IopCoreInstruction.hpp"

IopCoreInstruction::IopCoreInstruction(const uword value) :
	MipsInstruction(value)
{
	info = IOPCoreInstructionTable::getInfo(this);
}

const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * IopCoreInstruction::get_info() const
{
	return info;
}