#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Register/BitfieldRegister16_t.h"

/*
The SPU2 Core Voice VOL general purpose bitfield register.
*/
class SPU2CoreVoiceRegister_VOL_t : public BitfieldRegister16_t
{
public:
	struct Fields
	{
		static constexpr int ConstValue = 0;
		static constexpr int ConstToggle = 1;
		static constexpr int LinExpMode = 2;
		static constexpr int X = 3;
		static constexpr int LinExpValue = 4;
	};

	SPU2CoreVoiceRegister_VOL_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The SPU2 ADSR1 register.
*/
class SPU2CoreVoiceRegister_ADSR1_t : public BitfieldRegister16_t
{
public:
	struct Fields
	{
		static constexpr int SL = 0;
		static constexpr int DR = 1;
		static constexpr int AR = 2;
		static constexpr int X = 3;
	};

	SPU2CoreVoiceRegister_ADSR1_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The SPU2 ADSR2 register.
*/
class SPU2CoreVoiceRegister_ADSR2_t : public BitfieldRegister16_t
{
public:
	struct Fields
	{
		static constexpr int RR = 0;
		static constexpr int Z = 1;
		static constexpr int SR = 2;
		static constexpr int Y = 3;
	};

	SPU2CoreVoiceRegister_ADSR2_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};