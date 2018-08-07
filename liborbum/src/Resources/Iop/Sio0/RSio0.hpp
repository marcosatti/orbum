#pragma once

#include "Common/Types/Register/SizedHwordRegister.hpp"
#include "Resources/Iop/Sio0/Sio0Registers.hpp"

/// SIO0 resources.
/// Responsible for communication with controllers and memory cards.
class RSio0
{
public:
    Sio0Register_Data data; // Hybrid FIFO port - can read and write to this port simultaneously.
    Sio0Register_Stat stat;
    SizedHwordRegister mode;
    Sio0Register_Ctrl ctrl;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(data),
            CEREAL_NVP(stat),
            CEREAL_NVP(mode),
            CEREAL_NVP(ctrl)
        );
    }
};