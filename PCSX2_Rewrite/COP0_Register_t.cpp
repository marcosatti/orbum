#include "stdafx.h"

#include "Globals.h"
#include "COP0_Register_t.h"

namespace PS2 {
	namespace EE {

		// RegisterIndex_t
		u32 RegisterIndex_t::getIndex()
		{
			return getBitRange32(INDEX_BIT_STARTPOS, INDEX_BIT_LENGTH);
		}

		void RegisterIndex_t::setIndex(u32 value)
		{
			setBitRange32(INDEX_BIT_STARTPOS, INDEX_BIT_LENGTH, value);
		}

		u32 RegisterIndex_t::getP()
		{
			return getBitRange32(P_BIT_STARTPOS, P_BIT_LENGTH);
		}

		void RegisterIndex_t::setP(u32 value)
		{
			setBitRange32(P_BIT_STARTPOS, P_BIT_LENGTH, value);
		}

		// RegisterRandom_t
		u32 RegisterRandom_t::getRandom()
		{
			return getBitRange32(RANDOM_BIT_STARTPOS, RANDOM_BIT_LENGTH);
		}

		void RegisterRandom_t::setRandom(u32 value)
		{
			setBitRange32(RANDOM_BIT_STARTPOS, RANDOM_BIT_LENGTH, value);
		}

		// RegisterEntryLo0_t
		u32 RegisterEntryLo0_t::getG()
		{
			return getBitRange32(G_BIT_STARTPOS, G_BIT_LENGTH);
		}

		void RegisterEntryLo0_t::setG(u32 value)
		{
			setBitRange32(G_BIT_STARTPOS, G_BIT_LENGTH, value);
		}

		u32 RegisterEntryLo0_t::getV()
		{
			return getBitRange32(V_BIT_STARTPOS, V_BIT_LENGTH);
		}

		void RegisterEntryLo0_t::setV(u32 value)
		{
			setBitRange32(V_BIT_STARTPOS, V_BIT_LENGTH, value);
		}

		u32 RegisterEntryLo0_t::getD()
		{
			return getBitRange32(D_BIT_STARTPOS, D_BIT_LENGTH);
		}

		void RegisterEntryLo0_t::setD(u32 value)
		{
			setBitRange32(D_BIT_STARTPOS, D_BIT_LENGTH, value);
		}

		u32 RegisterEntryLo0_t::getC()
		{
			return getBitRange32(C_BIT_STARTPOS, C_BIT_LENGTH);
		}

		void RegisterEntryLo0_t::setC(u32 value)
		{
			setBitRange32(C_BIT_STARTPOS, C_BIT_LENGTH, value);
		}

		u32 RegisterEntryLo0_t::getPFN()
		{
			return getBitRange32(PFN_BIT_STARTPOS, PFN_BIT_LENGTH);
		}

		void RegisterEntryLo0_t::setPFN(u32 value)
		{
			setBitRange32(PFN_BIT_STARTPOS, PFN_BIT_LENGTH, value);
		}

		u32 RegisterEntryLo0_t::getS()
		{
			return getBitRange32(S_BIT_STARTPOS, S_BIT_LENGTH);
		}

		void RegisterEntryLo0_t::setS(u32 value)
		{
			setBitRange32(S_BIT_STARTPOS, S_BIT_LENGTH, value);
		}

		// RegisterEntryLo1_t
		u32 RegisterEntryLo1_t::getG()
		{
			return getBitRange32(G_BIT_STARTPOS, G_BIT_LENGTH);
		}

		void RegisterEntryLo1_t::setG(u32 value)
		{
			setBitRange32(G_BIT_STARTPOS, G_BIT_LENGTH, value);
		}

		u32 RegisterEntryLo1_t::getV()
		{
			return getBitRange32(V_BIT_STARTPOS, V_BIT_LENGTH);
		}

		void RegisterEntryLo1_t::setV(u32 value)
		{
			setBitRange32(V_BIT_STARTPOS, V_BIT_LENGTH, value);
		}

		u32 RegisterEntryLo1_t::getD()
		{
			return getBitRange32(D_BIT_STARTPOS, D_BIT_LENGTH);
		}

		void RegisterEntryLo1_t::setD(u32 value)
		{
			setBitRange32(D_BIT_STARTPOS, D_BIT_LENGTH, value);
		}

		u32 RegisterEntryLo1_t::getC()
		{
			return getBitRange32(C_BIT_STARTPOS, C_BIT_LENGTH);
		}

		void RegisterEntryLo1_t::setC(u32 value)
		{
			setBitRange32(C_BIT_STARTPOS, C_BIT_LENGTH, value);
		}

		u32 RegisterEntryLo1_t::getPFN()
		{
			return getBitRange32(PFN_BIT_STARTPOS, PFN_BIT_LENGTH);
		}

		void RegisterEntryLo1_t::setPFN(u32 value)
		{
			setBitRange32(PFN_BIT_STARTPOS, PFN_BIT_LENGTH, value);
		}

		// RegisterContext_t
		u32 RegisterContext_t::getBadVPN2()
		{
			return getBitRange32(BADVPN2_BIT_STARTPOS, BADVPN2_BIT_LENGTH);
		}

		void RegisterContext_t::setBadVPN2(u32 value)
		{
			setBitRange32(BADVPN2_BIT_STARTPOS, BADVPN2_BIT_LENGTH, value);
		}

		u32 RegisterContext_t::getPTEBase()
		{
			return getBitRange32(PTEBASE_BIT_STARTPOS, PTEBASE_BIT_LENGTH);
		}

		void RegisterContext_t::setPTEBase(u32 value)
		{
			setBitRange32(PTEBASE_BIT_STARTPOS, PTEBASE_BIT_LENGTH, value);
		}

		// RegisterPageMask_t
		u32 RegisterPageMask_t::getMASK()
		{
			return getBitRange32(MASK_BIT_STARTPOS, MASK_BIT_LENGTH);
		}

		void RegisterPageMask_t::setMASK(u32 value)
		{
			setBitRange32(MASK_BIT_STARTPOS, MASK_BIT_LENGTH, value);
		}

		// RegisterWired_t
		u32 RegisterWired_t::getWired()
		{
			return getBitRange32(WIRED_BIT_STARTPOS, WIRED_BIT_LENGTH);
		}

		void RegisterWired_t::setWired(u32 value)
		{
			setBitRange32(WIRED_BIT_STARTPOS, WIRED_BIT_LENGTH, value);
		}

		// RegisterBadVAddr_t
		u32 RegisterBadVAddr_t::getBadVAddr()
		{
			return getBitRange32(BADVADDR_BIT_STARTPOS, BADVADDR_BIT_LENGTH);
		}

		void RegisterBadVAddr_t::setBadVAddr(u32 value)
		{
			setBitRange32(BADVADDR_BIT_STARTPOS, BADVADDR_BIT_LENGTH, value);
		}

		// RegisterCount_t
		u32 RegisterCount_t::getCount()
		{
			return getBitRange32(COUNT_BIT_STARTPOS, COUNT_BIT_LENGTH);
		}

		void RegisterCount_t::setCount(u32 value)
		{
			setBitRange32(COUNT_BIT_STARTPOS, COUNT_BIT_LENGTH, value);
		}

		// RegisterEntryHi_t
		u32 RegisterEntryHi_t::getASID()
		{
			return getBitRange32(ASID_BIT_STARTPOS, ASID_BIT_LENGTH);
		}

		void RegisterEntryHi_t::setASID(u32 value)
		{
			setBitRange32(ASID_BIT_STARTPOS, ASID_BIT_LENGTH, value);
		}

		u32 RegisterEntryHi_t::getVPN2()
		{
			return getBitRange32(VPN2_BIT_STARTPOS, VPN2_BIT_LENGTH);
		}

		void RegisterEntryHi_t::setVPN2(u32 value)
		{
			setBitRange32(VPN2_BIT_STARTPOS, VPN2_BIT_LENGTH, value);
		}

		// RegisterCompare_t
		u32 RegisterCompare_t::getCompare()
		{
			return getBitRange32(COMPARE_BIT_STARTPOS, COMPARE_BIT_LENGTH);
		}

		void RegisterCompare_t::setCompare(u32 value)
		{
			setBitRange32(COMPARE_BIT_STARTPOS, COMPARE_BIT_LENGTH, value);
		}

		// RegisterStatus_t
		u32 RegisterStatus_t::getIE()
		{
			return getBitRange32(IE_BIT_STARTPOS, IE_BIT_LENGTH);
		}

		void RegisterStatus_t::setIE(u32 value)
		{
			setBitRange32(IE_BIT_STARTPOS, IE_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getEXL()
		{
			return getBitRange32(EXL_BIT_STARTPOS, EXL_BIT_LENGTH);
		}

		void RegisterStatus_t::setEXL(u32 value)
		{
			setBitRange32(EXL_BIT_STARTPOS, EXL_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getERL()
		{
			return getBitRange32(ERL_BIT_STARTPOS, ERL_BIT_LENGTH);
		}

		void RegisterStatus_t::setERL(u32 value)
		{
			setBitRange32(ERL_BIT_STARTPOS, ERL_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getKSU()
		{
			return getBitRange32(KSU_BIT_STARTPOS, KSU_BIT_LENGTH);
		}

		void RegisterStatus_t::setKSU(u32 value)
		{
			setBitRange32(KSU_BIT_STARTPOS, KSU_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getIM()
		{
			return getBitRange32(IM_BIT_STARTPOS, IM_BIT_LENGTH);
		}

		void RegisterStatus_t::setIM(u32 value)
		{
			setBitRange32(IM_BIT_STARTPOS, IM_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getBEM()
		{
			return getBitRange32(BEM_BIT_STARTPOS, BEM_BIT_LENGTH);
		}

		void RegisterStatus_t::setBEM(u32 value)
		{
			setBitRange32(BEM_BIT_STARTPOS, BEM_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getIM7()
		{
			return getBitRange32(IM7_BIT_STARTPOS, IM7_BIT_LENGTH);
		}

		void RegisterStatus_t::setIM7(u32 value)
		{
			setBitRange32(IM7_BIT_STARTPOS, IM7_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getEIE()
		{
			return getBitRange32(EIE_BIT_STARTPOS, EIE_BIT_LENGTH);
		}

		void RegisterStatus_t::setEIE(u32 value)
		{
			setBitRange32(EIE_BIT_STARTPOS, EIE_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getEDI()
		{
			return getBitRange32(EDI_BIT_STARTPOS, EDI_BIT_LENGTH);
		}

		void RegisterStatus_t::setEDI(u32 value)
		{
			setBitRange32(EDI_BIT_STARTPOS, EDI_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getCH()
		{
			return getBitRange32(CH_BIT_STARTPOS, CH_BIT_LENGTH);
		}

		void RegisterStatus_t::setCH(u32 value)
		{
			setBitRange32(CH_BIT_STARTPOS, CH_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getBEV()
		{
			return getBitRange32(BEV_BIT_STARTPOS, BEV_BIT_LENGTH);
		}

		void RegisterStatus_t::setBEV(u32 value)
		{
			setBitRange32(BEV_BIT_STARTPOS, BEV_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getDEV()
		{
			return getBitRange32(DEV_BIT_STARTPOS, DEV_BIT_LENGTH);
		}

		void RegisterStatus_t::setDEV(u32 value)
		{
			setBitRange32(DEV_BIT_STARTPOS, DEV_BIT_LENGTH, value);
		}

		u32 RegisterStatus_t::getCU()
		{
			return getBitRange32(CU_BIT_STARTPOS, CU_BIT_LENGTH);
		}

		void RegisterStatus_t::setCU(u32 value)
		{
			setBitRange32(CU_BIT_STARTPOS, CU_BIT_LENGTH, value);
		}

		// RegisterCause_t
		u32 RegisterCause_t::getExcCode()
		{
			return getBitRange32(EXCCODE_BIT_STARTPOS, EXCCODE_BIT_LENGTH);
		}

		void RegisterCause_t::setExcCode(u32 value)
		{
			setBitRange32(EXCCODE_BIT_STARTPOS, EXCCODE_BIT_LENGTH, value);
		}

		u32 RegisterCause_t::getIP2()
		{
			return getBitRange32(IP2_BIT_STARTPOS, IP2_BIT_LENGTH);
		}

		void RegisterCause_t::setIP2(u32 value)
		{
			setBitRange32(IP2_BIT_STARTPOS, IP2_BIT_LENGTH, value);
		}

		u32 RegisterCause_t::getIP3()
		{
			return getBitRange32(IP3_BIT_STARTPOS, IP3_BIT_LENGTH);
		}

		void RegisterCause_t::setIP3(u32 value)
		{
			setBitRange32(IP3_BIT_STARTPOS, IP3_BIT_LENGTH, value);
		}

		u32 RegisterCause_t::getIP7()
		{
			return getBitRange32(IP7_BIT_STARTPOS, IP7_BIT_LENGTH);
		}

		void RegisterCause_t::setIP7(u32 value)
		{
			setBitRange32(IP7_BIT_STARTPOS, IP7_BIT_LENGTH, value);
		}

		u32 RegisterCause_t::getEXC2()
		{
			return getBitRange32(EXC2_BIT_STARTPOS, EXC2_BIT_LENGTH);
		}

		void RegisterCause_t::setEXC2(u32 value)
		{
			setBitRange32(EXC2_BIT_STARTPOS, EXC2_BIT_LENGTH, value);
		}

		u32 RegisterCause_t::getCE()
		{
			return getBitRange32(CE_BIT_STARTPOS, CE_BIT_LENGTH);
		}

		void RegisterCause_t::setCE(u32 value)
		{
			setBitRange32(CE_BIT_STARTPOS, CE_BIT_LENGTH, value);
		}

		u32 RegisterCause_t::getBD2()
		{
			return getBitRange32(BD2_BIT_STARTPOS, BD2_BIT_LENGTH);
		}

		void RegisterCause_t::setBD2(u32 value)
		{
			setBitRange32(BD2_BIT_STARTPOS, BD2_BIT_LENGTH, value);
		}

		u32 RegisterCause_t::getBD()
		{
			return getBitRange32(BD_BIT_STARTPOS, BD_BIT_LENGTH);
		}

		void RegisterCause_t::setBD(u32 value)
		{
			setBitRange32(BD_BIT_STARTPOS, BD_BIT_LENGTH, value);
		}

		// RegisterEPC_t
		u32 RegisterEPC_t::getEPC()
		{
			return getBitRange32(EPC_BIT_STARTPOS, EPC_BIT_LENGTH);
		}

		void RegisterEPC_t::setEPC(u32 value)
		{
			setBitRange32(EPC_BIT_STARTPOS, EPC_BIT_LENGTH, value);
		}

		// RegisterPRId_t
		u32 RegisterPRId_t::getRev()
		{
			return getBitRange32(REV_BIT_STARTPOS, REV_BIT_LENGTH);
		}

		void RegisterPRId_t::setRev(u32 value)
		{
			setBitRange32(REV_BIT_STARTPOS, REV_BIT_LENGTH, value);
		}

		u32 RegisterPRId_t::getImp()
		{
			return getBitRange32(IMP_BIT_STARTPOS, IMP_BIT_LENGTH);
		}

		void RegisterPRId_t::setImp(u32 value)
		{
			setBitRange32(IMP_BIT_STARTPOS, IMP_BIT_LENGTH, value);
		}

	} // namespace EE
} // namespace PS2