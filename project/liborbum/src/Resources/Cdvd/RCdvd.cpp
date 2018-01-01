#include "Resources/Cdvd/RCdvd.hpp"

RCdvd::RCdvd()
{
    n_rdy_din.ready.write_ubyte(0x4E);
    s_rdy_din.ready.write_ubyte(0x40);
}