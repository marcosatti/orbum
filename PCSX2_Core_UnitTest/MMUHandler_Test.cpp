#include "stdafx.h"
#include <gtest/gtest.h>

#include "Globals.h"
#include "MMUHandler.h"

TEST(MMUHandler_Test, AllPTEsValidNotNull_MAX_MAP_SIZE) {
	MMUHandler a(nullptr);

	u8 * MEMORYBLOCK = new u8[a.getTableMaxSize()];
	a.mapMemory(MEMORYBLOCK, a.getTableMaxSize(), 0x0);

	// Check if all PTE's are valid and not null.
	for (u32 i = 0; i < a.getTableMaxSize(); i++)
	{
		EXPECT_NE(nullptr, a.getclientMemoryAddress(i));
	}

	delete[] MEMORYBLOCK;
}

TEST(MMUHandler_Test, AllPTEsValidNotNull_MIN_PAGE_SIZE) {
	MMUHandler a(nullptr);

	u8 ** MEMORYBLOCKS = new u8*[a.getTotalPageEntries()];
	for (u32 i = 0; i < a.getTotalPageEntries(); i++)
	{
		MEMORYBLOCKS[i] = new u8[a.getPageSizeBytes()];
		a.mapMemory(MEMORYBLOCKS[i], a.getPageSizeBytes(), i * a.getPageSizeBytes());
	}

	// Check if all PTE's are valid and not null.
	for (u32 i = 0; i < a.getTableMaxSize(); i++)
	{
		EXPECT_NE(nullptr, a.getclientMemoryAddress(i));
	}

	for (u32 i = 0; i < a.getTotalPageEntries(); i++)
	{
		delete[] MEMORYBLOCKS[i];
	}

	delete[] MEMORYBLOCKS;
}