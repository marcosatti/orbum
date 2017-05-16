#include "Resources/IOP/IOPCore/Types/IOPCoreInstruction_t.h"

IOPCoreInstruction_t::IOPCoreInstruction_t(const u32 value) :
	MIPSInstruction_t(value)
{
	mInfo = IOPCoreInstructionTable::getInfo(this);
}

const IOPCoreInstructionTable::IOPCoreInstructionInfo_t * IOPCoreInstruction_t::getInfo() const
{
	return mInfo;
}