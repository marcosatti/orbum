#pragma once

#include "Common/Types/Register/SizedHwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

/// Program counter registers.

class HwordPcRegister final : public SizedHwordRegister
{
public:
	using SizedHwordRegister::SizedHwordRegister;
};

class WordPcRegister final : public SizedWordRegister
{
public:
	using SizedWordRegister::SizedWordRegister;
};
