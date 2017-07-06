#include "Resources/SPU2/Types/SPU2Registers_t.h"

constexpr int SPU2Register_SPDIF_IRQINFO_t::Fields::IRQ_KEYS[Constants::SPU2::NUMBER_CORES];

SPU2Register_SPDIF_IRQINFO_t::SPU2Register_SPDIF_IRQINFO_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
    BitfieldRegister16_t(mnemonic, debugReads, debugWrites)
{
    registerField(Fields::IrqCore0, "IrqCore0", 2, 1, 0);
    registerField(Fields::IrqCore1, "IrqCore1", 3, 1, 0);
}