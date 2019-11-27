#pragma once
#include "Graphics.h"
#include "Colors.h"
#include<random>
#include"Snak.h"
#include"Grid.h"
#include"Graphics.h"
class Goal
{
public:
	void DrawObstacle(Graphics&gfx) const;
	void ObstaclesInit();
	void Init(int xn, int yn);
	void Draw(Graphics&gfx)const;
	void DrawMixture(Graphics&gfx)const;
	void GridConversion();
	bool Mixture(Snak &snek);

	int GetX()const;
	int GetY() const;
	void Food(Snak& snek);
	void NewXY();
	bool eaten = false;

private:
	std::random_device seed;
	int x;
	int y;
	Snak snek;
	Grid grid;

};

