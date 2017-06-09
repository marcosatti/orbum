#include <VM/VM.h>
#include <VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h>
#include <Resources/Resources_t.h>
#include <Resources/IOP/IOP_t.h>
#include <Resources/IOP/IOPCore/IOPCore_t.h>
#include <Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h>
#include <Common/Types/Register/Register32_t.h>
#include <Common/Types/ByteMMU/ByteMMU_t.h>
#include <Common/Types/Register/PCRegister32_t.h>

#include "Util/MIPSUtil.h"

#include <boost/test/unit_test.hpp>

class R_TEST_IOPCoreInterpreter_s
{
public:
	R_TEST_IOPCoreInterpreter_s()
	{
		VMOptions vmOptions =
		{
			nullptr,
			"",
			"",
			"",
			"",
			0,
			VMOptions::ST,
			{}
		};

		vm = new VM(vmOptions);
		vm->reset(false);
        core = vm->mSystemIOPCore.get();
		BOOST_TEST_MESSAGE("Setup EECoreInterpreter_s");
	}

	~R_TEST_IOPCoreInterpreter_s()
	{
		core = nullptr;
		delete vm;
		BOOST_TEST_MESSAGE("TearDown EECoreInterpreter_s");
	}

	VM * vm;
	IOPCoreInterpreter_s * core;
};

BOOST_FIXTURE_TEST_SUITE(TEST_IOPCoreInterpreter_s, R_TEST_IOPCoreInterpreter_s)

BOOST_AUTO_TEST_CASE(MIPS_INSTRUCTION_IMPLEMENTATIONS)
{
	// Test follows the basic MIPS I instruction set.
	// https://en.wikipedia.org/wiki/MIPS_instruction_set

	// ADD
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 32);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("ADD" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 5412);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 7891);
		core->ADD();
		BOOST_TEST(13303 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// ADDI
	{
		auto inst = MIPSUtil::genIInstruction(8, 4, 2, -256);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("ADDI" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 5412);
		core->ADDI();
		BOOST_TEST(5156 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SUB
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 34);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SUB" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 12345);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 81);
		core->SUB();
		BOOST_TEST(12264 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// ADDU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 33);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("ADDU" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 5412);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), -7891);
		core->ADDU();
		BOOST_TEST(-2479 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SUBU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 35);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SUBU" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 64841);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 314898);
		core->SUBU();
		BOOST_TEST(-250057 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// ADDIU
	{
		auto inst = MIPSUtil::genIInstruction(9, 4, 2, -256);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("ADDIU" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 12);
		core->ADDIU();
		BOOST_TEST(-244 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// AND
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 36);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("AND" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x1234ABCD);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x56789EF0);
		core->AND();
		BOOST_TEST(0x12308AC0 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// ANDI
	{
		auto inst = MIPSUtil::genIInstruction(12, 4, 2, 0xCCCC);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("ANDI" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x66666666);
		core->ANDI();
		BOOST_TEST(0x4444 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// OR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 37);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("OR" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x88888888);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x11111111);
		core->OR();
		BOOST_TEST(0x99999999 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// ORI
	{
		auto inst = MIPSUtil::genIInstruction(13, 4, 2, 0x8888);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("ORI" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x11111111);
		core->ORI();
		BOOST_TEST(0x11119999 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// NOR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 39);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("NOR" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x88888888);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x77777777);
		core->NOR();
		BOOST_TEST(0x0 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}


	// SLL
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 2, 0);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SLL" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x11111111);
		core->SLL();
		BOOST_TEST(0x44444444 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SLLV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 4);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SLLV" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x3);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x11111111);
		core->SLLV();
		BOOST_TEST(0x88888888 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SRA
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 3);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SRA" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x88888888);
		core->SRA();
		BOOST_TEST(0xF8888888 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SRAV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 7);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SRAV" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0X4);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x88888888);
		core->SRAV();
		BOOST_TEST(0xF8888888 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SRL
	{
		auto inst = MIPSUtil::genRInstruction(0, 0, 5, 2, 4, 2);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SRL" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x88888888);
		core->SRL();
		BOOST_TEST(0x08888888 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SRLV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 6);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SRLV" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0X4);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x88888888);
		core->SRLV();
		BOOST_TEST(0x08888888 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SLT
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 42);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SLT" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x10);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x20);
		core->SLT();
		BOOST_TEST(0x1 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SLTI
	{
		auto inst = MIPSUtil::genIInstruction(10, 4, 2, -256);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SLTI" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), -1000);
		core->SLTI();
		BOOST_TEST(0x1 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SLTU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 43);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SLTU" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x8E000000);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x8F000000);
		core->SLTU();
		BOOST_TEST(0x1 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SLTIU
	{
		auto inst = MIPSUtil::genIInstruction(11, 4, 2, -256);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SLTIU" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), -1000);
		core->SLTIU();
		BOOST_TEST(0x1 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// XOR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 2, 0, 38);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("XOR" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x88888888);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0xFFFFFFFF);
		core->XOR();
		BOOST_TEST(0x77777777 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// XORI
	{
		auto inst = MIPSUtil::genIInstruction(14, 4, 2, 0x8888);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("XORI" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xFFFFFFFF);
		core->XORI();
		BOOST_TEST(0xFFFF7777 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// LUI
	{
		auto inst = MIPSUtil::genIInstruction(15, 0, 2, 0x8888);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("LUI" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		core->LUI();
		BOOST_TEST(0x88880000 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// BEQ
	{
		auto inst = MIPSUtil::genIInstruction(4, 4, 2, -256);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("BEQ" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(core->getContext(), 0x1234ABCD);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x1234ABCD);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BEQ();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFBFFC04 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
	}

	// BGEZ
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 1, 63);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("BGEZ" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x1);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BGEZ();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFC00100 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
	}

	// BGEZAL
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 17, 63);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("BGEZAL" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x0);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BGEZAL();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFC00100 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
		BOOST_TEST(0xBFC00008 == vm->getResources()->IOP->IOPCore->R3000->GPR[31]->readWord(core->getContext()));
	}

	// BGTZ
	{
		auto inst = MIPSUtil::genIInstruction(7, 4, 0, 63);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("BGTZ" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x1);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BGTZ();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFC00100 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
	}

	// BLEZ
	{
		auto inst = MIPSUtil::genIInstruction(6, 4, 0, 63);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("BLEZ" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x87654321);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BLEZ();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFC00100 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
	}

	// BLTZ
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 0, 63);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("BLTZ" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x87654321);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BLTZ();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFC00100 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
	}

	// BLTZAL
	{
		auto inst = MIPSUtil::genIInstruction(1, 4, 16, 63);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("BLTZAL" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x87654321);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BLTZAL();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFC00100 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
		BOOST_TEST(0xBFC00008 == vm->getResources()->IOP->IOPCore->R3000->GPR[31]->readWord(core->getContext()));
	}

	// BNE
	{
		auto inst = MIPSUtil::genIInstruction(5, 4, 2, -256);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("BNE" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(core->getContext(), 0x87654321);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x1234ABCD);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->BNE();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFBFFC04 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
	}

	// MULT
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 24);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("MULT" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xFFFFFFFB);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0xFFFFFFFE);
		core->MULT();
		BOOST_TEST(0xA == vm->getResources()->IOP->IOPCore->R3000->LO->readWord(core->getContext()));
		BOOST_TEST(0x0 == vm->getResources()->IOP->IOPCore->R3000->HI->readWord(core->getContext()));
	}

	// MULTU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 25);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("MULTU" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xFFFFFFFB);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0xFFFFFFFE);
		core->MULTU();
		BOOST_TEST(0x0000000A == vm->getResources()->IOP->IOPCore->R3000->LO->readWord(core->getContext()));
		BOOST_TEST(0xFFFFFFF9 == vm->getResources()->IOP->IOPCore->R3000->HI->readWord(core->getContext()));
	}

	// DIV
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 26);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("DIV" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xFFFFFFFB);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0xFFFFFFFE);
		core->DIV();
		BOOST_TEST(0x2 == vm->getResources()->IOP->IOPCore->R3000->LO->readWord(core->getContext()));
		BOOST_TEST(0xFFFFFFFF == vm->getResources()->IOP->IOPCore->R3000->HI->readWord(core->getContext()));
	}

	// DIVU
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 5, 0, 0, 27);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("DIVU" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0x10);
		vm->getResources()->IOP->IOPCore->R3000->GPR[5]->writeWord(core->getContext(), 0x7);
		core->DIVU();
		BOOST_TEST(0x2 == vm->getResources()->IOP->IOPCore->R3000->LO->readWord(core->getContext()));
		BOOST_TEST(0x2 == vm->getResources()->IOP->IOPCore->R3000->HI->readWord(core->getContext()));
	}

	// J
	{
		auto inst = MIPSUtil::genJInstruction(2, 0x3F00400);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("J" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->J();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFC01000 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
	}

	// JAL
	{
		auto inst = MIPSUtil::genJInstruction(3, 0x3F00400);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("JAL" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		core->JAL();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFC01000 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
		BOOST_TEST(0xBFC00008 == vm->getResources()->IOP->IOPCore->R3000->GPR[31]->readWord(core->getContext()));
	}

	// JALR
	{
		auto inst = MIPSUtil::genRInstruction(0, 4, 0, 31, 0, 9);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("JALR" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->PC->setPCValueAbsolute(core->getContext(), 0xBFC00000);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xBFC01000);
		core->JALR();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFC01000 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
		BOOST_TEST(0xBFC00008 == vm->getResources()->IOP->IOPCore->R3000->GPR[31]->readWord(core->getContext()));
	}

	// JR
	{
		auto inst = MIPSUtil::genRInstruction(0, 31, 0, 0, 0, 8);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("JR" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[31]->writeWord(core->getContext(), 0xBFC00008);
		core->JR();
		BOOST_TEST(true == vm->getResources()->IOP->IOPCore->R3000->PC->isBranchPending());
		vm->getResources()->IOP->IOPCore->R3000->PC->doBranchNow(core->getContext());
		BOOST_TEST(0xBFC00008 == vm->getResources()->IOP->IOPCore->R3000->PC->readWord(core->getContext()));
	}

	// LB
	{
		auto inst = MIPSUtil::genIInstruction(32, 4, 2, -4);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("LB" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->MMU->writeByte(core->getContext(), 0x0, 0xCD);
		core->LB();
		BOOST_TEST(0xFFFFFFCD == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// LBU
	{
		auto inst = MIPSUtil::genIInstruction(36, 4, 2, -4);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("LBU" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->MMU->writeByte(core->getContext(), 0x0, 0xAB);
		core->LBU();
		BOOST_TEST(0xAB == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// LH
	{
		auto inst = MIPSUtil::genIInstruction(33, 4, 2, -4);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("LH" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->MMU->writeHword(core->getContext(), 0x0, 0xCDEF);
		core->LH();
		BOOST_TEST(0xFFFFCDEF == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// LHU
	{
		auto inst = MIPSUtil::genIInstruction(37, 4, 2, -4);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("LHU" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->MMU->writeHword(core->getContext(), 0x0, 0xABCD);
		core->LHU();
		BOOST_TEST(0xABCD == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// LW
	{
		auto inst = MIPSUtil::genIInstruction(35, 4, 2, -4);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("LW" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->MMU->writeWord(core->getContext(), 0x0, 0x12345678);
		core->LW();
		BOOST_TEST(0x12345678 == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SB
	{
		auto inst = MIPSUtil::genIInstruction(40, 4, 2, -4);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SB" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(core->getContext(), 0x1234ABCD);
		core->SB();
		BOOST_TEST(0xCD == vm->getResources()->IOP->MMU->readByte(core->getContext(), 0x0));
	}

	// SH
	{
		auto inst = MIPSUtil::genIInstruction(41, 4, 2, -4);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SH" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(core->getContext(), 0x1234ABCD);
		core->SH();
		BOOST_TEST(0xABCD == vm->getResources()->IOP->MMU->readHword(core->getContext(), 0x0));
	}

	// SW
	{
		auto inst = MIPSUtil::genIInstruction(43, 4, 2, -4);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SW" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(core->getContext(), 0x1234ABCD);
		core->SW();
		BOOST_TEST(0x1234ABCD == vm->getResources()->IOP->MMU->readWord(core->getContext(), 0x0));
	}

	// LWL
	{
		auto inst = MIPSUtil::genIInstruction(34, 4, 2, -3);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("LWL" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(core->getContext(), 0xCDCDCDCD);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->MMU->writeWord(core->getContext(), 0x0, 0x01234567);
		core->LWL();
		BOOST_TEST(0x4567CDCD == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// LWR
	{
		auto inst = MIPSUtil::genIInstruction(38, 4, 2, 2);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("LWR" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(core->getContext(), 0xCDCDCDCD);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->MMU->writeWord(core->getContext(), 0x4, 0x89ABCDEF);
		core->LWR();
		BOOST_TEST(0xCDCD89AB == vm->getResources()->IOP->IOPCore->R3000->GPR[2]->readWord(core->getContext()));
	}

	// SWL
	{
		auto inst = MIPSUtil::genIInstruction(42, 4, 2, -3);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SWL" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(core->getContext(), 0x11111111);
		vm->getResources()->IOP->MMU->writeWord(core->getContext(), 0x0, 0xABABABAB);
		core->SWL();
		BOOST_TEST(0xABAB1111 == vm->getResources()->IOP->MMU->readWord(core->getContext(), 0x0));
	}

	// SWR
	{
		auto inst = MIPSUtil::genIInstruction(46, 4, 2, 2);
		core->mIOPCoreInstruction = inst;
		BOOST_TEST("SWR" == core->mIOPCoreInstruction.getInfo()->mMIPSInstructionInfo.mMnemonic);
		vm->getResources()->IOP->IOPCore->R3000->GPR[4]->writeWord(core->getContext(), 0xA0000004);
		vm->getResources()->IOP->IOPCore->R3000->GPR[2]->writeWord(core->getContext(), 0x11111111);
		vm->getResources()->IOP->MMU->writeWord(core->getContext(), 0x4, 0xCDCDCDCD);
		core->SWR();
		BOOST_TEST(0x1111CDCD == vm->getResources()->IOP->MMU->readWord(core->getContext(), 0x4));
	}
}

BOOST_AUTO_TEST_SUITE_END()