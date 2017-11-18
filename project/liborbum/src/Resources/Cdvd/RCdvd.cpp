#include "Resources/Cdvd/RCdvd.hpp"

RCdvd::RCdvd() :
    n_rdy_din(DEBUG_FIFO_SIZE),
    n_data_out(DEBUG_FIFO_SIZE),
    s_rdy_din(DEBUG_FIFO_SIZE),
    s_data_out(DEBUG_FIFO_SIZE)
{
}