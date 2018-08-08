#pragma once

#include <cereal/cereal.hpp>

#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

class RGif
{
public:
    RGif();

    /// GIF memory mapped registers. See page 21 of EE Users Manual.
    SizedWordRegister ctrl;
    SizedWordRegister mode;
    SizedWordRegister stat;
    ArrayByteMemory memory_3030;
    SizedWordRegister tag0;
    SizedWordRegister tag1;
    SizedWordRegister tag2;
    SizedWordRegister tag3;
    SizedWordRegister cnt;
    SizedWordRegister p3cnt;
    SizedWordRegister p3tag;
    ArrayByteMemory memory_30b0;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(ctrl),
            CEREAL_NVP(mode),
            CEREAL_NVP(stat),
            CEREAL_NVP(memory_3030),
            CEREAL_NVP(tag0),
            CEREAL_NVP(tag1),
            CEREAL_NVP(tag2),
            CEREAL_NVP(tag3),
            CEREAL_NVP(cnt),
            CEREAL_NVP(p3cnt),
            CEREAL_NVP(p3tag),
            CEREAL_NVP(memory_30b0)
        );
    }
};
