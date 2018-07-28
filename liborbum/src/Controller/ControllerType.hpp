#pragma once

#include <string>

#include <EnumMap.hpp>

/// Describes the controller type context.
struct ControllerType
{
    enum class Type
    {
        EeCore,
        EeDmac,
        EeTimers,
        EeIntc,
        Gif,
        Ipu,
        Vif,
        Vu,
        IopCore,
        IopDmac,
        IopTimers,
        IopIntc,
        Cdvd,
        Spu2,
        GsCore,
        Crtc,
        Sio0,
        Sio2,

        COUNT
    };

    static constexpr const char* TYPE_STRINGS[] =
        {
            "EeCore",
            "EeDmac",
            "EeTimers",
            "EeIntc",
            "Gif",
            "Ipu",
            "Vif",
            "Vu",
            "IopCore",
            "IopDmac",
            "IopTimers",
            "IopIntc",
            "Cdvd",
            "Spu2",
            "GsCore",
            "Crtc",
            "Sio0",
            "Sio2",
    };
};