#include "stdafx.h"
#include <gtest/gtest.h>

#include <VM/VM.h>
#include <VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h>
#include <Resources/Resources_t.h>
#include <Resources/EE/EE_t.h>
#include <Resources/EE/EECore/EECore_t.h>
#include <Resources/EE/EECore/Types/EECoreR5900_t.h>
#include <Common/Types/Registers/Register32_t.h>
#include <Common/Types/Registers/Register128_t.h>
#include <Common/Types/PhysicalMMU/PhysicalMMU_t.h>
#include <Common/Types/Registers/MIPS/PCRegister32_t.h>
#include <Common/Types/MIPSInstructionInfo/MIPSInstructionInfo_t.h>
#include <Common/Tables/EECoreInstructionTable/EECoreInstructionTable.h>
#include "Util/MIPSUtil.h"

class TEST_EECoreInterpreter_s : public testing::Test
{
public:
	VM * vm;
	EECoreInterpreter_s * core;

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
		core = dynamic_cast<EECoreInterpreter_s*>(vm->mSystems[System_t::EECore].get());
	}

	virtual void TearDown() 
	{
		core = nullptr;
		delete vm;
	}
};

TEST_F(TEST_EECoreInterpreter_s, MIPS_INSTRUCTION_IMPLEMENTATIONS)
{
	// Test follows the basic MIPS III instruction set.
	// https://en.wikipedia.org/wiki/MIPS_instruction_set

	// ADD
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 32);
		EXPECT_STREQ("ADD", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, static_cast<s64>(-5412));
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, static_cast<s64>(-7891));
		core->ADD();
		EXPECT_EQ(-13303, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0)));
	}

	// ADDI
	{
		auto inst = MIPSUtil::genIInstruction(8, 4, 2, 256);
		EXPECT_STREQ("ADDI", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, static_cast<s64>(-5412));
		core->ADDI();
		EXPECT_EQ(-5156, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0)));
	}

	// ADDIU
	{
		auto inst = MIPSUtil::genIInstruction(9, 4, 2, -256);
		EXPECT_STREQ("ADDIU", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 12);
		core->ADDIU();
		EXPECT_EQ(-244, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0)));
	}

	// ADDU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 33);
		EXPECT_STREQ("ADDU", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 5412);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, static_cast<s64>(-7891));
		core->ADDU();
		EXPECT_EQ(-2479, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0)));
	}

	// SUB
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 34);
		EXPECT_STREQ("SUB", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, static_cast<s64>(-12345));
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, static_cast<s64>(-81));
		core->SUB();
		EXPECT_EQ(-12264, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0)));
	}

	// SUBU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 35);
		EXPECT_STREQ("SUBU", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 5649652);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, -856261945);
		core->SUBU();
		EXPECT_EQ(861911597, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// AND
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 36);
		EXPECT_STREQ("AND", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, static_cast<s64>(-48446));
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, static_cast<s64>(-636952));
		core->AND();
		EXPECT_EQ(-638272, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0)));
	}

	// ANDI
	{
		auto inst = MIPSUtil::genIInstruction(12, 4, 2, 0xCCCC);
		EXPECT_STREQ("ANDI", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xFFFFFFFF66666666);
		core->ANDI();
		EXPECT_EQ(0x4444, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// OR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 37);
		EXPECT_STREQ("OR", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x88888888);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0xFFFFFFFF11111111);
		core->OR();
		EXPECT_EQ(0xFFFFFFFF99999999, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// ORI
	{
		auto inst = MIPSUtil::genIInstruction(13, 4, 2, 0x8888);
		EXPECT_STREQ("ORI", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xCCCCCCCC11111111);
		core->ORI();
		EXPECT_EQ(0xCCCCCCCC11119999, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// NOR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 39);
		EXPECT_STREQ("NOR", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x88888888);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0x77777777);
		core->NOR();
		EXPECT_EQ(0xFFFFFFFF00000000, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SLL
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 0);
		EXPECT_STREQ("SLL", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0x08888888);
		core->SLL();
		EXPECT_EQ(0xFFFFFFFF88888880, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SLLV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 4);
		EXPECT_STREQ("SLLV", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x3);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0x11111111);
		core->SLLV();
		EXPECT_EQ(0xFFFFFFFF88888888, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SRA
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 3);
		EXPECT_STREQ("SRA", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0x88888888);
		core->SRA();
		EXPECT_EQ(0xFFFFFFFFF8888888, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SRAV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 7);
		EXPECT_STREQ("SRAV", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x4);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0x88888888);
		core->SRAV();
		EXPECT_EQ(0xFFFFFFFFF8888888, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SRL
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 2);
		EXPECT_STREQ("SRL", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0x88888888);
		core->SRL();
		EXPECT_EQ(0x08888888, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SRLV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 6);
		EXPECT_STREQ("SRLV", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x0);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0x88888888);
		core->SRLV();
		EXPECT_EQ(0xFFFFFFFF88888888, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SLT
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 42);
		EXPECT_STREQ("SLT", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, static_cast<s64>(-81));
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, static_cast<s64>(-1));
		core->SLT();
		EXPECT_EQ(0x1, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SLTI
	{
		auto inst = MIPSUtil::genIInstruction(10, 4, 2, -256);
		EXPECT_STREQ("SLTI", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, static_cast<s64>(-1000));
		core->SLTI();
		EXPECT_EQ(0x1, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SLTU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 43);
		EXPECT_STREQ("SLTU", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 1);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, static_cast<s64>(-1));
		core->SLTU();
		EXPECT_EQ(0x1, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SLTIU
	{
		auto inst = MIPSUtil::genIInstruction(11, 4, 2, -256);
		EXPECT_STREQ("SLTIU", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, static_cast<s64>(-1000));
		core->SLTIU();
		EXPECT_EQ(0x1, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// XOR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 38);
		EXPECT_STREQ("XOR", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xFFFFFFFF88888888);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0x88888888FFFFFFFF);
		core->XOR();
		EXPECT_EQ(0x7777777777777777, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// XORI
	{
		auto inst = MIPSUtil::genIInstruction(14, 4, 2, 0x8888);
		EXPECT_STREQ("XORI", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xFFFFFFFFFFFFFFFF);
		core->XORI();
		EXPECT_EQ(0xFFFFFFFFFFFF7777, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// LUI
	{
		auto inst = MIPSUtil::genIInstruction(15, 0, 2, 0x8888);
		EXPECT_STREQ("LUI", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		core->LUI();
		EXPECT_EQ(0xFFFFFFFF88880000, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// BEQ
	{
		auto inst = MIPSUtil::genIInstruction(4, 4, 2, -256);
		EXPECT_STREQ("BEQ", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(RAW, 0, 0x1234ABCD);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x1234ABCD);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(0xBFC00000);
		core->BEQ();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFBFFC04, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
	}

	// BGEZ
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 1, 63);
		EXPECT_STREQ("BGEZ", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x1);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(0xBFC00000);
		core->BGEZ();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
	}

	// BGEZAL
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 17, 63);
		EXPECT_STREQ("BGEZAL", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x0);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(0xBFC00000);
		core->BGEZAL();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
		EXPECT_EQ(0xBFC00008, vm->getResources()->EE->EECore->R5900->GPR[31]->readDword(RAW, 0));
	}

	// BGTZ
	{
		auto inst = MIPSUtil::genIInstruction(7, 4, 0, 63);
		EXPECT_STREQ("BGTZ", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x1);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(0xBFC00000);
		core->BGTZ();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
	}

	// BLEZ
	{
		auto inst = MIPSUtil::genIInstruction(6, 4, 0, 63);
		EXPECT_STREQ("BLEZ", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x87654321);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(0xBFC00000);
		core->BLEZ();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
	}

	// BLTZ
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 0, 63);
		EXPECT_STREQ("BLTZ", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x87654321);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(0xBFC00000);
		core->BLTZ();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
	}

	// BLTZAL
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 16, 63);
		EXPECT_STREQ("BLTZAL", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x87654321);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(0xBFC00000);
		core->BLTZAL();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
		EXPECT_EQ(0xBFC00008, vm->getResources()->EE->EECore->R5900->GPR[31]->readDword(RAW, 0));
	}

	// BNE
	{
		auto inst = MIPSUtil::genIInstruction(5, 4, 2, -256);
		EXPECT_STREQ("BNE", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(RAW, 0, 0x87654321);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x1234ABCD);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(0xBFC00000);
		core->BNE();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFBFFC04, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
	}

	// MULT
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 24);
		EXPECT_STREQ("MULT", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xFFFFFFFB);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0xFFFFFFFE);
		core->MULT();
		EXPECT_EQ(0xA, vm->getResources()->EE->EECore->R5900->LO->readDword(RAW, 0));
		EXPECT_EQ(0x0, vm->getResources()->EE->EECore->R5900->HI->readDword(RAW, 0));
	}

	// MULTU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 25);
		EXPECT_STREQ("MULTU", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xFFFFFFFB);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0xFFFFFFFE);
		core->MULTU();
		EXPECT_EQ(0x0000000A, vm->getResources()->EE->EECore->R5900->LO->readDword(RAW, 0));
		EXPECT_EQ(0xFFFFFFF9, vm->getResources()->EE->EECore->R5900->HI->readDword(RAW, 0));
	}

	// DIV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 26);
		EXPECT_STREQ("DIV", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xFFFFFFFB);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0xFFFFFFFE);
		core->DIV();
		EXPECT_EQ(0x2, vm->getResources()->EE->EECore->R5900->LO->readDword(RAW, 0));
		EXPECT_EQ(0xFFFFFFFF, vm->getResources()->EE->EECore->R5900->HI->readDword(RAW, 0));
	}

	// DIVU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 27);
		EXPECT_STREQ("DIVU", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0x10);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(RAW, 0, 0x7);
		core->DIVU();
		EXPECT_EQ(0x2, vm->getResources()->EE->EECore->R5900->LO->readDword(RAW, 0));
		EXPECT_EQ(0x2, vm->getResources()->EE->EECore->R5900->HI->readDword(RAW, 0));
	}

	// J
	{
		auto inst = MIPSUtil::genJInstruction(2, 0x3F00400);
		EXPECT_STREQ("J", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(0xBFC00000);
		core->J();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFC01000, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
	}

	// JAL
	{
		auto inst = MIPSUtil::genJInstruction(3, 0x3F00400);
		EXPECT_STREQ("JAL", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(0xBFC00000);
		core->JAL();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFC01000, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
		EXPECT_EQ(0xBFC00008, vm->getResources()->EE->EECore->R5900->GPR[31]->readDword(RAW, 0));
	}

	// JALR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 0, 31, 0, 9);
		EXPECT_STREQ("JALR", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(0xBFC00000);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xBFC01000);
		core->JALR();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFC01000, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
		EXPECT_EQ(0xBFC00008, vm->getResources()->EE->EECore->R5900->GPR[31]->readDword(RAW, 0));
	}

	// JR
	{
		auto inst = MIPSUtil::genRInstruction(0, 31, 0, 0, 0, 8);
		EXPECT_STREQ("JR", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[31]->writeDword(RAW, 0, 0xBFC00008);
		core->JR();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow();
		EXPECT_EQ(0xBFC00008, vm->getResources()->EE->EECore->R5900->PC->readWord(RAW));
	}

	// LB
	{
		auto inst = MIPSUtil::genIInstruction(32, 4, 2, -4);
		EXPECT_STREQ("LB", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->PhysicalMMU->writeByte(RAW, 0x0, 0xCD);
		core->LB();
		EXPECT_EQ(0xFFFFFFCD, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// LBU
	{
		auto inst = MIPSUtil::genIInstruction(36, 4, 2, -4);
		EXPECT_STREQ("LBU", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->PhysicalMMU->writeByte(RAW, 0x0, 0xAB);
		core->LBU();
		EXPECT_EQ(0xAB, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// LH
	{
		auto inst = MIPSUtil::genIInstruction(33, 4, 2, -4);
		EXPECT_STREQ("LH", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->PhysicalMMU->writeHword(RAW, 0x0, 0xCDEF);
		core->LH();
		EXPECT_EQ(0xFFFFCDEF, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// LHU
	{
		auto inst = MIPSUtil::genIInstruction(37, 4, 2, -4);
		EXPECT_STREQ("LHU", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->PhysicalMMU->writeHword(RAW, 0x0, 0xABCD);
		core->LHU();
		EXPECT_EQ(0xABCD, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// LW
	{
		auto inst = MIPSUtil::genIInstruction(35, 4, 2, -4);
		EXPECT_STREQ("LW", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->PhysicalMMU->writeDword(RAW, 0x0, 0x12345678);
		core->LW();
		EXPECT_EQ(0x12345678, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SB
	{
		auto inst = MIPSUtil::genIInstruction(40, 4, 2, -4);
		EXPECT_STREQ("SB", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(RAW, 0, 0x1234ABCD);
		core->SB();
		EXPECT_EQ(0xCD, vm->getResources()->EE->PhysicalMMU->readByte(RAW, 0x0));
	}

	// SH
	{
		auto inst = MIPSUtil::genIInstruction(41, 4, 2, -4);
		EXPECT_STREQ("SH", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(RAW, 0, 0x1234ABCD);
		core->SH();
		EXPECT_EQ(0xABCD, vm->getResources()->EE->PhysicalMMU->readHword(RAW, 0x0));
	}

	// SW
	{
		auto inst = MIPSUtil::genIInstruction(43, 4, 2, -4);
		EXPECT_STREQ("SW", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(RAW, 0, 0x1234ABCD);
		core->SW();
		EXPECT_EQ(0x1234ABCD, vm->getResources()->EE->PhysicalMMU->readDword(RAW, 0x0));
	}

	// LWL
	{
		auto inst = MIPSUtil::genIInstruction(34, 4, 2, -3);
		EXPECT_STREQ("LWL", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(RAW, 0, 0xCDCDCDCD);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->PhysicalMMU->writeDword(RAW, 0x0, 0x01234567);
		core->LWL();
		EXPECT_EQ(0x4567CDCD, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// LWR
	{
		auto inst = MIPSUtil::genIInstruction(38, 4, 2, 2);
		EXPECT_STREQ("LWR", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(RAW, 0, 0xCDCDCDCD);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->PhysicalMMU->writeDword(RAW, 0x4, 0x89ABCDEF);
		core->LWR();
		EXPECT_EQ(0xCDCD89AB, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(RAW, 0));
	}

	// SWL
	{
		auto inst = MIPSUtil::genIInstruction(42, 4, 2, -3);
		EXPECT_STREQ("SWL", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(RAW, 0, 0x11111111);
		vm->getResources()->EE->PhysicalMMU->writeDword(RAW, 0x0, 0xABABABAB);
		core->SWL();
		EXPECT_EQ(0xABAB1111, vm->getResources()->EE->PhysicalMMU->readDword(RAW, 0x0));
	}

	// SWR
	{
		auto inst = MIPSUtil::genIInstruction(46, 4, 2, 2);
		EXPECT_STREQ("SWR", EECoreInstructionTable::getInstructionInfo(inst)->mMnemonic);
		core->mInstruction.setInstructionValue(inst);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(RAW, 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(RAW, 0, 0x11111111);
		vm->getResources()->EE->PhysicalMMU->writeDword(RAW, 0x4, 0xCDCDCDCD);
		core->SWR();
		EXPECT_EQ(0x1111CDCD, vm->getResources()->EE->PhysicalMMU->readDword(RAW, 0x4));
	}
}

/*
TEST_F(TEST_EECoreInterpreter_s, SONY_MMI_INSTRUCTION_IMPLEMENTATIONS)
{
}
*/