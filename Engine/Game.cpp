/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(std::random_device()()),
	DistX(15, 765),
	DistY(15, 565)
{
	for (int i = 0; i < nGoals; ++i)
	{
		goal[i].Init();
		goal[i].GridConversion();
	}
	Snake.SnakeInit(Vec2D (DistX(rng), DistY(rng)));
	Snake.fuckingConversion();
	Snake.seg[0].Init(Vec2D (Snake.pos.x + grid.GetDimension(), Snake.pos.y));
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dT = Zeit.TimeMeasure();  // time it takes for every frame to happen  dT

	if (!Snake.GameOver) {
		Snake.SnakControl(wnd.kbd);
		for (int i = 0; i < nGoals; ++i)
		{
			if (goal[i].Collision(Snake))
			{
				goal[i].Init();
				Snake.Grow();
				Snake.seg[Snake.GetnSegments()].SegmentInit(Snake);
				Snake.SpeedUp();
				nObstacles++;
				obstacles[nObstacles].Init(); // goal function init obstaacle here
				for(int g=0; g<= nGoals; g++)
				obstacles[nObstacles].SamePosition(goal[g].pos);
			}
		}


		TimeSum += dT; // timer count
		if (TimeSum >= 8.0f) {
			nMixtures++;
			Mixture[nMixtures].Init();
			for (int g = 0; g <= nGoals; g++)
			Mixture[nMixtures].SamePosition(goal[g].pos);
			for (int i =0; i<= nObstacles; i++)
				Mixture[nMixtures].Init3(goal[i].pos);
			TimeSum = 0;
		}

        
        for (int i = 0; i <= nMixtures; i++)
        {
        	if (Mixture[i].Collision(Snake))
        	{
        		Snake.SlowDown();
        		Mixture[i].eaten = true;
        	}
        	//actually I would like to let it stay as a source but make it be surrounded by rocks
        }
        
        for (int i = 0; i <= nObstacles; i++)
        {
        	if (obstacles[i].Collision(Snake))
        		Snake.GameOver = true;
        }

        Snake.KeepOnGoing(dT);
        Snake.Collision();
        Snake.Border_Collision();
        }
}


void Game::ComposeFrame()
{
	for (int i = 0; i < nGoals; ++i)
		goal[i].Draw(gfx);
	
	grid.Borders(gfx);

	for (int i = 0; i <= Snake.GetnSegments(); ++i) 
		Snake.seg[i].Draw(gfx, i);

	Snake.SnakDraw(gfx);

	for (int i = 0; i <= nObstacles; i++)
		obstacles[i].DrawObstacle(gfx);

	for (int i = 0; i <= nMixtures; i++) {
		if (!Mixture[i].eaten)
		Mixture[i].DrawMixture(gfx);
	}
	

	if (Snake.GameOver)
		ded.DrawGameOver(gfx);
}
