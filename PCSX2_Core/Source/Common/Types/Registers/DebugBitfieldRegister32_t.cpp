#include "stdafx.h"

#include "Common/Global/Globals.h"

#if defined(BUILD_DEBUG)

#include "Common/Types/Registers/DebugBitfieldRegister32_t.h"

DebugBitfieldRegister32_t::DebugBitfieldRegister32_t(const char* mnemonic) :
	BitfieldRegister32_t(mnemonic)
{
}

DebugBitfieldRegister32_t::~DebugBitfieldRegister32_t()
{
}

u32 DebugBitfieldRegister32_t::readWord()
{
	auto value = BitfieldRegister32_t::readWord();
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Read u32, Value = %d.", getMnemonic(), value);
#endif
	logDebugAllFields();
	return value;
}

void DebugBitfieldRegister32_t::writeWord(u32 value)
{
	BitfieldRegister32_t::writeWord(value);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Write u32, Value = %d.", getMnemonic() value);
#endif
	logDebugAllFields();
}

void DebugBitfieldRegister32_t::logDebugAllFields()
{
	for (auto &field : mFieldMap)
	{
		// I'll assume that when an empty mnemonic is encountered, its because the rest of the fields arent defined.
		// I'm also sorry in advance if anyone has to debug the debug function :) .
		if (field.mFieldName.empty())
			break;

#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("\t%s = 0x%X.", field.mFieldName.c_str(), field.mFieldValue);
#else
		logDebug("\t%s = %d.", field.mFieldName.c_str(), field.mFieldValue);
#endif
	}
}
#endif
