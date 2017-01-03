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

u32 FIFOQueue_t::readWord(const Context_t& context)
{
	auto temp = mFIFOQueue.front();
	mFIFOQueue.pop();
	return temp;
}

u128 FIFOQueue_t::readQword(const Context_t& context)
{
	u128 data;
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto temp = mFIFOQueue.front();
		mFIFOQueue.pop();
		data.UW[i] = temp;
	}
	
	return data;
}

void FIFOQueue_t::writeWord(const Context_t& context, const u32 & data)
{
	if ((getCurrentSize() + 1) > mMaxSize)
		throw std::runtime_error("FIFO Queue overloaded. Please fix.");

	mFIFOQueue.push(data);
}

void FIFOQueue_t::writeQword(const Context_t& context, const u128 & data)
{
	if ((getCurrentSize() + Constants::NUMBER_WORDS_IN_QWORD) > mMaxSize)
		throw std::runtime_error("FIFO Queue overloaded. Please fix.");

	mFIFOQueue.push(data.UW[0]);
	mFIFOQueue.push(data.UW[1]);
	mFIFOQueue.push(data.UW[2]);
	mFIFOQueue.push(data.UW[3]);
}

bool FIFOQueue_t::isEmpty() const
{
	return getCurrentSize() == 0;
}

bool FIFOQueue_t::isFull() const
{
	return !(getCurrentSize() < getMaxSize());
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
