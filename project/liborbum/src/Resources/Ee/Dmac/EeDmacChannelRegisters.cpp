#include "Resources/Ee/Dmac/EeDmacChannelRegisters.hpp"

EeDmacChannelRegister_Chcr::EeDmacChannelRegister_Chcr() :
	dma_started(false),
	tag_exit(false),
	tag_stall(false),
	tag_irq(false)
{
}

EeDmacChannelRegister_Chcr::LogicalMode EeDmacChannelRegister_Chcr::get_logical_mode()
{
	return static_cast<LogicalMode>(extract_field(MOD));
}

EeDmacChannelRegister_Chcr::Direction EeDmacChannelRegister_Chcr::get_direction()
{
	return static_cast<Direction>(extract_field(DIR));
}

void EeDmacChannelRegister_Chcr::write_uword(const uword value)
{
	auto start_old = SizedWordRegister::extract_field(STR);

	SizedWordRegister::write_uword(value);

	auto start_new = SizedWordRegister::extract_field(STR);

	// Reset DMA flags on suspended -> start.
	if ((start_old == 0) && (start_new != 0))
	{
		dma_started = false;
		tag_exit = false;
		tag_stall = false;
		tag_irq = false;
		dma_tag = EeDmatag();
	}
}

void EeDmacChannelRegister_Chcr::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	auto _lock = scope_lock();
	write_uword(value);
}

void EeDmacChannelRegister_Chcr_To::write_uword(const uword value)
{
	EeDmacChannelRegister_Chcr::write_uword(value | (1 << 0));
}

void EeDmacChannelRegister_Chcr_From::write_uword(const uword value)
{
	EeDmacChannelRegister_Chcr::write_uword(value & ~(1 << 0));
}

EeDmacChannelRegister_Chcr_Sif0::EeDmacChannelRegister_Chcr_Sif0() :
	sbus_f240(nullptr)
{
}

void EeDmacChannelRegister_Chcr_Sif0::write_uword(const uword value)
{
	EeDmacChannelRegister_Chcr_From::write_uword(value);

	auto start = extract_field(STR);
	auto direction = get_direction();

	// Trigger SBUS update.
	if (start == 0 && direction == Direction::FROM)
		handle_sbus_update_finish();
}

void EeDmacChannelRegister_Chcr_Sif0::handle_sbus_update_finish() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic values.
	sbus_f240->write_uword(sbus_f240->read_uword() & (~0x20));
	sbus_f240->write_uword(sbus_f240->read_uword() & (~0x2000));
}

EeDmacChannelRegister_Chcr_Sif1::EeDmacChannelRegister_Chcr_Sif1() :
	sbus_f240(nullptr)
{
}

void EeDmacChannelRegister_Chcr_Sif1::write_uword(const uword value)
{
	EeDmacChannelRegister_Chcr_To::write_uword(value);

	auto start = extract_field(STR);
	auto direction = get_direction();

	// Trigger SBUS update.
	if (start > 0 && direction == Direction::TO)
		handle_sbus_update_start();
}

void EeDmacChannelRegister_Chcr_Sif1::handle_sbus_update_start() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic value.
	sbus_f240->write_uword(sbus_f240->read_uword() | 0x4000);
}

EeDmacChannelRegister_Chcr_Sif2::EeDmacChannelRegister_Chcr_Sif2() :
	sbus_f240(nullptr)
{
}

void EeDmacChannelRegister_Chcr_Sif2::write_uword(const uword value)
{
	EeDmacChannelRegister_Chcr::write_uword(value);
	
	auto str = extract_field(STR);
	auto direction = get_direction();

	// Trigger SBUS update.
	if (str > 0 && direction == Direction::TO)
		handle_sbus_update_start();
	else if (str == 0 && direction == Direction::FROM)
		handle_sbus_update_finish();
}

void EeDmacChannelRegister_Chcr_Sif2::handle_sbus_update_start() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic value.
	sbus_f240->write_uword(sbus_f240->read_uword() | 0x8000);
}

void EeDmacChannelRegister_Chcr_Sif2::handle_sbus_update_finish() const
{
	// Update 0x1000F240 (maps to Common->REGISTER_F240) with magic values.
	sbus_f240->write_uword(sbus_f240->read_uword() & (~0x80));
	sbus_f240->write_uword(sbus_f240->read_uword() & (~0x8000));
}
