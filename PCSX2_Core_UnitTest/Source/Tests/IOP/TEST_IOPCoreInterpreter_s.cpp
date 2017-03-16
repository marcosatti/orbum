#include "stdafx.h"
#include <gtest/gtest.h>

#include <VM/VM.h>
#include <VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h>
#include <Resources/Resources_t.h>
#include <Resources/IOP/IOP_t.h>
#include <Resources/IOP/IOPCore/IOPCore_t.h>
#include <Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h>
#include <Common/Types/Registers/Register32_t.h>
#include <Common/Types/Registers/MIPS/PCRegister32_t.h>
#include <Common/Types/MIPSInstructionInfo/MIPSInstructionInfo_t.h>
#include <Common/Tables/IOPCoreInstructionTable/IOPCoreInstructionTable.h>

class TEST_IOPCoreInterpreter_s : public testing::Test
{
public:
	VM * vm;
	IOPCoreInterpreter_s * core;

	u32 genRInstruction(int opcode, int s, int t, int d, int shamt, int funct)
	{
		return (((opcode & 0x3F) << 26) | ((s & 0x1F) << 21) | ((t & 0x1F) << 16) | ((d & 0x1F) << 11) | ((shamt & 0x1F) << 6) | ((funct & 0x3F) << 0));
	}

	u32 genIInstruction(int opcode, int s, int t, int imm)
	{
		return (((opcode & 0x3F) << 26) | ((s & 0x1F) << 21) | ((t & 0x1F) << 16) | ((imm & 0xFFFF) << 0));
	}

	u32 genJInstruction(int opcode, int target)
	{
		return (((opcode & 0x1F) << 26) | ((target & 0x3FFFFFF) << 0));
	}

	virtual void SetUp()
	{
		VMOptions vmOptions =
		{
			nullptr,
			"",
			"",
			"",
			"",
			0,
			false,
			{}
		};
		
		vm = new VM(vmOptions);
		core = dynamic_cast<IOPCoreInterpreter_s*>(vm->mSystems[System_t::IOPCore].get());
	}

	virtual void TearDown() 
	{
		core = nullptr;
		delete vm;
	}
};

TEST_F(TEST_IOPCoreInterpreter_s, MIPS_INSTRUCTION_IMPLEMENTATIONS)
{
	// Test follows the basic MIPS I instruction set.
	// https://en.wikipedia.org/wiki/MIPS_instruction_set

	// ADD
	{
		auto inst = genRInstruction(0, 4, 5, 2, 0, 32);
		EXPECT_STREQ("ADD", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 5412);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 7891);
		core->ADD();
		EXPECT_EQ(13303, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// ADDI
	{
		auto inst = genIInstruction(8, 4, 2, -256);
		EXPECT_STREQ("ADDI", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 5412);
		core->ADDI();
		EXPECT_EQ(5156, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// ADDU (overflows)
	{
		auto inst = genRInstruction(0, 4, 5, 2, 0, 33);
		EXPECT_STREQ("ADDU", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 2505381576);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 2505381576);
		core->ADDU();
		EXPECT_EQ(715795856, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// ADDIU (underflows)
	{
		auto inst = genIInstruction(9, 4, 2, -256);
		EXPECT_STREQ("ADDIU", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 12);
		core->ADDIU();
		EXPECT_EQ(-244, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// AND
	{
		auto inst = genRInstruction(0, 4, 5, 2, 0, 36);
		EXPECT_STREQ("AND", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x1234ABCD);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x56789EF0);
		core->AND();
		EXPECT_EQ(0x12308AC0, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// ANDI
	{
		auto inst = genIInstruction(12, 4, 2, 0xCCCC);
		EXPECT_STREQ("ANDI", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x66666666);
		core->ANDI();
		EXPECT_EQ(0x4444, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// BEQ
	{
		auto inst = genIInstruction(4, 4, 2, -256);
		EXPECT_STREQ("BEQ", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(RAW, 0x1234ABCD);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x1234ABCD);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(0xBFC00000);
		core->BEQ();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFBFFC04, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
	}

}