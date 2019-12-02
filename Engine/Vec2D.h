#pragma once
class Vec2D
{
public:
	Vec2D() = default; // generate the default DO NOTHING constructor
	Vec2D(int fl_x, int fl_y);
	Vec2D operator + (const Vec2D &rhs) const; // lfs = rhs
	Vec2D& operator += (const Vec2D &rhs); // no more const, we are changing the left side
	Vec2D operator *(float rhs)const;
	Vec2D& operator *=(float rhs);
public:
	int x;
	int y;

};

