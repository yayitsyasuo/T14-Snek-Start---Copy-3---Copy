#include "Zeit.h"

using namespace std::chrono;
Zeit::Zeit()
{
	last = steady_clock::now();
}

float Zeit::TimeMeasure()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> duration = last - old;
	return duration.count();
}
