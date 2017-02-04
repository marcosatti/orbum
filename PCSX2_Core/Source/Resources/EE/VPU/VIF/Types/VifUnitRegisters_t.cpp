#include "stdafx.h"

#include "Resources/EE/VPU/VIF/Types/VIFUnitRegisters_t.h"

VifUnitRegister_CYCLE_t::VifUnitRegister_CYCLE_t()
{
	registerField(Fields::CL, "CL", 0, 8, 0);
	registerField(Fields::WL, "WL", 8, 8, 0);
}

VifUnitRegister_MASK_t::VifUnitRegister_MASK_t()
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

VifUnitRegister_MODE_t::VifUnitRegister_MODE_t()
{
	registerField(Fields::MOD, "MOD", 0, 2, 0);
}

VifUnitRegister_ITOP_t::VifUnitRegister_ITOP_t()
{
	registerField(Fields::ITOP, "ITOP", 0, 10, 0);
}

VifUnitRegister_ITOPS_t::VifUnitRegister_ITOPS_t()
{
	registerField(Fields::ITOPS, "ITOPS", 0, 10, 0);
}

VifUnitRegister_BASE_t::VifUnitRegister_BASE_t()
{
	registerField(Fields::BASE, "BASE", 0, 10, 0);
}

VifUnitRegister_OFST_t::VifUnitRegister_OFST_t()
{
	registerField(Fields::OFFSET, "OFFSET", 0, 10, 0);
}

VifUnitRegister_TOP_t::VifUnitRegister_TOP_t()
{
	registerField(Fields::TOP, "TOP", 0, 10, 0);
}

VifUnitRegister_TOPS_t::VifUnitRegister_TOPS_t()
{
	registerField(Fields::TOPS, "TOPS", 0, 10, 0);
}

VifUnitRegister_MARK_t::VifUnitRegister_MARK_t()
{
	registerField(Fields::MARK, "MARK", 0, 16, 0);
}

VifUnitRegister_NUM_t::VifUnitRegister_NUM_t()
{
	registerField(Fields::NUM, "NUM", 0, 8, 0);
}

VifUnitRegister_CODE_t::VifUnitRegister_CODE_t()
{
	registerField(Fields::IMMEDIATE, "IMMEDIATE", 0, 16, 0);
	registerField(Fields::NUM, "NUM", 16, 8, 0);
	registerField(Fields::CMD, "CMD", 24, 8, 0);
}

VifUnitRegister_STAT_t::VifUnitRegister_STAT_t()
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

VifUnitRegister_FBRST_t::VifUnitRegister_FBRST_t()
{
	registerField(Fields::RST, "RST", 0, 1, 0);
	registerField(Fields::FBK, "FBK", 1, 1, 0);
	registerField(Fields::STP, "STP", 2, 1, 0);
	registerField(Fields::STC, "STC", 3, 1, 0);
}

VifUnitRegister_ERR_t::VifUnitRegister_ERR_t()
{
	registerField(Fields::MII, "MII", 0, 1, 0);
	registerField(Fields::ME0, "ME0", 1, 1, 0);
	registerField(Fields::ME1, "ME1", 2, 1, 0);
}
