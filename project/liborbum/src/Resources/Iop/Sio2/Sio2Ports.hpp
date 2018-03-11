#include "Resources/Iop/Sio2/Sio2PortRegisters.hpp"

/// Describes an abstract SIO2 port.
class Sio2Port
{
public:
    Sio2Port();

    Sio2PortRegister_Ctrl1 * ctrl_1;
    Sio2PortRegister_Ctrl2 * ctrl_2;
    Sio2PortRegister_Ctrl3 * ctrl_3;
};

/// Port that contains all 3 CTRL registers.
class Sio2Port_Full
{
public:
    Sio2PortRegister_Ctrl1 ctrl_1;
    Sio2PortRegister_Ctrl2 ctrl_2;
    Sio2PortRegister_Ctrl3 ctrl_3;
};

/// Port that contains only 1 CTRL register (ctrl_3).
class Sio2Port_Slim
{
public:
    Sio2PortRegister_Ctrl3 ctrl_3;
};
