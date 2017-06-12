#pragma once

#include <iterator>
#include <initializer_list>

/*
An enum 'map' type, but using a C array as the underlying container for performance.
This will only work if used with an enum and enumKey_t::COUNT exists.
It is up to the user to provide a sequential enum with no gaps, and COUNT will be the last enum entry.
Can be used with enum classes or regular enums.
Assumes int as the underlying storage & enum format.

TODO: Move into solution global types.
*/
template<typename EnumKey_t, typename Value_t>
class EnumMap_t
{
public:
	static_assert(std::is_enum<EnumKey_t>::value, "Supplied template argument EnumKey_t was not of enum type.");

	/*
	Uses own version of std::pair<K,V> as Visual Studio doesn't like it for whatever reason (intelisense errors)... still compiles fine however.
	*/
	struct Element_t
	{
		EnumKey_t first;
		Value_t second;
	};

	/*
	Construct the map using:
	 - Default initialised types,
	 - Value initalised types,
	 - or with a initialiser list.
	*/
	constexpr EnumMap_t() : mMap{}
	{
		for (int i = 0; i < static_cast<int>(EnumKey_t::COUNT); i++)
		{
			Element_t & entry = mMap[i];
			entry.first = static_cast<EnumKey_t>(i);
			entry.second = Value_t();
		}
	}
	constexpr EnumMap_t(const std::initializer_list<Value_t> & list) : mMap{}
	{
		for (int i = 0; i < static_cast<int>(EnumKey_t::COUNT); i++)
		{
			Element_t & entry = mMap[i];
			entry.first = static_cast<EnumKey_t>(i);
			entry.second = list.begin()[i];
		}
	}

	/*
	Returns a value reference for the given key.
	*/
	Value_t & operator[](const EnumKey_t & key)
	{
		return mMap[static_cast<int>(key)].second;
	}
	constexpr const Value_t & operator[](const EnumKey_t & key) const
	{
		return mMap[static_cast<int>(key)].second;
	}

	/*
	Iterator functions.
	*/
	Element_t * begin()
	{
		return std::begin(mMap);
	}
	constexpr const Element_t * begin() const
	{
		return std::begin(mMap);
	}
	Element_t * end()
	{
		return std::end(mMap);
	}
	constexpr const Element_t * end() const
	{
		return std::end(mMap);
	}

private:
	/*
	Underlying array for map.
	*/
	Element_t mMap[static_cast<int>(EnumKey_t::COUNT)];
};