#pragma once

#include <string>

/*
Helper base class for accessing debug functionality.
*/
class DebugBaseObject_t
{
public:
	DebugBaseObject_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
		mMnemonic(mnemonic),
		mDebugReads(debugReads),
		mDebugWrites(debugWrites)
	{
	}

protected:
	std::string mMnemonic;
	bool mDebugReads;
	bool mDebugWrites;
};