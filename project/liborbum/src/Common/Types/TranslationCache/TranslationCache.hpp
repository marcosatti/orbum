#pragma once

#include <functional>
#include <Caches.hpp>

#include "Common/Types/Mips/MipsCoprocessor0.hpp"
#include "Common/Types/Mips/MmuAccess.hpp"

using OperatingContext = MipsCoprocessor0::OperatingContext;

/// Emulator translation cache, used to speed up virtual address translation.
/// Based around the MIPS translation process, using the current mode.
/// This works as the minimum TLB page size is 4KB, and everything else is a
/// multiple of it. Even the unmapped memory regions are aligned to this value.
template<size_t Size, typename AddressTy, template<size_t, typename, typename> class LruCacheTy>
class TranslationCache
{
public:
    using FallbackFn = std::function<bool(const AddressTy, const MmuAccess, AddressTy&)>;

    bool lookup(const OperatingContext context, const AddressTy virtual_address, const MmuAccess access, AddressTy & physical_address, const FallbackFn & fallback_lookup)
    {
        const AddressTy va_masked_4kb = virtual_address & (~static_cast<AddressTy>(0xFFF));

        LruCacheTy<Size, AddressTy, AddressTy> * cache;
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
    LruCacheTy<Size, AddressTy, AddressTy> user_lru_cache;
    LruCacheTy<Size, AddressTy, AddressTy> supervisor_lru_cache;
    LruCacheTy<Size, AddressTy, AddressTy> kernel_lru_cache;
};