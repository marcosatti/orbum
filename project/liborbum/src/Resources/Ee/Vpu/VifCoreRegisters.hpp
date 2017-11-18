#pragma once

#include "Common/Types/Register/SizedWordRegister.hpp"

/// VIF core registers.
/// See EE Users Manual page 127 onwards.

class VifCoreRegister_Cycle : public SizedWordRegister
{
public:
	static constexpr Bitfield CL = Bitfield(0, 8);
	static constexpr Bitfield WL = Bitfield(8, 8);
};

class VifCoreRegister_Mask : public SizedWordRegister
{
public:
	static constexpr Bitfield M0  = Bitfield(0, 2);
	static constexpr Bitfield M1  = Bitfield(2, 2);
	static constexpr Bitfield M2  = Bitfield(4, 2);
	static constexpr Bitfield M3  = Bitfield(6, 2);
	static constexpr Bitfield M4  = Bitfield(8, 2);
	static constexpr Bitfield M5  = Bitfield(10, 2);
	static constexpr Bitfield M6  = Bitfield(12, 2);
	static constexpr Bitfield M7  = Bitfield(14, 2);
	static constexpr Bitfield M8  = Bitfield(16, 2);
	static constexpr Bitfield M9  = Bitfield(18, 2);
	static constexpr Bitfield M10 = Bitfield(20, 2);
	static constexpr Bitfield M11 = Bitfield(22, 2);
	static constexpr Bitfield M12 = Bitfield(24, 2);
	static constexpr Bitfield M13 = Bitfield(26, 2);
	static constexpr Bitfield M14 = Bitfield(28, 2);
	static constexpr Bitfield M15 = Bitfield(30, 2);
};

class VifCoreRegister_Mode : public SizedWordRegister
{
public:	
	static constexpr Bitfield MOD = Bitfield(0, 2);
};

class VifCoreRegister_Itop : public SizedWordRegister
{
public:
	static constexpr Bitfield ITOP = Bitfield(0, 10);
};

class VifCoreRegister_Itops : public SizedWordRegister
{
public:
	static constexpr Bitfield ITOPS = Bitfield(0, 10);
};

class VifCoreRegister_Base : public SizedWordRegister
{
public:
	static constexpr Bitfield BASE = Bitfield(0, 10);
};

class VifCoreRegister_Ofst : public SizedWordRegister
{
public:
	static constexpr Bitfield OFFSET = Bitfield(0, 10);
};

class VifCoreRegister_Top : public SizedWordRegister
{
public:
	static constexpr Bitfield TOP = Bitfield(0, 10);
};

class VifCoreRegister_Tops : public SizedWordRegister
{
public:
	static constexpr Bitfield TOPS = Bitfield(0, 10);
};

class VifCoreRegister_Mark : public SizedWordRegister
{
public:
	static constexpr Bitfield MARK = Bitfield(0, 16);
};

class VifCoreRegister_Num : public SizedWordRegister
{
public:
	static constexpr Bitfield NUM = Bitfield(0, 8);
};

class VifCoreRegister_Code : public SizedWordRegister
{
public:
	static constexpr Bitfield IMMEDIATE = Bitfield(0, 16);
	static constexpr Bitfield NUM = Bitfield(16, 8);
	static constexpr Bitfield CMD = Bitfield(24, 8);
};

class VifCoreRegister_Stat : public SizedWordRegister
{
public:
	static constexpr Bitfield VPS = Bitfield(0, 2);
	static constexpr Bitfield VEW = Bitfield(2, 1);
	static constexpr Bitfield VGW = Bitfield(3, 1);
	static constexpr Bitfield MRK = Bitfield(6, 1);
	static constexpr Bitfield DBF = Bitfield(7, 1);
	static constexpr Bitfield VSS = Bitfield(8, 1);
	static constexpr Bitfield VFS = Bitfield(9, 1);
	static constexpr Bitfield VIS = Bitfield(10, 1);
	static constexpr Bitfield INT = Bitfield(11, 1);
	static constexpr Bitfield ER0 = Bitfield(12, 1);
	static constexpr Bitfield ER1 = Bitfield(13, 1);
	static constexpr Bitfield FDR = Bitfield(23, 1);
	static constexpr Bitfield FQC = Bitfield(24, 4);
};

class VifCoreRegister_Fbrst : public SizedWordRegister
{
public:
	static constexpr Bitfield RST = Bitfield(0, 1);
	static constexpr Bitfield FBK = Bitfield(1, 1);
	static constexpr Bitfield STP = Bitfield(2, 1);
	static constexpr Bitfield STC = Bitfield(3, 1);
};

class VifCoreRegister_Err : public SizedWordRegister
{
public:
	static constexpr Bitfield MII = Bitfield(0, 1);
	static constexpr Bitfield ME0 = Bitfield(1, 1);
	static constexpr Bitfield ME1 = Bitfield(2, 1);
};