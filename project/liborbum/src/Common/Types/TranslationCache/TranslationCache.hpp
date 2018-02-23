#pragma once

#include <utility>
#include <optional>
#include <algorithm>
#include <array>
#include <functional>

#include "Common/Types/Mips/MipsCoprocessor0.hpp"
#include "Common/Types/Mips/MmuAccess.hpp"

using OperatingContext = MipsCoprocessor0::OperatingContext;


/// Small LRU cache that uses an array with access counts for eviction.
template<size_t Size, typename KeyTy, typename ValueTy>
class ArrayLruCache
{
public:
    typedef std::tuple<KeyTy, ValueTy, size_t> CacheEntry;
    typedef std::array<typename CacheEntry, Size> Cache;

    ArrayLruCache() :
        current_cache_size(0),
        cache{ std::make_tuple(0, 0, 0) },
        hit_counter(0),
        miss_counter(0)
    {
    }

    /// Returns the value associated with the key and increments the access count.
    std::optional<const ValueTy> get(const KeyTy key)
    {
        auto& entry_it = std::find_if(cache.begin(), cache.end(), [&key](const CacheEntry & e) {
            return std::get<0>(e) == key;
        });

        if (entry_it != cache.end())
        {
            // Found an entry, return it.
            hit_counter++;
            std::get<2>(*entry_it) += 1;
            return std::get<1>(*entry_it);
        }
        else
        {
            // Didn't find an entry, return nothing so the caller can deal with.
            miss_counter++;
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
    Cache cache;

    size_t hit_counter;
    size_t miss_counter;

    /// Finds the entry with the lowest access count to evict, and returns its position.
    typename Cache::iterator find_eviction_entry()
    {
        if (current_cache_size >= Size)
        {
            auto& entry_it = std::min_element(cache.begin(), cache.end(), [](const CacheEntry & e1, const CacheEntry & e2) {
                return (std::get<2>(e1) < std::get<2>(e2));
            });


            if (entry_it == cache.end())
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

/// Emulator translation cache, used to speed up virtual address translation.
/// Based around the MIPS translation process, using the current mode.
template<size_t Size, typename AddressTy>
class TranslationCache
{
public:
    typedef std::function<bool(const AddressTy, const MmuAccess, AddressTy&)> FallbackFn;
    typedef ArrayLruCache<Size, AddressTy, AddressTy> Cache;

    bool lookup(const OperatingContext context, const AddressTy virtual_address, const MmuAccess access, AddressTy & physical_address, const FallbackFn & fallback_lookup)
    {
        const AddressTy va_masked_4kb = virtual_address & (~static_cast<AddressTy>(0xFFF));

        Cache * cache;
        switch (context)
        {
        case OperatingContext::User:
            cache = &user_lru_cache; break;
        case OperatingContext::Supervisor:
            cache = &supervisor_lru_cache; break;
        case OperatingContext::Kernel:
            cache = &kernel_lru_cache; break;
        default:
            throw std::runtime_error("Unrecognised operating context");
        }

        AddressTy pa_masked_4kb;
        std::optional<AddressTy> result = cache->get(va_masked_4kb);
        if (!result)
        {
            if (fallback_lookup(va_masked_4kb, access, pa_masked_4kb))
                return true;
            cache->insert(va_masked_4kb, pa_masked_4kb);
        }
        else
        {
            pa_masked_4kb = *result;
        }

        physical_address = pa_masked_4kb | (virtual_address & 0xFFF);
        return false;
    }

private:
    Cache user_lru_cache;
    Cache supervisor_lru_cache;
    Cache kernel_lru_cache;
};