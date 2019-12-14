#include "Goal.h"
#include<random>


Goal::Goal()
	:
	DistX1(15, 765),
	DistY1(15, 570),
	rand(seed()),
	gfx(gfx)
{
}

void Goal::DrawObstacle(Grid& grid) const
{
	int i = 0;
	while (i != (grid.Columns* grid.Rows))
	{
		if (grid.HasObstacle[i])
		{
			int Row, Column;
			if (i != 0) {
				Row = i / grid.Columns; // i = 1 938 no nie xD //38
				if (Row != 0)
					Column = i - (Row*grid.Columns);
				else
					Column = i;
			}
			else
			{
				Row = 0;
				Column = 0;
			}
			// gfx.DrawRectDim(15 * Column, 15 * Row, grid.GetDimension(), grid.GetDimension(), c);
			gfx.DrawRect(15 * Column, 15 * Row, 
				15 * Column + grid.GetDimension(), 
				15 * Row+ grid.GetDimension(), c);
		}
		i++;
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
