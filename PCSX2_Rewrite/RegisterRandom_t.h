#pragma once

#include "Globals.h"

#include "Register_t.h"

/*
The Random register of COP0, subclassed off the base Register32 class (Register_t.h).
Implements the bitfields specified in the docs. See EE Core Users Manual page 64.
Get and Set functions provided for each field.

Bitfield map (defined as constants in the class below):
- Bits 0-5 (length 6): "Random".
- Bits 6-30 (length 25): Constant 0.
*/

namespace PS2 {
	namespace EE {

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

	} // namespace EE
} // namespace PS2