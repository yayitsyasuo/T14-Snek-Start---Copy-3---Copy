#include "Zeit.h"
#include <cstdlib>
using namespace std::chrono;
Zeit::Zeit()
{
	last = steady_clock::now();
}

float Zeit::TimeMeasure()
{
	steady_clock::time_point now = steady_clock::now();
	duration<float> duration = abs(now - last);
	last = steady_clock::now();
	return duration.count();
}
