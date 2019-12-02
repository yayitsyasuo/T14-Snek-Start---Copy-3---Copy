#include "Snak.h"
#include "Segment.h"

void Snak::fuckingConversion()
{
	float xn;
	xn = pos.x / grid.GetDimension();
	float yn;
	yn = pos.y / grid.GetDimension();
	pos.x = xn * grid.GetDimension();
	pos.y = yn * grid.GetDimension();
	seg[0].Init(pos);
}

void Snak::SnakeInit(Vec2D &pos_in)
{
	pos = pos_in;
}

void Snak::SnakDraw(Graphics & gfx) const
{
	for (int c = 1; c < 14; c++) 
		for (int d = 1; d < 14; d++) 
				gfx.PutPixel(pos.x + c, pos.y + d, Colors::Yellow);
}

void Snak::SnakControl(Keyboard&kbd)
{
		if (kbd.KeyIsPressed(0x57) && !WeGoinDown)// W
		{
				GoW = true;
				GoA = false;
				GoS = false;
				GoD = false;
		}
		else if ((kbd.KeyIsPressed(0x41) && !WeGoinRight) || WpressedStimulation)// A
		{
				GoA = true;
				GoW = false;
				GoS = false;
				GoD = false;
				WpressedStimulation = false;
		}
		else if (kbd.KeyIsPressed(0x44) && !WeGoinLeft)// D
		{
				GoD = true;
				GoA = false;
				GoS = false;
				GoW = false;
		}
		else if (kbd.KeyIsPressed(0x53) && !WeGoinUp)// S
		{
				GoS = true;
				GoA = false;
				GoW = false;
				GoD = false;
		}
}

void Snak::KeepOnGoing(float dT)
{
	Zeit += dT;
	if (Zeit >= TimeForOneMove) {
		once = true;
		for (int i = 0; i <= nSegments; i++) { //MODERN VERSION <3
			if (GoW)
				FollowUp(i, -1, pos.x, &WeGoinUp, &WeGoinDown, &WeGoinRight, &WeGoinLeft);
			else if (GoS)
				FollowUp(i, 1, pos.x, &WeGoinDown, &WeGoinUp, &WeGoinLeft, &WeGoinRight); // true false false false
			else if (GoA)
				FollowUp(i, -1, pos.y, &WeGoinLeft, &WeGoinRight, &WeGoinUp, &WeGoinDown);
			else if (GoD)
				FollowUp(i, 1, pos.y, &WeGoinRight, &WeGoinLeft, &WeGoinUp, &WeGoinDown);
		}
		Zeit = 0;
	}
}

void Snak::Grow()
{
	nSegments++;
}

void Snak::Border_Collision()
{

int SnakeRightSide = pos.x + grid.GetDimension();
int SnakeDownSide = pos.y + grid.GetDimension();

	if (pos.x <= grid.Border - 1 || pos.y <= grid.Border - 1 ||
	SnakeRightSide >= 800 - grid.Border + 1 ||
	SnakeDownSide >= 600 - grid.Border + 1)
	GameOver = true;
	
}

void Snak::Collision()
{
	int SnakeRightSide = pos.x + grid.GetDimension();
	int SnakeDownSide = pos.y + grid.GetDimension();

	for (int i = 0; i <= nSegments; i++)
	{
		if (SnakeRightSide > seg[i].x &&
			pos.x < seg[i].x + grid.GetDimension() &&
			SnakeDownSide > seg[i].y &&
			pos.y < seg[i].y + grid.GetDimension()) {
			GameOver=true;
		}
	}
		
}

void Snak::Segment::PositionSave()
{
	x_previous = x;
	y_previous = y;
}

float Snak::ReadTimeForOneMove() const
{
	return TimeForOneMove;
}

void Snak::SpeedUp()
{
	TimeForOneMove -= 0.015f;
}

void Snak::SlowDown()
{
	TimeForOneMove = 0.13f;
}

int Snak::GetnSegments()
{
	return nSegments;
}

void Snak::Segment::SegmentInit(Snak&snek)
{
		x = snek.seg[snek.nSegments-1].x;
		y = snek.seg[snek.nSegments - 1].y;
}

void Snak::Segment::Init(Vec2D &pos)
{
	x = pos.x + grid.GetDimension();
	y = pos.y;
}

void Snak::Segment::Draw(Graphics & gfx, int i)
{
	for (int c=1; c < 14; c++) {
		for (int d = 1; d < 14; d++) {
			if (i % 4==0)
				gfx.PutPixel(x + c, y + d, color[0][0], color[0][1], color[0][2]);
			else if (i % 3==0)
				gfx.PutPixel(x + c, y + d, color[1][0], color[1][1], color[1][2]);
			else if (i % 2==0)
				gfx.PutPixel(x + c, y + d, color[2][0], color[2][1], color[2][2]);
			else
				gfx.PutPixel(x + c, y + d, color[3][0], color[3][1], color[3][2]);
		}
	}
	//gfx.DrawRectDim(x,y,grid.GetDimension(),grid.GetDimension(), );
}

void Snak::FollowUp(int i, int G, float direction, bool *Direction, bool *DirectionFalse, bool*d, bool*d2)
{
	seg[i].PositionSave();
	if (i != 0)
	{
		seg[i].x = seg[i - 1].x_previous;
		seg[i].y = seg[i - 1].y_previous;
	}
	else
	{
	seg[0].x = pos.x;
	seg[0].y = pos.y;
	}
	if (once) {
	direction += grid.GetDimension() *G;
	once = false;
	*Direction = true;
	*DirectionFalse = false;
	*d = false;
	*d2 = false;
	}
}

