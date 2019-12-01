#pragma once

#include<chrono>

class Zeit {
public:
	Zeit();
	float TimeMeasure();

private:
	std::chrono::steady_clock::time_point last;


};