#pragma once

#include "Globals.h"

#include "Register_t.h"


/*
COP0_Register_t.h contains all of the subclassed register declarations for COP0.
Each register will have documentation attached to it.
Note: where registers have a constant 0, this is already done due to the Register32_t initalisation code (set to 0 automatically) and so no additional initialisation code is needed.
*/
namespace PS2 {
	namespace EE {

		/*
		The Index register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 63.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0-5 (length 6): "Index".
		- Bits 6-30 (length 25): Constant 0.
		- Bits 31 (length 1): "P".
		*/
		class RegisterIndex_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "Index"
			const u8 INDEX_BIT_STARTPOS = 0;
			const u8 INDEX_BIT_LENGTH = 6;
			u32 getIndex();
			void setIndex(u32 value);

			// "P"
			const u8 P_BIT_STARTPOS = 31;
			const u8 P_BIT_LENGTH = 1;
			u32 getP();
			void setP(u32 value);
		private:
		};

		/*
		The Random register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 64.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0-5 (length 6): "Random".
		- Bits 6-31 (length 26): Constant 0.
		*/
		class RegisterRandom_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "Random"
			const u8 RANDOM_BIT_STARTPOS = 0;
			const u8 RANDOM_BIT_LENGTH = 6;
			u32 getRandom();
			void setRandom(u32 value);
		private:
		};

		/*
		The EntryLo0 register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 65.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0 (length 1): "G".
		- Bits 1 (length 1): "V".
		- Bits 2 (length 1): "D".
		- Bits 3-5 (length 3): "C".
		- Bits 6-25 (length 20): "PFN".
		- Bits 26-30 (length 5): Constant 0.
		- Bits 31 (length 1): "S"
		*/
		class RegisterEntryLo0_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "G"
			const u8 G_BIT_STARTPOS = 0;
			const u8 G_BIT_LENGTH = 1;
			u32 getG();
			void setG(u32 value);

			// "V"
			const u8 V_BIT_STARTPOS = 1;
			const u8 V_BIT_LENGTH = 1;
			u32 getV();
			void setV(u32 value);

			// "D"
			const u8 D_BIT_STARTPOS = 2;
			const u8 D_BIT_LENGTH = 1;
			u32 getD();
			void setD(u32 value);

			// "C"
			const u8 C_BIT_STARTPOS = 3;
			const u8 C_BIT_LENGTH = 3;
			u32 getC();
			void setC(u32 value);

			// "PFN"
			const u8 PFN_BIT_STARTPOS = 6;
			const u8 PFN_BIT_LENGTH = 20;
			u32 getPFN();
			void setPFN(u32 value);

			// "S"
			const u8 S_BIT_STARTPOS = 31;
			const u8 S_BIT_LENGTH = 1;
			u32 getS();
			void setS(u32 value);
		private:
		};

		/*
		The EntryLo1 register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 65.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0 (length 1): "G".
		- Bits 1 (length 1): "V".
		- Bits 2 (length 1): "D".
		- Bits 3-5 (length 3): "C".
		- Bits 6-25 (length 20): "PFN".
		- Bits 26-31 (length 6): Constant 0.
		*/
		class RegisterEntryLo1_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "G"
			const u8 G_BIT_STARTPOS = 0;
			const u8 G_BIT_LENGTH = 1;
			u32 getG();
			void setG(u32 value);

			// "V"
			const u8 V_BIT_STARTPOS = 1;
			const u8 V_BIT_LENGTH = 1;
			u32 getV();
			void setV(u32 value);

			// "D"
			const u8 D_BIT_STARTPOS = 2;
			const u8 D_BIT_LENGTH = 1;
			u32 getD();
			void setD(u32 value);

			// "C"
			const u8 C_BIT_STARTPOS = 3;
			const u8 C_BIT_LENGTH = 3;
			u32 getC();
			void setC(u32 value);

			// "PFN"
			const u8 PFN_BIT_STARTPOS = 6;
			const u8 PFN_BIT_LENGTH = 20;
			u32 getPFN();
			void setPFN(u32 value);
		private:
		};

		/*
		The Context register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 66.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0-3 (length 4): Constant 0.
		- Bits 4-22 (length 19): "BadVPN2".
		- Bits 23-31 (length 9): "PTEBase".
		*/
		class RegisterContext_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "BadVPN2"
			const u8 BADVPN2_BIT_STARTPOS = 4;
			const u8 BADVPN2_BIT_LENGTH = 19;
			u32 getBadVPN2();
			void setBadVPN2(u32 value);

			// "PTEBase"
			const u8 PTEBASE_BIT_STARTPOS = 23;
			const u8 PTEBASE_BIT_LENGTH = 9;
			u32 getPTEBase();
			void setPTEBase(u32 value);
		private:
		};

		/*
		The PageMask register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 67.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0-12 (length 13): Constant 0.
		- Bits 13-24 (length 12): "MASK".
		- Bits 25-31 (length 7): Constant 0.
		*/
		class RegisterPageMask_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "MASK"
			const u8 MASK_BIT_STARTPOS = 13;
			const u8 MASK_BIT_LENGTH = 12;
			u32 getMASK();
			void setMASK(u32 value);
		private:
		};

		/*
		The Wired register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 68.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0-5 (length 6): "Wired".
		- Bits 6-31 (length 26): Constant 0.
		*/
		class RegisterWired_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "Wired"
			const u8 WIRED_BIT_STARTPOS = 0;
			const u8 WIRED_BIT_LENGTH = 6;
			u32 getWired();
			void setWired(u32 value);
		private:
		};

		/*
		The BadVAddr register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 69.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0-31 (length 32): "BadVAddr".
		*/
		class RegisterBadVAddr_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "Wired"
			const u8 BADVADDR_BIT_STARTPOS = 0;
			const u8 BADVADDR_BIT_LENGTH = 6;
			u32 getBadVAddr();
			void setBadVAddr(u32 value);
		private:
		};

		/*
		The Count register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 70.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0-31 (length 32): "Count".
		*/
		class RegisterCount_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "Wired"
			const u8 COUNT_BIT_STARTPOS = 0;
			const u8 COUNT_BIT_LENGTH = 32;
			u32 getCount();
			void setCount(u32 value);
		private:
		};

		/*
		The EntryHI register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 71.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0-7 (length 8): "ASID".
		- Bits 8-12 (length 5): Constant 0.
		- Bits 13-31 (length 19): "VPN2".
		*/
		class RegisterEntryHi_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "ASID"
			const u8 ASID_BIT_STARTPOS = 0;
			const u8 ASID_BIT_LENGTH = 8;
			u32 getASID();
			void setASID(u32 value);

			// "VPN2"
			const u8 VPN2_BIT_STARTPOS = 13;
			const u8 VPN2_BIT_LENGTH = 19;
			u32 getVPN2();
			void setVPN2(u32 value);
		private:
		};

		/*
		The Compare register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 72.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0-31 (length 32): "Compare".
		*/
		class RegisterCompare_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "Compare"
			const u8 COMPARE_BIT_STARTPOS = 0;
			const u8 COMPARE_BIT_LENGTH = 32;
			u32 getCompare();
			void setCompare(u32 value);
		private:
		};

		/*
		The Status register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 73.
		Get and Set functions provided for each field.

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
		class RegisterStatus_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "IE"
			const u8 IE_BIT_STARTPOS = 0;
			const u8 IE_BIT_LENGTH = 1;
			u32 getIE();
			void setIE(u32 value);

			// "EXL"
			const u8 EXL_BIT_STARTPOS = 1;
			const u8 EXL_BIT_LENGTH = 1;
			u32 getEXL();
			void setEXL(u32 value);

			// "ERL"
			const u8 ERL_BIT_STARTPOS = 2;
			const u8 ERL_BIT_LENGTH = 1;
			u32 getERL();
			void setERL(u32 value);

			// "KSU"
			const u8 KSU_BIT_STARTPOS = 3;
			const u8 KSU_BIT_LENGTH = 2;
			u32 getKSU();
			void setKSU(u32 value);

			// "IM"
			const u8 IM_BIT_STARTPOS = 10;
			const u8 IM_BIT_LENGTH = 2;
			u32 getIM();
			void setIM(u32 value);

			// "BEM"
			const u8 BEM_BIT_STARTPOS = 12;
			const u8 BEM_BIT_LENGTH = 1;
			u32 getBEM();
			void setBEM(u32 value);

			// "IM7"
			const u8 IM7_BIT_STARTPOS = 15;
			const u8 IM7_BIT_LENGTH = 1;
			u32 getIM7();
			void setIM7(u32 value);

			// "EIE"
			const u8 EIE_BIT_STARTPOS = 16;
			const u8 EIE_BIT_LENGTH = 1;
			u32 getEIE();
			void setEIE(u32 value);

			// "EDI"
			const u8 EDI_BIT_STARTPOS = 17;
			const u8 EDI_BIT_LENGTH = 1;
			u32 getEDI();
			void setEDI(u32 value);

			// "CH"
			const u8 CH_BIT_STARTPOS = 18;
			const u8 CH_BIT_LENGTH = 1;
			u32 getCH();
			void setCH(u32 value);

			// "BEV"
			const u8 BEV_BIT_STARTPOS = 22;
			const u8 BEV_BIT_LENGTH = 1;
			u32 getBEV();
			void setBEV(u32 value);

			// "DEV"
			const u8 DEV_BIT_STARTPOS = 23;
			const u8 DEV_BIT_LENGTH = 1;
			u32 getDEV();
			void setDEV(u32 value);

			// "CU"
			const u8 CU_BIT_STARTPOS = 28;
			const u8 CU_BIT_LENGTH = 4;
			u32 getCU();
			void setCU(u32 value);
		private:
		};

		/*
		The Cause register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 75.
		Get and Set functions provided for each field.

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
		class RegisterCause_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "ExcCode"
			const u8 EXCCODE_BIT_STARTPOS = 2;
			const u8 EXCCODE_BIT_LENGTH = 5;
			u32 getExcCode();
			void setExcCode(u32 value);

			// "IP2"
			const u8 IP2_BIT_STARTPOS = 10;
			const u8 IP2_BIT_LENGTH = 1;
			u32 getIP2();
			void setIP2(u32 value);

			// "IP3"
			const u8 IP3_BIT_STARTPOS = 11;
			const u8 IP3_BIT_LENGTH = 1;
			u32 getIP3();
			void setIP3(u32 value);

			// "IP7"
			const u8 IP7_BIT_STARTPOS = 15;
			const u8 IP7_BIT_LENGTH = 1;
			u32 getIP7();
			void setIP7(u32 value);

			// "EXC2"
			const u8 EXC2_BIT_STARTPOS = 16;
			const u8 EXC2_BIT_LENGTH = 3;
			u32 getEXC2();
			void setEXC2(u32 value);

			// "CE"
			const u8 CE_BIT_STARTPOS = 28;
			const u8 CE_BIT_LENGTH = 2;
			u32 getCE();
			void setCE(u32 value);

			// "BD2"
			const u8 BD2_BIT_STARTPOS = 30;
			const u8 BD2_BIT_LENGTH = 1;
			u32 getBD2();
			void setBD2(u32 value);

			// "BD"
			const u8 BD_BIT_STARTPOS = 31;
			const u8 BD_BIT_LENGTH = 1;
			u32 getBD();
			void setBD(u32 value);

		private:
		};

		/*
		The EPC register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 76.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0-31 (length 32): "EPC".
		*/
		class RegisterEPC_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "EPC"
			const u8 EPC_BIT_STARTPOS = 0;
			const u8 EPC_BIT_LENGTH = 32;
			u32 getEPC();
			void setEPC(u32 value);

		private:
		};

		/*
		The PRId register of COP0, subclassed off the base Register32 class (Register_t.h).
		Implements the bitfields specified in the docs. See EE Core Users Manual page 77.
		Get and Set functions provided for each field.

		Bitfield map (defined as constants in the class below):
		- Bits 0-7 (length 8): "Rev".
		- Bits 8-15 (length 8): "Imp".
		- Bits 16-31 (length 16): Constant 0.
		*/
		class RegisterPRId_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "Rev"
			const u8 REV_BIT_STARTPOS = 0;
			const u8 REV_BIT_LENGTH = 8;
			u32 getRev();
			void setRev(u32 value);

			// "Imp"
			const u8 IMP_BIT_STARTPOS = 8;
			const u8 IMP_BIT_LENGTH = 8;
			u32 getImp();
			void setImp(u32 value);

		private:
		};

	} // namespace EE
} // namespace PS2 