#pragma once
#include"Graphics.h"

class Grid
{
public:
	int GetDimension()const;
	void Borders(Graphics &gfx) const;
	static const int Border = 15;
private:
	static const int dimension = 15;// this nibba decides for all
};

