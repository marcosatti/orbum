#include "stdafx.h"

#include "PS2Resources/EE/VPU/Types/EEVifUnitRegisters_t.h"

EEVifUnitRegister_R_t::EEVifUnitRegister_R_t()
{
	registerField(Fields::R, "R", 0, 32, 0);
}

EEVifUnitRegister_C_t::EEVifUnitRegister_C_t()
{
	registerField(Fields::C, "C", 0, 32, 0);
}

EEVifUnitRegister_CYCLE_t::EEVifUnitRegister_CYCLE_t()
{
	registerField(Fields::CL, "CL", 0, 8, 0);
	registerField(Fields::WL, "WL", 8, 8, 0);
}

EEVifUnitRegister_MASK_t::EEVifUnitRegister_MASK_t()
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

EEVifUnitRegister_MODE_t::EEVifUnitRegister_MODE_t()
{
	registerField(Fields::MOD, "MOD", 0, 2, 0);
}

EEVifUnitRegister_ITOP_t::EEVifUnitRegister_ITOP_t()
{
	registerField(Fields::ITOP, "ITOP", 0, 10, 0);
}

EEVifUnitRegister_ITOPS_t::EEVifUnitRegister_ITOPS_t()
{
	registerField(Fields::ITOPS, "ITOPS", 0, 10, 0);
}

EEVifUnitRegister_BASE_t::EEVifUnitRegister_BASE_t()
{
	registerField(Fields::BASE, "BASE", 0, 10, 0);
}

EEVifUnitRegister_OFST_t::EEVifUnitRegister_OFST_t()
{
	registerField(Fields::OFFSET, "OFFSET", 0, 10, 0);
}

EEVifUnitRegister_TOP_t::EEVifUnitRegister_TOP_t()
{
	registerField(Fields::TOP, "TOP", 0, 10, 0);
}

EEVifUnitRegister_TOPS_t::EEVifUnitRegister_TOPS_t()
{
	registerField(Fields::TOPS, "TOPS", 0, 10, 0);
}

EEVifUnitRegister_MARK_t::EEVifUnitRegister_MARK_t()
{
	registerField(Fields::MARK, "MARK", 0, 16, 0);
}

EEVifUnitRegister_NUM_t::EEVifUnitRegister_NUM_t()
{
	registerField(Fields::NUM, "NUM", 0, 8, 0);
}

EEVifUnitRegister_CODE_t::EEVifUnitRegister_CODE_t()
{
	registerField(Fields::IMMEDIATE, "IMMEDIATE", 0, 16, 0);
	registerField(Fields::NUM, "NUM", 16, 8, 0);
	registerField(Fields::CMD, "CMD", 24, 8, 0);
}

EEVifUnitRegister_STAT_t::EEVifUnitRegister_STAT_t()
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

EEVifUnitRegister_FBRST_t::EEVifUnitRegister_FBRST_t()
{
	registerField(Fields::RST, "RST", 0, 1, 0);
	registerField(Fields::FBK, "FBK", 1, 1, 0);
	registerField(Fields::STP, "STP", 2, 1, 0);
	registerField(Fields::STC, "STC", 3, 1, 0);
}

EEVifUnitRegister_ERR_t::EEVifUnitRegister_ERR_t()
{
	registerField(Fields::MII, "MII", 0, 1, 0);
	registerField(Fields::ME0, "ME0", 1, 1, 0);
	registerField(Fields::ME1, "ME1", 2, 1, 0);
}
