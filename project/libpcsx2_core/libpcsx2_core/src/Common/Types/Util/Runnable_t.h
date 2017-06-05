#pragma once

/*
Runnable interface - represents a object which can run and update a state.
*/
class Runnable_t
{
public:
	virtual ~Runnable_t() = default;
	virtual void run() = 0;
};