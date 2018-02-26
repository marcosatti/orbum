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
template<int UserInstructionSize, int UserDataSize, 
	     int SupervisorInstructionSize, int SupervisorDataSize, 
	     int KernelInstructionSize, int KernelDataSize,
		 typename AddressTy, 
	     AddressTy CacheMask, 
	     template<int, typename, typename> class CacheTy>
class TranslationCache
{
private:
	using UserInstructionCacheTy = CacheTy<UserInstructionSize, AddressTy, AddressTy>;
	using UserDataCacheTy = CacheTy<UserDataSize, AddressTy, AddressTy>;
	using SupervisorInstructionCacheTy = CacheTy<SupervisorInstructionSize, AddressTy, AddressTy>;
	using SupervisorDataCacheTy = CacheTy<SupervisorDataSize, AddressTy, AddressTy>;
	using KernelInstructionCacheTy = CacheTy<KernelInstructionSize, AddressTy, AddressTy>;
	using KernelDataCacheTy = CacheTy<KernelDataSize, AddressTy, AddressTy>;

public:
    using FallbackFn = std::function<std::optional<AddressTy>(const AddressTy, const MmuRwAccess, const MmuIdAccess)>;

    /// Performs the virtual address to physical address translation.
    std::optional<AddressTy> lookup(const OperatingContext context, const AddressTy virtual_address, const MmuRwAccess rw_access, const MmuIdAccess id_access, const FallbackFn & fallback_lookup)
    {
        const AddressTy key = virtual_address & (~CacheMask);

		// Neat way to reuse code for templates... :)
		auto cache_lookup_template = [&](auto& cache) -> std::optional<AddressTy>
		{
			std::optional<AddressTy> result = cache.get(key);
			if (!result)
			{
				result = fallback_lookup(key, rw_access, id_access);
				if (!result)
					return std::nullopt;
				cache.insert(key, *result);
			}
			return result;
		};

		std::optional<AddressTy> result = std::nullopt;
        switch (context)
        {
		case OperatingContext::User:
		{
			switch (id_access)
			{
			case INSTRUCTION:
				result = cache_lookup_template(user_instruction_cache); break;
			case DATA:
				result = cache_lookup_template(user_data_cache); break;
			default:
				throw std::runtime_error("Unrecognised id_access");
			}
			break;
		}
		case OperatingContext::Kernel:
		{
			switch (id_access)
			{
			case INSTRUCTION:
				result = cache_lookup_template(kernel_instruction_cache); break;
			case DATA:
				result = cache_lookup_template(kernel_data_cache); break;
			default:
				throw std::runtime_error("Unrecognised id_access");
			}
			break;
		}
        case OperatingContext::Supervisor:
		{
			switch (id_access)
			{
			case INSTRUCTION:
				result = cache_lookup_template(supervisor_instruction_cache); break;
			case DATA:
				result = cache_lookup_template(supervisor_data_cache); break;
			default:
				throw std::runtime_error("Unrecognised id_access");
			}
			break;
		}
        default:
		{
			throw std::runtime_error("Unrecognised operating context");
		}
        }

        return result ? std::make_optional((*result) | (virtual_address & CacheMask)) : std::nullopt;
    }

    /// Flushes the caches of all translation results.
    void flush()
    {
		user_instruction_cache = UserInstructionCacheTy();
		user_data_cache = UserDataCacheTy();
		supervisor_instruction_cache = SupervisorInstructionCacheTy();
		supervisor_data_cache = SupervisorDataCacheTy();
		kernel_instruction_cache = KernelInstructionCacheTy();
		kernel_data_cache = KernelDataCacheTy();
    }

private:
	UserInstructionCacheTy user_instruction_cache;
	UserDataCacheTy user_data_cache;
	SupervisorInstructionCacheTy supervisor_instruction_cache;
	SupervisorDataCacheTy supervisor_data_cache;
	KernelInstructionCacheTy kernel_instruction_cache;
	KernelDataCacheTy kernel_data_cache;
};