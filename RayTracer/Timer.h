#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
    void restart();
    std::chrono::nanoseconds getDuration();
private:
	std::chrono::steady_clock::time_point start;
};

