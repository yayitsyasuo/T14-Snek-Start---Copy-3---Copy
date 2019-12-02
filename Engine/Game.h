/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Snak.h"
#include <random>
#include "Grid.h"
#include "Goal.h"
#include"OnScreen.h"
#include "Zeit.h"



class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	std::mt19937 rng;
	std::uniform_int_distribution<int> DistX;
	std::uniform_int_distribution<int> DistY;
	
	/********************************/
	/*  User Variables              */
	Snak Snake;
	
	static constexpr int nGoals = 5;
	static constexpr int nMaxObstacles = 40;
	static constexpr int MaxMixtures= 5;
	Goal goal[nGoals];
	Goal obstacles[nMaxObstacles];
	Goal Mixture[MaxMixtures];
	int nObstacles=0;
	int nMixtures = 0;
	Grid grid;
	OnScreen ded;
	Zeit Zeit;


	bool GoObstacle = false;
	bool eaten[nGoals];
	bool shitt = false;
	bool shitt2 = false;
	bool just_once = false;
	bool start_drawing = false;
	bool GoMixture = false;
	bool just_once2 = false;
	bool once3 = false;
	
	
	
	/********************************/
};