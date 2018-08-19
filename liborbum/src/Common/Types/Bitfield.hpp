#pragma once

#include <stdexcept>

#include "Common/Types/Primitive.hpp"

/// Describes a bitfield within a primitive value.
struct Bitfield
{
    constexpr Bitfield() :
        start(0),
        length(0)
    {
    }

    constexpr Bitfield(const int start, const int length) :
        start(start),
        length(length)
    {
        // Perform checks.
        // Note: a zero-length bitfield is ok - in this case all operations
        // (ie: extract) will result in a value of 0 or (ie: insert) no change.
        if (start < 0)
            throw std::logic_error("Start must be >= 0");
        if (length < 0)
            throw std::logic_error("Length must be >= 0");
    }

    template <typename T>
    constexpr T unshifted_mask() const
    {
        return (static_cast<T>(1) << length) - static_cast<T>(1);
    }

    template <typename T>
    constexpr T shifted_mask() const
    {
        return unshifted_mask<T>() << static_cast<T>(start);
    }

    template <typename T>
    constexpr T extract_from(const T value) const
    {
        return (value & shifted_mask<T>()) >> start;
    }

    template <typename T>
    constexpr T insert_into(const T value, const T field_value) const
    {
        T cleaned_value = value & (~shifted_mask<T>());
        T cleaned_field_value = (field_value & unshifted_mask<T>()) << start;
        return cleaned_value | cleaned_field_value;
    }

    template <typename To, typename From>
    constexpr To extract_from(const From value) const
    {
        return static_cast<To>((value & shifted_mask<From>()) >> start);
    }

    template <typename To, typename From>
    constexpr To insert_into(const From value, const From field_value) const
    {
        From cleaned_value = value & (~shifted_mask<From>());
        From cleaned_field_value = (field_value & unshifted_mask<From>()) << start;
        return static_cast<To>(cleaned_value | cleaned_field_value);
    }

    /// qword template specialization.
    template <typename To>
    constexpr To extract_from(const uqword value) const
    {
        // Most (all?) bitfields within uqword types are aligned to 64 bit 
        // boundaries... But this should be easy to implement if needed.
        if ((start < 64) && ((length + start) >= 64))
            throw std::logic_error("Cannot extract bitfield over 64 bit boundary from a uqword [not implemented]");

        if (start < 64)
            return Bitfield(start, length).extract_from<To>(value.lo);
        else
            return Bitfield(start - 64, length).extract_from<To>(value.hi);
    }

    constexpr bool operator==(const Bitfield& rhs) const
    {
        return (start == rhs.start) && (length == rhs.length);
    }

    constexpr bool operator!=(const Bitfield& rhs) const
    {
        return !operator==(rhs);
    }

    int start;
    int length;
};
