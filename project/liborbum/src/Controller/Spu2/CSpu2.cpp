#include "Core.hpp"

#include "Controller/Spu2/CSpu2.hpp"

#include "Resources/RResources.hpp"
#include "Resources/Spu2/Spu2CoreTable.hpp"

CSpu2::CSpu2(Core * core) : 
	CController(core)
{
}

void CSpu2::handle_event(const ControllerEvent & event) const
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
		throw std::runtime_error("CSpu2 event handler not implemented - please fix!");
	}
	}
}

int CSpu2::time_to_ticks(const double time_us) const
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::SPU2::SPU2_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::Spu2]);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "SPU2 ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}


int CSpu2::time_step(const int ticks_available) const
{
	auto& r = core->get_resources();

	for (auto& spu2_core : r.spu2.cores)
	{
		// For each core, run through DMA transfers and sound generation.
		handle_dma_transfer(*spu2_core);
		handle_sound_generation(*spu2_core);

		// Finally do an interrupt check, and send signal to the IOP INTC if needed.
		handle_interrupt_check(*spu2_core);
	}

	return 1;
}

bool CSpu2::handle_dma_transfer(Spu2Core_Base & spu2_core) const
{
	// Check which DMA mode we are in, based on the ATTR.DMAMODE bits. Either manual DMA read/writes or auto DMA read/writes are possible.
	// If we are using auto DMA, the ADMAS register still needs to be set properly.
	// TODO: Not sure this is actually correct - I am lead to believe it is like this because of Nocash's psx docs (SPUCNT.SoundTxferMode), and it works.
	// TODO: Currently, reading from the SPU2 memory is unsupported. Although it is implemented in PCSX2/SPU2-X, I haven't been able to trigger it.
	//       In terms of the ATTR register, manual/auto DMA read mode probably sets it to 0b01xxxx or 0b11xxxx respectively, so these are set to throw an error for now.
	// TODO: I do not know what the "DMABITS" field is for, but probably doesn't matter after looking at SPU2-X code (not needed?). Probably not even related to DMA...
	//       Nocash PSX docs says related to other things, such as CD audio (SPUCNT)... 
	if (spu2_core.attr.extract_field(Spu2CoreRegister_Attr::DMABITS) > 0)
		throw std::runtime_error("SPU2 ATTR DMABITS field set to non-zero. What is this for?");

	int dma_count = 0;
	switch (spu2_core.attr.extract_field(Spu2CoreRegister_Attr::DMAMODE))
	{
	case 0:
	{
		// Auto DMA write mode.
		if (spu2_core.admas.is_adma_enabled()) 
			dma_count = transfer_data_adma_write(spu2_core); 
		break;
	}
	case 1:
	{
		// Auto DMA read mode. 
		if (spu2_core.admas.is_adma_enabled())
			dma_count = transfer_data_adma_read(spu2_core);
		break;
	}		
	case 2:
	{
		// Manual DMA write mode.
		dma_count = transfer_data_mdma_write(spu2_core);
		break;
	}
	case 3:
	{
		// Manual DMA read mode.
		dma_count = transfer_data_mdma_read(spu2_core);
		break;
	}
	default:
	{
		throw std::runtime_error("SPU2 could not determine DMA mode. Please fix.");
	}
	}

	return (dma_count > 0);
}

bool CSpu2::handle_sound_generation(Spu2Core_Base & spu2_core) const
{
	// Check if core is enabled.
	if (!spu2_core.attr.extract_field(Spu2CoreRegister_Attr::COREENABLE))
		return false; 

	return true;
}

int CSpu2::transfer_data_adma_write(Spu2Core_Base & spu2_core) const
{
	// TODO: Check this, its probably wrong. The write addresses are also meant to be used in conjunction with the current read address (double buffer).
	// Note: TSA is not used here! The write addresses are fixed. See pages 13, 28 and 55 of the SPU2 Overview manual.

	// Exit early if theres no data to process.
	if (!spu2_core.dma_fifo_queue->has_read_available(NUMBER_BYTES_IN_HWORD))
	{
		// Set 'no data available' magic values for SPU2 registers (done on each try).
		spu2_core.admas.set_adma_running(false);	
		spu2_core.statx.insert_field(Spu2CoreRegister_Statx::NEEDDATA, 1);
		return 0;
	}

	// Read in data and set 'data available' magic values for SPU2 registers.
	uhword data;
	spu2_core.dma_fifo_queue->read(reinterpret_cast<ubyte*>(&data), NUMBER_BYTES_IN_HWORD);
	spu2_core.admas.set_adma_running(true);	
	spu2_core.statx.insert_field(Spu2CoreRegister_Statx::NEEDDATA, 0);

	// Depending on the current transfer count, we are in the left or right sound channel data block (from SPU2-X/Dma.cpp).
	// Data incoming is in a striped pattern with 0x100 hwords for the left channel, followed by 0x100 hwords for the right channel, repeated.
	int block = static_cast<int>(spu2_core.attr.dma_offset / 0x100);
	bool in_left_block = ((block % 2) == 0);
	size_t channel_offset;
	if (in_left_block)
		channel_offset = spu2_core.attr.dma_offset - (block / 2) * 0x100;
	else
		channel_offset = spu2_core.attr.dma_offset - (block / 2 + 1) * 0x100;

	// ADMA is limited to a hword space of 0x100 for each sound channel (left and right), for each buffer (2 total), for a total of 0x100 * 4 address space.
	// See SPU2 Overview manual page 28.
	channel_offset %= 0x400;

	// Calculate final address.
	uptr address;
	if (in_left_block)
		address = Spu2CoreTable::SPU2_STATIC_INFO[spu2_core.core_id].base_tsa_left + static_cast<uptr>(channel_offset);
	else
		address = Spu2CoreTable::SPU2_STATIC_INFO[spu2_core.core_id].base_tsa_right + static_cast<uptr>(channel_offset);

		
	//log(Debug, "SPU2 core %d ADMA write ATTR.dma_offset = 0x%08X, channel_offset = 0x%08X, address = 0x%08X. FIFO queue size = 0x%X.", spu2_core.core_id, spu2_core.attr.dma_offset, channel_offset, address, spu2_core.FifoQueue->read_available());

	// Write to SPU2 memory.
	write_hword_memory(spu2_core, address, data);

	// Increment the transfer count.
	spu2_core.attr.dma_offset += 1;

	// ADMA has completed one transfer.
	return 1;
}

int CSpu2::transfer_data_adma_read(Spu2Core_Base & spu2_core) const
{
	throw std::runtime_error("SPU2 ADMA read not yet implemented. Look into the ATTR.DMAMODE bits, as this might be incorrectly called.");
}

int CSpu2::transfer_data_mdma_write(Spu2Core_Base & spu2_core) const
{
	// TODO: Check this!

	// Exit early if theres no data to process.
	if (!spu2_core.dma_fifo_queue->has_read_available(NUMBER_BYTES_IN_HWORD))
	{
		// Set 'no data available' magic values for SPU2 registers.
		spu2_core.statx.insert_field(Spu2CoreRegister_Statx::NEEDDATA, 1);
		return 0;
	}

	// Read in data and set 'data available' magic values for SPU2 registers.
	uhword data;
	spu2_core.dma_fifo_queue->read(reinterpret_cast<ubyte*>(&data), NUMBER_BYTES_IN_HWORD);
	spu2_core.statx.insert_field(Spu2CoreRegister_Statx::NEEDDATA, 0);

	// Calculate write address. Make sure address is not outside 2MB limit (remember, we are addressing by hwords).
	uhword tsal_addr_lo = spu2_core.tsal.read_uhword();
	uhword tsal_addr_hi = spu2_core.tsah.read_uhword();
	uptr tsal_addr = (static_cast<uptr>(tsal_addr_hi) << 16) | tsal_addr_lo;
	uptr address = static_cast<uptr>((tsal_addr + spu2_core.attr.dma_offset) % 0x100000);

	// Write to SPU2 memory.
	write_hword_memory(spu2_core, address, data);

	//log(Debug, "SPU2 core %d ADMA write ATTR.dma_offset = 0x%08X, address = 0x%08X. FIFO queue size = 0x%X.", spu2_core.core_id, spu2_core.attr.dma_offset, address, spu2_core.FifoQueue->read_available());

	// Increment the transfer count.
	spu2_core.attr.dma_offset += 1;
	
	// ADMA has completed one transfer.
	return 1;
}

int CSpu2::transfer_data_mdma_read(Spu2Core_Base & spu2_core) const
{
	throw std::runtime_error("SPU2 MDMA read not yet implemented. Look into the ATTR.DMAMODE bits, as this might be incorrectly called.");
}

uhword CSpu2::read_hword_memory(Spu2Core_Base & spu2_core, const uptr address) const
{
	auto& r = core->get_resources();

	// Check for IRQ conditions by comparing the address given with the IRQA register pair. Set IRQ if they match.
	uhword irq_addr_lo = spu2_core.irqal.read_uhword();
	uhword irq_addr_hi = spu2_core.irqah.read_uhword();
	uptr irq_addr = (static_cast<uptr>(irq_addr_hi) << 16) | irq_addr_lo;
	if (irq_addr == address)
		r.spu2.spdif_irqinfo.insert_field(Spu2Register_Spdif_Irqinfo::IRQ_KEYS[spu2_core.core_id], 1);

	return r.spu2.main_memory.read_uhword(address);
}

void CSpu2::write_hword_memory(Spu2Core_Base & spu2_core, const uptr address, const uhword value) const
{
	auto& r = core->get_resources();

	// Check for IRQ conditions by comparing the address given with the IRQA register pair. Set IRQ if they match.
	uhword irq_addr_lo = spu2_core.irqal.read_uhword();
	uhword irq_addr_hi = spu2_core.irqah.read_uhword();
	uptr irq_addr = (static_cast<uptr>(irq_addr_hi) << 16) | irq_addr_lo;
	if (irq_addr == address)
		r.spu2.spdif_irqinfo.insert_field(Spu2Register_Spdif_Irqinfo::IRQ_KEYS[spu2_core.core_id], 1);

	r.spu2.main_memory.write_uhword(address, value);
}

void CSpu2::handle_interrupt_check(Spu2Core_Base & spu2_core) const
{
	auto& r = core->get_resources();

	if (spu2_core.attr.extract_field(Spu2CoreRegister_Attr::IRQENABLE) 
		&& r.spu2.spdif_irqinfo.extract_field(Spu2Register_Spdif_Irqinfo::IRQ_KEYS[spu2_core.core_id]))
	{
		// IRQ was set, notify the IOP INTC.
		r.iop.intc.stat.insert_field(IopIntcRegister_Stat::SPU, 1);
	}
}