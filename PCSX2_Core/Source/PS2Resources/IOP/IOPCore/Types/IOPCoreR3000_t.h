#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"


class PS2Resources_t;
class Register32_t;
class PCRegister32_t;
class LinkRegister32_t;
class ConstantRegister32_t;

/*
The IOP MIPS R3000 CPU (used as the IOP / PSX CPU).
It uses a little-endian configuration (bit 0 is always the LSB).

There is no official documentation from Sony on any of the IOP - implementation is based off PCSX2's code, and other documents available online.
There are many user-submitted documents about the PSX architecture, which has been used to aid implementation.
*/
class IOPCoreR3000_t : public PS2ResourcesSubobject
{
public:
	explicit IOPCoreR3000_t(const PS2Resources_t* const PS2Resources);

	// CPU state implementations.

	/*
	The branch delay slot functionality. Use the provided functions to set a branch target (to trigger in a given number of cycles).
	Cycles determines when the branch will be performed, and the PCTarget determines where the branch goes to.
	Most of the time cycles will be equal to one.
	See the IOPCoreInterpreter::checkBranchDelaySlot() for the logic that controls this.
	*/
	bool mIsInBranchDelay;
	u8 mBranchDelayCycles;
	u32 mBranchDelayPCTarget;
	void setBranchDelayPCTarget(u32 pcTarget, u8 cycles);
	void setBranchDelayPCJRegion(u32 JInstructionTarget, u8 cycles); // Convenience function for MIPS J Instruction types.
	void setBranchDelayPCIOffset(s16 IInstructionOffset, u8 cycles); // Convenience function for MIPS I Instruction types.
	const bool & isInBranchDelaySlot() const;
	
	// Register implementations.

	/*
	The Program Counter (PC) register.
	The PC has 3 states:
	1) During normal program execution, it will point to the current instruction and then get incremented by 4 when finished to move on to the next instruction.
	2) When a jump or branch instruction is encountered, it will point to the target address.
	3) When an exception occurs, the PC is changed to point to the exception vector address.
	It is a 32-bit register, pointing to a virtual address (NOT a PHYSICAL address! This means you need to use the IOPCoreMMUHandler component to get the proper PS2 physical address.)
	Some convience functions are provided for manipulating this value.

	Must be initalised before LinkRegister below due to dependency.
	*/
	std::shared_ptr<PCRegister32_t> PC;

	/*
	The 32 general purpose registers. They are each 32-bits long.
	GPR[0] is hardwired to 0.
	GPR[31] is known as the link register.
	*/
	std::shared_ptr<ConstantRegister32_t> ZeroRegister;
	std::shared_ptr<LinkRegister32_t> LinkRegister;
	std::shared_ptr<Register32_t> GPR[PS2Constants::IOP::IOPCore::R3000A::NUMBER_GP_REGISTERS];

	/*
	The HI and LO registers.
	These registers are used to hold the results of integer multiply and divide operations.
	They are 32-bit long.
	*/
	std::shared_ptr<Register32_t> HI;
	std::shared_ptr<Register32_t> LO;
};

