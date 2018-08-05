#pragma once

#include "Common/Types/Bus/ByteBus.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Primitive.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Dmac/REeDmac.hpp"
#include "Resources/Ee/EeRegisters.hpp"
#include "Resources/Ee/Gif/RGif.hpp"
#include "Resources/Ee/Intc/REeIntc.hpp"
#include "Resources/Ee/Ipu/RIpu.hpp"
#include "Resources/Ee/Timers/REeTimers.hpp"
#include "Resources/Ee/Vpu/RVpu.hpp"

/// EE structure.
/// See page 22 of the EE Overview Manual, and the items within the EE Users Manual.
class REe
{
public:
    REe();

    /// EE Core resources.
    REeCore core;

    /// DMAC resources.
    REeDmac dmac;

    /// INTC resources.
    REeIntc intc;

    /// Timers resources.
    REeTimers timers;

    /// IPU resources.
    RIpu ipu;

    /// GIF resources.
    RGif gif;

    /// VPU resources.
    RVpu vpu;

    /// EE bus space.
    ByteBus<uptr> bus;

    /// Main Memory (32MB).
    ArrayByteMemory main_memory;

    /// Misc. EE memory/registers, defined on page 21 onwards of the EE Users Manual.
    /// Other resources come from PCSX2.
    ArrayByteMemory unknown_1a000000; // Undocumented memory/register @ 0x1A000000 -> 0x1A00FFFF.
    EeRegister_Sio memory_sio;        // Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE).
    SizedWordRegister register_f400;
    ArrayByteMemory memory_f410; // Needs to be constant value (by BIOS).
    SizedWordRegister register_f420;
    EeRegister_Mch memory_mch; // No documentation (except for name)! From old PCSX2. Needed by the BIOS for RDRAM initialisation.
    ArrayByteMemory memory_f450;

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(core),
            CEREAL_NVP(dmac),
            CEREAL_NVP(intc),
            CEREAL_NVP(timers),
            CEREAL_NVP(ipu),
            CEREAL_NVP(gif),
            CEREAL_NVP(vpu),
            CEREAL_NVP(main_memory),
            CEREAL_NVP(unknown_1a000000),
            CEREAL_NVP(memory_sio),
            CEREAL_NVP(register_f400),
            CEREAL_NVP(memory_f410),
            CEREAL_NVP(register_f420),
            CEREAL_NVP(memory_mch),
            CEREAL_NVP(memory_f450)
        );
    }
};