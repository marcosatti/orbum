#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/InterpreterR5900/InterpreterR5900.h"
#include "VM/VMMain.h"

InterpreterR5900::InterpreterR5900(const VMMain* const vmMain, const Interpreter* const interpreter) :
	VMInterpreterComponent(vmMain, interpreter)
{
}

InterpreterR5900::~InterpreterR5900()
{
}

void InterpreterR5900::runInterpreterComponent()
{
	// Set the instruction holder to the instruction at the current PC.
	mInstruction.setInstruction(getVM()->getMMU()->readWordU(getR5900PCValue()));

	// Get the instruction opcode and look it up in opcodeTable. The corresponding function will be called to further handle the instruction.
	const u8 & opcodeValue = mInstruction.getOpcode();
	(this->*opcodeTable[opcodeValue])();
}

INLINE u32 & InterpreterR5900::getR5900PCValue() const
{
	return getVM()->getResources()->EE.EECore.R5900.PC.UW;
}

INLINE void InterpreterR5900::setR5900PCValueRelative(s32 relativeLocation) const
{
	getVM()->getResources()->EE.EECore.R5900.PC.UW += relativeLocation;
}

void InterpreterR5900::opcodeUnknown()
{
	// Unknown opcode, log if debug is enabled and increment PC by 4 regardless.
#if defined(BUILD_DEBUG)
	logDebug("Unknown R5900 opcode encountered!");
#endif
}
