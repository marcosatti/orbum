#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Register/BitfieldRegister16_t.h"
#include "Common/Types/System/Context_t.h"

/*
The SPU2 SPDIF_IRQINFO register.
Contains information about the SPU2 cores' interrupted states.
See the SPU2-X/spu2sys.cpp file for information about the IRQ's.
IRQ's are set, for example, when an address is accessed equaling the IRQA register pair value.
Weird how general IRQ's not related to SPDIF use this register...
*/
class SPU2Register_SPDIF_IRQINFO_t : public BitfieldRegister16_t
{
public:
	struct Fields
	{
		static constexpr int IrqCore0 = 0;
		static constexpr int IrqCore1 = 1;

        static constexpr int IRQ_KEYS[Constants::SPU2::NUMBER_CORES] = { IrqCore0, IrqCore1 };
	};

	SPU2Register_SPDIF_IRQINFO_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

    /*
    Returns if any of the core IRQ's are set.
    */
    bool isInterrupted(const Context_t context);
};