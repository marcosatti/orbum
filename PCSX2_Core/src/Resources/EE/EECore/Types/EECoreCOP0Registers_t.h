#pragma once

#include <memory>

#include "Common/Types/Register/BitfieldRegister32_t.h"

/*
EECoreCOP0Registers_t.h implements the EE Core specific COP0 control registers.
Each register will have documentation attached to it, and is prefixed with EECoreCOP0Register.
Only the registers that need bitfield definitions or additional functionality are provided here.
For other simple registers, using the full 32-bit space, a Register32_t instance is sufficient.
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
		static constexpr int Index = 0;
		static constexpr int P = 1;
	};

	EECoreCOP0Register_Index_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int Random = 0;
	};

	EECoreCOP0Register_Random_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int G = 0;
		static constexpr int V = 1;
		static constexpr int D = 2;
		static constexpr int C = 3;
		static constexpr int PFN = 4;
		static constexpr int S = 5;
	};

	EECoreCOP0Register_EntryLo0_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int G = 0;
		static constexpr int V = 1;
		static constexpr int D = 2;
		static constexpr int C = 3;
		static constexpr int PFN = 4;
	};

	EECoreCOP0Register_EntryLo1_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The Context register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 66.

Bitfield map (defined as constants in the class below):
- Bits 0-3 (length 4): Constant 0.
- Bits 4-22 (length 19): "BadVPN2".
- Bits 23-31 (length 9): "PTEBase".
*/
class EECoreCOP0Register_System_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int BadVPN2 = 0;
		static constexpr int PTEBase = 1;
	};

	EECoreCOP0Register_System_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int MASK = 0;
	};

	EECoreCOP0Register_PageMask_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int Wired = 0;
	};

	EECoreCOP0Register_Wired_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
The Count register of COP0, subclassed off the Register32_t class.
See EE Core Users Manual page 70.
*/
class EECoreCOP0Register_Count_t : public Register32_t
{
public:
	EECoreCOP0Register_Count_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	// Convenience function that increments the count field value by the specified amount. 
	void increment(const Context_t context, const size_t value);
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
		static constexpr int ASID = 0;
		static constexpr int VPN2 = 1;
	};

	EECoreCOP0Register_EntryHi_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};

/*
[Listed before COP0.Compare due to dependency.]
The Cause register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 75.

Bitfield map (defined as constants in the class below):
- Bits 0-1 (length 2): Constant 0.
- Bits 2-6 (length 5): "ExcCode".
- Bits 7 (length 1): Constant 0.
- Bits 8-15 (length 8): "IP". While not mentioned in the manual, this is a standard MIPS convention to use and is compatible (see eg PSX docs). Using this makes it easy to implement interrupt handling.
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
		static constexpr int ExcCode = 0;
		static constexpr int IP = 1;
		static constexpr int EXC2 = 2;
		static constexpr int CE = 3;
		static constexpr int BD2 = 4;
		static constexpr int BD = 5;
	};

	EECoreCOP0Register_Cause_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Clears the Cause.IP bits (from bits 8 -> 15).
	*/
	void clearIP(const Context_t context);

	/*
	Sets the given IP[irq] bit given.
	The other IP bits are left unchanged (uses OR).
	*/
	void setIRQLine(const Context_t context, const int irq);

	/*
	Clears the given IP[irq] bit given.
	The other IP bits are left unchanged (uses ~AND).
	*/
	void clearIRQLine(const Context_t context, const int irq);
};

/*
The Status register of COP0, subclassed off the base BitfieldRegister32_t & Register32_t class.
Implements the bitfields specified in the docs. See EE Core Users Manual page 73.

Bitfield map (defined as constants in the class below):
- Bits 0 (length 1): "IE".
- Bits 1 (length 1): "EXL".
- Bits 2 (length 1): "ERL".
- Bits 3-4 (length 2): "KSU".
- Bits 5-7 (length 3): Constant 0.
- Bits 8-15 (length 8): "IM". While not mentioned in the manual, this is a standard MIPS convention to use and is compatible (see eg PSX docs). Using this makes it easy to implement interrupt handling. Note that BEM (bus error mask) behaves the same way as other interrupt sources.
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
		static constexpr int IE = 0;
		static constexpr int EXL = 1;
		static constexpr int ERL = 2;
		static constexpr int KSU = 3;
		static constexpr int IM = 4;
		static constexpr int EIE = 5;
		static constexpr int EDI = 6;
		static constexpr int CH = 7;
		static constexpr int BEV = 8;
		static constexpr int DEV = 9;
		static constexpr int CU = 10;
	};

	EECoreCOP0Register_Status_t(const char * mnemonic, const bool debugReads, const bool debugWrites);

	/*
	Returns if all interrupts are currently masked ( = NOT ENABLED).
	Does so by checking the master EIE and IE bit.
	*/
	bool isInterruptsMasked(const Context_t context);
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
		static constexpr int Rev = 0;
		static constexpr int Imp = 1;
	};

	EECoreCOP0Register_PRId_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int K0 = 0;
		static constexpr int DC = 1;
		static constexpr int IC = 2;
		static constexpr int BPE = 3;
		static constexpr int NBE = 4;
		static constexpr int DCE = 5;
		static constexpr int ICE = 6;
		static constexpr int DIE = 7;
		static constexpr int EC = 8;
	};

	EECoreCOP0Register_Config_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int BadPAddr = 0;
	};

	EECoreCOP0Register_BadPAddr_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int IAB = 0;
		static constexpr int DRB = 1;
		static constexpr int DWB = 2;
		static constexpr int BED = 3;
		static constexpr int DTE = 4;
		static constexpr int ITE = 5;
		static constexpr int DXE = 6;
		static constexpr int DKE = 7;
		static constexpr int DSE = 8;
		static constexpr int DUE = 9;
		static constexpr int IXE = 10;
		static constexpr int IKE = 11;
		static constexpr int ISE = 12;
		static constexpr int IUE = 13;
		static constexpr int DVE = 14;
		static constexpr int DWE = 15;
		static constexpr int DRE = 16;
		static constexpr int IAE = 17;
	};

	EECoreCOP0Register_BPC_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int EXL0 = 0;
		static constexpr int K0 = 1;
		static constexpr int S0 = 2;
		static constexpr int U0 = 3;
		static constexpr int EVENT0 = 4;
		static constexpr int EXL1 = 5;
		static constexpr int K1 = 6;
		static constexpr int S1 = 7;
		static constexpr int U1 = 8;
		static constexpr int EVENT1 = 9;
		static constexpr int CTE = 10;
	};

	EECoreCOP0Register_PCCR_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int VALUE = 0;
		static constexpr int OVFL = 1;
	};

	EECoreCOP0Register_PCR0_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int VALUE = 0;
		static constexpr int OVFL = 1;
	};

	EECoreCOP0Register_PCR1_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int L = 0;
		static constexpr int R = 1;
		static constexpr int V = 2;
		static constexpr int D = 3;
		static constexpr int PTagLo = 4;
	};

	EECoreCOP0Register_TagLo_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
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
		static constexpr int L = 0;
		static constexpr int R = 1;
		static constexpr int V = 2;
		static constexpr int D = 3;
		static constexpr int PTagHi = 4;
	};

	EECoreCOP0Register_TagHi_t(const char * mnemonic, const bool debugReads, const bool debugWrites);
};
