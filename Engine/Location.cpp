#include "Location.h"

Location::Location(int n_x, int n_y)
{
	x = n_x;
	y = n_y;
}

void Location::fuckingConversion()
{
		int xn;
		xn = x / grid.GetDimension();
		int yn;
		yn = y / grid.GetDimension();
		x = xn * grid.GetDimension();
		y = yn * grid.GetDimension();
}
