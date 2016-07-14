#include "stdafx.h"

#include <memory>

#include "Globals.h"
#include "PS2Resources_t.h"

using namespace std;

void scopeFunction5(shared_ptr<PS2Resources_t> resources1)
{
	for (u32 i = 0; i < 32; i++)
	{
		resources1->EE.EECore.R5900.GPR[i % 32].UW[i % 4] = i;
	}
}

void bad_memory_leak()
{
	PS2Resources_t * memleak = new PS2Resources_t();
}

int main(int argc, char *argv[])
{
	shared_ptr<PS2Resources_t> resources = make_shared<PS2Resources_t>();

	for (u32 i = 0; i < 10000; i++)
	{
		scopeFunction5(resources);
	}

	for (u32 i = 0; i < 100; i++)
	{
		bad_memory_leak();
	}

	return 0;
}

