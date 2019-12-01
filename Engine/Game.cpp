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
		goal[i].Init(DistX(rng), DistY(rng));
		goal[i].GridConversion();
		eaten[i] = false;
	}
	Snake.SnakeInit(DistX(rng), DistY(rng));
	Snake.fuckingConversion();
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
			goal[i].Food(Snake);
			if (goal[i].eaten)
			{
				goal[i].NewXY();
				goal[i].GridConversion();
				Snake.Grow();
				Snake.seg[Snake.GetnSegments()].SegmentInit(Snake);
				Snake.SpeedUp();
				goal[i].eaten = false;
				GoObstacle = true;
				if (just_once) {
					nObstacles++;
					just_once = false;
					just_once2 = true;
				}
				once3 = true;
			}
		}
			// Obstacle shit here ONLY INITIALIZATION
			if (GoObstacle) {
				do {
					obstacles[nObstacles].ObstaclesInit();
					obstacles[nObstacles].GridConversion();
					for (int i = 0; i < nGoals; i++) {
						if (obstacles[nObstacles].GetX() == goal[i].GetX() ||
							obstacles[nObstacles].GetY() == goal[i].GetY() ||
							obstacles[nObstacles].GetX() == goal[i].GetX() + grid.GetDimension() ||
							obstacles[nObstacles].GetY() == goal[i].GetY() + grid.GetDimension())
							shitt = true;
						else shitt = false;
					}
				} while (shitt);
				just_once = true;
				start_drawing = true;
			}
			GoObstacle = false;

			if (just_once2) {   // mixture stuff
				if ((nObstacles + 1) % 6 == 0) { //could be given those  already taken
					bool shitt1;
					do {
						Mixture[nMixtures].NewXY();
						Mixture[nMixtures].GridConversion();

						for (int i = 0; i < nGoals; i++) {
							if (Mixture[nMixtures].GetX() == goal[i].GetX() ||
								Mixture[nMixtures].GetY() == goal[i].GetY() ||
								Mixture[nMixtures].GetX() == goal[i].GetX() + grid.GetDimension() ||
								Mixture[nMixtures].GetY() == goal[i].GetY() + grid.GetDimension())
								shitt1 = true;
							else shitt1 = false;
						}
						for (int i = 0; i < nObstacles; i++) {
							if (Mixture[nMixtures].GetX() == obstacles[i].GetX() ||
								Mixture[nMixtures].GetY() == obstacles[i].GetY() ||
								Mixture[nMixtures].GetX() == obstacles[i].GetX() + grid.GetDimension() ||
								Mixture[nMixtures].GetY() == obstacles[i].GetY() + grid.GetDimension())
								shitt2 = true;
							else shitt2 = false;
						}
					} while (shitt2 || shitt1);
					GoMixture = true; // FALSE WHEN WE EAT IT
					just_once2 = false;
					Mixture[nMixtures].eaten = false;
					nMixtures++;
				}
			}

			for (int i = 0; i <= nMixtures; i++)
			{
				if (Mixture[i].Mixture(Snake))
				{
					Snake.SlowDown();
					Mixture[i].eaten = true;
				}
				//actually I would like to let it stay as a source but make it be surrounded by rocks
			}

			for (int i = 0; i <= nObstacles; i++)
			{
				if (obstacles[i].Mixture(Snake))
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

	if (start_drawing) {
		for (int i = 0; i <= nObstacles; i++)
			obstacles[i].DrawObstacle(gfx);
	}
	if (GoMixture) {
		for (int i = 0; i < nMixtures; i++) {
			if (!Mixture[i].eaten)
			Mixture[i].DrawMixture(gfx);
		}
	}

	if (Snake.GameOver)
		ded.DrawGameOver(gfx);
}
