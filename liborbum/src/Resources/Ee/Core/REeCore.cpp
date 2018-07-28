#include "Resources/Ee/Core/REeCore.hpp"

#include "Common/Constants.hpp"

REeCore::REeCore() :
    scratchpad_memory(Constants::EE::EECore::ScratchpadMemory::SIZE_SCRATCHPAD_MEMORY)
{
}