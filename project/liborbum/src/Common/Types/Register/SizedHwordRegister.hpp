#pragma once

#include "Common/Types/Register/HwordRegister.hpp"

/*
Hword register.
*/
class SizedHwordRegister : public HwordRegister
{
public:
	SizedHwordRegister(const uhword initial_value = 0, const bool read_only = false);

	/*
	Initialise register.
	*/
	void initialise() override;

	/*
	Read/write functions to access the register.
    */
    ubyte read_ubyte(const size_t offset) override;
	void write_ubyte(const size_t offset, const ubyte value) override;
	uhword read_uhword() override;
	void write_uhword(const uhword value) override;
	
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
        ubyte  b[NUMBER_BYTES_IN_HWORD];
        uhword h;
	};

	/*
	Initial value.
	*/
	uhword initial_value;
	
	/*
	Read-only flag.
	Writes are silently discarded if turned on.
	*/
	bool read_only;
};