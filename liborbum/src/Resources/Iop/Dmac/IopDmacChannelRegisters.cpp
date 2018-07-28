#include "Resources/Iop/Dmac/IopDmacChannelRegisters.hpp"

#include "Resources/SbusRegisters.hpp"

using LogicalMode = IopDmacChannelRegister_Chcr::LogicalMode;
using Direction = IopDmacChannelRegister_Chcr::Direction;

IopDmacChannelRegister_Chcr::IopDmacChannelRegister_Chcr() :
    dma_started(false)
{
}

LogicalMode IopDmacChannelRegister_Chcr::get_logical_mode()
{
    return static_cast<LogicalMode>(extract_field(SM));
}

Direction IopDmacChannelRegister_Chcr::get_direction()
{
    return static_cast<Direction>(extract_field(TD));
}

void IopDmacChannelRegister_Chcr::write_uword(const uword value)
{
    auto start_old = extract_field(START);

    SizedWordRegister::write_uword(value);

    auto start_new = extract_field(START);

    // Reset DMA flags on suspended -> start.
    if ((start_old == 0) && (start_new != 0))
    {
        dma_started = false;
        dma_tag = IopDmatag();
    }
}

void IopDmacChannelRegister_Chcr::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
    auto _lock = scope_lock();
    write_uword(value);
}

IopDmacChannelRegister_Bcr::IopDmacChannelRegister_Bcr() :
    SizedWordRegister(),
    transfer_length(0)
{
}

void IopDmacChannelRegister_Bcr::calculate(const bool use_blocks)
{
    // Update the transfer size.
    // When BS = 0, it is interpreted as 0x10000 (see wisi and sp193's IOP DMAC docs).
    // Wben BA = 0, it is also interpreted as 0x10000 (see wisi and sp193's IOP DMAC docs).
    if (use_blocks)
    {
        uword bs = extract_field(BS);
        uword ba = extract_field(BA);
        bs = (bs > 0) ? bs : 0x10000;
        ba = (ba > 0) ? ba : 0x10000;
        transfer_length = ba * bs;
    }
    else
    {
        uword bs = extract_field(BS);
        bs = (bs > 0) ? bs : 0x10000;
        transfer_length = bs;
    }
}

void IopDmacChannelRegister_Chcr_To::write_uword(const uword value)
{
    IopDmacChannelRegister_Chcr::write_uword(value | (1 << 0));
}

void IopDmacChannelRegister_Chcr_From::write_uword(const uword value)
{
    IopDmacChannelRegister_Chcr::write_uword(value & ~(1 << 0));
}

IopDmacChannelRegister_Chcr_Sif0::IopDmacChannelRegister_Chcr_Sif0() :
    sbus_f240(nullptr)
{
}

void IopDmacChannelRegister_Chcr_Sif0::write_uword(const uword value)
{
    IopDmacChannelRegister_Chcr_To::write_uword(value);

    auto start = extract_field(START);
    auto dir = get_direction();

    // Trigger SBUS update.
    if (start > 0 && dir == Direction::TO)
        handle_sbus_update_start();
}

void IopDmacChannelRegister_Chcr_Sif0::handle_sbus_update_start() const
{
    // Update 0x1D000040 (maps to Common->REGISTER_F240) with magic value.
    sbus_f240->write_uword(sbus_f240->read_uword() | 0x2000);
}

IopDmacChannelRegister_Chcr_Sif1::IopDmacChannelRegister_Chcr_Sif1() :
    sbus_f240(nullptr)
{
}

void IopDmacChannelRegister_Chcr_Sif1::write_uword(const uword value)
{
    IopDmacChannelRegister_Chcr_From::write_uword(value);

    auto start = extract_field(START);
    auto dir = get_direction();

    // Trigger SBUS update.
    if (start == 0 && dir == Direction::FROM)
        handle_sbus_update_finish();
}

void IopDmacChannelRegister_Chcr_Sif1::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
    // Force chain mode.
    uword temp = value;
    if (context == BusContext::Iop)
        temp |= (1 << 10);

    write_uword(temp);
}

void IopDmacChannelRegister_Chcr_Sif1::handle_sbus_update_finish() const
{
    // Update 0x1000F240 (maps to Common->REGISTER_F240) with magic values.
    sbus_f240->write_uword(sbus_f240->read_uword() & (~0x40));
    sbus_f240->write_uword(sbus_f240->read_uword() & (~0x4000));
}

IopDmacChannelRegister_Chcr_Sif2::IopDmacChannelRegister_Chcr_Sif2() :
    IopDmacChannelRegister_Chcr(),
    sbus_f240(nullptr)
{
}

void IopDmacChannelRegister_Chcr_Sif2::write_uword(const uword value)
{
    IopDmacChannelRegister_Chcr::write_uword(value);

    auto start = extract_field(START);
    auto dir = get_direction();

    // Trigger SBUS update.
    if (start > 0 && dir == Direction::TO)
        handle_sbus_update_start();
    else if (start == 0 && dir == Direction::FROM)
        handle_sbus_update_finish();
}

void IopDmacChannelRegister_Chcr_Sif2::handle_sbus_update_start() const
{
    // Update 0x1D000040 (maps to Common->REGISTER_F240) with magic value.
    sbus_f240->write_uword(sbus_f240->read_uword() | 0x8000);
}

void IopDmacChannelRegister_Chcr_Sif2::handle_sbus_update_finish() const
{
    // Update 0x1D000040 (maps to Common->REGISTER_F240) with magic values.
    sbus_f240->write_uword(sbus_f240->read_uword() & (~0x80));
    sbus_f240->write_uword(sbus_f240->read_uword() & (~0x8000));
}
