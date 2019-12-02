#include "Goal.h"
#include<random>


void Goal::DrawObstacle(Graphics&gfx) const
{
	gfx.DrawRectDim(x,y,grid.GetDimension(), grid.GetDimension(), Colors::Gray);
}

void Goal::ObstaclesInit()
{
	std::mt19937 rand(seed());
	std::uniform_int_distribution<int> DistX1(15, 765);
	std::uniform_int_distribution<int> DistY1(15, 570);
	x = DistX1(rand);
	y = DistY1(rand);
}

void Goal::Init(int xn, int yn)
{
	x = xn;
	y = yn;
}

void Goal::Draw(Graphics&gfx)const
{
	gfx.DrawRectDim(x,y, grid.GetDimension(), grid.GetDimension(), Colors::Red);
}

void Goal::DrawMixture(Graphics & gfx) const
{
	gfx.DrawRectDim(x, y, grid.GetDimension(), grid.GetDimension(), Colors::Green);
}

void Goal::GridConversion()
{
	int xn;
	xn = x /grid.GetDimension();
	int yn;
	yn =y / grid.GetDimension();
	x = xn *grid.GetDimension();
	y = yn *grid.GetDimension();
}


int Goal::GetX() const
{
	return x;
}

int Goal::GetY() const
{
	return y;
}

void Goal::NewXY()
{

	std::mt19937 rand(seed());
	std::uniform_int_distribution<int> DistX1(15, 765);
	std::uniform_int_distribution<int> DistY1(15, 570);
	x = DistX1(rand);
	y = DistY1(rand);
}

void Goal::Food(Snak& snek)
{
	const int goal_right_side = x + grid.GetDimension();
	const int goal_down_side = y + grid.GetDimension();
	const int snek_right_side = snek.pos.x + grid.GetDimension();
	const int snek_down_side = snek.pos.y + grid.GetDimension();

	if (snek_right_side > x &&
		snek.pos.x < goal_right_side &&
		snek_down_side > y &&
		snek.pos.y < goal_down_side) {
		eaten = true;
	}
}

bool Goal::Mixture(Snak& snek)
{
	const int goal_right_side = x + grid.GetDimension();
	const int goal_down_side = y + grid.GetDimension();
	const int snek_right_side = snek.pos.x + grid.GetDimension();
	const int snek_down_side = snek.pos.y + grid.GetDimension();

	return (snek_right_side > x &&
		snek.pos.x < goal_right_side &&
		snek_down_side > y &&
		snek.pos.y < goal_down_side);
}

