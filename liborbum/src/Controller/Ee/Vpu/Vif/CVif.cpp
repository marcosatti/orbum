#include <boost/format.hpp>

#include "Controller/Ee/Vpu/Vif/CVif.hpp"

#include "Core.hpp"
#include "Resources/RResources.hpp"

CVif::CVif(Core* core) :
    CController(core)
{
}

void CVif::handle_event(const ControllerEvent& event)
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
    int ticks = static_cast<int>(time_us / 1.0e6 * Constants::EE::EEBUS_CLK_SPEED * core->get_options().system_bias_vif);

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

void CVif::INSTRUCTION_UNSUPPORTED(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    throw std::runtime_error("VIFcode CMD field was invalid! Please fix.");
}

// Refer to EE Users Manual pg 103.
void CVif::NOP(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    // nothing to do
    return;
}

// Refer to EE Users Manual pg 104.
void CVif::STCYCL(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    // Writes CODE.IMMEDIATE to CYCLE
    uword immediate = inst.imm();
    unit->cycle.write_uword(immediate);
}

// Refer to EE Users Manual pg 105.
void CVif::OFFSET(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    // VIF1 only
    if (unit->core_id != 1) {
        BOOST_LOG(Core::get_logger()) << str(boost::format("Warning: VIF%d called a VIF1-only instruction: OFFSET") % unit->core_id);
        return;
    }

    // Clear STAT.DBF
    unit->stat.insert_field(VifUnitRegister_Stat::DBF, 0);

    // Writes the lower 10 bits of CODE.IMMEDIATE to OFST
    uword immediate = inst.imm();
    unit->ofst.insert_field(VifUnitRegister_Ofst::OFFSET, immediate);

    // Transfer BASE to TOPS
    unit->tops.write_uword(unit->base.read_uword());
}

// Refer to EE Users Manual pg 106.
void CVif::BASE(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    // VIF1 only
    if (unit->core_id != 1) {
        BOOST_LOG(Core::get_logger()) << str(boost::format("Warning: VIF%d called a VIF1-only instruction: BASE") % unit->core_id);
        return;
    }

    // Writes the lower 10 bits of CODE.IMMEDIATE to BASE
    uword immediate = inst.imm();
    unit->base.insert_field(VifUnitRegister_Base::BASE, immediate);
}

// Refer to EE Users Manual pg 107.
void CVif::ITOP(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    uword immediate = inst.imm();
    unit->itops.insert_field(VifUnitRegister_Itops::ITOPS, immediate);
}

// Refer to EE Users Manual pg 108.
void CVif::STMOD(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    uword immediate = inst.imm();
    unit->mode.insert_field(VifUnitRegister_Mode::MOD, immediate);
}

void CVif::MSKPATH3(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    // VIF1 only
    if (unit->core_id != 1) {
        BOOST_LOG(Core::get_logger()) << str(boost::format("Warning: VIF%d called a VIF1-only instruction: MSKPATH3") % unit->core_id);
        return;
    }

    // TODO: Implement this when GIF is implemented
}

void CVif::MARK(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    uword immediate = inst.imm();
    unit->mark.insert_field(VifUnitRegister_Mark::MARK, immediate);
}

void CVif::FLUSHE(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::FLUSH(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    // VIF1 only
    if (unit->core_id != 1) {
        BOOST_LOG(Core::get_logger()) << str(boost::format("Warning: VIF%d called a VIF1-only instruction: FLUSH") % unit->core_id);
        return;
    }

    // TODO: Implement this
}

void CVif::FLUSHA(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    // VIF1 only
    if (unit->core_id != 1) {
        BOOST_LOG(Core::get_logger()) << str(boost::format("Warning: VIF%d called a VIF1-only instruction: FLUSHA") % unit->core_id);
        return;
    }

    // TODO: Implement this
}

void CVif::MSCAL(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::MSCNT(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::MSCALF(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    // VIF1 only
    if (unit->core_id != 1) {
        BOOST_LOG(Core::get_logger()) << str(boost::format("Warning: VIF%d called a VIF1-only instruction: MSCALF") % unit->core_id);
        return;
    }

    // TODO: Implement this
}

void CVif::STMASK(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::STROW(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::STCOL(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::MPG(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::DIRECT(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    // VIF1 only
    if (unit->core_id != 1) {
        BOOST_LOG(Core::get_logger()) << str(boost::format("Warning: VIF%d called a VIF1-only instruction: DIRECT") % unit->core_id);
        return;
    }

    // TODO: Implement this
}

void CVif::DIRECTHL(VifUnit_Base* unit, const VifcodeInstruction inst)
{
    // VIF1 only
    if (unit->core_id != 1) {
        BOOST_LOG(Core::get_logger()) << str(boost::format("Warning: VIF%d called a VIF1-only instruction: DIRECTHL") % unit->core_id);
        return;
    }

    // TODO: Implement this
}

void CVif::UNPACK(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_S_32(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_S_16(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_S_8(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V2_32(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V2_16(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V2_8(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V3_32(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V3_16(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V3_8(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V4_32(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V4_16(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V4_8(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}

void CVif::UNPACK_V4_5(VifUnit_Base* unit, const VifcodeInstruction inst)
{
}
