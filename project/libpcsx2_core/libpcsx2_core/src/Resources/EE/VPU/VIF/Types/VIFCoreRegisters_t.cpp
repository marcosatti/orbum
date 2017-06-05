#include "Resources/EE/VPU/VIF/Types/VIFCoreRegisters_t.h"

VIFCoreRegister_CYCLE_t::VIFCoreRegister_CYCLE_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::CL, "CL", 0, 8, 0);
	registerField(Fields::WL, "WL", 8, 8, 0);
}

VIFCoreRegister_MASK_t::VIFCoreRegister_MASK_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::m0, "m0", 0, 2, 0);
	registerField(Fields::m1, "m1", 2, 2, 0);
	registerField(Fields::m2, "m2", 4, 2, 0);
	registerField(Fields::m3, "m3", 6, 2, 0);
	registerField(Fields::m4, "m4", 8, 2, 0);
	registerField(Fields::m5, "m5", 10, 2, 0);
	registerField(Fields::m6, "m6", 12, 2, 0);
	registerField(Fields::m7, "m7", 14, 2, 0);
	registerField(Fields::m8, "m8", 16, 2, 0);
	registerField(Fields::m9, "m9", 18, 2, 0);
	registerField(Fields::m10, "m10", 20, 2, 0);
	registerField(Fields::m11, "m11", 22, 2, 0);
	registerField(Fields::m12, "m12", 24, 2, 0);
	registerField(Fields::m13, "m13", 26, 2, 0);
	registerField(Fields::m14, "m14", 28, 2, 0);
	registerField(Fields::m15, "m15", 30, 2, 0);
}

VIFCoreRegister_MODE_t::VIFCoreRegister_MODE_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::MOD, "MOD", 0, 2, 0);
}

VIFCoreRegister_ITOP_t::VIFCoreRegister_ITOP_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::ITOP, "ITOP", 0, 10, 0);
}

VIFCoreRegister_ITOPS_t::VIFCoreRegister_ITOPS_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::ITOPS, "ITOPS", 0, 10, 0);
}

VIFCoreRegister_BASE_t::VIFCoreRegister_BASE_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::BASE, "BASE", 0, 10, 0);
}

VIFCoreRegister_OFST_t::VIFCoreRegister_OFST_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::OFFSET, "OFFSET", 0, 10, 0);
}

VIFCoreRegister_TOP_t::VIFCoreRegister_TOP_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::TOP, "TOP", 0, 10, 0);
}

VIFCoreRegister_TOPS_t::VIFCoreRegister_TOPS_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::TOPS, "TOPS", 0, 10, 0);
}

VIFCoreRegister_MARK_t::VIFCoreRegister_MARK_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::MARK, "MARK", 0, 16, 0);
}

VIFCoreRegister_NUM_t::VIFCoreRegister_NUM_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::NUM, "NUM", 0, 8, 0);
}

VIFCoreRegister_CODE_t::VIFCoreRegister_CODE_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::IMMEDIATE, "IMMEDIATE", 0, 16, 0);
	registerField(Fields::NUM, "NUM", 16, 8, 0);
	registerField(Fields::CMD, "CMD", 24, 8, 0);
}

VIFCoreRegister_STAT_t::VIFCoreRegister_STAT_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::VPS, "VPS", 0, 2, 0);
	registerField(Fields::VEW, "VEW", 2, 1, 0);
	registerField(Fields::VGW, "VGW", 3, 1, 0);
	registerField(Fields::MRK, "MRK", 6, 1, 0);
	registerField(Fields::DBF, "DBF", 7, 1, 0);
	registerField(Fields::VSS, "VSS", 8, 1, 0);
	registerField(Fields::VFS, "VFS", 9, 1, 0);
	registerField(Fields::VIS, "VIS", 10, 1, 0);
	registerField(Fields::INT, "INT", 11, 1, 0);
	registerField(Fields::ER0, "ER0", 12, 1, 0);
	registerField(Fields::ER1, "ER1", 13, 1, 0);
	registerField(Fields::FDR, "FDR", 23, 1, 0);
	registerField(Fields::FQC, "FQC", 24, 4, 0);
}

VIFCoreRegister_FBRST_t::VIFCoreRegister_FBRST_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::RST, "RST", 0, 1, 0);
	registerField(Fields::FBK, "FBK", 1, 1, 0);
	registerField(Fields::STP, "STP", 2, 1, 0);
	registerField(Fields::STC, "STC", 3, 1, 0);
}

VIFCoreRegister_ERR_t::VIFCoreRegister_ERR_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::MII, "MII", 0, 1, 0);
	registerField(Fields::ME0, "ME0", 1, 1, 0);
	registerField(Fields::ME1, "ME1", 2, 1, 0);
}
