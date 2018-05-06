#pragma once

#include "Common/Types/Register/SizedHwordRegister.hpp"

#include "Resources/Spu2/Spu2CoreVoiceRegisters.hpp"

/// SPU2 core voice. There are 24 voices per core.
class Spu2CoreVoice
{
public:
	SizedHwordRegister          voll;
	SizedHwordRegister          volr;
	SizedHwordRegister          pitch;
	Spu2CoreVoiceRegister_Adsr1 adsr1;
	Spu2CoreVoiceRegister_Adsr2 adsr2;
	SizedHwordRegister          envx;
	SizedHwordRegister          volxl;
	SizedHwordRegister          volxr;
	SizedHwordRegister          ssah;
	SizedHwordRegister          ssal;
	SizedHwordRegister          lsaxh;
	SizedHwordRegister          lsaxl;
	SizedHwordRegister          naxh;
	SizedHwordRegister          naxl;
};