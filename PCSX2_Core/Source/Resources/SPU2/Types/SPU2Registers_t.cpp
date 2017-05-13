#include "stdafx.h"

#include "Resources/SPU2/Types/SPU2Registers_t.h"

SPU2Register_SPDIF_IRQINFO_t::SPU2Register_SPDIF_IRQINFO_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
    BitfieldRegister16_t(mnemonic, debugReads, debugWrites)
{
    registerField(Fields::IrqCore0, "IrqCore0", 2, 1, 0);
    registerField(Fields::IrqCore1, "IrqCore1", 3, 1, 0);
}

bool SPU2Register_SPDIF_IRQINFO_t::isInterrupted(const System_t context)
{
    // Core 0 and 1 IRQ bits located at bits 2 and 3 (0xC mask).
    return ((readHword(context) & 0xC) > 0);
}