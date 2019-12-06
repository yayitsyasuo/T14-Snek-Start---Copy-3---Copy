#pragma once

#include<chrono>

class Zeit {
public:
	Zeit(); // gets executed once we create a Zeit object in Game.h
	float TimeMeasure();

private:
	std::chrono::steady_clock::time_point last;
};