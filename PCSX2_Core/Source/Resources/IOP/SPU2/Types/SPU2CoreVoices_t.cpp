#include "stdafx.h"

#include "Common/Types/Register/Register16_t.h"

#include "Resources/IOP/SPU2/Types/SPU2CoreVoices_t.h"
#include "Resources/IOP/SPU2/Types/SPU2CoreVoiceRegisters_t.h"

SPU2CoreVoice_t::SPU2CoreVoice_t() :
	VOLL(nullptr),
	VOLR(nullptr),
	PITCH(nullptr),
	ADSR1(nullptr),
	ADSR2(nullptr),
	ENVX(nullptr),
	VOLXL(nullptr),
	VOLXR(nullptr),
	SSAL(nullptr),
	SSAH(nullptr),
	LSAXL(nullptr),
	LSAXH(nullptr),
	NAXL(nullptr),
	NAXH(nullptr)
{
}

SPU2CoreVoice_C0V0_t::SPU2CoreVoice_C0V0_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V0 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V0 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V0 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V0 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V0 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V0 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V0 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V0 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V0 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V0 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V0 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V0 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V0 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V0 NAXH", false, true);
}

SPU2CoreVoice_C0V1_t::SPU2CoreVoice_C0V1_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V1 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V1 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V1 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V1 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V1 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V1 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V1 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V1 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V1 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V1 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V1 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V1 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V1 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V1 NAXH", false, true);
}

SPU2CoreVoice_C0V2_t::SPU2CoreVoice_C0V2_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V2 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V2 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V2 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V2 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V2 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V2 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V2 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V2 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V2 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V2 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V2 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V2 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V2 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V2 NAXH", false, true);
}

SPU2CoreVoice_C0V3_t::SPU2CoreVoice_C0V3_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V3 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V3 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V3 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V3 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V3 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V3 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V3 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V3 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V3 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V3 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V3 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V3 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V3 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V3 NAXH", false, true);
}

SPU2CoreVoice_C0V4_t::SPU2CoreVoice_C0V4_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V4 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V4 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V4 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V4 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V4 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V4 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V4 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V4 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V4 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V4 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V4 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V4 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V4 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V4 NAXH", false, true);
}

SPU2CoreVoice_C0V5_t::SPU2CoreVoice_C0V5_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V5 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V5 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V5 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V5 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V5 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V5 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V5 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V5 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V5 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V5 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V5 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V5 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V5 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V5 NAXH", false, true);
}

SPU2CoreVoice_C0V6_t::SPU2CoreVoice_C0V6_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V6 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V6 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V6 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V6 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V6 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V6 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V6 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V6 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V6 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V6 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V6 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V6 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V6 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V6 NAXH", false, true);
}

SPU2CoreVoice_C0V7_t::SPU2CoreVoice_C0V7_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V7 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V7 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V7 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V7 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V7 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V7 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V7 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V7 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V7 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V7 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V7 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V7 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V7 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V7 NAXH", false, true);
}

SPU2CoreVoice_C0V8_t::SPU2CoreVoice_C0V8_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V8 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V8 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V8 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V8 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V8 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V8 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V8 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V8 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V8 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V8 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V8 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V8 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V8 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V8 NAXH", false, true);
}

SPU2CoreVoice_C0V9_t::SPU2CoreVoice_C0V9_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V9 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V9 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V9 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V9 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V9 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V9 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V9 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V9 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V9 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V9 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V9 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V9 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V9 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V9 NAXH", false, true);
}

SPU2CoreVoice_C0V10_t::SPU2CoreVoice_C0V10_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V10 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V10 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V10 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V10 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V10 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V10 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V10 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V10 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V10 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V10 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V10 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V10 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V10 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V10 NAXH", false, true);
}

SPU2CoreVoice_C0V11_t::SPU2CoreVoice_C0V11_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V11 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V11 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V11 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V11 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V11 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V11 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V11 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V11 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V11 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V11 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V11 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V11 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V11 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V11 NAXH", false, true);
}

SPU2CoreVoice_C0V12_t::SPU2CoreVoice_C0V12_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V12 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V12 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V12 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V12 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V12 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V12 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V12 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V12 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V12 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V12 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V12 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V12 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V12 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V12 NAXH", false, true);
}

SPU2CoreVoice_C0V13_t::SPU2CoreVoice_C0V13_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V13 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V13 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V13 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V13 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V13 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V13 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V13 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V13 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V13 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V13 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V13 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V13 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V13 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V13 NAXH", false, true);
}

SPU2CoreVoice_C0V14_t::SPU2CoreVoice_C0V14_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V14 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V14 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V14 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V14 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V14 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V14 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V14 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V14 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V14 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V14 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V14 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V14 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V14 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V14 NAXH", false, true);
}

SPU2CoreVoice_C0V15_t::SPU2CoreVoice_C0V15_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V15 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V15 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V15 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V15 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V15 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V15 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V15 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V15 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V15 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V15 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V15 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V15 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V15 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V15 NAXH", false, true);
}

SPU2CoreVoice_C0V16_t::SPU2CoreVoice_C0V16_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V16 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V16 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V16 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V16 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V16 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V16 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V16 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V16 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V16 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V16 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V16 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V16 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V16 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V16 NAXH", false, true);
}

SPU2CoreVoice_C0V17_t::SPU2CoreVoice_C0V17_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V17 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V17 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V17 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V17 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V17 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V17 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V17 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V17 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V17 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V17 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V17 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V17 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V17 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V17 NAXH", false, true);
}

SPU2CoreVoice_C0V18_t::SPU2CoreVoice_C0V18_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V18 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V18 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V18 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V18 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V18 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V18 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V18 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V18 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V18 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V18 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V18 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V18 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V18 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V18 NAXH", false, true);
}

SPU2CoreVoice_C0V19_t::SPU2CoreVoice_C0V19_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V19 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V19 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V19 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V19 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V19 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V19 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V19 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V19 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V19 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V19 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V19 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V19 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V19 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V19 NAXH", false, true);
}

SPU2CoreVoice_C0V20_t::SPU2CoreVoice_C0V20_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V20 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V20 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V20 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V20 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V20 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V20 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V20 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V20 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V20 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V20 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V20 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V20 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V20 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V20 NAXH", false, true);
}

SPU2CoreVoice_C0V21_t::SPU2CoreVoice_C0V21_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V21 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V21 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V21 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V21 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V21 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V21 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V21 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V21 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V21 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V21 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V21 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V21 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V21 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V21 NAXH", false, true);
}

SPU2CoreVoice_C0V22_t::SPU2CoreVoice_C0V22_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V22 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V22 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V22 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V22 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V22 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V22 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V22 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V22 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V22 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V22 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V22 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V22 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V22 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V22 NAXH", false, true);
}

SPU2CoreVoice_C0V23_t::SPU2CoreVoice_C0V23_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V23 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C0V23 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C0V23 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C0V23 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C0V23 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C0V23 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C0V23 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C0V23 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C0V23 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C0V23 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C0V23 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C0V23 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C0V23 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C0V23 NAXH", false, true);
}

SPU2CoreVoice_C1V0_t::SPU2CoreVoice_C1V0_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V0 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V0 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V0 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V0 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V0 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V0 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V0 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V0 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V0 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V0 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V0 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V0 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V0 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V0 NAXH", false, true);
}

SPU2CoreVoice_C1V1_t::SPU2CoreVoice_C1V1_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V1 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V1 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V1 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V1 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V1 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V1 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V1 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V1 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V1 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V1 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V1 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V1 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V1 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V1 NAXH", false, true);
}

SPU2CoreVoice_C1V2_t::SPU2CoreVoice_C1V2_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V2 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V2 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V2 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V2 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V2 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V2 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V2 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V2 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V2 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V2 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V2 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V2 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V2 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V2 NAXH", false, true);
}

SPU2CoreVoice_C1V3_t::SPU2CoreVoice_C1V3_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V3 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V3 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V3 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V3 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V3 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V3 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V3 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V3 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V3 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V3 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V3 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V3 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V3 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V3 NAXH", false, true);
}

SPU2CoreVoice_C1V4_t::SPU2CoreVoice_C1V4_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V4 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V4 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V4 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V4 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V4 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V4 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V4 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V4 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V4 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V4 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V4 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V4 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V4 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V4 NAXH", false, true);
}

SPU2CoreVoice_C1V5_t::SPU2CoreVoice_C1V5_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V5 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V5 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V5 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V5 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V5 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V5 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V5 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V5 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V5 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V5 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V5 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V5 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V5 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V5 NAXH", false, true);
}

SPU2CoreVoice_C1V6_t::SPU2CoreVoice_C1V6_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V6 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V6 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V6 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V6 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V6 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V6 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V6 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V6 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V6 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V6 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V6 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V6 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V6 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V6 NAXH", false, true);
}

SPU2CoreVoice_C1V7_t::SPU2CoreVoice_C1V7_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V7 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V7 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V7 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V7 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V7 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V7 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V7 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V7 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V7 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V7 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V7 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V7 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V7 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V7 NAXH", false, true);
}

SPU2CoreVoice_C1V8_t::SPU2CoreVoice_C1V8_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V8 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V8 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V8 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V8 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V8 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V8 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V8 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V8 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V8 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V8 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V8 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V8 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V8 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V8 NAXH", false, true);
}

SPU2CoreVoice_C1V9_t::SPU2CoreVoice_C1V9_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V9 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V9 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V9 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V9 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V9 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V9 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V9 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V9 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V9 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V9 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V9 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V9 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V9 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V9 NAXH", false, true);
}

SPU2CoreVoice_C1V10_t::SPU2CoreVoice_C1V10_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V10 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V10 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V10 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V10 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V10 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V10 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V10 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V10 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V10 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V10 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V10 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V10 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V10 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V10 NAXH", false, true);
}

SPU2CoreVoice_C1V11_t::SPU2CoreVoice_C1V11_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V11 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V11 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V11 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V11 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V11 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V11 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V11 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V11 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V11 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V11 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V11 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V11 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V11 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V11 NAXH", false, true);
}

SPU2CoreVoice_C1V12_t::SPU2CoreVoice_C1V12_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V12 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V12 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V12 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V12 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V12 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V12 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V12 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V12 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V12 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V12 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V12 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V12 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V12 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V12 NAXH", false, true);
}

SPU2CoreVoice_C1V13_t::SPU2CoreVoice_C1V13_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V13 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V13 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V13 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V13 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V13 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V13 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V13 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V13 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V13 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V13 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V13 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V13 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V13 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V13 NAXH", false, true);
}

SPU2CoreVoice_C1V14_t::SPU2CoreVoice_C1V14_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V14 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V14 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V14 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V14 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V14 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V14 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V14 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V14 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V14 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V14 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V14 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V14 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V14 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V14 NAXH", false, true);
}

SPU2CoreVoice_C1V15_t::SPU2CoreVoice_C1V15_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V15 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V15 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V15 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V15 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V15 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V15 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V15 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V15 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V15 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V15 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V15 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V15 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V15 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V15 NAXH", false, true);
}

SPU2CoreVoice_C1V16_t::SPU2CoreVoice_C1V16_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V16 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V16 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V16 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V16 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V16 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V16 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V16 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V16 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V16 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V16 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V16 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V16 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V16 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V16 NAXH", false, true);
}

SPU2CoreVoice_C1V17_t::SPU2CoreVoice_C1V17_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V17 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V17 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V17 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V17 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V17 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V17 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V17 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V17 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V17 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V17 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V17 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V17 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V17 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V17 NAXH", false, true);
}

SPU2CoreVoice_C1V18_t::SPU2CoreVoice_C1V18_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V18 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V18 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V18 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V18 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V18 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V18 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V18 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V18 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V18 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V18 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V18 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V18 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V18 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V18 NAXH", false, true);
}

SPU2CoreVoice_C1V19_t::SPU2CoreVoice_C1V19_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V19 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V19 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V19 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V19 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V19 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V19 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V19 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V19 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V19 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V19 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V19 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V19 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V19 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V19 NAXH", false, true);
}

SPU2CoreVoice_C1V20_t::SPU2CoreVoice_C1V20_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V20 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V20 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V20 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V20 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V20 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V20 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V20 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V20 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V20 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V20 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V20 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V20 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V20 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V20 NAXH", false, true);
}

SPU2CoreVoice_C1V21_t::SPU2CoreVoice_C1V21_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V21 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V21 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V21 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V21 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V21 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V21 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V21 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V21 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V21 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V21 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V21 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V21 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V21 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V21 NAXH", false, true);
}

SPU2CoreVoice_C1V22_t::SPU2CoreVoice_C1V22_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V22 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V22 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V22 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V22 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V22 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V22 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V22 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V22 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V22 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V22 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V22 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V22 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V22 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V22 NAXH", false, true);
}

SPU2CoreVoice_C1V23_t::SPU2CoreVoice_C1V23_t()
{
	VOLL = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V23 VOLL", false, true);
	VOLR = std::make_shared<SPU2CoreVoiceRegister_VOL_t>("SPU2 C1V23 VOLR", false, true);
	PITCH = std::make_shared<Register16_t>("SPU2 C1V23 PITCH", false, true);
	ADSR1 = std::make_shared<SPU2CoreVoiceRegister_ADSR1_t>("SPU2 C1V23 ADSR1", false, true);
	ADSR2 = std::make_shared<SPU2CoreVoiceRegister_ADSR2_t>("SPU2 C1V23 ADSR2", false, true);
	ENVX = std::make_shared<Register16_t>("SPU2 C1V23 ENVX", false, true);
	VOLXL = std::make_shared<Register16_t>("SPU2 C1V23 VOLXL", false, true);
	VOLXR = std::make_shared<Register16_t>("SPU2 C1V23 VOLXR", false, true);
	SSAL = std::make_shared<Register16_t>("SPU2 C1V23 SSAL", false, true);
	SSAH = std::make_shared<Register16_t>("SPU2 C1V23 SSAH", false, true);
	LSAXL = std::make_shared<Register16_t>("SPU2 C1V23 LSAXL", false, true);
	LSAXH = std::make_shared<Register16_t>("SPU2 C1V23 LSAXH", false, true);
	NAXL = std::make_shared<Register16_t>("SPU2 C1V23 NAXL", false, true);
	NAXH = std::make_shared<Register16_t>("SPU2 C1V23 NAXH", false, true);
}
