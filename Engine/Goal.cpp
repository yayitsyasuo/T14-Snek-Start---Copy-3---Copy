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
	gfx.DrawRectDim(pos.x,pos.y,grid.GetDimension(), grid.GetDimension(), Colors::Gray);
}

void Goal::Init2(Vec2D goal_pos1, Vec2D goal_pos2, Vec2D goal_pos3, Vec2D goal_pos4 )
{
	pos = Vec2D(DistX1(rand), DistY1(rand));
	GridConversion();
	if (pos == goal_pos1 || pos == goal_pos2 || pos == goal_pos3 || pos == goal_pos4)
		Init2(goal_pos1, goal_pos2, goal_pos3, goal_pos4);
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
