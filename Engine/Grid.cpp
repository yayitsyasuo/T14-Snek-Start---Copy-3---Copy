#include "Grid.h"

int Grid::GetDimension() const
{
	return dimension;
}

void Grid::Borders(Graphics &gfx) const
{
	for (int i = Border - 1; i <= 600 - Border + 1; i++) //left
	{
		gfx.PutPixel(Border - 1, i, Colors::Blue);
	}
	for (int i = 780; i >= Border - 1; i--) //up
	{
		gfx.PutPixel(i, Border - 1, Colors::Blue);
	}
	for (int i = Border; i <= 780; i++) //down
	{
		gfx.PutPixel(i, 585, Colors::Blue);
	}
	for (int i = Border ; i <= 584; i++) //right
	{
		gfx.PutPixel(780 , i, Colors::Blue);
	}
}

void Grid::OnGridPosInit(std::mt19937 & rng)
{
	std::uniform_int_distribution<int> GridPosXInit(0, GridPositionsX);
	std::uniform_int_distribution<int> GridPosYInit(0, GridPositionsY);
	OnGridPos=(Vec2D(GridPosXInit(rng), GridPosYInit(rng)));

	HasObstacle[GridPositionsX* OnGridPos.y + OnGridPos.x] = true; //BIG GUY
}



