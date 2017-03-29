#pragma once

#include <type_traits>
#include <vector>
#include <initializer_list>

/*
An enum 'map' type, but using a std::vector as the underlying container for performance.
This will only compile if used with an enum and enumKey_t::COUNT exists.
It is up to the user to provide a sequential enum with no gaps, and COUNT will be the last enum entry.
Can be used with enum classes or regular enums.
Assumes int as the underlying storage format.

TODO: Move into solution global types.
*/
template<typename enumKey_t, typename value_t>
class EnumMap_t
{
public:
	static_assert(std::is_enum<enumKey_t>::value, "Supplied template argument was not of enum type.");

	/*
	Constructs the map, allocating space for enumKey_t::COUNT values and setting the key values.
	Optionally with an initaliser list that must be same size as enumKey_t::COUNT.
	*/
	EnumMap_t()
	{
		mMap.resize(static_cast<int>(enumKey_t::COUNT));
		for (int i = 0; i < mMap.size(); i++)
		{
			auto& entry = mMap[i];
			entry.first = static_cast<enumKey_t>(i);
		}
	}
	EnumMap_t(const std::initializer_list<value_t> & list)
	{
		if (list.size() != static_cast<int>(enumKey_t::COUNT)) 
			throw std::exception("(EnumMap_t) Supplied initaliser list was not the required size.");

		mMap.resize(static_cast<int>(enumKey_t::COUNT));
		for (int i = 0; i < mMap.size(); i++)
		{
			auto& entry = mMap[i];
			entry.first = static_cast<enumKey_t>(i);
			entry.second = list.begin()[i];
		}
	}

	/*
	Returns a value reference for the given key.
	*/
	value_t & operator[](const enumKey_t & key)
	{
		return mMap[static_cast<int>(key)].second;
	}
	const value_t & operator[](const enumKey_t & key) const
	{
		return mMap[static_cast<int>(key)].second;
	}

	/*
	Iterator functions.
	*/
	typename std::vector<std::pair<enumKey_t, value_t>>::iterator begin()
	{
		return mMap.begin();
	}
	typename std::vector<std::pair<enumKey_t, value_t>>::const_iterator begin() const
	{
		return mMap.begin();
	}
	typename std::vector<std::pair<enumKey_t, value_t>>::iterator end()
	{
		return mMap.end();
	}
	typename std::vector<std::pair<enumKey_t, value_t>>::const_iterator end() const
	{
		return mMap.end();
	}

private:
	/*
	Underlying vector used as the map.
	*/
	std::vector<std::pair<enumKey_t, value_t>> mMap;
};
