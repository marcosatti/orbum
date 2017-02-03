#include "stdafx.h"

#include "FIFOQueue_t.h"

FIFOQueue_t::FIFOQueue_t(const size_t& maxSize) :
	mMnemonic(""),
	mMaxSize(maxSize)
{
}

FIFOQueue_t::FIFOQueue_t(const char* mnemonic, const size_t& maxSize) :
	mMnemonic(mnemonic),
	mMaxSize(maxSize)
{
}

FIFOQueue_t::~FIFOQueue_t()
{
}

u32 FIFOQueue_t::readWord(const Context& context)
{
	auto temp = mFIFOQueue.front();
	mFIFOQueue.pop();
	return temp;
}

u128 FIFOQueue_t::readQword(const Context& context)
{
	u128 data;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
		data.UW[i] = readWord(context);
	
	return data;
}

void FIFOQueue_t::writeWord(const Context& context, const u32 & data)
{
	if ((getCurrentSize() + 1) > mMaxSize)
		throw std::runtime_error("FIFO Queue overloaded. Please fix.");

	mFIFOQueue.push(data);
}

void FIFOQueue_t::writeQword(const Context& context, const u128 & data)
{
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
		writeWord(context, data.UW[i]); 
}

bool FIFOQueue_t::isEmpty() const
{
	return getCurrentSize() == 0;
}

bool FIFOQueue_t::isFull() const
{
	return getCurrentSize() >= getMaxSize();
}

size_t FIFOQueue_t::getCurrentSize() const
{
	return mFIFOQueue.size();
}

size_t FIFOQueue_t::getMaxSize() const
{
	return mMaxSize;
}

const char* FIFOQueue_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
