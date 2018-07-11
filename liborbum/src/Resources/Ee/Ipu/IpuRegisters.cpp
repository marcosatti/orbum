#include "Resources/Ee/Ipu/IpuRegisters.hpp"

bool IpuRegister_Cmd::is_busy() 
{
    udword cmd = this->read_udword();
    return (this->BUSY.extract_from(cmd) == 1);
}

void IpuRegister_Cmd::set_busy() 
{
    udword cmd = this->read_udword();
    this->write_udword(this->BUSY.insert_into(cmd, (udword)1));
}
