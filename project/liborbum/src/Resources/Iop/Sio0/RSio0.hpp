#pragma once

#include "Common/Types/Register/SizedHwordRegister.hpp"

/// SIO0 resources.
/// Responsible for communication with controllers and memory cards.
struct RSio0
{
	SizedHwordRegister data;
	SizedHwordRegister stat;
	SizedHwordRegister mode;
	SizedHwordRegister ctrl;
};