#pragma once

#include <cereal/cereal.hpp>

#include "Common/Constants.hpp"
#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Iop/Sio2/Sio2Ports.hpp"
#include "Resources/Iop/Sio2/Sio2Registers.hpp"

/// SIO2 resources.
/// Responsible for communication with controllers and memory cards.
/// "SIO2 is a DMA interface for the SIO" - IopHW.h from PCSX2. See also IopSio2.h/cpp.
/// A lot of information can be found through the PS2SDK too: https://github.com/ps2dev/ps2sdk/tree/master/iop/system/sio2log/src.
class RSio2
{
public:
    RSio2();

    /// SIO2 ports (16 total).
    Sio2Port_Full port_0;
    Sio2Port_Full port_1;
    Sio2Port_Full port_2;
    Sio2Port_Full port_3;
    Sio2Port_Slim port_4;
    Sio2Port_Slim port_5;
    Sio2Port_Slim port_6;
    Sio2Port_Slim port_7;
    Sio2Port_Slim port_8;
    Sio2Port_Slim port_9;
    Sio2Port_Slim port_a;
    Sio2Port_Slim port_b;
    Sio2Port_Slim port_c;
    Sio2Port_Slim port_d;
    Sio2Port_Slim port_e;
    Sio2Port_Slim port_f;
    Sio2Port ports[Constants::IOP::SIO2::NUMBER_PORTS];

    /// Common registers.
    Sio2Register_Ctrl ctrl;
    SizedWordRegister recv1; // TODO: for now, returns device unplugged magic value (0x1D100).
    SizedWordRegister recv2; // Constant 0xF value.
    SizedWordRegister recv3;
    SizedWordRegister register_8278;
    SizedWordRegister register_827c;
    SizedWordRegister intr; // Also known as the STAT register.

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(port_0),
            CEREAL_NVP(port_1),
            CEREAL_NVP(port_2),
            CEREAL_NVP(port_3),
            CEREAL_NVP(port_4),
            CEREAL_NVP(port_5),
            CEREAL_NVP(port_6),
            CEREAL_NVP(port_7),
            CEREAL_NVP(port_8),
            CEREAL_NVP(port_9),
            CEREAL_NVP(port_a),
            CEREAL_NVP(port_b),
            CEREAL_NVP(port_c),
            CEREAL_NVP(port_d),
            CEREAL_NVP(port_e),
            CEREAL_NVP(port_f),
            CEREAL_NVP(ctrl),
            CEREAL_NVP(recv1),
            CEREAL_NVP(recv2),
            CEREAL_NVP(recv3),
            CEREAL_NVP(register_8278),
            CEREAL_NVP(register_827c),
            CEREAL_NVP(intr)
        );
    }
};