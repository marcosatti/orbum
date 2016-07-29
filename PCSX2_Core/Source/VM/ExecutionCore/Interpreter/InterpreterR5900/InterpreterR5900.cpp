#include "stdafx.h"

#include "Common/Global/GlobalConstants.h"

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

u32 & InterpreterR5900::getR5900PCValue() const
{
	return getVM()->getResources()->EE.EECore.R5900.PC.UW;
}

void InterpreterR5900::setR5900PCValueRelative(s32 relativeLocation) const
{
	getVM()->getResources()->EE.EECore.R5900.PC.UW += relativeLocation;
}

void InterpreterR5900::setR5900PCValueAbsolute(s32 absoluteLocation) const
{
	getVM()->getResources()->EE.EECore.R5900.PC.UW = absoluteLocation;
}

void InterpreterR5900::setR5900PCValueNext() const
{
	setR5900PCValueRelative(Constants::SIZE_MIPS_INSTRUCTION);
}

void InterpreterR5900::unknownOperation()
{
	// Unknown opcode, log if debug is enabled and increment PC by 4 regardless.
#if defined(BUILD_DEBUG)
	logDebug("Unknown R5900 opcode encountered!");
#endif

	setR5900PCValueNext();
}
