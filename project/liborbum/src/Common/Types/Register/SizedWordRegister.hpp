#pragma once

#include "Common/Types/Register/WordRegister.hpp"

/*
Word register.
*/
class SizedWordRegister : public WordRegister
{
public:
	SizedWordRegister(const uword initial_value = 0, const bool read_only = false);

	/*
	Initialise register.
	*/
	void initialise() override;

	/*
	Read/write functions to access the register.
    */
    ubyte read_ubyte(const size_t offset) override;
	void write_ubyte(const size_t offset, const ubyte value) override;
	uhword read_uhword(const size_t offset) override;
	void write_uhword(const size_t offset, const uhword value) override;
	uword read_uword() override;
	void write_uword(const uword value) override;
	
	/*
	ByteBusMappable overrides.
	*/
	usize byte_bus_map_size() const override;
	
private:
	/*
	Primitive (sized) storage for register.
	*/
	union
	{
        ubyte  b[NUMBER_BYTES_IN_WORD];
		uhword h[NUMBER_HWORDS_IN_WORD];
		uword  w;
	};

	/*
	Initial value.
	*/
	uword initial_value;
	
	/*
	Read-only flag.
	Writes are silently discarded if turned on.
	*/
	bool read_only;
};