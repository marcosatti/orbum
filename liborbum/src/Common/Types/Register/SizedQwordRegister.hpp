#pragma once

#include "Common/Types/Register/QwordRegister.hpp"

/// Sized Qword register.
class SizedQwordRegister : public QwordRegister
{
public:
	SizedQwordRegister(const uqword initial_value = 0, const bool read_only = false);

	/// Initialise register.
	void initialise() override;

	/// Read/write functions to access the register.
    ubyte read_ubyte(const size_t offset) override;
	void write_ubyte(const size_t offset, const ubyte value) override;
	uhword read_uhword(const size_t offset) override;
	void write_uhword(const size_t offset, const uhword value) override;
	uword read_uword(const size_t offset) override;
	void write_uword(const size_t offset, const uword value) override;
	udword read_udword(const size_t offset) override;
	void write_udword(const size_t offset, const udword value) override;
	uqword read_uqword() override;
	void write_uqword(const uqword value) override;
	
private:
	/// Primitive (sized) storage for register.
	union
	{
        ubyte  b[NUMBER_BYTES_IN_QWORD];
		uhword h[NUMBER_HWORDS_IN_QWORD];
		uword  w[NUMBER_WORDS_IN_QWORD];
		udword d[NUMBER_DWORDS_IN_QWORD];
		uqword q;
	};

	/// Initial value.
	uqword initial_value;
	
	/// Read-only flag.
	/// Writes are silently discarded if turned on.
	bool read_only;
};