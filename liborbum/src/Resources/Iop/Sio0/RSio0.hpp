#pragma once

#include "Common/Types/Register/SizedHwordRegister.hpp"

#include "Resources/Iop/Sio0/Sio0Registers.hpp"

/// SIO0 resources.
/// Responsible for communication with controllers and memory cards.
struct RSio0
{
	Sio0Register_Data  data; // Hybrid FIFO port - can read and write to this port simultaneously.
	Sio0Register_Stat  stat;
	SizedHwordRegister mode;
	Sio0Register_Ctrl  ctrl;
};
