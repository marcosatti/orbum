#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class PCRegister32_t;

/*
Implements MIPS branch delay slot functionality.
Exposes handleBranchDelay(), which will automatically set the associated PC register
 to the branch address when enough cycles have passed.
Use the set* functions to set the branch location. They are tailored for MIPS branch/jump instructions.
*/
class MIPSBranchDelay_t
{
public:
	explicit MIPSBranchDelay_t(std::shared_ptr<PCRegister32_t> & pcRegister32);

	/*
	Handles the updating of the branch delay slot.
	Decrements the number of delay cycles by 1 until the cycles are 0, then sets the PC to the branch location.
	Use this every CPU tick.
	*/
	void handleBranchDelay();

	/*
	Causes the branch delay to execute immediately (useful for pipeline flushes).
	Sets cycles to 0.
	*/
	void executeBranchDelayNow();

	/*
	Resets the state to no branch delay occuring.
	*/
	void resetBranchDelay();

	/*
	Set the branch delay location (mBranchDelayPC), to be triggered in the number of cycles set (mBranchDelayCycles).
	*/
	void setBranchDelayPCAbsolute(const u32 & pc, const u8 & cycles);
	void setBranchDelayPCJRegion(const u32 & JInstructionTarget, const u8 & cycles); // Convenience function for MIPS J Instruction types.
	void setBranchDelayPCIOffset(const s16 & IInstructionOffset, const u8 & cycles); // Convenience function for MIPS I Instruction types.

	/*
	Returns if there is a pending branch delay.
	*/
	bool isInBranchDelay() const;

private:
	/*
	Branch delay context variables.
	See functions above.
	*/
	std::shared_ptr<PCRegister32_t> mPCRegister32;
	u8 mBranchDelayCycles;
	u32 mBranchDelayPC;
};