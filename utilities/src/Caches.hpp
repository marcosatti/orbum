#pragma once

#include <iostream>
#include <utility>
#include <optional>
#include <algorithm>
#include <array>
#include <boost/compute/detail/lru_cache.hpp>

/// Small LFU cache that uses an array with access counts for eviction.
template<int Size, typename KeyTy, typename ValueTy>
class CounterLfuCache
{
private:
    using CacheEntry = std::tuple<KeyTy, ValueTy, size_t>;
    using CacheContainer = std::array<CacheEntry, Size>;

public:
    CounterLfuCache() :
        current_cache_size(0),
        cache{ std::make_tuple(KeyTy(), ValueTy(), 0) }
    {
    }

    /// Returns the value associated with the key and increments the access count.
    std::optional<const ValueTy> get(const KeyTy key)
    {
        auto entry_it = std::find_if(cache.begin(), cache.begin() + current_cache_size, [key](const CacheEntry & e) {
            return std::get<0>(e) == key;
        });

        if (entry_it != (cache.begin() + current_cache_size))
        {
            // Found an entry, return it.
            std::get<2>(*entry_it) += 1;
            return std::get<1>(*entry_it);
        }
        else
        {
            // Didn't find an entry, return nothing so the caller can deal with.
            return std::nullopt;
        }
    }

    /// Inserts a new key value pair into the cache, evicting the least used one if full.
    void insert(const KeyTy key, const ValueTy value)
    {
        auto&[entry_key, entry_value, entry_access_count] = *find_eviction_entry();

        entry_key = key;
        entry_value = value;
        entry_access_count = 0;
    }

private:
    size_t current_cache_size;
    CacheContainer cache;

    /// Finds the entry with the lowest access count to evict, and returns its position.
    typename CacheContainer::iterator find_eviction_entry()
    {
        if (current_cache_size >= Size)
        {
            auto entry_it = std::min_element(cache.begin(), cache.begin() + current_cache_size, [](const CacheEntry & e1, const CacheEntry & e2) {
                return (std::get<2>(e1) < std::get<2>(e2));
            });


            if (entry_it == (cache.begin() + current_cache_size))
                throw std::runtime_error("Couldn't find an entry to evict...");
            
            return entry_it;
        } 
        else
        {
            current_cache_size += 1;
            return (cache.begin() + current_cache_size - 1);
        }
    }
};

/// Small LRU cache that uses an array with access timestamps for eviction.
template<int Size, typename KeyTy, typename ValueTy>
class TimestampLruCache
{
private:
	using CacheEntry = std::tuple<KeyTy, ValueTy, size_t>;
	using CacheContainer = std::array<CacheEntry, Size>;

public:
    TimestampLruCache() :
		total_cache_access(0),
		current_cache_size(0),
		cache{ std::make_tuple(KeyTy(), ValueTy(), 0) }
	{
	}

	/// Returns the value associated with the key and sets the access timestamp.
	std::optional<const ValueTy> get(const KeyTy key)
	{
		auto entry_it = std::find_if(cache.begin(), cache.begin() + current_cache_size, [key](const CacheEntry & e) {
			return std::get<0>(e) == key;
		});

		if (entry_it != (cache.begin() + current_cache_size))
		{
			// Found an entry, return it.
			total_cache_access++;
			std::get<2>(*entry_it) = total_cache_access;
			return std::get<1>(*entry_it);
		}
		else
		{
			// Didn't find an entry, return nothing so the caller can deal with.
			return std::nullopt;
		}
	}

	/// Inserts a new key value pair into the cache, evicting the least used one if full.
	void insert(const KeyTy key, const ValueTy value)
	{
		auto&[entry_key, entry_value, entry_access_count] = *find_eviction_entry();

		entry_key = key;
		entry_value = value;
		entry_access_count = total_cache_access;
	}

private:
	size_t total_cache_access;
	size_t current_cache_size;
	CacheContainer cache;

	/// Finds the entry with the lowest timestamp to evict, and returns its position.
	typename CacheContainer::iterator find_eviction_entry()
	{
		if (current_cache_size >= Size)
		{
			auto entry_it = std::min_element(cache.begin(), cache.begin() + current_cache_size, [](const CacheEntry & e1, const CacheEntry & e2) {
				return (std::get<2>(e1) < std::get<2>(e2));
			});


			if (entry_it == (cache.begin() + current_cache_size))
				throw std::runtime_error("Couldn't find an entry to evict...");

			return entry_it;
		}
		else
		{
			current_cache_size += 1;
			return (cache.begin() + current_cache_size - 1);
		}
	}
};

/// Wrapper around the Boost LRU cache to provide a get std::optional interface.
template<int Size, typename KeyTy, typename ValueTy>
class HashedLruCache
{
public:
	HashedLruCache() :
        cache(Size)
    {
    }
    
    std::optional<const ValueTy> get(const KeyTy key)
    {
        auto result = cache.get(key);
        return result ? std::make_optional(*result) : std::nullopt;
    }
    
    void insert(const KeyTy key, const ValueTy value)
    {
        cache.insert(key, value);
    }

private:
    boost::compute::detail::lru_cache<KeyTy, ValueTy> cache;
};

/// Cache container using the LRU eviction policy - recent cache hit entries are moved to the front of the array.
template<int Size, typename KeyTy, typename ValueTy>
class OrderedLruCache
{
private:
    using CacheEntry = std::tuple<KeyTy, ValueTy>;
    using CacheContainer = std::array<CacheEntry, Size>;

public:
    OrderedLruCache() :
        current_cache_size(0),
        cache{ std::make_tuple(KeyTy(), ValueTy()) }
    {
    }

    /// Returns the value associated with the key and sets the access timestamp.
    std::optional<const ValueTy> get(const KeyTy key)
    {
        auto end_it = cache.begin() + current_cache_size;

        auto entry_it = std::find_if(cache.begin(), end_it, [key](const CacheEntry & e) {
            return std::get<0>(e) == key;
        });

        if (entry_it != end_it)
        {
            ValueTy value = std::get<1>(*entry_it);

            // Move to the front if needed.
            if (entry_it != cache.begin())
            {
                std::move_backward(cache.begin(), entry_it - 1, entry_it);
                *cache.begin() = std::make_tuple(key, value);
            }

            return value;
        }
        
        // Didn't find an entry, return nothing so the caller can deal with.
        return std::nullopt;
    }

    /// Inserts a new key value pair into the cache, evicting the least used one if full.
    void insert(const KeyTy key, const ValueTy value)
    {
        auto end_it = cache.begin() + current_cache_size;

        if (end_it == cache.end())
        {
            // Cache is full, evict last one.
            std::move_backward(cache.begin(), end_it - 1, end_it);
        }
        else
        {
            // Cache not full, just need to move entries.
            std::move_backward(cache.begin(), end_it, end_it + 1);
            current_cache_size++;
        }

        *cache.begin() = std::make_tuple(key, value);
    }

private:
    size_t current_cache_size;
    CacheContainer cache;
};

/// Cache container using the CLOCK eviction policy - organised in a circular buffer.
template<int Size, typename KeyTy, typename ValueTy>
class ClockCache
{
private:
    using CacheEntry = std::tuple<KeyTy, ValueTy, bool>;
    using CacheContainer = std::array<CacheEntry, Size>;
    using CacheIterator = typename CacheContainer::iterator;

public:
    ClockCache() :
        current_cache_size(0),
        cache{ std::make_tuple(KeyTy(), ValueTy(), false) }
    {
    }
    
    /// Returns the value associated with the key and sets the recently used flag.
    std::optional<ValueTy> get(const KeyTy key)
    {
        if (!current_cache_size)
            return std::nullopt;

        auto end = hand_iterator;

        // Search towards the end of the clock.
        while (true)
        {
            auto&[entry_key, entry_value, entry_recently_used] = *hand_iterator;

            if (entry_key == key)
            {
                entry_recently_used = true;
                return entry_value;
            }

            next_hand();

            if (hand_iterator == end)
                return std::nullopt;
        }
    }

    /// Inserts an entry into the cache or evicts the first entry that has not been recently used.
    void insert(const KeyTy key, const ValueTy value)
    {
        // Slot available.
        if (current_cache_size < Size)
        {
            auto it = cache.begin() + current_cache_size;
            *it = std::make_tuple(key, value, true);
            return;
        }

        // Start searching for a slot to evict by looking at the recently used flag.
        while (true)
        {
            auto& entry_recently_used = std::get<2>(*hand_iterator);

            if (!entry_recently_used)
            {
                *hand_iterator = std::make_tuple(key, value, true);
                return;
            }

            entry_recently_used = false;
            next_hand();
        }
    }

private:
    /// Increments the hand iterator and wraps around to the start when required.
    void next_hand()
    {
        hand_iterator += 1;

        auto end_it = cache.begin() + current_cache_size;
        if (hand_iterator == end_it)
            hand_iterator = cache.begin();
    }

    CacheIterator hand_iterator;
    size_t current_cache_size;
    CacheContainer cache;
};
