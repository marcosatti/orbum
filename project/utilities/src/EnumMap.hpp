#pragma once

#include <iterator>
#include <initializer_list>

/*
An enum 'map' type, but using a C array as the underlying container for performance.
This will only work if used with an enum and enumKey::COUNT exists.
It is up to the user to provide a sequential enum with no gaps, and COUNT will be the last enum entry.
Can be used with enum classes or regular enums.
Assumes int as the underlying storage & enum format.

TODO: Move into solution global types.
*/
template<typename EnumKey, typename Value>
class EnumMap
{
public:
	static_assert(std::is_enum<EnumKey>::value, "Supplied template argument EnumKey was not of enum type.");

	/*
	Uses own version of std::pair<K,V> as Visual Studio doesn't like it for whatever reason (intelisense errors)... still compiles fine however.
	*/
	struct Element
	{
		EnumKey first;
		Value second;
	};

	/*
	Construct the map using:
	 - Default initialised types,
	 - Value initalised types,
	 - or with a initialiser list.
	*/
	constexpr EnumMap() : mMap{}
	{
		for (int i = 0; i < static_cast<int>(EnumKey::COUNT); i++)
		{
			Element & entry = mMap[i];
			entry.first = static_cast<EnumKey>(i);
			entry.second = Value();
		}
	}
	constexpr EnumMap(const std::initializer_list<Value> & list) : mMap{}
	{
		for (int i = 0; i < static_cast<int>(EnumKey::COUNT); i++)
		{
			Element & entry = mMap[i];
			entry.first = static_cast<EnumKey>(i);
			entry.second = list.begin()[i];
		}
	}

	/*
	Returns a value reference for the given key.
	*/
	Value & operator[](const EnumKey & key)
	{
		return mMap[static_cast<int>(key)].second;
	}
	constexpr const Value & operator[](const EnumKey & key) const
	{
		return mMap[static_cast<int>(key)].second;
	}

	/*
	Iterator functions.
	*/
	Element * begin()
	{
		return std::begin(mMap);
	}
	constexpr const Element * begin() const
	{
		return std::begin(mMap);
	}
	Element * end()
	{
		return std::end(mMap);
	}
	constexpr const Element * end() const
	{
		return std::end(mMap);
	}

private:
	/*
	Underlying array for map.
	*/
	Element mMap[static_cast<int>(EnumKey::COUNT)];
};