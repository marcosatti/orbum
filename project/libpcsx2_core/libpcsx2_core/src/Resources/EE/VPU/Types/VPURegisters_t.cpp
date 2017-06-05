#include "Resources/EE/VPU/Types/VPURegisters_t.h"

VPURegister_STAT_t::VPURegister_STAT_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::VBS0, "VBS0", 0, 1, 0);
	registerField(Fields::VDS0, "VDS0", 1, 1, 0);
	registerField(Fields::VTS0, "VTS0", 2, 1, 0);
	registerField(Fields::VFS0, "VFS0", 3, 1, 0);
	registerField(Fields::DIV0, "DIV0", 5, 1, 0);
	registerField(Fields::IBS0, "IBS0", 7, 1, 0);
	registerField(Fields::VBS1, "VBS1", 8, 1, 0);
	registerField(Fields::VDS1, "VDS1", 9, 1, 0);
	registerField(Fields::VTS1, "VTS1", 10, 1, 0);
	registerField(Fields::VFS1, "VFS1", 11, 1, 0);
	registerField(Fields::VGW1, "VGW1", 12, 1, 0);
	registerField(Fields::DIV1, "DIV1", 13, 1, 0);
	registerField(Fields::EFU1, "EFU1", 14, 1, 0);
}
