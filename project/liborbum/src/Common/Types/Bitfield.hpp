#pragma once

#include <stdexcept>

/// Describes a bitfield within a primitive value.
struct Bitfield
{
	constexpr Bitfield(const int start, const int length) :
		start(start),
		length(length)
	{
		// Do compile time checks.
		// Note: a zero-length bitfield is ok - in this case all operations
		// (ie: extraction) will result in a value of 0. This is used within
		// the Iop ByteBus constructor.
		if (start < 0)
			throw std::logic_error("Start must be >= 0");
		if (length < 0)
			throw std::logic_error("Length must be >= 0");
	}

	template<typename T>
	constexpr T unshifted_mask() const
	{
		return (static_cast<T>(1) << length) - static_cast<T>(1);
	}

	template<typename T>
	constexpr T shifted_mask() const
	{
		return unshifted_mask<T>() << static_cast<T>(start);
	}

	template<typename T>
	constexpr T extract_from(const T value) const
	{
		return (value & shifted_mask<T>()) >> start;
	}

	template<typename T>
	constexpr T insert_into(const T value, const T field_value) const
	{
		T cleaned_value = value & (~shifted_mask<T>());
		T cleaned_field_value = (field_value & unshifted_mask<T>()) << start;
		return cleaned_value | cleaned_field_value;
	}

	const int start;
	const int length;
};