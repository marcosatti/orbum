#pragma once

#include <memory>

class Register16_t;
class SPU2CoreVoiceRegister_VOL_t;
class SPU2CoreVoiceRegister_ADSR1_t;
class SPU2CoreVoiceRegister_ADSR2_t;

/*
Base class representing a SPU2 core voice.
There are 24 voices/channels per core.
*/
class SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_t();

	std::shared_ptr<SPU2CoreVoiceRegister_VOL_t>   VOLL;
	std::shared_ptr<SPU2CoreVoiceRegister_VOL_t>   VOLR;
	std::shared_ptr<Register16_t>                  PITCH;
	std::shared_ptr<SPU2CoreVoiceRegister_ADSR1_t> ADSR1;
	std::shared_ptr<SPU2CoreVoiceRegister_ADSR2_t> ADSR2;
	std::shared_ptr<Register16_t>                  ENVX;
	std::shared_ptr<Register16_t>                  VOLXL;
	std::shared_ptr<Register16_t>                  VOLXR;
	std::shared_ptr<Register16_t>                  SSAL;
	std::shared_ptr<Register16_t>                  SSAH;
	std::shared_ptr<Register16_t>                  LSAXL;
	std::shared_ptr<Register16_t>                  LSAXH;
	std::shared_ptr<Register16_t>                  NAXL;
	std::shared_ptr<Register16_t>                  NAXH;
};

class SPU2CoreVoice_C0V0_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V0_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 0;
};

class SPU2CoreVoice_C0V1_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V1_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 1;
};

class SPU2CoreVoice_C0V2_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V2_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 2;
};

class SPU2CoreVoice_C0V3_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V3_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 3;
};

class SPU2CoreVoice_C0V4_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V4_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 4;
};

class SPU2CoreVoice_C0V5_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V5_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 5;
};

class SPU2CoreVoice_C0V6_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V6_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 6;
};

class SPU2CoreVoice_C0V7_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V7_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 7;
};

class SPU2CoreVoice_C0V8_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V8_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 8;
};

class SPU2CoreVoice_C0V9_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V9_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 9;
};

class SPU2CoreVoice_C0V10_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V10_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 10;
};

class SPU2CoreVoice_C0V11_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V11_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 11;
};

class SPU2CoreVoice_C0V12_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V12_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 12;
};

class SPU2CoreVoice_C0V13_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V13_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 13;
};

class SPU2CoreVoice_C0V14_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V14_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 14;
};

class SPU2CoreVoice_C0V15_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V15_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 15;
};

class SPU2CoreVoice_C0V16_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V16_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 16;
};

class SPU2CoreVoice_C0V17_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V17_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 17;
};

class SPU2CoreVoice_C0V18_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V18_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 18;
};

class SPU2CoreVoice_C0V19_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V19_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 19;
};

class SPU2CoreVoice_C0V20_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V20_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 20;
};

class SPU2CoreVoice_C0V21_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V21_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 21;
};

class SPU2CoreVoice_C0V22_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V22_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 22;
};

class SPU2CoreVoice_C0V23_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C0V23_t();

	static constexpr int CORE_ID = 0;
	static constexpr int VOICE_ID = 23;
};

class SPU2CoreVoice_C1V0_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V0_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 0;
};

class SPU2CoreVoice_C1V1_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V1_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 1;
};

class SPU2CoreVoice_C1V2_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V2_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 2;
};

class SPU2CoreVoice_C1V3_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V3_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 3;
};

class SPU2CoreVoice_C1V4_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V4_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 4;
};

class SPU2CoreVoice_C1V5_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V5_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 5;
};

class SPU2CoreVoice_C1V6_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V6_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 6;
};

class SPU2CoreVoice_C1V7_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V7_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 7;
};

class SPU2CoreVoice_C1V8_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V8_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 8;
};

class SPU2CoreVoice_C1V9_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V9_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 9;
};

class SPU2CoreVoice_C1V10_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V10_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 10;
};

class SPU2CoreVoice_C1V11_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V11_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 11;
};

class SPU2CoreVoice_C1V12_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V12_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 12;
};

class SPU2CoreVoice_C1V13_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V13_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 13;
};

class SPU2CoreVoice_C1V14_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V14_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 14;
};

class SPU2CoreVoice_C1V15_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V15_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 15;
};

class SPU2CoreVoice_C1V16_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V16_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 16;
};

class SPU2CoreVoice_C1V17_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V17_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 17;
};

class SPU2CoreVoice_C1V18_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V18_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 18;
};

class SPU2CoreVoice_C1V19_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V19_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 19;
};

class SPU2CoreVoice_C1V20_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V20_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 20;
};

class SPU2CoreVoice_C1V21_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V21_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 21;
};

class SPU2CoreVoice_C1V22_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V22_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 22;
};

class SPU2CoreVoice_C1V23_t : public SPU2CoreVoice_t
{
public:
	SPU2CoreVoice_C1V23_t();

	static constexpr int CORE_ID = 1;
	static constexpr int VOICE_ID = 23;
};