#pragma once

#include <memory>

#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
EECore_COP0_Registers_t.h implements the EE Core specific COP0 control registers. This is used primarily by EECoreCOP0_t.h.
Each register will have documentation attached to it, and is prefixed with EECore_COP0Register.
Note: where register fields have a constant 0, this is already done due to the base classes initalisation code.

It is recommended that you read the documentation of the BitfieldRegister32_t class, which documents how to access bitfields.
All of the fields available within each register are defined within the Fields struct located inside.
ie: to access a field in a register object from outside this file, you would use:
- RegisterIndex.setFieldValue(RegisterIndex::Fields::Index, u32 value) or
- u32 value = RegisterIndex.getFieldValue(RegisterIndex::Fields::Index)
All of the available field functions are listed in the BitfieldRegister32_t class.

The actual fields are defined at runtime within the EECore_COP0_Registers_t.cpp file.
*/

/*
The Index register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 63.

Bitfield map (defined as constants in the class below):
- Bits 0-5 (length 6): "Index".
- Bits 6-30 (length 25): Constant 0.
- Bits 31 (length 1): "P".
*/
class EECoreCOP0Register_Index_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 Index = 0;
		static constexpr u8 P = 1;
	};

	explicit EECoreCOP0Register_Index_t();
};

/*
The Random register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 64.

Bitfield map (defined as constants in the class below):
- Bits 0-5 (length 6): "Random".
- Bits 6-31 (length 26): Constant 0.
*/
class EECoreCOP0Register_Random_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 Random = 0;
	};

	explicit EECoreCOP0Register_Random_t();
};

/*
The EntryLo0 register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 65.

Bitfield map (defined as constants in the class below):
- Bits 0 (length 1): "G".
- Bits 1 (length 1): "V".
- Bits 2 (length 1): "D".
- Bits 3-5 (length 3): "C".
- Bits 6-25 (length 20): "PFN".
- Bits 26-30 (length 5): Constant 0.
- Bits 31 (length 1): "S"
*/
class EECoreCOP0Register_EntryLo0_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 G = 0;
		static constexpr u8 V = 1;
		static constexpr u8 D = 2;
		static constexpr u8 C = 3;
		static constexpr u8 PFN = 4;
		static constexpr u8 S = 5;
	};

	explicit EECoreCOP0Register_EntryLo0_t();
};

/*
The EntryLo1 register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 65.

Bitfield map (defined as constants in the class below):
- Bits 0 (length 1): "G".
- Bits 1 (length 1): "V".
- Bits 2 (length 1): "D".
- Bits 3-5 (length 3): "C".
- Bits 6-25 (length 20): "PFN".
- Bits 26-31 (length 6): Constant 0.
*/
class EECoreCOP0Register_EntryLo1_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 G = 0;
		static constexpr u8 V = 1;
		static constexpr u8 D = 2;
		static constexpr u8 C = 3;
		static constexpr u8 PFN = 4;
	};

	explicit EECoreCOP0Register_EntryLo1_t();
};

/*
The Context register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 66.

Bitfield map (defined as constants in the class below):
- Bits 0-3 (length 4): Constant 0.
- Bits 4-22 (length 19): "BadVPN2".
- Bits 23-31 (length 9): "PTEBase".
*/
class EECoreCOP0Register_Context_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 BadVPN2 = 0;
		static constexpr u8 PTEBase = 1;
	};

	explicit EECoreCOP0Register_Context_t();
};

/*
The PageMask register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 67.

Bitfield map (defined as constants in the class below):
- Bits 0-12 (length 13): Constant 0.
- Bits 13-24 (length 12): "MASK".
- Bits 25-31 (length 7): Constant 0.
*/
class EECoreCOP0Register_PageMask_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 MASK = 0;
	};

	explicit EECoreCOP0Register_PageMask_t();
};

/*
The Wired register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 68.

Bitfield map (defined as constants in the class below):
- Bits 0-5 (length 6): "Wired".
- Bits 6-31 (length 26): Constant 0.
*/
class EECoreCOP0Register_Wired_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 Wired = 0;
	};

	explicit EECoreCOP0Register_Wired_t();
};

/*
The BadVAddr register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 69.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "BadVAddr".
*/
class EECoreCOP0Register_BadVAddr_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 BadVAddr = 0;
	};

	explicit EECoreCOP0Register_BadVAddr_t();
};

/*
The Count register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 70.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "Count".
*/
class EECoreCOP0Register_Count_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 Count = 0;
	};

	explicit EECoreCOP0Register_Count_t();

	// Convenience function that increments the count field value by the specified amount. 
	void increment(u32 value);
};

/*
The EntryHI register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 71.

Bitfield map (defined as constants in the class below):
- Bits 0-7 (length 8): "ASID".
- Bits 8-12 (length 5): Constant 0.
- Bits 13-31 (length 19): "VPN2".
*/
class EECoreCOP0Register_EntryHi_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ASID = 0;
		static constexpr u8 VPN2 = 1;
	};

	explicit EECoreCOP0Register_EntryHi_t();
};

/*
[Listed before COP0.Compare due to dependency.]
The Cause register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 75.

Bitfield map (defined as constants in the class below):
- Bits 0-1 (length 2): Constant 0.
- Bits 2-6 (length 5): "ExcCode".
- Bits 7-9 (length 3): Constant 0.
- Bits 10 (length 1): "IP2".
- Bits 11 (length 1): "IP3".
- Bits 12-14 (length 3): Constant 0.
- Bits 15 (length 1): "IP7".
- Bits 16-18 (length 3): "EXC2".
- Bits 19-27 (length 9): Constant 0.
- Bits 28-29 (length 2): "CE".
- Bits 30 (length 1): "BD2".
- Bits 31 (length 1): "BD".
*/
class EECoreCOP0Register_Cause_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ExcCode = 0;
		static constexpr u8 IP2 = 1;
		static constexpr u8 IP3 = 2;
		static constexpr u8 IP7 = 3;
		static constexpr u8 EXC2 = 4;
		static constexpr u8 CE = 5;
		static constexpr u8 BD2 = 6;
		static constexpr u8 BD = 7;
	};

	explicit EECoreCOP0Register_Cause_t();
};

/*
The Compare register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 72.
Note: Also clears the COP0.Cause.IP7 field when written to (see overridden functions). This is from the documentation on the same page.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "Compare".
*/
class EECoreCOP0Register_Compare_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 Compare = 0;
	};

	explicit EECoreCOP0Register_Compare_t(std::shared_ptr<EECoreCOP0Register_Cause_t> Cause);

	void setFieldValue(const u8 & fieldIndex, const u32& value) override;
	void writeWord(const Context_t & context, u32 value) override;

private:
	std::shared_ptr<EECoreCOP0Register_Cause_t> mCause;
};

/*
The Status register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 73.

Bitfield map (defined as constants in the class below):
- Bits 0 (length 1): "IE".
- Bits 1 (length 1): "EXL".
- Bits 2 (length 1): "ERL".
- Bits 3-4 (length 2): "KSU".
- Bits 5-9 (length 5): Constant 0.
- Bits 10-11 (length 2): "IM".
- Bits 12 (length 1): "BEM".
- Bits 13-14 (length 2): Constant 0.
- Bits 15 (length 1): "IM7".
- Bits 16 (length 1): "EIE".
- Bits 17 (length 1): "EDI".
- Bits 18 (length 1): "CH".
- Bits 19-21 (length 3): Constant 0.
- Bits 22 (length 1): "BEV".
- Bits 23 (length 1): "DEV".
- Bits 24-27 (length 4): Constant 0.
- Bits 28-31 (length 4): "CU".
*/
class EECoreCOP0Register_Status_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 IE = 0;
		static constexpr u8 EXL = 1;
		static constexpr u8 ERL = 2;
		static constexpr u8 KSU = 3;
		static constexpr u8 IM = 4;
		static constexpr u8 BEM = 5;
		static constexpr u8 IM7 = 6;
		static constexpr u8 EIE = 7;
		static constexpr u8 EDI = 8;
		static constexpr u8 CH = 9;
		static constexpr u8 BEV = 10;
		static constexpr u8 DEV = 11;
		static constexpr u8 CU = 12;
	};

	explicit EECoreCOP0Register_Status_t();
};

/*
The PRId register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 77.

Bitfield map (defined as constants in the class below):
- Bits 0-7 (length 8): "Rev".
- Bits 8-15 (length 8): "Imp".
- Bits 16-31 (length 16): Constant 0.
*/
class EECoreCOP0Register_PRId_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 Rev = 0;
		static constexpr u8 Imp = 1;
	};

	explicit EECoreCOP0Register_PRId_t();
};

/*
The Config register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 78.

Bitfield map (defined as constants in the class below):
- Bits 0-2 (length 3): "K0".
- Bits 3-5 (length 3): Constant 0.
- Bits 6-8 (length 3): "DC".
- Bits 9-11 (length 3): "IC".
- Bits 12 (length 1): "BPE".
- Bits 13 (length 1): "NBE".
- Bits 14-15 (length 2): Constant 0.
- Bits 16 (length 1): "DCE".
- Bits 17 (length 1): "ICE".
- Bits 18 (length 1): "DIE".
- Bits 19-27 (length 9): Constant 0.
- Bits 28-30 (length 3): "EC".
- Bits 31 (length 1): Constant 0.
*/
class EECoreCOP0Register_Config_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 K0 = 0;
		static constexpr u8 DC = 1;
		static constexpr u8 IC = 2;
		static constexpr u8 BPE = 3;
		static constexpr u8 NBE = 4;
		static constexpr u8 DCE = 5;
		static constexpr u8 ICE = 6;
		static constexpr u8 DIE = 7;
		static constexpr u8 EC = 8;
	};

	explicit EECoreCOP0Register_Config_t();
};

/*
The BadPAddr register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 79.

Bitfield map (defined as constants in the class below):
- Bits 0-3 (length 4): Constant 0.
- Bits 4-31 (length 28): "BadPAddr".
*/
class EECoreCOP0Register_BadPAddr_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 BadPAddr = 0;
	};

	explicit EECoreCOP0Register_BadPAddr_t();
};

/*
The BPC register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 80.

Bitfield map (defined as constants in the class below):
- Bits 0 (length 1): "IAB".
- Bits 1 (length 1): "DRB".
- Bits 2 (length 1): "DWB".
- Bits 3-14 (length 12): Constant 0.
- Bits 15 (length 1): "BED".
- Bits 16 (length 1): "DTE".
- Bits 17 (length 1): "ITE".
- Bits 18 (length 1): "DXE".
- Bits 19 (length 1): "DKE".
- Bits 20 (length 1): "DSE".
- Bits 21 (length 1): "DUE".
- Bits 22 (length 1): Constant 0.
- Bits 23 (length 1): "IXE".
- Bits 24 (length 1): "IKE".
- Bits 25 (length 1): "ISE".
- Bits 26 (length 1): "IUE".
- Bits 27 (length 1): Constant 0.
- Bits 28 (length 1): "DVE".
- Bits 29 (length 1): "DWE".
- Bits 30 (length 1): "DRE".
- Bits 31 (length 1): "IAE".
*/
class EECoreCOP0Register_BPC_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 IAB = 0;
		static constexpr u8 DRB = 1;
		static constexpr u8 DWB = 2;
		static constexpr u8 BED = 3;
		static constexpr u8 DTE = 4;
		static constexpr u8 ITE = 5;
		static constexpr u8 DXE = 6;
		static constexpr u8 DKE = 7;
		static constexpr u8 DSE = 8;
		static constexpr u8 DUE = 9;
		static constexpr u8 IXE = 10;
		static constexpr u8 IKE = 11;
		static constexpr u8 ISE = 12;
		static constexpr u8 IUE = 13;
		static constexpr u8 DVE = 14;
		static constexpr u8 DWE = 15;
		static constexpr u8 DRE = 16;
		static constexpr u8 IAE = 17;
	};

	explicit EECoreCOP0Register_BPC_t();
};

/*
The IAB register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 81.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "IAB".
*/
class EECoreCOP0Register_IAB_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 IAB = 0;
	};

	explicit EECoreCOP0Register_IAB_t();
};

/*
The IABM register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 81.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "IABM".
*/
class EECoreCOP0Register_IABM_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 IABM = 0;
	};

	explicit EECoreCOP0Register_IABM_t();
};

/*
The DAB register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 82.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "DAB".
*/
class EECoreCOP0Register_DAB_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 DAB = 0;
	};

	explicit EECoreCOP0Register_DAB_t();
};

/*
The DABM register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 82.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "DABM".
*/
class EECoreCOP0Register_DABM_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 DABM = 0;
	};

	explicit EECoreCOP0Register_DABM_t();
};

/*
The DVB register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 83.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "DVB".
*/
class EECoreCOP0Register_DVB_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 DVB = 0;
	};

	explicit EECoreCOP0Register_DVB_t();
};

/*
The DVBM register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 83.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "DVBM".
*/
class EECoreCOP0Register_DVBM_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 DVBM = 0;
	};

	explicit EECoreCOP0Register_DVBM_t();
};

/*
The PCCR register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 84.

Bitfield map (defined as constants in the class below):
- Bits 0 (length 1): Constant 0.
- Bits 1 (length 1): "EXL0".
- Bits 2 (length 1): "K0".
- Bits 3 (length 1): "S0".
- Bits 4 (length 1): "U0".
- Bits 5-9 (length 5): "EVENT0".
- Bits 10 (length 1): Constant 0.
- Bits 11 (length 1): "EXL1".
- Bits 12 (length 1): "K1".
- Bits 13 (length 1): "S1".
- Bits 14 (length 1): "U1".
- Bits 15-19 (length 5): "EVENT1".
- Bits 20-30 (length 11): Constant 0.
- Bits 31 (length 1): "CTE".
*/
class EECoreCOP0Register_PCCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 EXL0 = 0;
		static constexpr u8 K0 = 1;
		static constexpr u8 S0 = 2;
		static constexpr u8 U0 = 3;
		static constexpr u8 EVENT0 = 4;
		static constexpr u8 EXL1 = 5;
		static constexpr u8 K1 = 6;
		static constexpr u8 S1 = 7;
		static constexpr u8 U1 = 8;
		static constexpr u8 EVENT1 = 9;
		static constexpr u8 CTE = 10;
	};

	explicit EECoreCOP0Register_PCCR_t();
};

/*
The PCR0 register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 85.

Bitfield map (defined as constants in the class below):
- Bits 0-30 (length 31): "VALUE".
- Bits 31 (length 1): "OVFL".
*/
class EECoreCOP0Register_PCR0_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 VALUE = 0;
		static constexpr u8 OVFL = 1;
	};

	explicit EECoreCOP0Register_PCR0_t();
};

/*
The PCR1 register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 85.

Bitfield map (defined as constants in the class below):
- Bits 0-30 (length 31): "VALUE".
- Bits 31 (length 1): "OVFL".
*/
class EECoreCOP0Register_PCR1_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 VALUE = 0;
		static constexpr u8 OVFL = 1;
	};

	explicit EECoreCOP0Register_PCR1_t();
};

/*
The TagLo register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 86.

Bitfield map (defined as constants in the class below):
- Bits 0-2 (length 3): Unknown ("-").
- Bits 3 (length 1): "L".
- Bits 4 (length 1): "R".
- Bits 5 (length 1): "V".
- Bits 6 (length 1): "D".
- Bits 7-11 (length 5): Unknown ("-").
- Bits 12-31 (length 20) "PTagLo".

TODO: Verify this is correct, the manual doesn't explain this well...
*/
class EECoreCOP0Register_TagLo_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 L = 0;
		static constexpr u8 R = 1;
		static constexpr u8 V = 2;
		static constexpr u8 D = 3;
		static constexpr u8 PTagLo = 4;
	};

	explicit EECoreCOP0Register_TagLo_t();
};

/*
The TagHi register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 87.

Bitfield map (defined as constants in the class below):
- Bits 0-2 (length 3): Unknown ("-").
- Bits 3 (length 1): "L".
- Bits 4 (length 1): "R".
- Bits 5 (length 1): "V".
- Bits 6 (length 1): "D".
- Bits 7-11 (length 5): Unknown ("-").
- Bits 12-31 (length 20) "PTagHi".

TODO: Verify this is correct, the manual doesn't explain this well...
*/
class EECoreCOP0Register_TagHi_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 L = 0;
		static constexpr u8 R = 1;
		static constexpr u8 V = 2;
		static constexpr u8 D = 3;
		static constexpr u8 PTagHi = 4;
	};

	explicit EECoreCOP0Register_TagHi_t();
};

/*
The ErrorEPC register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 88.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "ErrorEPC".
*/
class EECoreCOP0Register_ErrorEPC_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 ErrorEPC = 0;
	};

	explicit EECoreCOP0Register_ErrorEPC_t();
};