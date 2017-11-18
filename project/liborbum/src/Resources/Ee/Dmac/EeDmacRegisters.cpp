#include "Resources/Ee/Dmac/EeDmacRegisters.hpp"

constexpr Bitfield EeDmacRegister_Stat::CHANNEL_CIS_KEYS[Constants::EE::DMAC::NUMBER_DMAC_CHANNELS];
constexpr Bitfield EeDmacRegister_Stat::CHANNEL_CIM_KEYS[Constants::EE::DMAC::NUMBER_DMAC_CHANNELS];

void EeDmacRegister_Stat::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	auto _lock = scope_lock();

	uword temp = value;
	if (context == BusContext::Ee)
	{
		// For bits 0-15 (stat bits), they are cleared when 1 is written. For bits 16-31 (mask bits), they are reversed when 1 is written.
		uword regValue = read_uword();

		uword clrBits = (regValue & 0xFFFF) & (~(value & 0xFFFF));
		uword revBits = (regValue & 0xFFFF0000) ^ (value & 0xFFFF0000);
		temp = revBits | clrBits;
	}

	SizedWordRegister::write_uword(temp);
}

bool EeDmacRegister_Stat::is_interrupt_pending()
{
	uword regValue = read_uword();
	uword statValue = regValue & 0xFFFF;
	uword maskValue = (regValue & 0xFFFF0000) >> 16;

	if (statValue & maskValue)
		return true;

	if (extract_field(BEIS))
		return true;

	return false;
}