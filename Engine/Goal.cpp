#include "Goal.h"
#include<random>


Goal::Goal()
	:
	DistX1(15, 765),
	DistY1(15, 570),
	rand(seed())
{
}

void Goal::DrawObstacle(Graphics&gfx) const
{
	int i = 0;
	while (i != (grid.GridPositionsX* grid.GridPositionsY))
	{
		int Row = i / grid.GridPositionsX;
		int Column = i % Row;
		if(grid.HasObstacle[i]==true)
			gfx.DrawRectDim(15*(Column-1), 15*(Row-1), grid.GetDimension(), grid.GetDimension(), Colors::Gray);
	}
}

void Goal::Init3(Vec2D obstaacle_pos)
{
	pos = Vec2D(DistX1(rand), DistY1(rand));
	GridConversion();
	if (pos == obstaacle_pos)
		Init3(obstaacle_pos);
}


void Goal::Init()
{
	pos = Vec2D(DistX1(rand), DistY1(rand));
	GridConversion();
}

void Goal::Draw(Graphics&gfx)const
{
	gfx.DrawRectDim(pos.x,pos.y, grid.GetDimension(), grid.GetDimension(), Colors::Red);
}

void Goal::DrawMixture(Graphics & gfx) const
{
	gfx.DrawRectDim(pos.x, pos.y, grid.GetDimension(), grid.GetDimension(), Colors::Green);
}

void Goal::GridConversion()
{
	pos = Vec2D(pos.x / grid.GetDimension(), pos.y / grid.GetDimension());
	pos *= grid.GetDimension();
}


Vec2D Goal::GetPos() const
{
	return pos;
}

bool Goal::Collision(Snak& snek)
{
	const int goal_right_side = pos.x + grid.GetDimension();
	const int goal_down_side = pos.y + grid.GetDimension();
	const int snek_right_side = snek.pos.x + grid.GetDimension();
	const int snek_down_side = snek.pos.y + grid.GetDimension();

	return (snek_right_side > pos.x &&
		snek.pos.x < goal_right_side &&
		snek_down_side > pos.y &&
		snek.pos.y < goal_down_side);
}

void Goal::SamePosition(Vec2D goal_pos)
{
	if (pos == goal_pos)
	Init();
}
