#pragma once

#include <functional>
#include <utility>
#include <Caches.hpp>

#include "Common/Types/Mips/MipsCoprocessor0.hpp"
#include "Common/Types/Mips/MmuAccess.hpp"

using OperatingContext = MipsCoprocessor0::OperatingContext;

/// Emulator translation cache, used to speed up virtual address translation.
/// Based around the MIPS translation process, using the current mode.
/// This works as the minimum TLB page size is 4KB, and everything else is a
/// multiple of it. Even the unmapped memory regions are aligned to this value.
template<size_t Size, typename AddressTy, AddressTy CacheMask, template<size_t, typename, typename> class LruCacheTy>
class TranslationCache
{
public:
    using FallbackFn = std::function<std::optional<AddressTy>(const AddressTy, const MmuRwAccess, const MmuIdAccess)>;

    /// Performs the virtual address to physical address translation.
    std::optional<AddressTy> lookup(const OperatingContext context, const AddressTy virtual_address, const MmuRwAccess rw_access, const MmuIdAccess id_access, const FallbackFn & fallback_lookup)
    {
        const AddressTy va_masked = virtual_address & (~CacheMask);
		auto key = std::make_pair(va_masked, rw_access);

        LruCacheTy<Size, std::pair<AddressTy, MmuRwAccess>, AddressTy> * cache;
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

        std::optional<AddressTy> result = cache->get(key);
        if (!result)
        {
            result = fallback_lookup(va_masked, rw_access, id_access);
            if (!result)
                return std::nullopt;
            cache->insert(key, *result);
        }

        return std::make_optional((*result) | (virtual_address & CacheMask));
    }

    /// Flushes the caches of all translation results.
    void flush()
    {
        user_lru_cache = LruCacheTy<Size, std::pair<AddressTy, MmuRwAccess>, AddressTy>();
        supervisor_lru_cache = LruCacheTy<Size, std::pair<AddressTy, MmuRwAccess>, AddressTy>();
        kernel_lru_cache = LruCacheTy<Size, std::pair<AddressTy, MmuRwAccess>, AddressTy>();
    }

private:
    LruCacheTy<Size, std::pair<AddressTy, MmuRwAccess>, AddressTy> user_lru_cache;
    LruCacheTy<Size, std::pair<AddressTy, MmuRwAccess>, AddressTy> supervisor_lru_cache;
    LruCacheTy<Size, std::pair<AddressTy, MmuRwAccess>, AddressTy> kernel_lru_cache;
};