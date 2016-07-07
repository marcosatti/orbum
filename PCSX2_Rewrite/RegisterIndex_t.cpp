#include "stdafx.h"

#include "Globals.h"
#include "RegisterIndex_t.h"

namespace PS2 {
	namespace EE {

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

	} // namespace EE
} // namespace PS2