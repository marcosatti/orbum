#pragma once


#include "VM/Component Interfaces/VMInterpreterComponent.h"
#include "Common/PS2 Types/MIPSInstructionHelper/MIPSInstructionHelper_t.h"

class VMMain;
class InterpreterR5900 : public VMInterpreterComponent
{
public:
	InterpreterR5900(const VMMain *const vmMain, const Interpreter *const interpreter);
	~InterpreterR5900();

	/*
	This is the "main loop" function called by the base interpreter component.
	*/
	void runInterpreterComponent() override;

private:

	// General functions

	/*
	Convenience functions to get/set the R5900 PC.
	*/
	INLINE u32& getR5900PCValue() const;
	INLINE void setR5900PCValueRelative(s32 relativeLocation) const;
	INLINE void setR5900PCValueAbsolute(s32 absoluteLocation) const;
	INLINE void setR5900PCValueNext() const; // Increments the PC by 4.

	// Component state functions

	/*
	The is used as a temporary holder for the current instruction, while the operation to perform is being determined.
	*/
	MIPSInstructionHelper_t mInstruction;

	// Instruction functions.

	/*
	Void function pointer type.
	This type specifies a pointer to a function which returns nothing and has no parameters.
	This is used extensively in the look-up tables when decoding instructions (see below).
	*/
	typedef void(InterpreterR5900::*voidfunc_ptr)();

	/*
	Unknown opcode function - does nothing when executed.
	If the PCSX2_DEBUG macro is enabled, can be used to debug an unknown opcode by logging a message.
	Will increase PC by 4 regardless.
	*/
	void unknownOperation();

	/*
	MIPS Instruction Opcode table. Calls functions based on opcode field.
	From here, either a subroutine will be called to handle the Instruction after determining the opcode.
	In total, there are 64 opcode posibilities (5 bits occupy the opcode field).
	Defined as an 8x8 grid.
	*/
	voidfunc_ptr opcodeTable[64] = 
	{
		&InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation,
		&InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation,
		&InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation,
		&InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation,
		&InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation,
		&InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation,
		&InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation,
		&InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation, &InterpreterR5900::unknownOperation
	};
};

