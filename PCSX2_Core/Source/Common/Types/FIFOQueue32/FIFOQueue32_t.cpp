#include "stdafx.h"

#include "Common/Types/FIFOQueue32/FIFOQueue32_t.h"

FIFOQueue32_t::FIFOQueue32_t(const size_t& maxSize) :
	mMnemonic(""),
	mMaxSize(maxSize)
{
}

FIFOQueue32_t::FIFOQueue32_t(const char* mnemonic, const size_t& maxSize) :
	mMnemonic(mnemonic),
	mMaxSize(maxSize)
{
}

u32 FIFOQueue32_t::readWord(const System_t context)
{
	auto temp = mFIFOQueue.front();
	mFIFOQueue.pop();
	return temp;
}

u128 FIFOQueue32_t::readQword(const System_t context)
{
	u128 data;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
		data.UW[i] = readWord(context);
	
	return data;
}

void FIFOQueue32_t::writeWord(const System_t context, const u32 data)
{
	if ((getCurrentSize() + 1) > mMaxSize)
		throw std::runtime_error("FIFO Queue overloaded. Please fix.");

	mFIFOQueue.push(data);
}

void FIFOQueue32_t::writeQword(const System_t context, const u128 data)
{
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
		writeWord(context, data.UW[i]); 
}

size_t FIFOQueue32_t::getCurrentSize() const
{
	return mFIFOQueue.size();
}

size_t FIFOQueue32_t::getMaxSize() const
{
	return mMaxSize;
}

const char* FIFOQueue32_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
