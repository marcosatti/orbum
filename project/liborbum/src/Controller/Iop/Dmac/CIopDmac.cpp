#include <boost/format.hpp>

#include "Core.hpp"
#include "Common/Options.hpp"

#include "Controller/Iop/Dmac/CIopDmac.hpp"

#include "Resources/RResources.hpp"

using LogicalMode = IopDmacChannelRegister_Chcr::LogicalMode;
using Direction = IopDmacChannelRegister_Chcr::Direction;

CIopDmac::CIopDmac(Core * core) :
	CController(core)
{
}

void CIopDmac::handle_event(const ControllerEvent & event) const
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
		throw std::runtime_error("CIopDmac event handler not implemented - please fix!");
	}
	}
}

int CIopDmac::time_to_ticks(const double time_us) const
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::IOP::IOPBUS_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::IopDmac]);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "IopDmac ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CIopDmac::time_step(const int ticks_available) const
{
	auto& r = core->get_resources();

	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (!r.iop.dmac.gctrl.read_uword())
		return 1;

	// Run through each channel that's enabled.
	for (auto& channel : r.iop.dmac.channels)
	{
		// Check if channel is enabled for transfer (both from PCR and the CHCR).
		bool channel_enabled = r.iop.dmac.pcrw.is_channel_enabled(&channel);
		bool channel_start = channel.chcr->extract_field(IopDmacChannelRegister_Chcr::START) > 0;
		if (channel_enabled && channel_start)
		{
			// TODO: this may not actually be needed, the IOP core will (should) never write 
			// while a dma transfer has started, but do it for now.
			auto _lock = channel.chcr->scope_lock();

			switch (channel.chcr->get_logical_mode())
			{
			case LogicalMode::NORMAL_BURST:
			{
				// Normal/burst mode.
				transfer_normal_burst(channel);
				break;
			}
			case LogicalMode::NORMAL_SLICE:
			{
				// Normal/slice mode.
				transfer_normal_slice(channel);
				break;
			}
			case LogicalMode::LINKEDLIST:
			{
				// Linked list mode.
				throw std::runtime_error("IOP DMAC linked list mode not implemented.");
			}
			case LogicalMode::CHAIN:
			{
				// Chain mode (listed as undefined in nocash PSX docs), based of wisi's docs.
				transfer_chain(channel);
				break;
			}
			default:
			{
				throw std::runtime_error("Could not determine IOP DMAC channel logical mode.");
			}
			}
		}
	}

	return 1;
}

bool CIopDmac::transfer_normal_burst(IopDmacChannel & channel) const
{
	// Perform pre-start checks.
	if (!channel.chcr->dma_started)
	{
		// Calculate transfer size.
		channel.bcr->calculate(false);

		// Pre checks ok - start the DMA transfer.
		channel.chcr->dma_started = true;
		return true;
	}
	else
	{
		// Check if BCR == 0 (transfer completed).
		if (channel.bcr->transfer_length == 0)
		{
			// If we are writing to a FIFO, check that the peripheral received the data before interrupting IOP INTC.
			// Try again until condition is met.
			if (channel.chcr->get_direction() == Direction::TO)
			{
				if (!channel.dma_fifo_queue->is_empty())
					return false;
			}

			// Send interrupt to IOP INTC.
			set_state_suspended(channel);
			return true;
		}

		// Transfer a data unit (32-bits). If no data was transfered, try again next cycle.
		int count = transfer_data(channel);
		if (count == 0)
			return false;

		// Transfer successful, done for this cycle.
		return true;
	}
}

bool CIopDmac::transfer_normal_slice(IopDmacChannel & channel) const
{
	// Perform pre-start checks.
	if (!channel.chcr->dma_started)
	{
		// Calculate transfer size.
		channel.bcr->calculate(true);

		// Pre checks ok - start the DMA transfer.
		channel.chcr->dma_started = true;
		return true;
	}
	else
	{
		// Check if BCR == 0 (transfer completed).
		if (channel.bcr->transfer_length == 0)
		{
			// If we are writing to a FIFO, check that the peripheral received the data before interrupting IOP INTC.
			// Try again until condition is met.
			if (channel.chcr->get_direction() == Direction::TO)
			{
				if (!channel.dma_fifo_queue->is_empty())
					return false;
			}

			// Send interrupt to IOP INTC.
			set_state_suspended(channel);
			return true;
		}

		// Transfer a data unit (32-bits). If no data was transfered, try again next cycle.
		int count = transfer_data(channel);
		if (count == 0)
			return false;

		// Transfer successful, done for this cycle.
		return true;
	}
}

bool CIopDmac::transfer_chain(IopDmacChannel & channel) const
{
	auto& r = core->get_resources();

	// Perform pre-start checks.
	if (!channel.chcr->dma_started)
	{
		// Tag length is always 0 to begin with.
		// TODO: wisi's DMA docs mention the TBCR register, which is not implemented, but used instead over BCR for chain modes (tag transfer length).
		//       But for the IOP, TBCR is always 0 so far. If emulator crashes with MMU error, this will probably need to be put in.
		channel.bcr->transfer_length = 0;

		// Pre checks ok - start the DMA transfer.
		channel.chcr->dma_started = true;
		return true;
	}
	else
	{
		// Check the transfer size, make sure that size > 0 for a transfer to occur (otherwise read a tag). 
		if (channel.bcr->transfer_length > 0)
		{
			// Transfer a data unit (32-bits). If no data was transfered, try again next cycle. 
			int count = transfer_data(channel);
			if (count == 0)
				return false;

			// Transfer successful, done for this cycle.
			return true;
		}
		else
		{
			// Check first if we need to exit the transfer (by tag instruction or IRQ).
			bool channel_irq_enabled = r.iop.dmac.icrw.get_channel_iqe(&channel) > 0;
			bool tag_irq = channel.chcr->dma_tag.irq();
			bool tag_exit = channel.chcr->dma_tag.ert();
			if ((channel_irq_enabled && tag_irq) || tag_exit)
			{
				// If we are writing to a FIFO, check that the peripheral received the data before interrupting IOP INTC.
				// Try again until condition is met.
				if (channel.chcr->get_direction() == Direction::TO)
				{
					if (!channel.dma_fifo_queue->is_empty())
						return false;
				}

				// Send interrupt to IOP INTC.
				set_state_suspended(channel);
				return true;
			}

			// Check if we are in source or dest chain mode, read in a tag, and perform action based on tag id (which will set MADR, BCR, etc).
			// TODO: Do check based off the CHCR.DIR (direction) set or based on constant properties? Works both ways, but direction is less code.
			switch (channel.chcr->get_direction())
			{
			case Direction::TO:
			{
				// Read in a tag, exit early if we need to wait for data.
				if (!read_chain_source_tag(channel))
					return false;
				
				break;
			}
			case Direction::FROM:
			{
				// Read in a tag, exit early if we need to wait for data.
				if (!read_chain_dest_tag(channel))
					return false;
				
				break;
			}
			default:
			{
				throw std::runtime_error("IOP DMAC could not determine chain mode context.");
			}
			}
			
			// Set the tag data transfer address.
			channel.madr->write_uword(channel.chcr->dma_tag.addr());

			// Chain mode setup was successful, done for this cycle.
			return true;
		}
	}
}

void CIopDmac::handle_interrupt_check() const
{
	auto& r = core->get_resources();
	auto _icr0_lock = r.iop.dmac.icr0.scope_lock();
	auto _icr1_lock = r.iop.dmac.icr1.scope_lock();

	// Check ICR0 and ICR1 for interrupt status, else clear the master interrupt and INTC bits.
	if (r.iop.dmac.icrw.is_interrupt_pending_and_set_master())
	{
		auto _lock = r.iop.intc.stat.scope_lock();
		r.iop.intc.stat.insert_field(IopIntcRegister_Stat::DMAC, 1);
	}
}

int CIopDmac::transfer_data(IopDmacChannel & channel) const
{
	auto& r = core->get_resources();

	// Determine the direction of data flow. 
	Direction direction = channel.chcr->get_direction();

	// Get the main memory address.
	uptr address = channel.madr->read_uword();

	// Transfer data to or from the FIFO queue.
	if (direction == Direction::FROM)
	{
		// Transfer data, return early if we could not read from the FIFO queue.
		if (!channel.dma_fifo_queue->has_read_available(NUMBER_BYTES_IN_WORD))
			return 0;

		uword packet;
		channel.dma_fifo_queue->read(reinterpret_cast<ubyte*>(&packet), NUMBER_BYTES_IN_WORD);
		r.iop.bus.write_uword(BusContext::Iop, address, packet);

#if DEBUG_LOG_IOP_DMAC_XFERS
		BOOST_LOG(Core::get_logger()) <<
			boost::format("IOP DMAC Read uword channel %s, value = 0x%08X ----> MemAddr = 0x%08X")
			% *channel.channel_id
			% packet
			% address;
#endif
	}
	else if (direction == Direction::TO)
	{
		// Transfer data, return early if we could not write to the FIFO queue.
		if (!channel.dma_fifo_queue->has_write_available(NUMBER_BYTES_IN_WORD))
			return 0;

		uword packet = r.iop.bus.read_uword(BusContext::Iop, address);
		channel.dma_fifo_queue->write(reinterpret_cast<const ubyte*>(&packet), NUMBER_BYTES_IN_WORD);

#if DEBUG_LOG_IOP_DMAC_XFERS
		BOOST_LOG(Core::get_logger()) <<
			boost::format("IOP DMAC Write uword channel %s, value = 0x%08X <---- MemAddr = 0x%08X")
			% *channel.channel_id
			% packet
			% address;
#endif
	}
	else
	{
		throw std::runtime_error("IOP DMAC could not determine direction! Please debug.");
	}

	// Increment or decrement (depending on CHCR.MAS) the MADR register by a word.
	if (channel.chcr->extract_field(IopDmacChannelRegister_Chcr::MAS) == 0)
		channel.madr->offset(NUMBER_BYTES_IN_WORD);
	else
		channel.madr->offset(-NUMBER_BYTES_IN_WORD);

	// Update number of word units left (BCR).
	channel.bcr->transfer_length -= 1;

	return 1;
}

void CIopDmac::set_state_suspended(IopDmacChannel & channel) const
{
	auto& r = core->get_resources();
	auto _icr0_lock = r.iop.dmac.icr0.scope_lock();
	auto _icr1_lock = r.iop.dmac.icr1.scope_lock();

	// Stop channel.
	channel.chcr->insert_field(IopDmacChannelRegister_Chcr::START, 0);

	// Set channel transfer complete interrupt bit.
	r.iop.dmac.icrw.set_channel_tci(&channel, 1);

	// Check for ICR0 or ICR1 interrupt bit status, send interrupt to IOP INTC (IRQ 3) if not masked.
	handle_interrupt_check();
}

bool CIopDmac::read_chain_source_tag(IopDmacChannel & channel) const
{
	auto& r = core->get_resources();

	// Get tag memory address (TADR).
	uptr tadr = channel.tadr->read_uword();

	// Read IOP tag (128-bits) from TADR. 
	// Use 4 word reads instead of a single qword read (force memory alignement accesses).
	uqword tag;
	for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
		tag.uw[i] = r.iop.bus.read_uword(BusContext::Iop, tadr + (i * NUMBER_BYTES_IN_WORD));

	// Check if we need to transfer the tag (CHCR bit 8 aka "chopping enable" set).
	if (channel.chcr->extract_field(IopDmacChannelRegister_Chcr::CE) > 0)
	{
		// Setup new tag with LSB 64-bits filled with data from MSB 64-bits of tag read from before, then send.
		// If there is no space in the FIFO queue, try again next cycle.
		if (!channel.dma_fifo_queue->has_write_available(NUMBER_BYTES_IN_QWORD))
			return false;
		uqword ee_tag = uqword(tag.uw[2], tag.uw[3], 0, 0);
		channel.dma_fifo_queue->write(reinterpret_cast<const ubyte*>(&ee_tag), NUMBER_BYTES_IN_QWORD);
	}

	// Set channel.chcr->dma_tag based upon the LSB 64-bits of tag.
	IopDmatag dma_tag = IopDmatag(tag.uw[0], tag.uw[1]);
	channel.chcr->dma_tag = dma_tag;

#if DEBUG_LOG_IOP_DMAC_TAGS
	BOOST_LOG(Core::get_logger()) << 
		boost::format("IOP tag (source chain mode) read on channel %s, TADR = 0x%08X. Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.")
		% *channel.channel_id
		% channel.tadr->read_uword()
		% dma_tag.tag0 % dma_tag.tag1
		% channel.chcr->extract_field(IopDmacChannelRegister_Chcr::CE);
#endif

	// Set tag transfer length.
	// The maximum supported length is 1MB - 16 bytes, rounded up to the nearest qword alignment (from PCSX2).
	// TODO: qword alignment is forced for source chain mode, but not dest - does it matter? Probably doesn't need it, when source chain is enforced anyway (ie: will never receive data that isn't qword aligned).
	// TODO: there is also a 'cache mode' part, but not sure where (also from PCSX2). It shouldn't need to be implemented anyway (explains the 0xFFFFC mask).
	channel.bcr->transfer_length = (channel.chcr->dma_tag.length() + 3) & 0xFFFFC;

	// Increment TADR.
	channel.tadr->offset(NUMBER_BYTES_IN_QWORD);

	// TODO: look into the tag transfer enable (TTE) option not set (CHCR bit 8 aka "chopping enable" set).
	//       PCSX2 does not implement anything at all, but wisi might know something. SIF0 has this bit set always. For now, left unimplemented.
	if (!channel.chcr->extract_field(IopDmacChannelRegister_Chcr::CE))
		throw std::runtime_error("IOP DMAC source chain mode had TTE set to 0 - what is meant to happen?");

	return true;
}

bool CIopDmac::read_chain_dest_tag(IopDmacChannel & channel) const
{
	// Read tag from channel FIFO. If no data is available, try again next cycle.
	if (!channel.dma_fifo_queue->has_read_available(NUMBER_BYTES_IN_QWORD))
		return false;
	uqword tag;
	channel.dma_fifo_queue->read(reinterpret_cast<ubyte*>(&tag), NUMBER_BYTES_IN_QWORD);

	// Set channel.chcr->dma_tag based upon the first 2 words read from the channel.
	IopDmatag dma_tag = IopDmatag(tag.uw[0], tag.uw[1]);
	channel.chcr->dma_tag = dma_tag;
	
#if DEBUG_LOG_IOP_DMAC_TAGS
	BOOST_LOG(Core::get_logger()) << 
		boost::format("IOP tag (dest chain mode) read on channel %s, Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.")
		% *channel.channel_id
		% dma_tag.tag0 % dma_tag.tag1
		% channel.chcr->extract_field(IopDmacChannelRegister_Chcr::CE);
#endif

	// Set tag transfer length.
	// The maximum supported length is 1MB - 16 bytes.
	// TODO: qword alignment is forced for source chain mode, but not dest - does it matter? Probably doesn't need it, when source chain is enforced anyway (ie: will never receive data that isn't qword aligned).
	// TODO: there is also a 'cache mode' part, but not sure where (also from PCSX2). It shouldn't need to be implemented anyway.
	// TODO: check if "& 0xFFFFC" is needed, or if its just PCSX2 specific.
	channel.bcr->transfer_length = channel.chcr->dma_tag.length();

	// TODO: look into the tag transfer enable (TTE) option not set (CHCR bit 8 aka "chopping enable").
	//       PCSX2 does not implement anything at all, but wisi might know something. SIF1 has this bit set always. For now, left unimplemented.
	if (channel.chcr->extract_field(IopDmacChannelRegister_Chcr::CE) == 0)
		throw std::runtime_error("IOP DMAC dest chain mode had TTE set to 0 - what is meant to happen?");

	return true;
}
