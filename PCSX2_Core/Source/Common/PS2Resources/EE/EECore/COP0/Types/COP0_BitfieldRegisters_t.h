#pragma once

#include "Common/PS2Resources/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
COP0_BitfieldRegister_t.h implements all of the bitfields in each of the COP0 control registers. This is used primarily by COP0_t.h.
Each register will have documentation attached to it.
Note: where register fields have a constant 0, this is already done due to the base classes initalisation code.

It is recommended that you read the documentation of the BitfieldRegister32_t class, which documents how to access bitfields.
All of the fields available within each register are defined within the Fields struct located inside.
ie: to access a field in a register object from outside this file, you would use:
- RegisterIndex.setFieldValue(RegisterIndex::Fields::Index, u32 value) or
- u32 value = RegisterIndex.getFieldValue(RegisterIndex::Fields::Index)
All of the available field functions are listed in the BitfieldRegister32_t class.

The actual fields are defined at runtime within the COP0_BitfieldRegisters_t.cpp file.
*/

class PS2Resources;

/*
RegisterReserved_t represents an unknown (blank) register. It is up to the user at runtime to define fields.
*/
class RegisterReserved_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
	};

	explicit RegisterReserved_t();
};

/*
The Index register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 63.

Bitfield map (defined as constants in the class below):
- Bits 0-5 (length 6): "Index".
- Bits 6-30 (length 25): Constant 0.
- Bits 31 (length 1): "P".
*/
class RegisterIndex_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * Index = "Index";
		static constexpr char * P = "P";
	};

	explicit RegisterIndex_t();
};

/*
The Random register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 64.

Bitfield map (defined as constants in the class below):
- Bits 0-5 (length 6): "Random".
- Bits 6-31 (length 26): Constant 0.
*/
class RegisterRandom_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * Random = "Random";
	};

	explicit RegisterRandom_t();
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
class RegisterEntryLo0_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * G = "G";
		static constexpr char * V = "V";
		static constexpr char * D = "D";
		static constexpr char * C = "C";
		static constexpr char * PFN = "PFN";
		static constexpr char * S = "S";
	};

	explicit RegisterEntryLo0_t();
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
class RegisterEntryLo1_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * G = "G";
		static constexpr char * V = "V";
		static constexpr char * D = "D";
		static constexpr char * C = "C";
		static constexpr char * PFN = "PFN";
	};

	explicit RegisterEntryLo1_t();
};

/*
The Context register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 66.

Bitfield map (defined as constants in the class below):
- Bits 0-3 (length 4): Constant 0.
- Bits 4-22 (length 19): "BadVPN2".
- Bits 23-31 (length 9): "PTEBase".
*/
class RegisterContext_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * BadVPN2 = "BadVPN2";
		static constexpr char * PTEBase = "PTEBase";
	};

	explicit RegisterContext_t();
private:
};

/*
The PageMask register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 67.

Bitfield map (defined as constants in the class below):
- Bits 0-12 (length 13): Constant 0.
- Bits 13-24 (length 12): "MASK".
- Bits 25-31 (length 7): Constant 0.
*/
class RegisterPageMask_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * MASK = "MASK";
	};

	explicit RegisterPageMask_t();
};

/*
The Wired register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 68.

Bitfield map (defined as constants in the class below):
- Bits 0-5 (length 6): "Wired".
- Bits 6-31 (length 26): Constant 0.
*/
class RegisterWired_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * Wired = "Wired";
	};

	explicit RegisterWired_t();
};

/*
The BadVAddr register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 69.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "BadVAddr".
*/
class RegisterBadVAddr_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * BadVAddr = "BadVAddr";
	};

	explicit RegisterBadVAddr_t();
};

/*
The Count register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 70.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "Count".
*/
class RegisterCount_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * Count = "Count";
	};

	explicit RegisterCount_t();

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
class RegisterEntryHi_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * ASID = "ASID";
		static constexpr char * VPN2 = "VPN2";
	};

	explicit RegisterEntryHi_t();
};

/*
The Compare register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 72.
Note: Also clears the COP0.Cause.IP7 field when written to (see overridden functions). This is from the documentation on the same page.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "Compare".
*/
class RegisterCompare_t : public BitfieldRegister32_t, public PS2ResourcesSubobject
{
public:
	struct Fields
	{
		static constexpr char * Compare = "Compare";
	};

	explicit RegisterCompare_t(const PS2Resources_t*const PS2Resources);

	void setFieldValue(const char * fieldName, const u32& value) override;
	void setRegisterValue(const u32 & value) override;
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
class RegisterStatus_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * IE = "IE";
		static constexpr char * EXL = "EXL";
		static constexpr char * ERL = "ERL";
		static constexpr char * KSU = "KSU";
		static constexpr char * IM = "IM";
		static constexpr char * BEM = "BEM";
		static constexpr char * IM7 = "IM7";
		static constexpr char * EIE = "EIE";
		static constexpr char * EDI = "EDI";
		static constexpr char * CH = "CH";
		static constexpr char * BEV = "BEV";
		static constexpr char * DEV = "DEV";
		static constexpr char * CU = "CU";
	};

	explicit RegisterStatus_t();
};

/*
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
class RegisterCause_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * ExcCode = "ExcCode";
		static constexpr char * IP2 = "IP2";
		static constexpr char * IP3 = "IP3";
		static constexpr char * IP7 = "IP7";
		static constexpr char * EXC2 = "EXC2";
		static constexpr char * CE = "IM";
		static constexpr char * BD2 = "BD2";
		static constexpr char * BD = "BD";
	};

	explicit RegisterCause_t();
};

/*
The EPC register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 76.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "EPC".
*/
class RegisterEPC_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * EPC = "EPC";
	};

	explicit RegisterEPC_t();
};

/*
The PRId register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 77.

Bitfield map (defined as constants in the class below):
- Bits 0-7 (length 8): "Rev".
- Bits 8-15 (length 8): "Imp".
- Bits 16-31 (length 16): Constant 0.
*/
class RegisterPRId_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * Rev = "Rev";
		static constexpr char * Imp = "Imp";
	};

	explicit RegisterPRId_t();
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
class RegisterConfig_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * K0 = "K0";
		static constexpr char * DC = "DC";
		static constexpr char * IC = "IC";
		static constexpr char * BPE = "BPE";
		static constexpr char * NBE = "NBE";
		static constexpr char * DCE = "DCE";
		static constexpr char * ICE = "ICE";
		static constexpr char * DIE = "DIE";
		static constexpr char * EC = "EC";
	};

	explicit RegisterConfig_t();
};

/*
The BadPAddr register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 79.

Bitfield map (defined as constants in the class below):
- Bits 0-3 (length 4): Constant 0.
- Bits 4-31 (length 28): "BadPAddr".
*/
class RegisterBadPAddr_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * BadPAddr = "BadPAddr";
	};

	explicit RegisterBadPAddr_t();
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
class RegisterBPC_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * IAB = "IAB";
		static constexpr char * DRB = "DRB";
		static constexpr char * DWB = "DWB";
		static constexpr char * BED = "BED";
		static constexpr char * DTE = "DTE";
		static constexpr char * ITE = "ITE";
		static constexpr char * DXE = "DXE";
		static constexpr char * DKE = "DKE";
		static constexpr char * DSE = "DSE";
		static constexpr char * DUE = "DUE";
		static constexpr char * IXE = "IXE";
		static constexpr char * IKE = "IKE";
		static constexpr char * ISE = "ISE";
		static constexpr char * IUE = "IUE";
		static constexpr char * DVE = "DVE";
		static constexpr char * DWE = "DWE";
		static constexpr char * DRE = "DRE";
		static constexpr char * IAE = "IAE";
	};

	explicit RegisterBPC_t();
};

/*
The IAB register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 81.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "IAB".
*/
class RegisterIAB_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * IAB = "IAB";
	};

	explicit RegisterIAB_t();
};

/*
The IABM register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 81.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "IABM".
*/
class RegisterIABM_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * IABM = "IABM";
	};

	explicit RegisterIABM_t();
};

/*
The DAB register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 82.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "DAB".
*/
class RegisterDAB_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * DAB = "DAB";
	};

	explicit RegisterDAB_t();
};

/*
The DABM register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 82.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "DABM".
*/
class RegisterDABM_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * DABM = "DABM";
	};

	explicit RegisterDABM_t();
};

/*
The DVB register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 83.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "DVB".
*/
class RegisterDVB_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * DVB = "DVB";
	};

	explicit RegisterDVB_t();
};

/*
The DVBM register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 83.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "DVBM".
*/
class RegisterDVBM_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * DVBM = "DVBM";
	};

	explicit RegisterDVBM_t();
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
class RegisterPCCR_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * EXL0 = "EXL0";
		static constexpr char * K0 = "K0";
		static constexpr char * S0 = "S0";
		static constexpr char * U0 = "U0";
		static constexpr char * EVENT0 = "EVENT0";
		static constexpr char * EXL1 = "EXL1";
		static constexpr char * K1 = "K1";
		static constexpr char * S1 = "S1";
		static constexpr char * U1 = "U1";
		static constexpr char * EVENT1 = "EVENT1";
		static constexpr char * CTE = "CTE";
	};

	explicit RegisterPCCR_t();
};

/*
The PCR0 register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 85.

Bitfield map (defined as constants in the class below):
- Bits 0-30 (length 31): "VALUE".
- Bits 31 (length 1): "OVFL".
*/
class RegisterPCR0_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * VALUE = "VALUE";
		static constexpr char * OVFL = "OVFL";
	};

	explicit RegisterPCR0_t();
};

/*
The PCR1 register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 85.

Bitfield map (defined as constants in the class below):
- Bits 0-30 (length 31): "VALUE".
- Bits 31 (length 1): "OVFL".
*/
class RegisterPCR1_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * VALUE = "VALUE";
		static constexpr char * OVFL = "OVFL";
	};

	explicit RegisterPCR1_t();
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
class RegisterTagLo_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * L = "L";
		static constexpr char * R = "R";
		static constexpr char * V = "V";
		static constexpr char * D = "D";
		static constexpr char * PTagLo = "PTagLo";
	};

	explicit RegisterTagLo_t();
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
class RegisterTagHi_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * L = "L";
		static constexpr char * R = "R";
		static constexpr char * V = "V";
		static constexpr char * D = "D";
		static constexpr char * PTagHi = "PTagHi";
	};

	explicit RegisterTagHi_t();
};

/*
The ErrorEPC register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 88.

Bitfield map (defined as constants in the class below):
- Bits 0-31 (length 32): "ErrorEPC".
*/
class RegisterErrorEPC_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr char * ErrorEPC = "ErrorEPC";
	};

	explicit RegisterErrorEPC_t();
};