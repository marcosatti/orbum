#pragma once

#include "Common/Constants.hpp"

struct IopDmacConstants
{
    static constexpr const char* MNEMONICS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS] =
        {
            "toMDEC",
            "fromMDEC",
            "SIF2",
            "CDVD",
            "SPU2c0",
            "PIO",
            "OTClear",
            "SPU2c1",
            "DEV9",
            "SIF0",
            "SIF1",
            "toSIO2",
            "fromSIO2",
            "Undefined"};
};