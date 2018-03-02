#pragma once

#include "Common/Types/Register/ByteRegister.hpp"

/// Sized Byte register.
class SizedByteRegister : public ByteRegister
{
public:
	SizedByteRegister(const ubyte initial_value = 0, const bool read_only = false);

	/// Initialise register.
	void initialise() override;

	/// Read/write functions to access the register.
	ubyte read_ubyte() override;
	void write_ubyte(const ubyte value) override;
	
private:
	/// Primitive (sized) storage for register.
	union
	{
		ubyte b;
	};

	/// Initial value.
	ubyte initial_value;
	
	/// Read-only flag.
	/// Writes are silently discarded if turned on.
	bool read_only;
};