#include <boost/format.hpp>

#include "Core.hpp"
#include "Common/Options.hpp"

#include "Controller/Ee/Dmac/CEeDmac.hpp"

#include "Resources/RResources.hpp"
#include "Resources/Ee/Dmac/EeDmacConstants.hpp"

using LogicalMode = EeDmacChannelRegister_Chcr::LogicalMode;
using Direction = EeDmacChannelRegister_Chcr::Direction;

CEeDmac::CEeDmac(Core * core) :
	CController(core)
{
}

void CEeDmac::handle_event(const ControllerEvent & event) const
{
	switch (event.type)
	{
	case ControllerEvent::Type::Time:
	{
		int ticks_remaining = time_to_ticks(event.data.time_us);
		while (ticks_remaining > 0)
			ticks_remaining -= time_step(ticks_remaining);
		break;
	}
	default:
	{
		throw std::runtime_error("CEeDmac event handler not implemented - please fix!");
	}
	}
}

int CEeDmac::time_to_ticks(const double time_us) const
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::EeDmac]);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "EeDmac ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CEeDmac::time_step(const int ticks_available) const
{
	auto& r = core->get_resources();

	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (!r.ee.dmac.ctrl.extract_field(EeDmacRegister_Ctrl::DMAE))
		return 1;

	// Check for any pending/started DMA transfers and perform transfer if enabled.
	for (auto& channel : r.ee.dmac.channels)
	{
		// Check if channel is enabled for transfer.
		if (channel.chcr->extract_field(EeDmacChannelRegister_Chcr::STR))
		{
			// TODO: this may not actually be needed, the EE core will (should) never write 
			// while a dma transfer has started, but do it for now.
			auto _lock = channel.chcr->scope_lock();

			switch (channel.chcr->get_logical_mode())
			{
			case LogicalMode::NORMAL:
			{
				transfer_normal(channel);
				break;
			}
			case LogicalMode::CHAIN:
			{
				transfer_chain(channel);  
				break;
			}
			case LogicalMode::INTERLEAVED:
			{
				transfer_interleaved(channel);
				break;
			}
			default:
			{
				throw std::runtime_error("Could not determine EE DMAC channel logical mode.");
			}
			}
		}
	}

	// Check for D_STAT interrupt bit status, send interrupt to EE Core (INT1 line) if not masked.
	handle_interrupt_check();

	return 1;
}

int CEeDmac::transfer_data(EeDmacChannel & channel) const
{
	// Determine the runtime direction of data flow by checking the CHCR.DIR field.
	Direction direction = channel.chcr->get_direction();

	// Get the main memory or SPR address we are reading or writing from. 
	// NOTE: The mask of 0x1FFFFFF0 comes from PCSX2, also in my own testing, the PS2 OS sets MADR to addresses such as 0x3xxxxxxx.
	// This is to do with cache modes, but they are left un-implemented. Also makes it qword aligned (undocumented requirement).
	const bool spr_flag = channel.madr->extract_field(EeDmacChannelRegister_Addr::SPR) > 0;
	const uword address = channel.madr->extract_field(EeDmacChannelRegister_Addr::ADDR) & 0x1FFFFFF0;

	// If we are using the from/toSPR channels (channel ID's 8 or 9), then we need to get the SPR address, and take a different code path. 
	// Within the these channels MADR.SPR is always 0 on these channels (have to use the SADR register as the SPR address).
	if (*channel.channel_id == 8 || *channel.channel_id == 9)
	{
		// We are doing a mem->SPR or SPR->mem, use both MADR and SADR registers.
		// NOTE: The mask of 0x3FF0 comes from PCSX2. I have not personally tested this, but assume it is required.
		//       This mask restricts the address to the 16 kB address range and makes the address qword aligned.
		const uptr spr_address = channel.sadr->read_uword() & 0x3FF0;

		if (direction == Direction::FROM)
		{
			uqword packet = read_qword_memory(spr_address, true);
			write_qword_memory(address, false, packet);

#if DEBUG_LOG_EE_DMAC_XFERS
			BOOST_LOG(Core::get_logger()) << 
				boost::format("EE DMAC Read uqword spram %d, spr_addr = 0x%08llX, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X ----> mem_addr = 0x%08X")
				% *channel.channel_id
				% spr_address
				% packet.uw[0] % packet.uw[1] % packet.uw[2] % packet.uw[3]
				% address;
#endif
		}
		else if (direction == Direction::TO)
		{
			uqword packet = read_qword_memory(address, false);
			write_qword_memory(spr_address, true, packet);
			
#if DEBUG_LOG_EE_DMAC_XFERS
			BOOST_LOG(Core::get_logger()) << 
				boost::format("EE DMAC write uqword spram %d, spr_addr = 0x%08llX, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X <---- mem_addr = 0x%08X")
				% *channel.channel_id
				% spr_address
				% packet.uw[0] % packet.uw[1] % packet.uw[2] % packet.uw[3]
				% address;
#endif
		}
		else
		{
			throw std::runtime_error("EE DMAC could not determine transfer direction (SPR)! Please debug.");
		}

		// Increment the MADR & SADR register by a qword, and decrement the QWC register by 1.
		channel.madr->offset(NUMBER_BYTES_IN_QWORD);
		channel.sadr->offset(NUMBER_BYTES_IN_QWORD);
		channel.qwc->offset(-1);

		return 1;
	}
	else
	{
		// Else transfer data normally.
		if (direction == Direction::FROM)
		{
			// Transfer data, return early if we could not read from the FIFO queue.
			if (!channel.dma_fifo_queue->has_read_available(NUMBER_BYTES_IN_QWORD))
				return 0;
			uqword packet;
			channel.dma_fifo_queue->read(reinterpret_cast<ubyte*>(&packet), NUMBER_BYTES_IN_QWORD);
			write_qword_memory(address, spr_flag, packet);

#if DEBUG_LOG_EE_DMAC_XFERS
			BOOST_LOG(Core::get_logger()) << 
				boost::format("EE DMAC Read uqword channel %d, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X ----> mem_addr = 0x%08X")
				% *channel.channel_id
				% packet.uw[0] % packet.uw[1] % packet.uw[2] % packet.uw[3]
				% address;
#endif
		}
		else if (direction == Direction::TO)
		{
			// Transfer data, return early if we could not write to the FIFO queue.
			if (!channel.dma_fifo_queue->has_write_available(NUMBER_BYTES_IN_QWORD))
				return 0;
			uqword packet = read_qword_memory(address, spr_flag);
			channel.dma_fifo_queue->write(reinterpret_cast<const ubyte*>(&packet), NUMBER_BYTES_IN_QWORD);

#if DEBUG_LOG_EE_DMAC_XFERS
			BOOST_LOG(Core::get_logger()) << 
				boost::format("EE DMAC Write uqword channel %d, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X <---- mem_addr = 0x%08X")
				% *channel.channel_id
				% packet.uw[0] % packet.uw[1] % packet.uw[2] % packet.uw[3]
				% address;
#endif
		}
		else
		{
			throw std::runtime_error("EE DMAC could not determine transfer direction! Please debug.");
		}

		// Increment the MADR register by a qword, and decrement the QWC register by a qword.
		channel.madr->offset(NUMBER_BYTES_IN_QWORD);
		channel.qwc->offset(-1);

		return 1;
	}
}

void CEeDmac::set_state_suspended(EeDmacChannel & channel) const
{
	auto& r = core->get_resources();
	auto _lock = r.ee.dmac.stat.scope_lock();

	// Emit the interrupt status bit.
	r.ee.dmac.stat.insert_field(EeDmacRegister_Stat::CHANNEL_CIS_KEYS[*channel.channel_id], 1);

	// Change CHCR.STR to 0.
	channel.chcr->insert_field(EeDmacChannelRegister_Chcr::STR, 0);
}

void CEeDmac::set_state_failed_transfer(EeDmacChannel & channel) const
{
	throw std::runtime_error("EE DMAC failed transfer not implemented.");
}

bool CEeDmac::transfer_normal(EeDmacChannel & channel) const
{
	// Perform pre-start checks.
	if (!channel.chcr->dma_started)
	{
		// Check the QWC register, make sure that size > 0 in order to start transfer.
		if (channel.qwc->read_uword() == 0)
		{
			set_state_failed_transfer(channel);
			return false;
		}

		// Pre checks ok - start the DMA transfer.
		channel.chcr->dma_started = true;
		return true;
	}
	else
	{
		// Check if QWC == 0 (transfer completed).
		if (channel.qwc->read_uword() == 0)
		{
			// If we are writing to a FIFO, check that the peripheral received the data before interrupting EE Core (except for toSPR).
			// Try again until condition is met.
			if ((channel.chcr->get_direction() == Direction::TO) && (*channel.channel_id != 9))
			{
				if (!channel.dma_fifo_queue->is_empty())
					return false;
			}

			// Send interrupt to EE Core.
			set_state_suspended(channel);
			return true;
		}

		// Check for drain stall control conditions, and skip cycle if the data is not ready (when the next slice is not ready).
		if (is_drain_stall_control_on(channel) && is_drain_stall_control_waiting(channel))
		{
			set_dmac_stall_control_sis();
			return false;
		}

		// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
		int count = transfer_data(channel);
		if (count == 0)
			return false;

		// Check for source stall control conditions, and update D_STADR if required.
		if (is_source_stall_control_on(channel))
			set_dmac_stall_control_stadr(channel);

		// Transfer successful, done for this cycle.
		return true;
	}
}

bool CEeDmac::transfer_chain(EeDmacChannel & channel) const
{
	// Perform pre-start checks.
	if (!channel.chcr->dma_started)
	{
		// No prechecks needed - start DMA transfer.
		// If QWC transfer size is 0 initially, then it just means that we read a tag straight away.
		channel.chcr->dma_started = true;
		return true;
	}
	else
	{
		// Check the QWC register, make sure that size > 0 for a transfer to occur (otherwise read a tag).
		if (channel.qwc->read_uword() > 0)
		{
			// Check for drain stall control conditions (including if we are in "refs" tag), and skip cycle if the data is not ready.
			if (is_drain_stall_control_on(channel) && is_drain_stall_control_waiting(channel) && channel.chcr->tag_stall)
			{
				set_dmac_stall_control_sis();
				return false;
			}

			// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
			int count = transfer_data(channel);
			if (count == 0)
				return false;

			// Check for source stall control conditions (including if we are in "cnts" tag id), and update D_STADR if required.
			if (is_source_stall_control_on(channel) && channel.chcr->tag_stall)
				set_dmac_stall_control_stadr(channel);
			
			// Transfer successful, done for this cycle.
			return true;
		}
		else
		{
			// Check first if we need to exit the transfer (by tag instruction or IRQ).
			bool tag_irq = (channel.chcr->extract_field(EeDmacChannelRegister_Chcr::TIE) > 0) && channel.chcr->tag_irq;
			if (tag_irq || channel.chcr->tag_exit)
			{
				// If we are writing to a FIFO, check that the peripheral received the data before interrupting EE Core (except for toSPR).
				// Try again until condition is met.
				if ((channel.chcr->get_direction() == Direction::TO) && (*channel.channel_id != 9))
				{
					if (!channel.dma_fifo_queue->is_empty())
						return false;
				}

				// Send interrupt to EE Core.
				set_state_suspended(channel);
				return true;
			}

			// We are instead reading in the next tag.
			// Check if we are in source or dest chain mode, read in a tag (to mDMAtag), and perform action based on tag id (which will set MADR, QWC, etc).
			// TODO: Do check based off the CHCR.DIR (direction) set or based on constant properties listed on pg 42 of EE Users Manual? Works both ways, but direction is less code.
			switch (channel.chcr->get_direction()) 
			{
			case Direction::TO:
			{
				// Read in a tag, exit early if we need to wait for data.
				if (!read_chain_source_tag(channel))
					return false;

				// Execute the tag handler
				(this->*SRC_CHAIN_INSTRUCTION_TABLE[channel.chcr->dma_tag.id()])(channel);
				break;
			}
			case Direction::FROM:
			{
				// Read in a tag, exit early if we need to wait for data.
				if (!read_chain_dest_tag(channel))
					return false;

				// Execute the tag handler
				(this->*DST_CHAIN_INSTRUCTION_TABLE[channel.chcr->dma_tag.id()])(channel);
				break;
			}
			default:
			{
				throw std::runtime_error("EE DMAC could not determine chain mode context.");
			}
			}

			// Set the IRQ flag if the DMAtag.IRQ bit is set.
			channel.chcr->tag_irq = channel.chcr->dma_tag.irq();

			// Set CHCR.TAG based upon the DMA tag read (bits 16-31).
			channel.chcr->insert_field(EeDmacChannelRegister_Chcr::TAG, channel.chcr->dma_tag.tag());

			// Transfer successful, done for this cycle.
			return true;
		}
	}
}

bool CEeDmac::transfer_interleaved(EeDmacChannel & channel) const
{
	throw std::runtime_error("EE DMAC interleave mode not fully implemented (fix me up).");

	/*
	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (channel.qwc->read_uword() == 0)
	{
		set_state_failed_transfer();
		return;
	}

	// Data of size D_SQWC.TQWC is transferred first, then data of size D_SQWC.SQWC is skipped, until Dn_QWC is reached.
	if (!mChannel->isInterleaveInSkipMode())
	{
		// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
		uword dataCount = transfer_data();
		if (!dataCount)
		{
			return;
		}
	}
	else
	{
		// Skip data by incrementing the channel MADR.
		channel.madr->increment();
	}
		
	// Increment the interleaved count.
	mChannel->incrementInterleaveCount();

	// Check the interleaved mode (transferring/skipping), and change mInterleavedSkipState if required, based on mInterleavedCountState.
	if (isInterleaveLimitReached())
	{
		mChannel->toggleInterleaveMode();
	}

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (channel.qwc->read_uword() == 0)
	{
		set_state_suspended();
	}
	*/
}

void CEeDmac::handle_interrupt_check() const
{
	auto& r = core->get_resources();
	auto _lock = r.ee.dmac.stat.scope_lock();

	// Set the interrupt line if there was a condition set, otherwise clear the interrupt line.
	if (r.ee.dmac.stat.is_interrupt_pending())
		r.ee.core.cop0.cause.set_irq_line(3);
	else
		r.ee.core.cop0.cause.clear_irq_line(3);
}

bool CEeDmac::is_source_stall_control_on(EeDmacChannel & channel) const
{
	auto& r = core->get_resources();

	if (channel.chcr->get_direction() == Direction::FROM)
	{
		const uword STS = r.ee.dmac.ctrl.extract_field(EeDmacRegister_Ctrl::STS);
		if (*channel.channel_id == EeDmacConstants::STS_MAP[STS])
		{
			return true;
		}
	}

	return false;
}

bool CEeDmac::is_drain_stall_control_on(EeDmacChannel & channel) const
{
	auto& r = core->get_resources();

	if (channel.chcr->get_direction() == Direction::TO)
	{
		auto STD = r.ee.dmac.ctrl.extract_field(EeDmacRegister_Ctrl::STD);
		if (*channel.channel_id == EeDmacConstants::STD_MAP[STD])
		{
			return true;
		}
	}

	return false;
}

void CEeDmac::set_dmac_stall_control_stadr(EeDmacChannel & channel) const
{
	auto& r = core->get_resources();

	uword MADR = channel.madr->extract_field(EeDmacChannelRegister_Addr::ADDR);
	r.ee.dmac.stadr.write_uword(MADR);
}

void CEeDmac::set_dmac_stall_control_sis() const
{
	auto& r = core->get_resources();
	auto _stat_lock = r.ee.dmac.stat.scope_lock();

	// Set the STAT.SIS bit.
	r.ee.dmac.stat.insert_field(EeDmacRegister_Stat::SIS, 1);
}

bool CEeDmac::is_drain_stall_control_waiting(EeDmacChannel & channel) const
{
	auto& r = core->get_resources();

	if (channel.chcr->get_direction() == Direction::TO)
	{
		const uword MADR = channel.madr->extract_field(EeDmacChannelRegister_Addr::ADDR);
		const uword STADR = r.ee.dmac.stadr.read_uword();

		if ((MADR + 8) > STADR)
		{
			return true;
		}
	}

	return false;
}

uqword CEeDmac::read_qword_memory(const uptr address, const bool spr_access) const
{
	auto& r = core->get_resources(); 

	// Read mem[addr] or spr[addr] (128-bits). SPR is at offset 0x70000000.
	if (spr_access)
		return r.ee.bus.read_uqword(BusContext::Ee, 0x70000000 + address);
	else
		return r.ee.bus.read_uqword(BusContext::Ee, address);
}

void CEeDmac::write_qword_memory(const uptr address, const bool spr_access, const uqword data) const
{
	auto& r = core->get_resources(); 
	
	// Write mem[addr] or spr[addr] (128-bits). SPR is at offset 0x70000000.
	if (spr_access)
		r.ee.bus.write_uqword(BusContext::Ee, 0x70000000 + address, data);
	else
		r.ee.bus.write_uqword(BusContext::Ee, address, data);
}

bool CEeDmac::read_chain_source_tag(EeDmacChannel & channel) const
{
	// Get tag memory address (TADR).
	const uptr tadr = channel.tadr->extract_field(EeDmacChannelRegister_Addr::ADDR);
	const bool spr_flag = channel.tadr->extract_field(EeDmacChannelRegister_Addr::SPR) > 0;

	// Read EE tag (128-bits) from TADR.
	const uqword tag = read_qword_memory(tadr, spr_flag);
	
	// Check if we need to transfer the tag.
	if (channel.chcr->extract_field(EeDmacChannelRegister_Chcr::TTE))
	{
		// Setup new tag with LSB 64-bits filled with data from MSB 64-bits of tag read from before, then send.
		// If there is no space in the FIFO queue, try again next cycle.
		if (!channel.dma_fifo_queue->has_write_available(NUMBER_BYTES_IN_QWORD))
			return false;
		uqword sendTag = uqword(tag.uw[2], tag.uw[3], 0, 0);
		channel.dma_fifo_queue->write(reinterpret_cast<const ubyte*>(&sendTag), NUMBER_BYTES_IN_QWORD);
	}
	
	// Set channel tag based upon the LSB 64-bits of tag.
	EeDmatag dma_tag = EeDmatag(tag.uw[0], tag.uw[1]);
	channel.chcr->dma_tag = dma_tag;

#if DEBUG_LOG_EE_DMAC_TAGS
	BOOST_LOG(Core::get_logger()) << 
		boost::format("EE tag (source chain mode) read on channel %s, TADR = 0x%08X. Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.")
		% *channel.channel_id
		% channel.tadr->read_uword()
		% dma_tag.tag0 % dma_tag.tag1
		% channel.chcr->extract_field(EeDmacChannelRegister_Chcr::TTE);
#endif

	return true;
}

bool CEeDmac::read_chain_dest_tag(EeDmacChannel & channel) const
{
	// Read tag from channel FIFO. If no data is available, try again next cycle.
	if (!channel.dma_fifo_queue->has_read_available(NUMBER_BYTES_IN_QWORD))
		return false;
	uqword tag;
	channel.dma_fifo_queue->read(reinterpret_cast<ubyte*>(&tag), NUMBER_BYTES_IN_QWORD);

	// Set channel tag based upon the first 2 words read from the channel.
	EeDmatag dma_tag = EeDmatag(tag.uw[0], tag.uw[1]);
	channel.chcr->dma_tag = dma_tag;

#if DEBUG_LOG_EE_DMAC_TAGS
	BOOST_LOG(Core::get_logger()) << 
		boost::format("EE tag (dest chain mode) read on channel %s, Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.")
		% *channel.channel_id
		% dma_tag.tag0 % dma_tag.tag1
		% channel.chcr->extract_field(EeDmacChannelRegister_Chcr::TTE);
#endif
	
	// Check if we need to transfer the tag.
	if (channel.chcr->extract_field(EeDmacChannelRegister_Chcr::TTE) > 0)
	{
		throw std::runtime_error("EE DMAC dest chain mode TTE set but not implemented.");
	}
	
	return true;
}
