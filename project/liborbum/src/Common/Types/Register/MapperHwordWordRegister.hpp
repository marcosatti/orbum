#pragma once

#include "Common/Types/Register/WordRegister.hpp"

class HwordRegister;

/// Maps a hword register to word register by zero-filling or truncating.
class MapperHwordWordRegister : public WordRegister
{
public:
	/// Initialise register (initialise underlying register).
	void initialise() override;

	ubyte read_ubyte(const size_t offset) override;
	void write_ubyte(const size_t offset, const ubyte value) override;
	uhword read_uhword(const size_t offset) override;
	void write_uhword(const size_t offset, const uhword value) override;
	uword read_uword() override;
	void write_uword(const uword value) override;
	
	/// ByteBusMappable overrides.
	usize byte_bus_map_size() const override;

	/// Reference to mapped hword register.
	HwordRegister * hword_register;
};