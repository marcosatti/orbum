#pragma once

#include <memory>

#include "Common/Types/Register/Register128_t.h"

class PCRegister32_t;

class LinkRegister128_t : public Register128_t
{
public:
	LinkRegister128_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<PCRegister32_t> & pcRegister);

	/*
	Sets the return (link) address, which is equal to the current PC + 8. Only the lower 64-bits are used, with the MSB's being 0 (ie: 32-bits effective).
	*/
	void setLinkAddress(const Context_t context);

private:
	/*
	A reference to the associated PC register, which will be read when setLinkAddress() is called.
	*/
	std::shared_ptr<PCRegister32_t> mPCRegister;
};

