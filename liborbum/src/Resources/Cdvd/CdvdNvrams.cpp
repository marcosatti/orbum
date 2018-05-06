#include <stdexcept>

#include "Common/Constants.hpp"
#include "Common/Types/Memory/HwordMemory.hpp"
#include "Resources/Cdvd/CdvdNvrams.hpp"

CdvdNvram::CdvdNvram() :
	memory(Constants::CDVD::SIZE_NVRAM),
	access_read_write(0),
	access_area_index(0),
	access_max_block_index(0),
	access_block_index(0)
{
}

void CdvdNvram::set_access_params(const int read_write, const int area_index, const int max_block_index, const int block_index)
{
	access_read_write = read_write;
	access_area_index = area_index;
	access_max_block_index = max_block_index;
	access_block_index = block_index;
}

void CdvdNvram_000::read_config_block(uhword * buffer)
{
	// Check for read mode (0), return magic values otherwise (TODO: check this, throws error for now).
	if (access_read_write == 0)
	{
		// Check if block is within bounds.
		if ( ((access_area_index == 0) && (access_block_index >= 4))
			|| ((access_area_index == 1) && (access_block_index >= 2))
			|| ((access_area_index == 2) && (access_block_index >= 7)) )
		{
			// Return empty data immediately.
			for (int i = 0; i < 8; i++)
				buffer[i] = 0x0;
		}
		// Check if block is within the max allowed parameter set.
		else if (access_block_index >= access_max_block_index)
		{
			throw std::runtime_error("CDVD read config block was outside of max block parameter set... What is meant to happen?");
		}
		// Ok to read a block. 
		else
		{
			// Remember, there are 8 hwords to a block (which is 16 bytes).
			// The addresses come from PCSX2/CDVD.cpp (transformed from a byte address to a hword address).
			switch (access_area_index)
			{
			case 0:
				memory.read(0x280 / NUMBER_BYTES_IN_HWORD + access_block_index * 8, buffer, 8); break;
			case 1:
				memory.read(0x300 / NUMBER_BYTES_IN_HWORD + access_block_index * 8, buffer, 8); break;
			case 2:
				memory.read(0x200 / NUMBER_BYTES_IN_HWORD + access_block_index * 8, buffer, 8); break;
			default:
				throw std::runtime_error("CDVD read config block tried to read from invalid config area. Please fix.");
			}
			
			// Increment block index.
			access_block_index += 1;
		}
	}
	else
	{
		throw std::runtime_error("CDVD read config block was not in read mode... What is meant to happen?");
		// buffer[0] = 0x80;
		// std::fill(&buffer[1], &buffer[1] + 15, 0x00);
	}
}

void CdvdNvram_000::write_config_block(const uhword * buffer)
{
	// Check for write mode (1), return magic values otherwise (TODO: check this, throws error for now).
	if (access_read_write == 1)
	{
		// Check if block is within bounds.
		if (((access_area_index == 0) && (access_block_index >= 4))
			|| ((access_area_index == 1) && (access_block_index >= 2))
			|| ((access_area_index == 2) && (access_block_index >= 7)))
		{
			throw std::runtime_error("CDVD read config block was outside of bounds... What is meant to happen?");
		}

		// Check if block is within the max allowed parameter set.
		if (access_block_index >= access_max_block_index)
		{
			throw std::runtime_error("CDVD read config block was outside of max block parameter set... What is meant to happen?");
		}

		// Ok to read a block. Remember, there are 8 hwords to a block (which is 16 bytes).
		// The addresses come from PCSX2/CDVD.cpp (transformed from a byte address to a hword address).
		switch (access_area_index)
		{
		case 0:
			memory.write(0x280 / NUMBER_BYTES_IN_HWORD + access_block_index * 8, buffer, 8); break;
		case 1:
			memory.write(0x300 / NUMBER_BYTES_IN_HWORD + access_block_index * 8, buffer, 8); break;
		case 2:
			memory.write(0x200 / NUMBER_BYTES_IN_HWORD + access_block_index * 8, buffer, 8); break;
		default:
			throw std::runtime_error("CDVD read config block tried to read from invalid config area. Please fix.");
		}

		// Increment block index.
		access_block_index += 1;
	}
	else
	{
		throw std::runtime_error("CDVD read config block was not in write mode... What is meant to happen?");
		// buffer[0] = 0x80;
		// std::fill(&buffer[1], &buffer[1] + 15, 0x00);
	}
}

void CdvdNvram_000::read_console_id(uhword * buffer)
{
	memory.read(0x1C8 / NUMBER_BYTES_IN_HWORD, buffer, 4);
}

void CdvdNvram_000::write_console_id(const uhword * buffer)
{
	memory.write(0x1C8 / NUMBER_BYTES_IN_HWORD, buffer, 4);
}

void CdvdNvram_000::read_ilink_id(uhword * buffer)
{
	memory.read(0x1C0 / NUMBER_BYTES_IN_HWORD, buffer, 4);
}

void CdvdNvram_000::write_ilink_id(const uhword * buffer)
{
	memory.write(0x1C0 / NUMBER_BYTES_IN_HWORD, buffer, 4);
}

void CdvdNvram_000::read_model_number(uhword * buffer)
{
	memory.read(0x1A0 / NUMBER_BYTES_IN_HWORD, buffer, 4);
}

void CdvdNvram_000::write_model_number(const uhword * buffer)
{
	memory.write(0x1A0 / NUMBER_BYTES_IN_HWORD, buffer, 4);
}

void CdvdNvram_000::read_region_params(uhword * buffer)
{
	memory.read(0x180 / NUMBER_BYTES_IN_HWORD, buffer, 4);
}

void CdvdNvram_000::write_region_params(const uhword * buffer)
{
	memory.write(0x180 / NUMBER_BYTES_IN_HWORD, buffer, 4);
}

void CdvdNvram_000::read_mac(uhword * buffer)
{
	memory.read(0x198 / NUMBER_BYTES_IN_HWORD, buffer, 4);
}

void CdvdNvram_000::write_mac(const uhword * buffer)
{
	memory.write(0x198 / NUMBER_BYTES_IN_HWORD, buffer, 4);
}

CdvdNvram_000::CdvdNvram_000()
{
	write_ilink_id(reinterpret_cast<const uhword*>(ILINK_DATA_MAGIC));
}