#pragma once
#include "Graphics.h"
#include "Colors.h"
#include<random>
#include"Snak.h"
#include"Grid.h"
#include"Graphics.h"
#include "Vec2D.h"

class Goal
{
public:
	Goal();
	void DrawObstacle(Graphics&gfx) const;
	void Init2(Vec2D goal_pos1, Vec2D goal_pos2, Vec2D goal_pos3, Vec2D goal_pos4);
	void Init3(Vec2D obstaacle_pos);
	void Init();
	void Draw(Graphics&gfx)const;
	void DrawMixture(Graphics&gfx)const;
	void GridConversion();
	bool Collision(Snak &snek);

	int nMixtures = 0;
	Vec2D GetPos()const;
	void Food(Snak& snek);
	bool eaten = false;
	std::random_device seed;
	std::mt19937 rand;
	std::uniform_int_distribution<int> DistX1;
	std::uniform_int_distribution<int> DistY1;
	Vec2D pos;
	Snak snek;
	Grid grid;

};

