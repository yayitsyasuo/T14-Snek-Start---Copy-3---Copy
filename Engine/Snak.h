#pragma once
#include"Graphics.h"
#include"Colors.h"
#include "Keyboard.h"
#include "Grid.h"
#include "Vec2D.h"

class Snak
{
public:
	class Segment {
	public:
		void Init(Vec2D pos);
		void Draw(Graphics&gfx, int i);
		Vec2D segpos; //position of the segment
		//int x;
		//int y;
		//int x_previous;
		//int y_previous;
		Vec2D segpos_previous;
		void SegmentInit(const Snak& seg);
		void PositionSave();
		// void Color(int i); xD couldn't initialize in .cpp
		Grid grid;
		int color[4][3] = {
		{ 10,100,32 },
		{ 10,130,48 },
		{ 18,160,48 },
		{ 10,130,48 }
		};
	};

public:
	void SnakeInit(Vec2D &pos_in); //
	void SnakDraw(Graphics&gfx) const; //
	void SnakControl(Keyboard&kbd);
	void fuckingConversion(); //
	void KeepOnGoing(float dT);
	void Grow();
	void FollowUp(int/* , bool*, bool*, bool*, bool* */);
	void Border_Collision();
	void Collision();
	float ReadTimeForOneMove() const;
	void SpeedUp();
	void SlowDown();
	int GetnSegments();
	void Set_pos_previous();
	// int x;
	// int y;
	static const int maxSegments=40;
	bool GameOver = false;
	Segment seg[maxSegments];  // important max value here
public:
	bool once;
	bool GoW=false;
	bool GoA = false;
	bool GoD = false;
	bool GoS = false;
	bool WeGoinRight;
	bool WeGoinLeft;
	bool WeGoinUp=false;
	bool WeGoinDown=false;
	bool WpressedStimulation = true;
	int nSegments = 0;
	Grid grid;
	Vec2D pos; 
	Vec2D pos_previous;
	float Zeit= 0;
	float TimeForOneMove=0.17f; // used to be 15 frames?
};

