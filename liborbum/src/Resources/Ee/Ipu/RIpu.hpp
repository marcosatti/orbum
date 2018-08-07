#pragma once

#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Register/SizedDwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Ee/Ipu/IpuRegisters.hpp"

class RIpu
{
public:
    RIpu();

    /// IPU memory mapped registers. See page 21 of EE Users Manual.
    /// 0x10002000
    IpuRegister_Cmd cmd;
    IpuRegister_Ctrl ctrl;
    IpuRegister_Bp bp;
    IpuRegister_Top top;
    ArrayByteMemory memory_2040;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(cmd),
            CEREAL_NVP(ctrl),
            CEREAL_NVP(bp),
            CEREAL_NVP(top),
            CEREAL_NVP(memory_2040)
        );
    }
};
