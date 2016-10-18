#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPInterpreter/IOPInterpreter.h"
#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPInterpreter/IOPMMUHandler/IOPMMUHandler.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPInterpreter/IOPExceptionHandler/IOPExceptionHandler.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/R3000/R3000_t.h"
#include "Common/PS2Resources/Types/Registers/PCRegister32_t.h"
#include "Common/Tables/IOPInstructionTable/IOPInstructionTable.h"
#include "Common/PS2Resources/Types/MIPSInstruction/MIPSInstruction_t.h"
#include "Common/PS2Resources/Types/MIPSInstructionInfo/MIPSInstructionInfo_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"

IOPInterpreter::IOPInterpreter(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain),
	mClockSources{ ClockSource_t::IOP },
	mExceptionHandler(std::make_unique<IOPExceptionHandler>(vmMain)),
	mMMUHandler(std::make_unique<IOPMMUHandler>(vmMain)),
	mInstructionInfo(nullptr)
{
}

const std::vector<ClockSource_t>& IOPInterpreter::getClockSources()
{
	return mClockSources;
}

void IOPInterpreter::initalise()
{
	// A Reset is done by raising a Reset exception.
	getExceptionHandler()->handleException(IOPException_t(IOPException_t::ExType::EX_RESET));
}

s64 IOPInterpreter::executionStep(const ClockSource_t & clockSource)
{
	// Check the exception queue to see if any are queued up - handle them first before executing an instruction (since the PC will change). 
	getExceptionHandler()->checkExceptionState();

	// Check if in a branch delay slot - function will set the PC automatically to the correct location.
	checkBranchDelaySlot();

	// Perform instruction related activities (such as execute instruction, increment PC and update timers).
	s64 cycles = executeInstruction();

#if defined(BUILD_DEBUG)
	// Debug increment loop counter.
	DEBUG_LOOP_COUNTER++;
#endif

	// Return the number of cycles, based upon how long the instruction would have taken to complete.
	return cycles;
}

void IOPInterpreter::checkBranchDelaySlot() const
{
	auto& R3000 = getVM()->getResources()->IOP->R3000;
	if (R3000->mIsInBranchDelay)
	{
		if (R3000->mBranchDelayCycles == 0)
		{
			R3000->PC->setPCValueAbsolute(R3000->mBranchDelayPCTarget);
			R3000->mIsInBranchDelay = false;
		}
		else
			R3000->mBranchDelayCycles--;
	}
}

s64 IOPInterpreter::executeInstruction()
{
	auto& IOP = getVM()->getResources()->IOP;

	// Set the instruction holder to the instruction at the current PC.
	const u32 & instructionValue = getMMUHandler()->readWordU(IOP->R3000->PC->getPCValue()); // TODO: Add error checking for address bus error.
	getInstruction().setInstructionValue(instructionValue);

	// Get the instruction details
	mInstructionInfo = IOPInstructionTable::getInstructionInfo(mInstruction);

	// Run the instruction, which is based on the implementation index.
	(this->*IOP_INSTRUCTION_TABLE[mInstructionInfo->mImplementationIndex])();

	// Increment PC.
	IOP->R3000->PC->setPCValueNext();

	// Return the number of cycles the instruction took to complete.
	return mInstructionInfo->mCycles;
}

const std::unique_ptr<IOPExceptionHandler>& IOPInterpreter::getExceptionHandler() const
{
	return mExceptionHandler;
}


const std::unique_ptr<IOPMMUHandler>& IOPInterpreter::getMMUHandler() const
{
	return mMMUHandler;
}

MIPSInstruction_t& IOPInterpreter::getInstruction()
{
	return mInstruction;
}

void IOPInterpreter::INSTRUCTION_UNKNOWN()
{
	// Unknown opcode, log if debug is enabled.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) Unknown R3000 opcode encountered!", __FILENAME__, __LINE__);
#endif
}

