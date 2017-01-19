#pragma once

#include <memory>

#include "Common/Types/Registers/Register32_t.h"

class PCRegister32_t;

class LinkRegister32_t : public Register32_t
{
public:
	explicit LinkRegister32_t(const std::shared_ptr<PCRegister32_t> & pcRegister);

	/*
	Sets the return (link) address, which is equal to the current PC + 8.
	*/
	void setLinkAddress();

private:
	/*
	A reference to the associated PC register, which will be read when setLinkAddress() is called.
	*/
	std::shared_ptr<PCRegister32_t> mPCRegister;
};

