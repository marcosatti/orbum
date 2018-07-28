#pragma once

#include "Common/Types/Bitfield.hpp"
#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"
#include "Common/Types/Register/ByteRegister.hpp"
#include "Common/Types/Register/SizedByteRegister.hpp"
#include "Common/Types/ScopeLock.hpp"

/// CDVD register / FIFO queue hybrid "register".
/// Read: SizedByteRegister: {N/S}_READY.
/// Write: DmaFifoQueue: {N/S}_DATA_IN.
/// The IOP uses this for 2 things (TODO: only valid for S commands so far, not sure about N):
/// 1. The DATA_IN FIFO is used as the command parameter input.
/// 2. The READY register communicates if the CDVD controller is busy (0x80 flag), or if the DATA_OUT(!) FIFO is empty (0x40 flag).
///    Yes, the DATA_OUT FIFO!!! See CdvdFifoQueue_Ns_Data_Out.
class CdvdRegister_Ns_Rdy_Din : public ByteRegister
{
public:
    static constexpr Bitfield READY_EMPTY = Bitfield(6, 1); // DATA_OUT FIFO empty flag (from PCSX2 / bios).
    static constexpr Bitfield READY_BUSY = Bitfield(7, 1);  // Busy / command pending flag (from bios).

    void initialise() override;

    ubyte read_ubyte() override;
    void write_ubyte(const ubyte value) override;

    /// Resources.
    SizedByteRegister ready;
    DmaFifoQueue<> data_in;
};

/// CDVD N/S command FIFO register.
/// TODO: might not need a lock, but on now to be safe. The IOP only writes to this register, and uses the ns_rdy_din
///       counterpart to check for busy/fifo status. Conversely, from the emulator, we only ever read from this and write
///       to the ns_rdy_din.
class CdvdRegister_Ns_Command : public SizedByteRegister, public ScopeLock
{
public:
    CdvdRegister_Ns_Command();

    /// (Locked) Sets the write latch and the ns_rdy_din->ready.busy flag when this is written to.
    void byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value) override;

    /// Bus write latch, used for checking if a command is pending.
    /// TODO: probably don't need this (can check busy status from ready register), but just do it to be safe.
    ///       The busy status could potentially be used across multiple ticks, so we would have no way of knowing
    ///       when to perform first-run tasks.
    bool write_latch;

    /// Reference to the ready register.
    CdvdRegister_Ns_Rdy_Din* ns_rdy_din;
};