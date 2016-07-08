#include "stdafx.h"

#include "Globals.h"
#include "RegisterEntryLo0_t.h"

namespace PS2 {
	namespace EE {

		u32 RegisterEntryLo0_t::getG()
		{
			return getBitRange32(G_BIT_STARTPOS, G_BIT_LENGTH);
		}

		void RegisterEntryLo0_t::setG(u32 value)
		{
			setBitRange32(G_BIT_STARTPOS, G_BIT_LENGTH, value);
		}

	} // namespace EE
} // namespace PS2