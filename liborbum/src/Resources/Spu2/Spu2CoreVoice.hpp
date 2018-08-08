#pragma once

#include <cereal/cereal.hpp>

#include "Common/Types/Register/SizedHwordRegister.hpp"
#include "Resources/Spu2/Spu2CoreVoiceRegisters.hpp"

/// SPU2 core voice. There are 24 voices per core.
class Spu2CoreVoice
{
public:
    SizedHwordRegister voll;
    SizedHwordRegister volr;
    SizedHwordRegister pitch;
    Spu2CoreVoiceRegister_Adsr1 adsr1;
    Spu2CoreVoiceRegister_Adsr2 adsr2;
    SizedHwordRegister envx;
    SizedHwordRegister volxl;
    SizedHwordRegister volxr;
    SizedHwordRegister ssah;
    SizedHwordRegister ssal;
    SizedHwordRegister lsaxh;
    SizedHwordRegister lsaxl;
    SizedHwordRegister naxh;
    SizedHwordRegister naxl;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(voll),
            CEREAL_NVP(volr),
            CEREAL_NVP(pitch),
            CEREAL_NVP(adsr1),
            CEREAL_NVP(adsr2),
            CEREAL_NVP(envx),
            CEREAL_NVP(volxl),
            CEREAL_NVP(volxr),
            CEREAL_NVP(ssah),
            CEREAL_NVP(ssal),
            CEREAL_NVP(lsaxh),
            CEREAL_NVP(lsaxl),
            CEREAL_NVP(naxh),
            CEREAL_NVP(naxl)
        );
    }
};