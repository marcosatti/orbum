// PCSX2_Core_UnitTest.cpp : Defines the entry point for the console application.

// Dont have to touch this file - you can put tests in separate source files if you wish.

#include <gtest/gtest.h>

int main(int argc, char **argv) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}