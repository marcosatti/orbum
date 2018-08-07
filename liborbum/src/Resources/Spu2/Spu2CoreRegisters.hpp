#pragma once

#include <cstddef>

#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Register/SizedHwordRegister.hpp"
#include "Common/Types/ScopeLock.hpp"

/// Used as a multipurpose register for registers of the same layout.
class Spu2CoreRegister_Vol : public SizedHwordRegister
{
public:
    static constexpr Bitfield CONSTVALUE = Bitfield(0, 15);
    static constexpr Bitfield CONSTTOGGLE = Bitfield(15, 1);
    static constexpr Bitfield LINEXPMODE = Bitfield(13, 2);
    static constexpr Bitfield X = Bitfield(12, 1);
    static constexpr Bitfield LINEXPVALUE = Bitfield(0, 7);
};

/// Used as a multipurpose register for registers of the same layout.
class Spu2CoreRegister_Chan0 : public SizedHwordRegister
{
public:
    static constexpr Bitfield V0 = Bitfield(0, 1);
    static constexpr Bitfield V1 = Bitfield(1, 1);
    static constexpr Bitfield V2 = Bitfield(2, 1);
    static constexpr Bitfield V3 = Bitfield(3, 1);
    static constexpr Bitfield V4 = Bitfield(4, 1);
    static constexpr Bitfield V5 = Bitfield(5, 1);
    static constexpr Bitfield V6 = Bitfield(6, 1);
    static constexpr Bitfield V7 = Bitfield(7, 1);
    static constexpr Bitfield V8 = Bitfield(8, 1);
    static constexpr Bitfield V9 = Bitfield(9, 1);
    static constexpr Bitfield V10 = Bitfield(10, 1);
    static constexpr Bitfield V11 = Bitfield(11, 1);
    static constexpr Bitfield V12 = Bitfield(12, 1);
    static constexpr Bitfield V13 = Bitfield(13, 1);
    static constexpr Bitfield V14 = Bitfield(14, 1);
    static constexpr Bitfield V15 = Bitfield(15, 1);
};

/// Used as a multipurpose register for registers of the same layout.
class Spu2CoreRegister_Chan1 : public SizedHwordRegister
{
public:
    static constexpr Bitfield V16 = Bitfield(0, 1);
    static constexpr Bitfield V17 = Bitfield(1, 1);
    static constexpr Bitfield V18 = Bitfield(2, 1);
    static constexpr Bitfield V19 = Bitfield(3, 1);
    static constexpr Bitfield V20 = Bitfield(4, 1);
    static constexpr Bitfield V21 = Bitfield(5, 1);
    static constexpr Bitfield V22 = Bitfield(6, 1);
    static constexpr Bitfield V23 = Bitfield(7, 1);
};

class Spu2CoreRegister_Mmix : public SizedHwordRegister
{
public:
    static constexpr Bitfield SINER = Bitfield(0, 1);
    static constexpr Bitfield SINEL = Bitfield(1, 1);
    static constexpr Bitfield SINR = Bitfield(2, 1);
    static constexpr Bitfield SINL = Bitfield(3, 1);
    static constexpr Bitfield MINER = Bitfield(4, 1);
    static constexpr Bitfield MINEL = Bitfield(5, 1);
    static constexpr Bitfield MINR = Bitfield(6, 1);
    static constexpr Bitfield MINL = Bitfield(7, 1);
    static constexpr Bitfield MSNDER = Bitfield(8, 1);
    static constexpr Bitfield MSNDEL = Bitfield(9, 1);
    static constexpr Bitfield MSNDR = Bitfield(10, 1);
    static constexpr Bitfield MSNDL = Bitfield(11, 1);
};

/// The SPU2 Core "ATTR" (attributes) register.
/// Contains the DMA transfer state parameters, see below for information.
/// Needs to be scope locked by the SPU2 controller.
class Spu2CoreRegister_Attr : public SizedHwordRegister, public ScopeLock
{
public:
    static constexpr Bitfield DMABITS = Bitfield(1, 3);
    static constexpr Bitfield DMAMODE = Bitfield(4, 2);
    static constexpr Bitfield IRQENABLE = Bitfield(6, 1);
    static constexpr Bitfield FXENABLE = Bitfield(7, 1);
    static constexpr Bitfield NOISECLOCK = Bitfield(8, 6);
    static constexpr Bitfield MUTE = Bitfield(14, 1);
    static constexpr Bitfield COREENABLE = Bitfield(15, 1);

    Spu2CoreRegister_Attr();

    /// When this register is written to, resets the DMA transfer state.
    /// Scope locked for the entire duration.
    void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value) override;

    /// Current auto/manual DMA transfer count state, in terms of hwords.
    /// Reset upon the register being written to.
    size_t dma_offset;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            cereal::base_class<SizedHwordRegister>(this),
            CEREAL_NVP(dma_offset)
        );
    }
};

/// SPU2 Core STATX register.
/// Lots of good info can be found by looking at where the IOP BIOS SPU2 debug
/// strings are used. BIOS will detect the SPU2 has timed out if many of these
/// bits are not set correctly, which it tries for 256 (0x100) / 3841 (0xF01)
/// times depending on the bit.
class Spu2CoreRegister_Statx : public SizedHwordRegister
{
public:
    static constexpr Bitfield UNKNOWN4 = Bitfield(4, 2); // Unknown, referenced from BIOS.
    static constexpr Bitfield DREQ = Bitfield(7, 1);     // Request for more data (confirmed with BIOS).
    static constexpr Bitfield WRDY_M = Bitfield(10, 1);  // (write?) ready flag? BIOS waits for this to be 0, otherwise it says SPU2 has timed out.
};

/// SPU2 Core ADMAS register.
/// Some vague references in the SPU2 overview manual, not much info overall.
class Spu2CoreRegister_Admas : public SizedHwordRegister
{
public:
    Spu2CoreRegister_Admas();

    /// Sets the ADMA running status (magic values).
    void set_adma_running(const bool running);

    /// Returns if ADMA is enabled for the core_id set.
    bool is_adma_enabled();

    const int* core_id;
};