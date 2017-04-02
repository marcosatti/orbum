#pragma once

#include <memory>

#include "Common/Types/Registers/Register128_t.h"

class PCRegister32_t;

class LinkRegister128_t : public Register128_t
{
public:
	explicit LinkRegister128_t(const std::shared_ptr<PCRegister32_t> & pcRegister);

	/*
	Sets the return (link) address, which is equal to the current PC + 8. Only the lower 64-bits are used, with the MSB's being 0 (ie: 32-bits effective).
	*/
	void setLinkAddress(const System_t context);

private:
	/*
	A reference to the associated PC register, which will be read when setLinkAddress() is called.
	*/
	std::shared_ptr<PCRegister32_t> mPCRegister;
};

