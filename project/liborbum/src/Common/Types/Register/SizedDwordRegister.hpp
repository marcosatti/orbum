#pragma once

#include "Common/Types/Register/DwordRegister.hpp"

/// Sized Dword register.
class SizedDwordRegister : public DwordRegister
{
public:
	SizedDwordRegister(const udword initial_value = 0, const bool read_only = false);

	/// Initialise register.
	void initialise() override;

	/// Read/write functions to access the register.
    ubyte read_ubyte(const size_t offset) override;
	void write_ubyte(const size_t offset, const ubyte value) override;
	uhword read_uhword(const size_t offset) override;
	void write_uhword(const size_t offset, const uhword value) override;
	uword read_uword(const size_t offset) override;
	void write_uword(const size_t offset, const uword value) override;
	udword read_udword() override;
	void write_udword(const udword value) override;

private:
	/// Primitive (sized) storage for register.
	union
	{
        ubyte  b[NUMBER_BYTES_IN_DWORD];
		uhword h[NUMBER_HWORDS_IN_DWORD];
		uword  w[NUMBER_WORDS_IN_DWORD];
		udword d;
	};

	/// Initial value.
	udword initial_value;
	
	/// Read-only flag.
	/// Writes are silently discarded if turned on.
	bool read_only;
};