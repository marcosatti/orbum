#pragma once

#include "Globals.h"

#include "Register_t.h"

/*
The Index register of COP0, subclassed off the base Register32 class (Register_t.h).
Implements the bitfields specified in the docs. See EE Core Users Manual page 63.
Get and Set functions provided for each field.

Bitfield map (defined as constants in the class below):
- Bits 0-5 (length 6): "Index".
- Bits 6-30 (length 25): Constant 0.
- Bits 31 (length 1): "P".
*/

namespace PS2 {
	namespace EE {

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

	} // namespace EE
} // namespace PS2