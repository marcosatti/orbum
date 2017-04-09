#include "stdafx.h"

#include "Resources/IOP/SPU2/Types/SPU2CoreRegisters_t.h"

SPU2CoreRegister_CHAN0_t::SPU2CoreRegister_CHAN0_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister16_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::V0, "V0", 0, 1, 0);
	registerField(Fields::V1, "V1", 1, 1, 0);
	registerField(Fields::V2, "V2", 2, 1, 0);
	registerField(Fields::V3, "V3", 3, 1, 0);
	registerField(Fields::V4, "V4", 4, 1, 0);
	registerField(Fields::V5, "V5", 5, 1, 0);
	registerField(Fields::V6, "V6", 6, 1, 0);
	registerField(Fields::V7, "V7", 7, 1, 0);
	registerField(Fields::V8, "V8", 8, 1, 0);
	registerField(Fields::V9, "V9", 9, 1, 0);
	registerField(Fields::V10, "V10", 10, 1, 0);
	registerField(Fields::V11, "V11", 11, 1, 0);
	registerField(Fields::V12, "V12", 12, 1, 0);
	registerField(Fields::V13, "V13", 13, 1, 0);
	registerField(Fields::V14, "V14", 14, 1, 0);
	registerField(Fields::V15, "V15", 15, 1, 0);
}

SPU2CoreRegister_CHAN1_t::SPU2CoreRegister_CHAN1_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister16_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::V16, "V16", 0, 1, 0);
	registerField(Fields::V17, "V17", 1, 1, 0);
	registerField(Fields::V18, "V18", 2, 1, 0);
	registerField(Fields::V19, "V19", 3, 1, 0);
	registerField(Fields::V20, "V20", 4, 1, 0);
	registerField(Fields::V21, "V21", 5, 1, 0);
	registerField(Fields::V22, "V22", 6, 1, 0);
	registerField(Fields::V23, "V23", 7, 1, 0);
}

SPU2CoreRegister_MMIX_t::SPU2CoreRegister_MMIX_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister16_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::SINER, "SINER", 0, 1, 0);
	registerField(Fields::SINEL, "SINEL", 1, 1, 0);
	registerField(Fields::SINR, "SINR", 2, 1, 0);
	registerField(Fields::SINL, "SINL", 3, 1, 0);
	registerField(Fields::MINER, "MINER", 4, 1, 0);
	registerField(Fields::MINEL, "MINEL", 5, 1, 0);
	registerField(Fields::MINR, "MINR", 6, 1, 0);
	registerField(Fields::MINL, "MINL", 7, 1, 0);
	registerField(Fields::MSNDER, "MSNDER", 8, 1, 0);
	registerField(Fields::MSNDEL, "MSNDEL", 9, 1, 0);
	registerField(Fields::MSNDR, "MSNDR", 10, 1, 0);
	registerField(Fields::MSNDL, "MSNDL", 11, 1, 0);
}

SPU2CoreRegister_ATTR_t::SPU2CoreRegister_ATTR_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister16_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::DMA, "DMA", 4, 2, 0);
	registerField(Fields::IRQ, "IRQ", 6, 1, 0);
	registerField(Fields::ReverbEn, "ReverbEn", 7, 1, 0);
	registerField(Fields::NoiseClock, "NoiseClock", 8, 6, 0);
	registerField(Fields::Mute, "Mute", 14, 1, 0);
}
