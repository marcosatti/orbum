#pragma once

#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"
#include "Common/Types/ScopeLock.hpp"

class CdvdRegister_Ns_Rdy_Din;

/// CDVD extended DmaFifoQueue, used as the N/S command result FIFO's (N/S_DATA_OUT).
/// Upon reading or writing, it will check for the FIFO being empty, and set the NS_RDY_DIN->Ready register accordingly (magic values).
class CdvdFifoQueue_Ns_Data_Out : public DmaFifoQueue<>, public ScopeLock
{
public:
    /// Updates the Ready register upon reads/writes with magic values, based on if FIFO is empty.
    /// Scope locked for the entire duration.
    ubyte read_ubyte() override;
    void write_ubyte(const ubyte data) override;

    /// Reference to the NS_RDY_DIN register.
    CdvdRegister_Ns_Rdy_Din* ns_rdy_din;
};