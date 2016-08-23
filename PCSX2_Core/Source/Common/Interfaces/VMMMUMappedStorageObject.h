#pragma once

#include "Common/Global/Globals.h"

/*
Interface class used for exposing a base client memory address, so it can be used in mapping (through the VM MMU).
*/

class VMMMUMappedStorageObject
{
public:
	virtual ~VMMMUMappedStorageObject()
	{
	}

	/*
	Gets the client memory address as a pointer to the base address of where to start mapping.
	*/
	virtual void * getClientMemoryAddress()
	{
		return nullptr;
	}

	/*
	Gets the client memory length, starting from the base memory address defined in the getClientMemoryAddress() function.
	*/
	virtual size_t getClientMemoryLength()
	{
		return 0;
	}
};