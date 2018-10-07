#pragma once

#include <climits>
#include <cstddef>
#include <cstdint>
#include <limits>

#include <cereal/cereal.hpp>

/// PS2 Primative Data Types.
/// These types should be used throughout the emulator when operating on the PS2 system state.
/// The PS2 and SCE manuals use this size terminology:
/// Byte               size is 8-bit.
/// Halfword (hword)   size is 16-bit.
/// Word               size is 32-bit.
/// Doubleword (dword) size is 64-bit.
/// Quadword (qword)   size is 128-bit.
/// Float (single)     size is 32-bit.
typedef int8_t sbyte;
typedef int16_t shword;
typedef int32_t sword;
typedef int64_t sdword;
typedef uint8_t ubyte;
typedef uint16_t uhword;
typedef uint32_t uword;
typedef uint64_t udword;

/// Pointer and size types.
typedef uword uptr;
typedef uword usize;
typedef sword ssize;

/// Floating point types.
/// Warning! Assumes sizeof(float) * CHAR_BIT == 32 !
/// A compile time error will be given to make sure.
typedef float f32;
static_assert(sizeof(f32) * CHAR_BIT == 32, "f32 is not 32-bits long!");

//// Qword (128-bit) type.
/// The PS2 never operates on pure 128-bit values - rather it operates on sub
/// sections of this value, such as 4 words or 2 dwords. It does not make sense for
/// a signed 128-bit value to exist (or performing arithmetic operations).
/// TODO: Look into boost/multiprecision (uint128_t) for endianess and compiler ordering?
struct uqword
{
    union {
        struct
        {
            udword lo;
            udword hi;
        };

        udword ud[2];
        uword uw[4];
        uhword uh[8];
        ubyte ub[16];
    };

    uqword() :
        lo(0),
        hi(0)
    {
    }

    uqword(const udword ud) :
        lo(ud),
        hi(ud)
    {
    }

    uqword(const udword lo, const udword hi) :
        lo(lo),
        hi(hi)
    {
    }

    uqword(const uword uw0, const uword uw1, const uword uw2, const uword uw3) :
        uw{uw0, uw1, uw2, uw3}
    {
    }

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            CEREAL_NVP(hi),
            CEREAL_NVP(lo));
    }
};

/// Primitive type min/max values.
static constexpr ubyte VALUE_UBYTE_MAX = std::numeric_limits<ubyte>::max();
static constexpr sbyte VALUE_SBYTE_MAX = std::numeric_limits<sbyte>::max();
static constexpr sbyte VALUE_SBYTE_MIN = std::numeric_limits<sbyte>::min();
static constexpr uhword VALUE_UHWORD_MAX = std::numeric_limits<uhword>::max();
static constexpr shword VALUE_SHWORD_MAX = std::numeric_limits<shword>::max();
static constexpr shword VALUE_SHWORD_MIN = std::numeric_limits<shword>::min();
static constexpr uword VALUE_UWORD_MAX = std::numeric_limits<uword>::max();
static constexpr sword VALUE_SWORD_MAX = std::numeric_limits<sword>::max();
static constexpr sword VALUE_SWORD_MIN = std::numeric_limits<sword>::min();
static constexpr udword VALUE_UDWORD_MAX = std::numeric_limits<udword>::max();
static constexpr sdword VALUE_SDWORD_MAX = std::numeric_limits<sdword>::max();
static constexpr sdword VALUE_SDWORD_MIN = std::numeric_limits<sdword>::min();

/// Primitive ratios.
static constexpr int NUMBER_BYTES_IN_QWORD = 16;
static constexpr int NUMBER_HWORDS_IN_QWORD = 8;
static constexpr int NUMBER_WORDS_IN_QWORD = 4;
static constexpr int NUMBER_DWORDS_IN_QWORD = 2;
static constexpr int NUMBER_BYTES_IN_DWORD = 8;
static constexpr int NUMBER_HWORDS_IN_DWORD = 4;
static constexpr int NUMBER_WORDS_IN_DWORD = 2;
static constexpr int NUMBER_BYTES_IN_WORD = 4;
static constexpr int NUMBER_HWORDS_IN_WORD = 2;
static constexpr int NUMBER_BYTES_IN_HWORD = 2;