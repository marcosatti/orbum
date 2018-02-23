#pragma once

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/TranslationCache/TranslationCache.hpp"

#include "Resources/Ee/Core/EeCoreR5900.hpp"
#include "Resources/Ee/Core/EeCoreCop0.hpp"
#include "Resources/Ee/Core/EeCoreFpu.hpp"
#include "Resources/Ee/Core/EeCoreTlb.hpp"

/// REeCore declares the R5900 structure, co-processors, etc, forming the EE Core.
/// For reference documentation, see the EE Core Users Manual (SCE).
/// VU0 is attached to the EE Core as COP2, declared separately from here.
struct REeCore
{
	REeCore();

	/// R5900 CPU.
	EeCoreR5900 r5900;

	/// COP0 coprocessor.
	EeCoreCop0 cop0;

	/// FPU (COP1) coprocessor.
	EeCoreFpu fpu;

	/// TLB state.
	EeCoreTlb tlb;

	/// Scratchpad memory.
	ArrayByteMemory scratchpad_memory;

    /// Emulator address translation cache.
    TranslationCache<3, uptr> translation_cache;
};
