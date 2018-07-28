#pragma once

#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Register/SizedHwordRegister.hpp"

class Spu2CoreVoiceRegister_Adsr1 : public SizedHwordRegister
{
public:
    static constexpr Bitfield SL = Bitfield(0, 4);
    static constexpr Bitfield DR = Bitfield(4, 4);
    static constexpr Bitfield AR = Bitfield(8, 7);
    static constexpr Bitfield X = Bitfield(15, 1);
};

class Spu2CoreVoiceRegister_Adsr2 : public SizedHwordRegister
{
public:
    static constexpr Bitfield RR = Bitfield(0, 5);
    static constexpr Bitfield Z = Bitfield(5, 1);
    static constexpr Bitfield SR = Bitfield(6, 7);
    static constexpr Bitfield Y = Bitfield(13, 3);
};