#pragma once

#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Register/SizedDwordRegister.hpp"
#include "Resources/Gs/Crtc/RCrtc.hpp"

/// Graphics synthesizer (GS) resources.
class RGs
{
public:
    RGs();

    /// (P)CRTC resources.
    RCrtc crtc;

    /// GS privileged registers, defined on page 26 onwards of the EE Users Manual. All start from PS2 physical address 0x12000000 to 0x14000000.
    // 0x12000000.
    SizedDwordRegister pmode;
    SizedDwordRegister smode1;
    SizedDwordRegister smode2;
    SizedDwordRegister srfsh;
    SizedDwordRegister synch1;
    SizedDwordRegister synch2;
    SizedDwordRegister syncv;
    SizedDwordRegister dispfb1;
    SizedDwordRegister display1;
    SizedDwordRegister dispfb2;
    SizedDwordRegister display2;
    SizedDwordRegister extbuf;
    SizedDwordRegister extdata;
    SizedDwordRegister extwrite;
    SizedDwordRegister bgcolor;
    ArrayByteMemory memory_00f0;

    // 0x12001000.
    SizedDwordRegister csr;
    SizedDwordRegister imr;
    ArrayByteMemory memory_1020;
    SizedDwordRegister busdir;
    ArrayByteMemory memory_1050;
    SizedDwordRegister siglblid;
    ArrayByteMemory memory_1090;
    ArrayByteMemory memory_1100;

    // 0x12002000.
    ArrayByteMemory memory_2000;

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(crtc),
            CEREAL_NVP(pmode),
            CEREAL_NVP(smode1),
            CEREAL_NVP(smode2),
            CEREAL_NVP(srfsh),
            CEREAL_NVP(synch1),
            CEREAL_NVP(synch2),
            CEREAL_NVP(syncv),
            CEREAL_NVP(dispfb1),
            CEREAL_NVP(display1),
            CEREAL_NVP(dispfb2),
            CEREAL_NVP(display2),
            CEREAL_NVP(extbuf),
            CEREAL_NVP(extdata),
            CEREAL_NVP(extwrite),
            CEREAL_NVP(bgcolor),
            CEREAL_NVP(memory_00f0),
            CEREAL_NVP(csr),
            CEREAL_NVP(imr),
            CEREAL_NVP(memory_1020),
            CEREAL_NVP(busdir),
            CEREAL_NVP(memory_1050),
            CEREAL_NVP(siglblid),
            CEREAL_NVP(memory_1090),
            CEREAL_NVP(memory_1100),
            CEREAL_NVP(memory_2000)
        );
    }
};
