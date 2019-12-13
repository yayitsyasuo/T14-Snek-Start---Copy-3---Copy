#pragma once
#include"Graphics.h"
#include "Vec2D.h"
#include <random>

class Grid
{
public:
	int GetDimension()const;
	void Borders(Graphics &gfx) const;
	static const int Border = 15;
	void OnGridPosInit(std::mt19937& rng);
	Vec2D OnGridPos;
	static constexpr int dimension = 15;// this nibba decides for all
	static constexpr int GridPositionsX= 765 / dimension;
	static constexpr int GridPositionsY = 570 / dimension;
	bool HasObstacle[GridPositionsX*GridPositionsY] = { false };

};

