#include "Core.hpp"
#include "Controller/Ee/Vpu/Vif/CVif.hpp"

#include "Resources/RResources.hpp"

CVif::CVif(Core * core) :
	CController(core)
{
}

void CVif::handle_event(const ControllerEvent & event)
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
		throw std::runtime_error("CVif event handler not implemented - please fix!");
	}
	}
}

int CVif::time_to_ticks(const double time_us)
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::Vif]);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "Vif ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CVif::time_step(const int ticks_available)
{
	auto& r = core->get_resources();

	for (auto& unit : r.ee.vpu.vif.units)
	{
		// Check if VIF is stalled, do not do anything (FBRST.STC needs to be written to before we continue).
		if (unit->stat.is_stalled())
			continue;

		// Check the FIFO queue for incoming DMA packet. Exit early if there is nothing to process.
		if (!unit->dma_fifo_queue->has_read_available(NUMBER_BYTES_IN_QWORD))
			continue;
		uqword packet;
		unit->dma_fifo_queue->read(reinterpret_cast<ubyte*>(&packet), NUMBER_BYTES_IN_QWORD);

		// We have an incoming DMA unit of data, now we must split it into 4 x 32-bit and process each one. // TODO: check wih pcsx2's code.
		for (auto& data : packet.uw)
		{
			// Check the NUM register, to determine if we are continuing a VIFcode instruction instead of reading a VIFcode.
			if (unit->num.extract_field(VifUnitRegister_Num::NUM))
			{
				
			}
			else
			{
				// Set the current data as the VIFcode.
				VifcodeInstruction inst = VifcodeInstruction(data);

				// Process the VIFcode by calling the instruction handler.
				(this->*INSTRUCTION_TABLE[inst.get_info()->impl_index])(unit, inst);

				// If the I bit is set, we need to raise an interrupt after the whole VIF packet has been processed - set a context variable.
				/*
				if (instruction.i())
				{
					auto _lock = r.ee.intc.stat.scope_lock();
					r.ee.intc.stat.insert_field(EeIntcRegister_Stat::VIF, 1);
				}
				*/
			}
		}
	}

	// TODO: different for each unit...
	return 1;
}

void CVif::INSTRUCTION_UNSUPPORTED(VifUnit_Base * unit, const VifcodeInstruction inst)
{
	throw std::runtime_error("VIFcode CMD field was invalid! Please fix.");
}

void CVif::NOP(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::STCYCL(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::OFFSET(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::BASE(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::ITOP(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::STMOD(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::MSKPATH3(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::MARK(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::FLUSHE(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::FLUSH(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::FLUSHA(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::MSCAL(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::MSCNT(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::MSCALF(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::STMASK(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::STROW(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::STCOL(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::MPG(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::DIRECT(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::DIRECTHL(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_S_32(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_S_16(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_S_8(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V2_32(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V2_16(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V2_8(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V3_32(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V3_16(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V3_8(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V4_32(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V4_16(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V4_8(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V4_5(VifUnit_Base * unit, const VifcodeInstruction inst)
{
}
