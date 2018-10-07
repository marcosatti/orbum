#pragma once

#include <cereal/cereal.hpp>

#include "Common/Constants.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Memory/ArrayHwordMemory.hpp"
#include "Resources/Spu2/Spu2Cores.hpp"
#include "Resources/Spu2/Spu2Registers.hpp"

/// Describes the SPU2 (sound) resources that is attached through the IOP.
/// No official documentation, except for the SPU2 Overview manual which does help.
/// Most of the implementation comes from PCSX2. Thanks to everyone involved!
/// The registers are assigned to the 0x1F900000 -> 0x1F900800 space in the IOP.
class RSpu2
{
public:
    RSpu2();

    /// SPU2 Cores.
    Spu2Core_Base core_0;
    Spu2Core_Base core_1;
    Spu2Core_Base* cores[Constants::SPU2::NUMBER_CORES];

    /// SPDIF Registers.
    SizedHwordRegister spdif_out;
    Spu2Register_Spdif_Irqinfo spdif_irqinfo;
    SizedHwordRegister spdif_07c4;
    SizedHwordRegister spdif_mode;
    SizedHwordRegister spdif_media;
    SizedHwordRegister spdif_07ca;
    SizedHwordRegister spdif_protect;

    /// SPU2 Local Memory (2MB).
    /// Addressed within the SPU2 system logic as 16-bit units (half-words) (address range 0x00_0000 -> 0x0F_FFFF).
    ArrayHwordMemory main_memory;

    /// Unknown memory / registers.
    /// There is a block of registers (with IOP MMU prefix address 0x1F900xxx) after both the core 0 and 1 known registers that are accessed.
    /// For core 0 this is in the range [0x346, 0x400).
    /// For core 1 this is in the range [0x746, 0x760), [0x7B0, 0x7C0) and [0x7CE, 0x800).
    ArrayByteMemory memory_0346;
    ArrayByteMemory memory_0746;
    ArrayByteMemory memory_07b0;
    ArrayByteMemory memory_07ce;

public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            CEREAL_NVP(core_0),
            CEREAL_NVP(core_1),
            CEREAL_NVP(spdif_out),
            CEREAL_NVP(spdif_irqinfo),
            CEREAL_NVP(spdif_07c4),
            CEREAL_NVP(spdif_mode),
            CEREAL_NVP(spdif_media),
            CEREAL_NVP(spdif_07ca),
            CEREAL_NVP(spdif_protect),
            CEREAL_NVP(main_memory),
            CEREAL_NVP(memory_0346),
            CEREAL_NVP(memory_0746),
            CEREAL_NVP(memory_07b0),
            CEREAL_NVP(memory_07ce));
    }
};