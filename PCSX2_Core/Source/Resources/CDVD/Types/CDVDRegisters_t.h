#pragma once

#include <memory>

#include "Common/Types/Register/Register8_t.h"
#include "Common/Types/FIFOQueue/FIFOQueue8_t.h"

/*
CDVD register / FIFO queue hybrid "register", mapped at 0x1F802005.
Read: Register8_t: N_READY.
Write: FIFOQueue8_t: N_DATA_IN.
*/
class CDVDRegister_N_2005_t : public Register8_t
{
public:
	CDVDRegister_N_2005_t(const char * mnemonic_N_READY, const char * mnemonic_N_DATA_IN, bool debugReads, bool debugWrites);

	/*
	Redirect read/write calls to resources.
	*/
	u8 readByte(const System_t context) override;
	void writeByte(const System_t context, u8 value) override;

	/*
	Resources.
	*/
	std::shared_ptr<Register8_t> N_READY;
	std::shared_ptr<FIFOQueue8_t> N_DATA_IN;
};