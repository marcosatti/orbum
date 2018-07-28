#pragma once

#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/ScopeLock.hpp"
#include "Resources/Iop/Dmac/IopDmatag.hpp"

class SbusRegister_F240;

/// The IOP DMAC D_CHCR register.
/// Register should be scope locked by the DMAC controller.
/// Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm), and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
class IopDmacChannelRegister_Chcr : public SizedWordRegister, public ScopeLock
{
public:
    enum class Direction
    {
        // Ordered according to CHCR.TD. Relative to FIFO's perspective.
        FROM = 0,
        TO = 1
    };

    enum class LogicalMode
    {
        // Ordered according to CHCR.SM.
        NORMAL_BURST = 0,
        NORMAL_SLICE = 1,
        LINKEDLIST = 2,
        CHAIN = 3
    };

    static constexpr Bitfield TD = Bitfield(0, 1);
    static constexpr Bitfield MAS = Bitfield(1, 1);
    static constexpr Bitfield CE = Bitfield(8, 1);
    static constexpr Bitfield SM = Bitfield(9, 2);
    static constexpr Bitfield ILINKUNK = Bitfield(11, 1);
    static constexpr Bitfield C_DWS = Bitfield(16, 3);
    static constexpr Bitfield C_CWS = Bitfield(20, 3);
    static constexpr Bitfield START = Bitfield(24, 1);
    static constexpr Bitfield FORCE = Bitfield(28, 1);
    static constexpr Bitfield FORCESLICE = Bitfield(29, 1);
    static constexpr Bitfield BUSSNOOPING = Bitfield(30, 1);
    static constexpr Bitfield ILINKAR = Bitfield(31, 1);

    IopDmacChannelRegister_Chcr();

    /// Returns the channel runtime logical mode its operating in.
    LogicalMode get_logical_mode();

    /// Gets the runtime direction. Useful for channels where it can be either way.
    Direction get_direction();

    /// Resets the flags below when START = 1 is written.
    void write_uword(const uword value) override;

    /// Scope locked for entire duration.
    void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;

    /// DMA started flag. Used to indicate if a DMA transfer is in progress, in order for the DMAC to perform some initial and final checks.
    /// An example of the DMAC using this is to check for an initial invalid transfer length.
    /// Reset to false upon writing to this register.
    bool dma_started;

    // DMA tag holding area, set by the DMAC when a tag is read.
    IopDmatag dma_tag;
};

/// The IOP DMAC D_BCR register.
/// Based off the nocash PSX docs (http://problemkaputt.de/psx-spx.htm),
/// and wisi and SP193's docs (http://psx-scene.com/forums/f167/speed-iop-dma-relaying-156928/).
class IopDmacChannelRegister_Bcr : public SizedWordRegister
{
public:
    static constexpr Bitfield BS = Bitfield(0, 16);
    static constexpr Bitfield BA = Bitfield(16, 16);

    IopDmacChannelRegister_Bcr();

    // Calculates the transfer size, based on the BCR register value.
    // Call this before starting a DMA transfer, and then use the transfer length member directly.
    // Parsing use_blocks = true means a block mode transfer size is calculated, otherwise, slice mode is calculated.
    // (This is why we cannot calculate it directly when written - relies on CHCR status.)
    void calculate(const bool use_blocks);

    // Transfer size.
    // The total length after calling calculate() is stored here.
    // The register value is not meant to change during the transfer.
    // This is directly accessible to the IOP DMAC which manipulates this value.
    size_t transfer_length;
};

// A base IOP TO DMAC D_CHCR register.
// Sets the constant direction (TO) upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
class IopDmacChannelRegister_Chcr_To : public IopDmacChannelRegister_Chcr
{
public:
    /// Upon writes, sets the correct direction (TO).
    void write_uword(const uword value) override;
};

// A base IOP FROM DMAC D_CHCR register.
// Sets the constant direction (FROM) upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
class IopDmacChannelRegister_Chcr_From : public IopDmacChannelRegister_Chcr
{
public:
    /// Upon writes, sets the correct direction (FROM).
    void write_uword(const uword value) override;
};

/// The IOP DMAC SIF0 CHCR register.
/// SIF0 requires access to the SBUS_F240 register (in the IOP, this is @ 0x1D000040), which is set on CHCR.Start becoming 1 or 0 (starting or finishing).
/// As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
/// TODO: Look into properly RE'ing the SBUS.
class IopDmacChannelRegister_Chcr_Sif0 : public IopDmacChannelRegister_Chcr_To
{
public:
    IopDmacChannelRegister_Chcr_Sif0();

    /// Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
    /// See PCSX2's "sif0.cpp".
    void write_uword(const uword value) override;

    /// Reference to the SBUS_F240 register.
    SbusRegister_F240* sbus_f240;

private:
    /// Contains logic for updating the SBUS registers.
    /// One function for starting a transfer - a ending function should never be called as this is fixed in the TO direction.
    void handle_sbus_update_start() const;
};

/// The IOP DMAC SIF1 CHCR register.
/// Sets the chain mode bit to 1 upon writes, as the bios overwrites this (hardware probably contains a hardwired bit).
/// SIF1 requires access to the SBUS_F240 register (in the IOP, this is @ 0x1D000040), which is set on CHCR.Start becoming 1 or 0 (starting or finishing).
/// As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
/// TODO: Look into properly RE'ing the SBUS.
class IopDmacChannelRegister_Chcr_Sif1 : public IopDmacChannelRegister_Chcr_From
{
public:
    IopDmacChannelRegister_Chcr_Sif1();

    /// Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
    /// See PCSX2's "sif1.cpp".
    void write_uword(const uword value) override;

    /// (IOP context only.) Upon writes, forces the chain mode bit (bit 10) to 1.
    /// TODO: Not sure why BIOS tries to change this *shrug*.
    void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;

    /// Reference to the SBUS_F240 register.
    SbusRegister_F240* sbus_f240;

private:
    /// Contains logic for updating the SBUS registers.
    /// One function for ending a transfer - a starting function should never be called as this is fixed in the FROM direction.
    void handle_sbus_update_finish() const;
};

/// The SIF2 DMAC D_CHCR register, aka channel control register.
/// SIF2 requires access to the SBUS_F240 register (in the IOP, this is @ 0x1D000040), which is set on CHCR.Start becoming 1 or 0 (starting or finishing).
/// As the SBUS (registers) is not fully understood, this is needed as a way to set the correct magic values.
/// TODO: Look into properly RE'ing the SBUS.
class IopDmacChannelRegister_Chcr_Sif2 : public IopDmacChannelRegister_Chcr
{
public:
    IopDmacChannelRegister_Chcr_Sif2();

    /// Whenever CHCR.STR = 1 or 0, trigger an update of the SBUS registers required.
    /// See PCSX2's "sif2.cpp".
    void write_uword(const uword value) override;

    /// Reference to the SBUS_F240 register.
    SbusRegister_F240* sbus_f240;

private:
    /// Contains logic for updating the SBUS registers.
    /// One function for starting a transfer, and ending a transfer.
    void handle_sbus_update_start() const;
    void handle_sbus_update_finish() const;
};
