#pragma once

#include "Common/Types/Memory/ArrayHwordMemory.hpp"

/// Contains information about the CDVD NVRAM state, used to store various data.
/// Undocumented - see PCSX2's CDVD.h/cpp.
/// There are 6 pieces of important information the NVRAM holds, in addition to the raw memory space it provides:
///  - Config areas ("0"/"1"/"2"), accessed by blocks (a block is 16 bytes).
///  - Console ID (8 bytes).
///  - iLink ID (8 bytes).
///  - Model Number (8 bytes).
///  - Region Parameters (PStwo bios' only?) (8 bytes).
///  - MAC (acronym for???) (PStwo bios' only?) (8 bytes).
/// While the memory space is always 1KB, the location of these special areas are different across bios versions (see .cpp file for locations/offsets).
/// Read/write virtual functions have been provided for these areas, that can be used to support different bios'.
/// The NVRAM is also exposed directly, needed by the CDVD system logic.
/// TODO: only valid for bios' v0.00 -> v1.70, look into others later.
class CdvdNvram
{
public:
    CdvdNvram();

    /// Static NVRAM information:
    ///  - Magic values for the iLink data section (written to NVRAM upon initialisation).
    static constexpr ubyte ILINK_DATA_MAGIC[8] = {0x00, 0xAC, 0xFF, 0xFF, 0xFF, 0xFF, 0xB9, 0x86};

    /// NVRAM memory space.
    /// 1KB of space total, Hword addressable.
    ArrayHwordMemory memory;

    /// Sets the NVRAM config access paramters below, used for reading/writing to config areas.
    /// Common across all bios versions (not virutal).
    void set_access_params(const int read_write, const int area_index, const int max_block_index, const int block_index);

    /// Reads the next block (16 bytes / 8 hwords) to the buffer given, based upon the config access parameters set.
    virtual void read_config_block(uhword* buffer) = 0;

    /// Writes the next block (16 bytes / 8 hwords) from the buffer given, based upon the config access parameters set.
    virtual void write_config_block(const uhword* buffer) = 0;

    /// Reads the console ID to the buffer given (8 bytes / 4 hwords).
    virtual void read_console_id(uhword* buffer) = 0;

    /// Writes the console ID from the buffer given (8 bytes / 4 hwords).
    virtual void write_console_id(const uhword* buffer) = 0;

    /// Reads the iLink ID to the buffer given (8 bytes / 4 hwords).
    virtual void read_ilink_id(uhword* buffer) = 0;

    /// Writes the iLink ID from the buffer given (8 bytes / 4 hwords).
    virtual void write_ilink_id(const uhword* buffer) = 0;

    /// Reads the model number to the buffer given (8 bytes / 4 hwords).
    virtual void read_model_number(uhword* buffer) = 0;

    /// Writes the model number from of the buffer given (8 bytes / 4 hwords).
    virtual void write_model_number(const uhword* buffer) = 0;

    /// Reads the region params to the buffer given (8 bytes / 4 hwords).
    virtual void read_region_params(uhword* buffer) = 0;

    /// Writes the region params from of the buffer given (8 bytes / 4 hwords).
    virtual void write_region_params(const uhword* buffer) = 0;

    /// Reads the MAC to the buffer given (8 bytes / 4 hwords).
    virtual void read_mac(uhword* buffer) = 0;

    /// Writes the MAC from of the buffer given (8 bytes / 4 hwords).
    virtual void write_mac(const uhword* buffer) = 0;

protected:
    /// Config access state variables including:
    ///  - Read or write status (0 = read, 1 = write).
    ///  - Current config area being accessed.
    ///  - Maximum block index allowed within config area (not really sure why this is a thing...).
    ///  - Current block index within config area.
    /// TODO: look into this... it kinda doesn't make a whole lot of sense.
    /// Block map:
    ///  - Config 0: 4 blocks (64B).
    ///  - Config 1: 2 blocks (32B).
    ///  - Config 2: 7 blocks (112B).
    int access_read_write;
    int access_area_index;
    int access_max_block_index;
    int access_block_index;
};

/// Class representing the NVRAM for bios versions v0.00 <= x < 1.70.
class CdvdNvram_000 : public CdvdNvram
{
public:
    CdvdNvram_000();

    /// Implementation of the NVRAM virtual functions.
    /// Contains magic size and offset values - see within functions for the values.
    void read_config_block(uhword* buffer) override;
    void write_config_block(const uhword* buffer) override;
    void read_console_id(uhword* buffer) override;
    void write_console_id(const uhword* buffer) override;
    void read_ilink_id(uhword* buffer) override;
    void write_ilink_id(const uhword* buffer) override;
    void read_model_number(uhword* buffer) override;
    void write_model_number(const uhword* buffer) override;
    void read_region_params(uhword* buffer) override;
    void write_region_params(const uhword* buffer) override;
    void read_mac(uhword* buffer) override;
    void write_mac(const uhword* buffer) override;
};