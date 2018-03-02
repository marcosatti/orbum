#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Register/SizedHwordRegister.hpp"

/// TODO: a little confused about the SPDIF_IRQINFO register - used for both SPDIF and IRQ information?
/// See the SPU2-X/spu2sys.cpp file for information about the IRQ's.
class Spu2Register_Spdif_Irqinfo : public SizedHwordRegister
{
public:
    static constexpr Bitfield IRQCORE0 = Bitfield(2, 1);
    static constexpr Bitfield IRQCORE1 = Bitfield(3, 1);
    static constexpr Bitfield IRQ_KEYS[Constants::SPU2::NUMBER_CORES] = { IRQCORE0, IRQCORE1 };
};
