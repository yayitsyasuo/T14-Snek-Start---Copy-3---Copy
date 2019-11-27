#pragma once
#include"Graphics.h"
#include"Colors.h"
#include "Keyboard.h"
#include "Grid.h"

class Snak
{
public:
	class Segment {
	public:
		void Init(int xx, int yy);
		void Draw(Graphics&gfx, int i);
		int x;
		int y;
		int x_previous;
		int y_previous;
		void SegmentInit(Snak&snek);
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
	void SnakeInit(int xxx, int yyy); //
	void SnakDraw(Graphics&gfx) const; //
	void SnakControl(Keyboard&kbd);
	void fuckingConversion(); //
	void KeepOnGoing();
	void Grow();
	void FollowUp(int, int, int*, bool*, bool*, bool*, bool*);
	void Border_Collision();
	void Collision();
	int ReadMeterTimerSpeed() const;
	void SpeedUp();
	void SlowDown();
	int GetnSegments();
	void MeterIncrease();
	int x;
	int y;
	static const int maxSegments=40;
	bool GameOver = false;
	Segment seg[maxSegments];  // important max value here
private:
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
	int meter = 0;
	int meterTimerSpeed=15; //15
};

