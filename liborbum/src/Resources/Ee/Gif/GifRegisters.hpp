#pragma once

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

class GifRegister_Ctrl : public SizedWordRegister
{
public:
    static constexpr Bitfield RST = Bitfield(0, 1);
    static constexpr Bitfield PSE = Bitfield(3, 1);

    GifRegister_Ctrl();

    /// Indicates whether the GIF is currently processing a GS primitive 
    /// (excluding the tag). Reset upon finishing a GS primitive.
    bool transfer_started;

    /// Number of qwords total/left for the current GS primitive.
    /// Set by the tag read.
    size_t transfer_data_target;
    size_t transfer_data_count;

    /// End of GS packet indicator. Set by the tag read.
    bool transfer_end_of_packet;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            cereal::base_class<SizedWordRegister>(this),
            CEREAL_NVP(transfer_started),
            CEREAL_NVP(transfer_data_target),
            CEREAL_NVP(transfer_data_count),
            CEREAL_NVP(transfer_end_of_packet)
        );
    }
};

class GifRegister_Mode : public SizedWordRegister
{
public:
    static constexpr Bitfield M3R = Bitfield(0, 1);
    static constexpr Bitfield IMT = Bitfield(2, 1);
};

class GifRegister_Stat : public SizedWordRegister
{
public:
    static constexpr Bitfield M3R = Bitfield(0, 1);
    static constexpr Bitfield M3P = Bitfield(1, 1);
    static constexpr Bitfield IMT = Bitfield(2, 1);
    static constexpr Bitfield PSE = Bitfield(3, 1);
    static constexpr Bitfield IP3 = Bitfield(5, 1);
    static constexpr Bitfield P3Q = Bitfield(6, 1);
    static constexpr Bitfield P2Q = Bitfield(7, 1);
    static constexpr Bitfield P1Q = Bitfield(8, 1);
    static constexpr Bitfield OPH = Bitfield(9, 1);
    static constexpr Bitfield APATH = Bitfield(10, 2);
    static constexpr Bitfield DIR = Bitfield(12, 1);
    static constexpr Bitfield FQC = Bitfield(24, 5);
};

class GifRegister_Tag0 : public SizedWordRegister
{
public:
    static constexpr Bitfield NLOOP = Bitfield(0, 15);
    static constexpr Bitfield EOP = Bitfield(15, 1);
    static constexpr Bitfield TAG = Bitfield(16, 16);
};

class GifRegister_Tag1 : public SizedWordRegister
{
public:
    static constexpr Bitfield TAG = Bitfield(0, 14);
    static constexpr Bitfield PRE = Bitfield(14, 1);
    static constexpr Bitfield PRIM = Bitfield(15, 11);
    static constexpr Bitfield FLG = Bitfield(26, 2);
    static constexpr Bitfield NREG = Bitfield(28, 4);
};

class GifRegister_Tag2 : public SizedWordRegister
{
public:
    static constexpr Bitfield TAG = Bitfield(0, 32);
};

class GifRegister_Tag3 : public SizedWordRegister
{
public:
    static constexpr Bitfield TAG = Bitfield(0, 32);
};

class GifRegister_Cnt : public SizedWordRegister
{
public:
    static constexpr Bitfield P3CNT = Bitfield(0, 15);
};

class GifRegister_P3tag : public SizedWordRegister
{
public:
    static constexpr Bitfield LOOPCNT = Bitfield(0, 15);
    static constexpr Bitfield EOP = Bitfield(15, 1);
};
