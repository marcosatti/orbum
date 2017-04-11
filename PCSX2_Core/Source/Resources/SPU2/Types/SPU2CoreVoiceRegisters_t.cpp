#include "stdafx.h"

#include "Resources/SPU2/Types/SPU2CoreVoiceRegisters_t.h"

SPU2CoreVoiceRegister_ADSR1_t::SPU2CoreVoiceRegister_ADSR1_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister16_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::SL, "SL", 0, 4, 0);
	registerField(Fields::DR, "DR", 4, 4, 0);
	registerField(Fields::AR, "AR", 8, 7, 0);
	registerField(Fields::X, "X", 15, 1, 0);
}

SPU2CoreVoiceRegister_ADSR2_t::SPU2CoreVoiceRegister_ADSR2_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister16_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::RR, "RR", 0, 5, 0);
	registerField(Fields::Z, "Z", 5, 1, 0);
	registerField(Fields::SR, "SR", 6, 7, 0);
	registerField(Fields::Y, "Y", 13, 3, 0);
}