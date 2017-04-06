#include "stdafx.h"
#include <gtest/gtest.h>

#include <VM/VM.h>
#include <VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h>
#include <Resources/Resources_t.h>
#include <Resources/EE/EE_t.h>
#include <Resources/EE/EECore/EECore_t.h>
#include <Resources/EE/EECore/Types/EECoreR5900_t.h>
#include <Common/Types/Register/Register32_t.h>
#include <Common/Types/Register/Register128_t.h>
#include <Common/Types/ByteMMU/ByteMMU_t.h>
#include <Common/Types/Register/PCRegister32_t.h>
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
	// Test follows the basic MIPS III / IV instruction set.
	// https://en.wikipedia.org/wiki/MIPS_instruction_set

	// ADD
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 32);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("ADD", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, static_cast<s64>(-5412));
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, static_cast<s64>(-7891));
		core->ADD();
		EXPECT_EQ(-13303, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// ADDI
	{
		auto inst = MIPSUtil::genIInstruction(8, 4, 2, 256);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("ADDI", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, static_cast<s64>(-5412));
		core->ADDI();
		EXPECT_EQ(-5156, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// ADDIU
	{
		auto inst = MIPSUtil::genIInstruction(9, 4, 2, -256);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("ADDIU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 12);
		core->ADDIU();
		EXPECT_EQ(-244, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// ADDU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 33);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("ADDU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 5412);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, static_cast<s64>(-7891));
		core->ADDU();
		EXPECT_EQ(-2479, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// DADD
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 44);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DADD", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x30000002CCCCDDDD);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0x0EEEEFF000000000);
		core->DADD();
		EXPECT_EQ(0x3EEEEFF2CCCCDDDD, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// DADDI
	{
		auto inst = MIPSUtil::genIInstruction(24, 4, 2, 256);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DADDI", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, static_cast<s64>(-5412));
		core->DADDI();
		EXPECT_EQ(-5156, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// DADDU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 45);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DADDU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 5412);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, static_cast<s64>(-7891));
		core->DADDU();
		EXPECT_EQ(-2479, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// DADDIU
	{
		auto inst = MIPSUtil::genIInstruction(25, 4, 2, -256);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DADDIU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 12);
		core->DADDIU();
		EXPECT_EQ(-244, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// SUB
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 34);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SUB", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, static_cast<s64>(-12345));
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, static_cast<s64>(-81));
		core->SUB();
		EXPECT_EQ(-12264, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// SUBU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 35);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SUBU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 5649652);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, static_cast<s64>(-856261945));
		core->SUBU();
		EXPECT_EQ(861911597, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// DSUB
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 46);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DSUB", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, static_cast<s64>(-12345));
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, static_cast<s64>(-81));
		core->DSUB();
		EXPECT_EQ(-12264, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// DSUBU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 47);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DSUBU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 5649652);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, static_cast<s64>(-856261945));
		core->DSUBU();
		EXPECT_EQ(861911597, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// MOVN
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 11);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("MOVN", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x20);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 1);
		core->MOVN();
		EXPECT_EQ(0x20, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// MOVZ
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 10);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("MOVZ", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x20);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0);
		core->MOVZ();
		EXPECT_EQ(0x20, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// AND
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 36);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("AND", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, static_cast<s64>(-48446));
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, static_cast<s64>(-636952));
		core->AND();
		EXPECT_EQ(-638272, static_cast<s64>(vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0)));
	}

	// ANDI
	{
		auto inst = MIPSUtil::genIInstruction(12, 4, 2, 0xCCCC);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("ANDI", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xFFFFFFFF66666666);
		core->ANDI();
		EXPECT_EQ(0x4444, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// OR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 37);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("OR", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x88888888);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xFFFFFFFF11111111);
		core->OR();
		EXPECT_EQ(0xFFFFFFFF99999999, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// ORI
	{
		auto inst = MIPSUtil::genIInstruction(13, 4, 2, 0x8888);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("ORI", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xCCCCCCCC11111111);
		core->ORI();
		EXPECT_EQ(0xCCCCCCCC11119999, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// NOR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 39);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("NOR", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x88888888);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0x77777777);
		core->NOR();
		EXPECT_EQ(0xFFFFFFFF00000000, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SLL
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 0);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SLL", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0x08888888);
		core->SLL();
		EXPECT_EQ(0xFFFFFFFF88888880, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SLLV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 4);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SLLV", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x3);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0x11111111);
		core->SLLV();
		EXPECT_EQ(0xFFFFFFFF88888888, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SRA
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 3);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SRA", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0x88888888);
		core->SRA();
		EXPECT_EQ(0xFFFFFFFFF8888888, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SRAV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 7);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SRAV", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x4);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0x88888888);
		core->SRAV();
		EXPECT_EQ(0xFFFFFFFFF8888888, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SRL
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 2);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SRL", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0x88888888);
		core->SRL();
		EXPECT_EQ(0x08888888, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SRLV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 6);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SRLV", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x0);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0x88888888);
		core->SRLV();
		EXPECT_EQ(0xFFFFFFFF88888888, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// DSLL
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 28, 56);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DSLL", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xABABABAB);
		core->DSLL();
		EXPECT_EQ(0x0ABABABAB0000000, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// DSLL32
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 0, 60);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DSLL32", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xABABABAB);
		core->DSLL32();
		EXPECT_EQ(0xABABABAB00000000, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// DSLLV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 20);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DSLLV", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 35);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0x11111111);
		core->DSLLV();
		EXPECT_EQ(0x8888888800000000, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// DSRA
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 59);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DSRA", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xABABABABCDCDCDCD);
		core->DSRA();
		EXPECT_EQ(0xFABABABABCDCDCDC, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// DSRA32
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 28, 63);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DSRA32", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xABABABABCDCDCDCD);
		core->DSRA32();
		EXPECT_EQ(0xFFFFFFFFFFFFFFFA, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// DSRAV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 23);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DSRAV", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 60);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xABABABABCDCDCDCD);
		core->DSRAV();
		EXPECT_EQ(0xFFFFFFFFFFFFFFFA, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// DSRL
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 58);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DSRL", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xAAAABBBBCCCCDDDD);
		core->DSRL();
		EXPECT_EQ(0x0AAAABBBBCCCCDDD, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// DSRL32
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 62);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DSRL32", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xAAAABBBBCCCCDDDD);
		core->DSRL32();
		EXPECT_EQ(0x0AAAABBB, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// DSRLV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 22);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DSRLV", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 4);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xAAAABBBBCCCCDDDD);
		core->DSRLV();
		EXPECT_EQ(0x0AAAABBBBCCCCDDD, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SLT
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 42);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SLT", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, static_cast<s64>(-81));
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, static_cast<s64>(-1));
		core->SLT();
		EXPECT_EQ(0x1, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SLTI
	{
		auto inst = MIPSUtil::genIInstruction(10, 4, 2, -256);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SLTI", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, static_cast<s64>(-1000));
		core->SLTI();
		EXPECT_EQ(0x1, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SLTU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 43);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SLTU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 1);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, static_cast<s64>(-1));
		core->SLTU();
		EXPECT_EQ(0x1, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SLTIU
	{
		auto inst = MIPSUtil::genIInstruction(11, 4, 2, -256);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SLTIU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, static_cast<s64>(-1000));
		core->SLTIU();
		EXPECT_EQ(0x1, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// XOR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 38);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("XOR", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xFFFFFFFF88888888);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0x88888888FFFFFFFF);
		core->XOR();
		EXPECT_EQ(0x7777777777777777, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// XORI
	{
		auto inst = MIPSUtil::genIInstruction(14, 4, 2, 0x8888);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("XORI", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xFFFFFFFFFFFFFFFF);
		core->XORI();
		EXPECT_EQ(0xFFFFFFFFFFFF7777, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// LUI
	{
		auto inst = MIPSUtil::genIInstruction(15, 0, 2, 0x8888);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LUI", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		core->LUI();
		EXPECT_EQ(0xFFFFFFFF88880000, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// BEQ
	{
		auto inst = MIPSUtil::genIInstruction(4, 4, 2, -256);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("BEQ", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0x1234ABCD);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x1234ABCD);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BEQ();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFBFFC04, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
	}

	// BGEZ
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 1, 63);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("BGEZ", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x1);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BGEZ();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
	}

	// BGEZAL
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 17, 63);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("BGEZAL", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x0);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BGEZAL();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
		EXPECT_EQ(0xBFC00008, vm->getResources()->EE->EECore->R5900->GPR[31]->readDword(core->getContext(), 0));
	}

	// BGTZ
	{
		auto inst = MIPSUtil::genIInstruction(7, 4, 0, 63);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("BGTZ", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x1);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BGTZ();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
	}

	// BLEZ
	{
		auto inst = MIPSUtil::genIInstruction(6, 4, 0, 63);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("BLEZ", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BLEZ();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
	}

	// BLTZ
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 0, 63);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("BLTZ", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, static_cast<s64>(-1));
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BLTZ();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
	}

	// BLTZAL
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 16, 63);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("BLTZAL", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, static_cast<s64>(-1));
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BLTZAL();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFC00100, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
		EXPECT_EQ(0xBFC00008, vm->getResources()->EE->EECore->R5900->GPR[31]->readDword(core->getContext(), 0));
	}

	// BNE
	{
		auto inst = MIPSUtil::genIInstruction(5, 4, 2, -256);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("BNE", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0xFFFFFFFF87654321);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x1234ABCD);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BNE();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFBFFC04, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
	}

	// MULT
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 24);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("MULT", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xFFFFFFFFFFFFFFFB);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xFFFFFFFFFFFFFFFE);
		core->MULT();
		EXPECT_EQ(0xA, vm->getResources()->EE->EECore->R5900->LO->readDword(core->getContext(), 0));
		EXPECT_EQ(0x0, vm->getResources()->EE->EECore->R5900->HI->readDword(core->getContext(), 0));
	}

	// MULTU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 25);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("MULTU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xFFFFFFFFFFFFFFFB);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xFFFFFFFFFFFFFFFE);
		core->MULTU();
		EXPECT_EQ(0xA, vm->getResources()->EE->EECore->R5900->LO->readDword(core->getContext(), 0));
		EXPECT_EQ(0xFFFFFFFFFFFFFFF9, vm->getResources()->EE->EECore->R5900->HI->readDword(core->getContext(), 0));
	}

	// DIV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 26);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DIV", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xFFFFFFFFFFFFFFFB);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0xFFFFFFFFFFFFFFFE);
		core->DIV();
		EXPECT_EQ(0x2, vm->getResources()->EE->EECore->R5900->LO->readDword(core->getContext(), 0));
		EXPECT_EQ(0xFFFFFFFFFFFFFFFF, vm->getResources()->EE->EECore->R5900->HI->readDword(core->getContext(), 0));
	}

	// DIVU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 27);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("DIVU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0x10);
		vm->getResources()->EE->EECore->R5900->GPR[5]->writeDword(core->getContext(), 0, 0x7);
		core->DIVU();
		EXPECT_EQ(0x2, vm->getResources()->EE->EECore->R5900->LO->readDword(core->getContext(), 0));
		EXPECT_EQ(0x2, vm->getResources()->EE->EECore->R5900->HI->readDword(core->getContext(), 0));
	}

	// J
	{
		auto inst = MIPSUtil::genJInstruction(2, 0x3F00400);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("J", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->J();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFC01000, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
	}

	// JAL
	{
		auto inst = MIPSUtil::genJInstruction(3, 0x3F00400);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("JAL", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->JAL();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFC01000, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
		EXPECT_EQ(0xBFC00008, vm->getResources()->EE->EECore->R5900->GPR[31]->readDword(core->getContext(), 0));
	}

	// JALR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 0, 31, 0, 9);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("JALR", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xBFC01000);
		core->JALR();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFC01000, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
		EXPECT_EQ(0xBFC00008, vm->getResources()->EE->EECore->R5900->GPR[31]->readDword(core->getContext(), 0));
	}

	// JR
	{
		auto inst = MIPSUtil::genRInstruction(0, 31, 0, 0, 0, 8);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("JR", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[31]->writeDword(core->getContext(), 0, 0xBFC00008);
		core->JR();
		EXPECT_EQ(true, vm->getResources()->EE->EECore->R5900->PC->isBranchPending());
		vm->getResources()->EE->EECore->R5900->PC->doBranchNow(core->getContext());
		EXPECT_EQ(0xBFC00008, vm->getResources()->EE->EECore->R5900->PC->readWord(core->getContext()));
	}

	// LB
	{
		auto inst = MIPSUtil::genIInstruction(32, 4, 2, -4);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LB", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->MMU->writeByte(core->getContext(), 0x0, 0xCD);
		core->LB();
		EXPECT_EQ(0xFFFFFFFFFFFFFFCD, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// LBU
	{
		auto inst = MIPSUtil::genIInstruction(36, 4, 2, -4);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LBU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->MMU->writeByte(core->getContext(), 0x0, 0xAB);
		core->LBU();
		EXPECT_EQ(0xAB, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// LH
	{
		auto inst = MIPSUtil::genIInstruction(33, 4, 2, -4);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LH", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->MMU->writeHword(core->getContext(), 0x0, 0xCDEF);
		core->LH();
		EXPECT_EQ(0xFFFFFFFFFFFFCDEF, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// LHU
	{
		auto inst = MIPSUtil::genIInstruction(37, 4, 2, -4);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LHU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->MMU->writeHword(core->getContext(), 0x0, 0xABCD);
		core->LHU();
		EXPECT_EQ(0xABCD, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// LW
	{
		auto inst = MIPSUtil::genIInstruction(35, 4, 2, -4);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LW", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->MMU->writeWord(core->getContext(), 0x0, 0xF2345678);
		core->LW();
		EXPECT_EQ(0xFFFFFFFFF2345678, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// LWU
	{
		auto inst = MIPSUtil::genIInstruction(39, 4, 2, -4);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LWU", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->MMU->writeWord(core->getContext(), 0x0, 0xF2345678);
		core->LWU();
		EXPECT_EQ(0xF2345678, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// LD
	{
		auto inst = MIPSUtil::genIInstruction(55, 4, 2, -4);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LD", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->MMU->writeDword(core->getContext(), 0x0, 0x12345678ABCDEF0);
		core->LD();
		EXPECT_EQ(0x12345678ABCDEF0, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SB
	{
		auto inst = MIPSUtil::genIInstruction(40, 4, 2, -4);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SB", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0x1234ABCD);
		core->SB();
		EXPECT_EQ(0xCD, vm->getResources()->EE->MMU->readByte(core->getContext(), 0x0));
	}

	// SH
	{
		auto inst = MIPSUtil::genIInstruction(41, 4, 2, -4);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SH", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0x1234ABCD);
		core->SH();
		EXPECT_EQ(0xABCD, vm->getResources()->EE->MMU->readHword(core->getContext(), 0x0));
	}

	// SW
	{
		auto inst = MIPSUtil::genIInstruction(43, 4, 2, -4);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SW", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0x1234ABCD);
		core->SW();
		EXPECT_EQ(0x1234ABCD, vm->getResources()->EE->MMU->readWord(core->getContext(), 0x0));
	}

	// LWL
	{
		auto inst = MIPSUtil::genIInstruction(34, 4, 2, -3);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LWL", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0xCDCDCDCD);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->MMU->writeWord(core->getContext(), 0x0, 0x01234567);
		core->LWL();
		EXPECT_EQ(0x4567CDCD, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// LWR
	{
		auto inst = MIPSUtil::genIInstruction(38, 4, 2, 2);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LWR", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0xCDCDCDCD);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->MMU->writeWord(core->getContext(), 0x4, 0x89ABCDEF);
		core->LWR();
		EXPECT_EQ(0xFFFFFFFFCDCD89AB, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// LDL
	{
		auto inst = MIPSUtil::genIInstruction(26, 4, 2, -1);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LDL", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0xCDCDCDCDCDCDCDCD);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->MMU->writeDword(core->getContext(), 0x0, 0x4141414141414141);
		core->LDL();
		EXPECT_EQ(0x41414141CDCDCDCD, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// LDR
	{
		auto inst = MIPSUtil::genIInstruction(27, 4, 2, 0);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("LDR", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0xCDCDCDCDCDCDCDCD);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->MMU->writeDword(core->getContext(), 0x0, 0x4141414141414141);
		core->LDR();
		EXPECT_EQ(0xCDCDCDCD41414141, vm->getResources()->EE->EECore->R5900->GPR[2]->readDword(core->getContext(), 0));
	}

	// SWL
	{
		auto inst = MIPSUtil::genIInstruction(42, 4, 2, -3);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SWL", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0x11111111);
		vm->getResources()->EE->MMU->writeWord(core->getContext(), 0x0, 0xABABABAB);
		core->SWL();
		EXPECT_EQ(0xABAB1111, vm->getResources()->EE->MMU->readWord(core->getContext(), 0x0));
	}

	// SWR
	{
		auto inst = MIPSUtil::genIInstruction(46, 4, 2, 2);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SWR", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0x11111111);
		vm->getResources()->EE->MMU->writeWord(core->getContext(), 0x4, 0xCDCDCDCD);
		core->SWR();
		EXPECT_EQ(0x1111CDCD, vm->getResources()->EE->MMU->readWord(core->getContext(), 0x4));
	}

	// SDL
	{
		auto inst = MIPSUtil::genIInstruction(44, 4, 2, -1);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SDL", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0x4141414141414141);
		vm->getResources()->EE->MMU->writeDword(core->getContext(), 0x0, 0xCDCDCDCDCDCDCDCD);
		core->SDL();
		EXPECT_EQ(0xCDCDCDCD41414141, vm->getResources()->EE->MMU->readDword(core->getContext(), 0x0));
	}

	// SDR
	{
		auto inst = MIPSUtil::genIInstruction(45, 4, 2, 0);
		core->mEECoreInstruction = inst;
		EXPECT_STREQ("SDR", core->mEECoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->EE->EECore->R5900->GPR[4]->writeDword(core->getContext(), 0, 0xA0000004);
		vm->getResources()->EE->EECore->R5900->GPR[2]->writeDword(core->getContext(), 0, 0x4141414141414141);
		vm->getResources()->EE->MMU->writeDword(core->getContext(), 0x0, 0xCDCDCDCDCDCDCDCD);
		core->SDR();
		EXPECT_EQ(0x41414141CDCDCDCD, vm->getResources()->EE->MMU->readDword(core->getContext(), 0x0));
	}
}

/*
TEST_F(TEST_EECoreInterpreter_s, SONY_MMI_INSTRUCTION_IMPLEMENTATIONS)
{
}
*/