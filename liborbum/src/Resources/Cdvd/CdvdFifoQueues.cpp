#include "Resources/Cdvd/CdvdFifoQueues.hpp"

#include "Resources/Cdvd/CdvdRegisters.hpp"

ubyte CdvdFifoQueue_Ns_Data_Out::read_ubyte()
{
    auto _lock = scope_lock();

    ubyte data = DmaFifoQueue::read_ubyte();

    // Check if FIFO is empty and signal no more data.
    if (is_empty())
        ns_rdy_din->ready.insert_field(CdvdRegister_Ns_Rdy_Din::READY_EMPTY, 1);

    return data;
}

void CdvdFifoQueue_Ns_Data_Out::write_ubyte(const ubyte data)
{
    auto _lock = scope_lock();

    DmaFifoQueue::write_ubyte(data);

    // Signal some data is available.
    ns_rdy_din->ready.insert_field(CdvdRegister_Ns_Rdy_Din::READY_EMPTY, 0);
}
