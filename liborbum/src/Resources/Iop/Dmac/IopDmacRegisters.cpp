#include <stdexcept>

#include "Resources/Iop/Dmac/IopDmacRegisters.hpp"
#include "Resources/Iop/Dmac/IopDmacChannels.hpp"

void IopDmacRegister_Icr0::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	auto _lock = scope_lock();

	// Preprocessing for IOP: reset (clear) the FL bits if 1 is written to them (taken from PCSX2 "IopHwWrite.cpp").
	uword temp = value;
	if (context == BusContext::Iop)
		temp = ((read_uword() & 0xFF000000) | (value & 0xFFFFFF)) & ~(value & 0x7F000000);
		
	write_uword(temp);
}

bool IopDmacRegister_Icr0::is_interrupt_pending_and_set_master()
{
	uword reg_value = read_uword();
	uword TCM = (reg_value & 0x7F0000) >> 16;
	uword TCI = (reg_value & 0x7F000000) >> 24;
	
	// Check for channel interrupts or error interrupt. Set the master interrupt bit if any of the conditions are true.
	if (((TCM & TCI) && extract_field(MASTER_ENABLE)) || extract_field(ERROR_))
	{
		insert_field(MASTER_INTERRUPT, 1);
		return true;
	}
	
	return false;
}

void IopDmacRegister_Icr1::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	auto _lock = scope_lock();

	// Preprocessing for IOP: reset (clear) the FL bits if 1 is written to them (taken from PCSX2 "IopHwWrite.cpp").
	uword temp = value;
	if (context == BusContext::Iop)
		temp = ((read_uword() & 0xFF000000) | (value & 0xFFFFFF)) & ~(value & 0x7F000000);

	write_uword(temp);
}

bool IopDmacRegister_Icr1::is_interrupt_pending_and_set_master()
{
	uword reg_value = read_uword();
	uword TCM = (reg_value & 0x7F0000) >> 16;
	uword TCI = (reg_value & 0x7F000000) >> 24;

	// Check for channel interrupts or error interrupt. Set the master interrupt bit if any of the conditions are true.
	if ((TCM & TCI) && icr0->extract_field(IopDmacRegister_Icr0::MASTER_ENABLE))
	{
		icr0->insert_field(IopDmacRegister_Icr0::MASTER_INTERRUPT, 1);
		return true;
	}

	return false;
}

uword IopDmacRegister_Pcrw::get_channel_priority(const IopDmacChannel * channel) const
{
	// Channels 0-6 belong to PCR0, channels 7-13 belong to PCR1.
	if (*channel->channel_id >= 0 && *channel->channel_id < 7)
		return pcr0->extract_field(IopDmacRegister_Pcr0::CHANNEL_PRIORITY_KEYS[*channel->channel_id]);
	else if (*channel->channel_id >= 7 && *channel->channel_id < 14)
		return pcr1->extract_field(IopDmacRegister_Pcr1::CHANNEL_PRIORITY_KEYS[*channel->channel_id % 7]);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get priority index.");
}

// void IopDmacRegister_Pcrw::set_channel_priority(const IopDmacChannel * channel, const uword value)
// {
// 	// Channels 0-6 belong to PCR0, channels 7-13 belong to PCR1.
// 	if (*channel->channel_id >= 0 && *channel->channel_id < 7)
// 		pcr0->insert_field(IopDmacRegister_Pcr0::CHANNEL_PRIORITY_KEYS[*channel->channel_id], value);
// 	else if (*channel->channel_id >= 7 && *channel->channel_id < 14)
// 		pcr1->insert_field(IopDmacRegister_Pcr1::CHANNEL_PRIORITY_KEYS[*channel->channel_id % 7], value);
// 	else
// 		throw std::runtime_error("IOP DMAC PCRW could not determine channel set priority index.");
// }

bool IopDmacRegister_Pcrw::is_channel_enabled(const IopDmacChannel * channel) const
{
	// Channels 0-6 belong to PCR0, channels 7-13 belong to PCR1.
	if (*channel->channel_id >= 0 && *channel->channel_id < 7)
		return (pcr0->extract_field(IopDmacRegister_Pcr0::CHANNEL_ENABLE_KEYS[*channel->channel_id]) > 0);
	else if (*channel->channel_id >= 7 && *channel->channel_id < 14)
		return (pcr1->extract_field(IopDmacRegister_Pcr1::CHANNEL_ENABLE_KEYS[*channel->channel_id % 7]) > 0);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get enabled index.");
}

// void IopDmacRegister_Pcrw::set_channel_enabled(const IopDmacChannel * channel, const bool value)
// {
// 	// Channels 0-6 belong to PCR0, channels 7-13 belong to PCR1.
// 	if (*channel->channel_id >= 0 && *channel->channel_id < 7)
// 		pcr0->insert_field(IopDmacRegister_Pcr0::CHANNEL_ENABLE_KEYS[*channel->channel_id], (value ? 1 : 0));
// 	else if (*channel->channel_id >= 7 && *channel->channel_id < 14)
// 		pcr1->insert_field(IopDmacRegister_Pcr1::CHANNEL_ENABLE_KEYS[*channel->channel_id % 7], (value ? 1: 0));
// 	else
// 		throw std::runtime_error("IOP DMAC PCRW could not determine channel set enabled index.");
// }

uword IopDmacRegister_Icrw::get_channel_irm(const IopDmacChannel * channel) const
{
	// Channels 0-6 belong to icr0.
	if (*channel->channel_id >= 0 && *channel->channel_id < 7)
		return icr0->extract_field(IopDmacRegister_Icr0::CHANNEL_IRM_KEYS[*channel->channel_id]);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get IRM index.");
}

void IopDmacRegister_Icrw::set_channel_irm(const IopDmacChannel * channel, const uword value) const
{
	// Channels 0-6 belong to icr0.
	if (*channel->channel_id >= 0 && *channel->channel_id < 7)
		icr0->insert_field(IopDmacRegister_Icr0::CHANNEL_IRM_KEYS[*channel->channel_id], value);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel set IRM index.");
}

uword IopDmacRegister_Icrw::get_channel_iqe(const IopDmacChannel * channel) const
{
	// Channels 0-13 belong to icr1.
	if (*channel->channel_id >= 0 && *channel->channel_id < 14)
		return icr1->extract_field(IopDmacRegister_Icr1::CHANNEL_IQE_KEYS[*channel->channel_id]);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get IQE index.");
}

void IopDmacRegister_Icrw::set_channel_iqe(const IopDmacChannel * channel, const uword value) const
{
	// Channels 0-13 belong to icr1.
	if (*channel->channel_id >= 0 && *channel->channel_id < 14)
		icr1->insert_field(IopDmacRegister_Icr1::CHANNEL_IQE_KEYS[*channel->channel_id], value);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel set IQE index.");
}

uword IopDmacRegister_Icrw::get_channel_tcm(const IopDmacChannel * channel) const
{
	// Channels 0-6 belong to ICR0, channels 7-13 belong to ICR1.
	if (*channel->channel_id >= 0 && *channel->channel_id < 7)
		return icr0->extract_field(IopDmacRegister_Icr0::CHANNEL_TCM_KEYS[*channel->channel_id]);
	else if (*channel->channel_id >= 7 && *channel->channel_id < 14)
		return icr1->extract_field(IopDmacRegister_Icr1::CHANNEL_TCM_KEYS[*channel->channel_id % 7]);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get TCM index.");
}

void IopDmacRegister_Icrw::set_channel_tcm(const IopDmacChannel * channel, const uword value) const
{
	// Channels 0-6 belong to ICR0, channels 7-13 belong to ICR1.
	if (*channel->channel_id >= 0 && *channel->channel_id < 7)
		icr0->insert_field(IopDmacRegister_Icr0::CHANNEL_TCM_KEYS[*channel->channel_id], value);
	else if (*channel->channel_id >= 7 && *channel->channel_id < 14)
		icr1->insert_field(IopDmacRegister_Icr1::CHANNEL_TCM_KEYS[*channel->channel_id % 7], value);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel set TCM index.");
}

uword IopDmacRegister_Icrw::get_channel_tci(const IopDmacChannel * channel) const
{
	// Channels 0-6 belong to ICR0, channels 7-13 belong to ICR1.
	if (*channel->channel_id >= 0 && *channel->channel_id < 7)
		return icr0->extract_field(IopDmacRegister_Icr0::CHANNEL_TCI_KEYS[*channel->channel_id]);
	else if (*channel->channel_id >= 7 && *channel->channel_id < 14)
		return icr1->extract_field(IopDmacRegister_Icr1::CHANNEL_TCI_KEYS[*channel->channel_id % 7]);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get TCI index.");
}

void IopDmacRegister_Icrw::set_channel_tci(const IopDmacChannel * channel, const uword value) const
{
	// Channels 0-6 belong to ICR0, channels 7-13 belong to ICR1.
	if (*channel->channel_id >= 0 && *channel->channel_id < 7)
		icr0->insert_field(IopDmacRegister_Icr0::CHANNEL_TCI_KEYS[*channel->channel_id], value);
	else if (*channel->channel_id >= 7 && *channel->channel_id < 14)
		icr1->insert_field(IopDmacRegister_Icr1::CHANNEL_TCI_KEYS[*channel->channel_id % 7], value);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel set TCI index.");
}

bool IopDmacRegister_Icrw::is_interrupt_pending_and_set_master() const
{
	return (icr0->is_interrupt_pending_and_set_master() || icr1->is_interrupt_pending_and_set_master());
}