#pragma once

/*
Used when converting an IEEE754 spec float to a PS2 spec float, to signify if:
- Z flag set: the parsed value was zero (applies to +/- 0).
- S flag set: the parsed value was negative.
- U flag set: the parsed value was denormalised (not supported by PS2).
- O flag set: the parsed value was NaN or +/- Inf (not supported by PS2).

See FPUUtil::formatIEEEToPS2Float() where this is filled in and used.
*/
struct FPUFlags_t
{
	bool ZF;
	bool SF;
	bool UF;
	bool OF;
};