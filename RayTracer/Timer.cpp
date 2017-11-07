#include "Timer.h"

using namespace std::chrono;

Timer::Timer():
	start(steady_clock::now())
{
}

void Timer::restart()
{
    start = steady_clock::now();
}

nanoseconds Timer::getDuration()
{
	steady_clock::time_point end = steady_clock::now();
	return end - start;
}
