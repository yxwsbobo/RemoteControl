#pragma once

#include <atomic>

class RunningTC
{
public:
	explicit RunningTC( std::atomic_int32_t& Common )
		:Count{ Common }
	{
		++Count;
	}

	~RunningTC()
	{
		--Count;
	}

private:
	std::atomic_int32_t& Count;
};