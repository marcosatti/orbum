#pragma once

#include <memory>

class Register16_t;

/*
SIO0 resources.
Responsible for communication with controllers and memory cards.
*/
class SIO0_t
{
public:
	SIO0_t();

	/*
	SIO0 Registers.
	*/
	std::shared_ptr<Register16_t> DATA;
	std::shared_ptr<Register16_t> STAT;
	std::shared_ptr<Register16_t> MODE;
	std::shared_ptr<Register16_t> CTRL;
};