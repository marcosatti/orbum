#pragma once

#include "Globals.h"

#include "Register_t.h"

/*
The EntryLo0 register of COP0, subclassed off the base Register32 class (Register_t.h).
Implements the bitfields specified in the docs. See EE Core Users Manual page 65.
Get and Set functions provided for each field.

Bitfield map (defined as constants in the class below):
- Bits 0-1 (length 1): "G".
*/

namespace PS2 {
	namespace EE {

		class RegisterEntryLo0_t : public Register32_t
		{
		public:
			// Uses default constructor and deconstructor.

			// "G"
			const u8 G_BIT_STARTPOS = 0;
			const u8 G_BIT_LENGTH = 1;
			u32 getG();
			void setG(u32 value);
		private:			
		};

	} // namespace EE
} // namespace PS2