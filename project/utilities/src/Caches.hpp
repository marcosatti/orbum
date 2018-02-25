#pragma once

#include <utility>
#include <optional>
#include <algorithm>
#include <array>
#include <boost/compute/detail/lru_cache.hpp>

/// Small LRU cache that uses an array with access counts for eviction.
template<size_t Size, typename KeyTy, typename ValueTy>
class ArrayLruCache
{
private:
    using CacheEntry = std::tuple<KeyTy, ValueTy, size_t>;
    using CacheContainer = std::array<typename CacheEntry, Size>;

public:
    ArrayLruCache() :
        current_cache_size(0),
        cache{ std::make_tuple(KeyTy(), ValueTy(), 0) }
    {
    }

    /// Returns the value associated with the key and increments the access count.
    std::optional<const ValueTy> get(const KeyTy key)
    {
        auto entry_it = std::find_if(cache.begin(), cache.begin() + current_cache_size, [&key](const CacheEntry & e) {
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
template<size_t Size, typename KeyTy, typename ValueTy>
class TimestampedArrayLruCache
{
private:
	using CacheEntry = std::tuple<KeyTy, ValueTy, size_t>;
	using CacheContainer = std::array<typename CacheEntry, Size>;

public:
	TimestampedArrayLruCache() :
		total_cache_access(0),
		current_cache_size(0),
		cache{ std::make_tuple(KeyTy(), ValueTy(), 0) }
	{
	}

	/// Returns the value associated with the key and increments the access count.
	std::optional<const ValueTy> get(const KeyTy key)
	{
		auto entry_it = std::find_if(cache.begin(), cache.begin() + current_cache_size, [&key](const CacheEntry & e) {
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

/// Wrapper around the Boost LRU cache to provide a get std::optional interface.
template<size_t Size, typename KeyTy, typename ValueTy>
class LruCache
{
public:
    LruCache() :
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
