#include "stdafx.h"

#include "Globals.h"
#include "RegisterRandom_t.h"

namespace PS2 {
	namespace EE {

		u32 RegisterRandom_t::getRandom()
		{
			return getBitRange32(RANDOM_BIT_STARTPOS, RANDOM_BIT_LENGTH);
		}

		void RegisterRandom_t::setRandom(u32 value)
		{
			setBitRange32(RANDOM_BIT_STARTPOS, RANDOM_BIT_LENGTH, value);
		}

	} // namespace EE
} // namespace PS2