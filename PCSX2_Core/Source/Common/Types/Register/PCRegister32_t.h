#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register32_t.h"

/*
Represents the program counter register of a MIPS CPU. It is defined as 32-bits long.
Extends a normal 32-bit register to provide convenience functions for manipulating the PC value, and provides a branch delay slot.
*/
class PCRegister32_t : public Register32_t
{
public:
	explicit PCRegister32_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Handles the updating of the PC by either jumping to the branch location or incrementing the PC by 4 (next instruction).
	*/
	void next(const System_t context);

	/*
	Set the PC to a relative value immediately.
	*/
	void setPCValueRelative(const System_t context, const s32 relativePC);

	/*
	Set the PC to an absolute value immediately.
	*/
	void setPCValueAbsolute(const System_t context, const u32 absolutePC);

	/*
	Set a branch PC, to be triggered in the number of cycles set.
	Convenience functions provided for different MIPS branch instructions.
	*/
	void setBranchPCAbsolute(const u32 pc, const int cycles);
	void setBranchPCJRegion(const System_t context, const u32 JInstructionTarget, const int cycles);
	void setBranchPCIOffset(const System_t context, const s16 IInstructionOffset, const int cycles);

	/*
	Causes the branch delay to execute immediately (useful for pipeline flushes).
	*/
	void doBranchNow(const System_t context);

	/*
	Returns if there is a pending branch delay.
	*/
	bool isBranchPending() const;

	/*
	Resets the state to no branch pending.
	*/
	void resetBranch();

private:
	/*
	Branch delay context.
	*/
	int mBranchDelayCycles;
	u32 mBranchDelayPC;
};

