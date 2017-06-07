#include <Common/Global/Globals.h>
#include <Common/Types/MIPS/MIPSInstruction_t.h>

#define BOOST_TEST_MODULE TEST_MIPSInstruction_t
#include <boost/test/unit_test.hpp>

/*
BOOST_AUTO_TEST_CASE(TEST_MIPSInstruction_t_RType)
{
	// SUB $7, $8, $9
	u32 rawInstruction = 0x01093822; // (8 << 21) | (9 << 16) | (7 << 11) | 34;

	MIPSInstruction_t instruction(rawInstruction);

	BOOST_TEST(instruction.getOpcode() == 0);
	BOOST_TEST(instruction.getRs() == 8);
	BOOST_TEST(instruction.getRt() == 9);
	BOOST_TEST(instruction.getRRd() == 7);
	BOOST_TEST(instruction.getRShamt() == 0);
	BOOST_TEST(instruction.getRFunct() == 34);
}

BOOST_AUTO_TEST_CASE(TEST_MIPSInstruction_t_IType)
{
	// LHU $5, +254($10)
	u32 rawInstruction = 0x954500FE; // (37 << 26) | (10 << 21) | (5 << 16) | 254;

	MIPSInstruction_t instruction(rawInstruction);

	BOOST_TEST(instruction.getOpcode() == 37);
	BOOST_TEST(instruction.getRs() == 10);
	BOOST_TEST(instruction.getRt() == 5);
	BOOST_TEST(instruction.getIImmS() == 254);
}

BOOST_AUTO_TEST_CASE(TEST_MIPSInstruction_t_JType)
{
	// J 4096
	u32 rawInstruction = 0x08001000;

	MIPSInstruction_t instruction(rawInstruction);

	BOOST_TEST(instruction.getOpcode() == 2);
	BOOST_TEST(instruction.getJRegionAddress() == 4096);
}
*/