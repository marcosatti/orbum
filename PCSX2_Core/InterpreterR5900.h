#pragma once

#include "Globals.h"

#include "VMInterpreterComponent.h"
#include "Instruction_t.h"

class InterpreterR5900 : public VMInterpreterComponent
{
public:
	InterpreterR5900(const VMMain *const vmMain, const Interpreter *const interpreter);
	~InterpreterR5900();
	void runInterpreterComponent() override;

private:
	/*
	Void function pointer type.
	This type specifies a pointer to a function which returns nothing and has no parameters.
	This is used extensively in the look-up tables when decoding instructions (see below).
	*/
	typedef void(InterpreterR5900::*voidfunc_ptr)();

	/*
	Convenience functions to get/set the R5900 PC.
	*/
	INLINE u32& getR5900PCValue() const;
	INLINE void setR5900PCValueRelative(s32 relativeLocation) const;

	/*
	The instruction holder, used as a temporary holder for the current instruction.
	This is used in the interpreter whilst looking up the instruction to determine what operation to perform.
	Convenience funcions are also defined as part of the Instruction object to access differnt parts of the opcode, but you will need to cast the Instruction_t to one of the sub-classes (I, J, R).
	This is done in the instruction lookup table.
	*/
	Instruction_t mInstruction;

	/*
	Unknown opcode function - does nothing when executed.
	If enabled, can be used to debug an unknown opcode by logging a message.
	Will increase PC by 4 regardless.
	*/
	void opcodeUnknown();

	/*
	MIPS Instruction Opcode table. Calls functions based on opcode field.
	From here, either a subroutine will be called to handle the Instruction after determining the opcode.
	In total, there are 64 opcode posibilities (5 bits occupy the opcode field).
	Defined as an 8x8 grid.
	*/
	voidfunc_ptr opcodeTable[64] = 
	{
		&InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown,
		&InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown,
		&InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown,
		&InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown,
		&InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown,
		&InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown,
		&InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown,
		&InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown, &InterpreterR5900::opcodeUnknown
	};
};

