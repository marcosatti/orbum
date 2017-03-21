#include "stdafx.h"
#include <gtest/gtest.h>

#include <VM/VM.h>
#include <VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h>
#include <Resources/Resources_t.h>
#include <Resources/IOP/IOP_t.h>
#include <Resources/IOP/IOPCore/IOPCore_t.h>
#include <Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h>
#include <Common/Types/Registers/Register32_t.h>
#include <Common/Types/PhysicalMMU/PhysicalMMU_t.h>
#include <Common/Types/Registers/MIPS/PCRegister32_t.h>
#include <Common/Types/MIPSInstructionInfo/MIPSInstructionInfo_t.h>
#include <Common/Tables/IOPCoreInstructionTable/IOPCoreInstructionTable.h>
#include "Util/MIPSUtil.h"

class TEST_IOPCoreInterpreter_s : public testing::Test
{
public:
	VM * vm;
	IOPCoreInterpreter_s * core;

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
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 32);
		EXPECT_STREQ("ADD", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 5412);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 7891);
		core->ADD();
		EXPECT_EQ(13303, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// ADDI
	{
		auto inst = MIPSUtil::genIInstruction(8, 4, 2, -256);
		EXPECT_STREQ("ADDI", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 5412);
		core->ADDI();
		EXPECT_EQ(5156, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SUB
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 34);
		EXPECT_STREQ("SUB", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 12345);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 81);
		core->SUB();
		EXPECT_EQ(12264, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// ADDU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 33);
		EXPECT_STREQ("ADDU", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 5412);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, -7891);
		core->ADDU();
		EXPECT_EQ(-2479, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SUBU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 35);
		EXPECT_STREQ("SUBU", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 64841);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 314898);
		core->SUBU();
		EXPECT_EQ(-250057, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// ADDIU
	{
		auto inst = MIPSUtil::genIInstruction(9, 4, 2, -256);
		EXPECT_STREQ("ADDIU", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 12);
		core->ADDIU();
		EXPECT_EQ(-244, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// AND
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 36);
		EXPECT_STREQ("AND", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x1234ABCD);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x56789EF0);
		core->AND();
		EXPECT_EQ(0x12308AC0, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// ANDI
	{
		auto inst = MIPSUtil::genIInstruction(12, 4, 2, 0xCCCC);
		EXPECT_STREQ("ANDI", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x66666666);
		core->ANDI();
		EXPECT_EQ(0x4444, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// OR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 37);
		EXPECT_STREQ("OR", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x88888888);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x11111111);
		core->OR();
		EXPECT_EQ(0x99999999, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// ORI
	{
		auto inst = MIPSUtil::genIInstruction(13, 4, 2, 0x8888);
		EXPECT_STREQ("ORI", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x11111111);
		core->ORI();
		EXPECT_EQ(0x11119999, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// NOR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 39);
		EXPECT_STREQ("NOR", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x88888888);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x77777777);
		core->NOR();
		EXPECT_EQ(0x0, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}


	// SLL
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 2, 0);
		EXPECT_STREQ("SLL", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x11111111);
		core->SLL();
		EXPECT_EQ(0x44444444, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SLLV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 4);
		EXPECT_STREQ("SLLV", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x3);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x11111111);
		core->SLLV();
		EXPECT_EQ(0x88888888, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SRA
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 3);
		EXPECT_STREQ("SRA", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x88888888);
		core->SRA();
		EXPECT_EQ(0xF8888888, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SRAV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 7);
		EXPECT_STREQ("SRAV", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0X4);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x88888888);
		core->SRAV();
		EXPECT_EQ(0xF8888888, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SRL
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 2);
		EXPECT_STREQ("SRL", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x88888888);
		core->SRL();
		EXPECT_EQ(0x08888888, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SRLV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 6);
		EXPECT_STREQ("SRLV", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0X4);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x88888888);
		core->SRLV();
		EXPECT_EQ(0x08888888, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SLT
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 42);
		EXPECT_STREQ("SLT", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x10);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x20);
		core->SLT();
		EXPECT_EQ(0x1, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SLTI
	{
		auto inst = MIPSUtil::genIInstruction(10, 4, 2, -256);
		EXPECT_STREQ("SLTI", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, -1000);
		core->SLTI();
		EXPECT_EQ(0x1, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SLTU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 43);
		EXPECT_STREQ("SLTU", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x8E000000);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x8F000000);
		core->SLTU();
		EXPECT_EQ(0x1, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SLTIU
	{
		auto inst = MIPSUtil::genIInstruction(11, 4, 2, -256);
		EXPECT_STREQ("SLTIU", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, -1000);
		core->SLTIU();
		EXPECT_EQ(0x1, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// XOR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 38);
		EXPECT_STREQ("XOR", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x88888888);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0xFFFFFFFF);
		core->XOR();
		EXPECT_EQ(0x77777777, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// XORI
	{
		auto inst = MIPSUtil::genIInstruction(14, 4, 2, 0x8888);
		EXPECT_STREQ("XORI", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xFFFFFFFF);
		core->XORI();
		EXPECT_EQ(0xFFFF7777, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// LUI
	{
		auto inst = MIPSUtil::genIInstruction(15, 0, 2, 0x8888);
		EXPECT_STREQ("LUI", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		core->LUI();
		EXPECT_EQ(0x88880000, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// BEQ
	{
		auto inst = MIPSUtil::genIInstruction(4, 4, 2, -256);
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

	// BGEZ
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 1, 63);
		EXPECT_STREQ("BGEZ", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x1);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(0xBFC00000);
		core->BGEZ();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
	}

	// BGEZAL
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 17, 63);
		EXPECT_STREQ("BGEZAL", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x0);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(0xBFC00000);
		core->BGEZAL();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
		EXPECT_EQ(0xBFC00008, vm->getResources()->IOP->IOPCore->R3000->GPR[31]->readWord(RAW));
	}

	// BGTZ
	{
		auto inst = MIPSUtil::genIInstruction(7, 4, 0, 63);
		EXPECT_STREQ("BGTZ", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x1);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(0xBFC00000);
		core->BGTZ();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
	}

	// BLEZ
	{
		auto inst = MIPSUtil::genIInstruction(6, 4, 0, 63);
		EXPECT_STREQ("BLEZ", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x87654321);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(0xBFC00000);
		core->BLEZ();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
	}

	// BLTZ
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 0, 63);
		EXPECT_STREQ("BLTZ", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x87654321);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(0xBFC00000);
		core->BLTZ();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
	}

	// BLTZAL
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 16, 63);
		EXPECT_STREQ("BLTZAL", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x87654321);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(0xBFC00000);
		core->BLTZAL();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
		EXPECT_EQ(0xBFC00008, vm->getResources()->IOP->IOPCore->R3000->GPR[31]->readWord(RAW));
	}

	// BNE
	{
		auto inst = MIPSUtil::genIInstruction(5, 4, 2, -256);
		EXPECT_STREQ("BNE", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(RAW, 0x87654321);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x1234ABCD);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(0xBFC00000);
		core->BNE();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFBFFC04, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
	}

	// MULT
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 24);
		EXPECT_STREQ("MULT", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xFFFFFFFB);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0xFFFFFFFE);
		core->MULT();
		EXPECT_EQ(0xA, vm->getResources()->IOP->IOPCore->R3000->LO->readWord(RAW));
		EXPECT_EQ(0x0, vm->getResources()->IOP->IOPCore->R3000->HI->readWord(RAW));
	}

	// MULTU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 25);
		EXPECT_STREQ("MULTU", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xFFFFFFFB);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0xFFFFFFFE);
		core->MULTU();
		EXPECT_EQ(0x0000000A, vm->getResources()->IOP->IOPCore->R3000->LO->readWord(RAW));
		EXPECT_EQ(0xFFFFFFF9, vm->getResources()->IOP->IOPCore->R3000->HI->readWord(RAW));
	}

	// DIV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 26);
		EXPECT_STREQ("DIV", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xFFFFFFFB);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0xFFFFFFFE);
		core->DIV();
		EXPECT_EQ(0x2, vm->getResources()->IOP->IOPCore->R3000->LO->readWord(RAW));
		EXPECT_EQ(0xFFFFFFFF, vm->getResources()->IOP->IOPCore->R3000->HI->readWord(RAW));
	}

	// DIVU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 27);
		EXPECT_STREQ("DIVU", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0x10);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(RAW, 0x7);
		core->DIVU();
		EXPECT_EQ(0x2, vm->getResources()->IOP->IOPCore->R3000->LO->readWord(RAW));
		EXPECT_EQ(0x2, vm->getResources()->IOP->IOPCore->R3000->HI->readWord(RAW));
	}

	// J
	{
		auto inst = MIPSUtil::genJInstruction(2, 0x3F00400);
		EXPECT_STREQ("J", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(0xBFC00000);
		core->J();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFC01000, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
	}

	// JAL
	{
		auto inst = MIPSUtil::genJInstruction(3, 0x3F00400);
		EXPECT_STREQ("JAL", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(0xBFC00000);
		core->JAL();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFC01000, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
		EXPECT_EQ(0xBFC00008, vm->getResources()->IOP->IOPCore->R3000->GPR[31]->readWord(RAW));
	}

	// JALR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 0, 31, 0, 9);
		EXPECT_STREQ("JALR", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(0xBFC00000);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xBFC01000);
		core->JALR();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFC01000, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
		EXPECT_EQ(0xBFC00008, vm->getResources()->IOP->IOPCore->R3000->GPR[31]->readWord(RAW));
	}

	// JR
	{
		auto inst = MIPSUtil::genRInstruction(0, 31, 0, 0, 0, 8);
		EXPECT_STREQ("JR", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[31]->writeWord(RAW, 0xBFC00008);
		core->JR();
		EXPECT_EQ(true, vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow();
		EXPECT_EQ(0xBFC00008, vm->getResources()->IOP->IOPCore->R3000->PC->readWord(RAW));
	}

	// LB
	{
		auto inst = MIPSUtil::genIInstruction(32, 4, 2, -4);
		EXPECT_STREQ("LB", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->PhysicalMMU->writeByte(RAW, 0x0, 0xCD);
		core->LB();
		EXPECT_EQ(0xFFFFFFCD, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// LBU
	{
		auto inst = MIPSUtil::genIInstruction(36, 4, 2, -4);
		EXPECT_STREQ("LBU", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->PhysicalMMU->writeByte(RAW, 0x0, 0xAB);
		core->LBU();
		EXPECT_EQ(0xAB, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// LH
	{
		auto inst = MIPSUtil::genIInstruction(33, 4, 2, -4);
		EXPECT_STREQ("LH", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->PhysicalMMU->writeHword(RAW, 0x0, 0xCDEF);
		core->LH();
		EXPECT_EQ(0xFFFFCDEF, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// LHU
	{
		auto inst = MIPSUtil::genIInstruction(37, 4, 2, -4);
		EXPECT_STREQ("LHU", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->PhysicalMMU->writeHword(RAW, 0x0, 0xABCD);
		core->LHU();
		EXPECT_EQ(0xABCD, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// LW
	{
		auto inst = MIPSUtil::genIInstruction(35, 4, 2, -4);
		EXPECT_STREQ("LW", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->PhysicalMMU->writeWord(RAW, 0x0, 0x12345678);
		core->LW();
		EXPECT_EQ(0x12345678, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SB
	{
		auto inst = MIPSUtil::genIInstruction(40, 4, 2, -4);
		EXPECT_STREQ("SB", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(RAW, 0x1234ABCD);
		core->SB();
		EXPECT_EQ(0xCD, vm->getResources()->IOP->PhysicalMMU->readByte(RAW, 0x0));
	}

	// SH
	{
		auto inst = MIPSUtil::genIInstruction(41, 4, 2, -4);
		EXPECT_STREQ("SH", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(RAW, 0x1234ABCD);
		core->SH();
		EXPECT_EQ(0xABCD, vm->getResources()->IOP->PhysicalMMU->readHword(RAW, 0x0));
	}

	// SW
	{
		auto inst = MIPSUtil::genIInstruction(43, 4, 2, -4);
		EXPECT_STREQ("SW", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(RAW, 0x1234ABCD);
		core->SW();
		EXPECT_EQ(0x1234ABCD, vm->getResources()->IOP->PhysicalMMU->readWord(RAW, 0x0));
	}

	// LWL
	{
		auto inst = MIPSUtil::genIInstruction(34, 4, 2, -3);
		EXPECT_STREQ("LWL", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(RAW, 0xCDCDCDCD);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->PhysicalMMU->writeWord(RAW, 0x0, 0x01234567);
		core->LWL();
		EXPECT_EQ(0x4567CDCD, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// LWR
	{
		auto inst = MIPSUtil::genIInstruction(38, 4, 2, 2);
		EXPECT_STREQ("LWR", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(RAW, 0xCDCDCDCD);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->PhysicalMMU->writeWord(RAW, 0x4, 0x89ABCDEF);
		core->LWR();
		EXPECT_EQ(0xCDCD89AB, vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(RAW));
	}

	// SWL
	{
		auto inst = MIPSUtil::genIInstruction(42, 4, 2, -3);
		EXPECT_STREQ("SWL", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(RAW, 0x11111111);
		vm->getResources()->IOP->PhysicalMMU->writeWord(RAW, 0x0, 0xABABABAB);
		core->SWL();
		EXPECT_EQ(0xABAB1111, vm->getResources()->IOP->PhysicalMMU->readWord(RAW, 0x0));
	}

	// SWR
	{
		auto inst = MIPSUtil::genIInstruction(46, 4, 2, 2);
		EXPECT_STREQ("SWR", IOPCoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(RAW, 0xA0000004);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(RAW, 0x11111111);
		vm->getResources()->IOP->PhysicalMMU->writeWord(RAW, 0x4, 0xCDCDCDCD);
		core->SWR();
		EXPECT_EQ(0x1111CDCD, vm->getResources()->IOP->PhysicalMMU->readWord(RAW, 0x4));
	}
}
