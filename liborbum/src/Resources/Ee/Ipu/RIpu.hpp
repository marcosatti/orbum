#pragma once

#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Register/SizedDwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Ee/Ipu/IpuRegisters.hpp"

struct RIpu
{
    RIpu();

    /// IPU memory mapped registers. See page 21 of EE Users Manual.
    /// 0x10002000
    IpuRegister_Cmd cmd;
    IpuRegister_Ctrl ctrl;
    IpuRegister_Bp bp;
    IpuRegister_Top top;
    ArrayByteMemory memory_2040;
};
