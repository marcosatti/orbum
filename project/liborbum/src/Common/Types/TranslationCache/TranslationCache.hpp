#pragma once

#include <functional>
#include <utility>
#include <Caches.hpp>

#include "Common/Types/Mips/MipsCoprocessor0.hpp"
#include "Common/Types/Mips/MmuAccess.hpp"

using OperatingContext = MipsCoprocessor0::OperatingContext;

/// Emulator translation cache, used to speed up virtual address translation.
/// Based around the MIPS translation process, using the current operating
/// context and instruction/data access. This works as there is a minimum TLB
/// page size (ie: 4KB on the EE Core), and everything else is a multiple of it. 
/// The unmapped memory regions are usually aligned to this value (care must be taken).
template<int Size, typename AddressTy, AddressTy CacheMask, template<int, typename, typename> class CacheTy>
class TranslationCache
{
private:
	using CacheTy_ = CacheTy<Size, AddressTy, AddressTy>;

public:
    using FallbackFn = std::function<std::optional<AddressTy>(const AddressTy, const MmuRwAccess, const MmuIdAccess)>;

    /// Performs the virtual address to physical address translation.
    std::optional<AddressTy> lookup(const OperatingContext context, const AddressTy virtual_address, const MmuRwAccess rw_access, const MmuIdAccess id_access, const FallbackFn & fallback_lookup)
    {
        const AddressTy key = virtual_address & (~CacheMask);

		CacheTy_ * cache = nullptr;
		switch (id_access)
		{
		case INSTRUCTION:
			cache = &instruction_cache; break;
		case DATA:
			cache = &data_cache; break;
		default:
			throw std::runtime_error("Unrecognised id_access");
		}

		std::optional<AddressTy> result = cache->get(key);
		if (!result)
		{
			result = fallback_lookup(key, rw_access, id_access);
			if (result)
				cache->insert(key, *result);
		}

        return result ? std::make_optional((*result) | (virtual_address & CacheMask)) : std::nullopt;
    }

    /// Flushes the caches of all translation results.
    void flush()
    {
		instruction_cache = CacheTy_();
		data_cache = CacheTy_();
    }

private:
	CacheTy_ instruction_cache;
	CacheTy_ data_cache;
};