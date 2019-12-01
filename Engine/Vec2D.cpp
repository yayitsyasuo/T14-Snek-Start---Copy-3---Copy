#include "Vec2D.h"

Vec2D::Vec2D(float fl_x, float fl_y)
     :
	x (fl_x),
    y (fl_y)
{
}

Vec2D Vec2D::operator+(const Vec2D & rhs) const
{
	return Vec2D(x + rhs.x, y + rhs.y);
}

Vec2D & Vec2D::operator+=(const Vec2D & rhs)
{
	return *this = *this + rhs;
}

Vec2D & Vec2D::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vec2D Vec2D::operator*(float rhs)const
{
	return Vec2D(x * rhs, y*rhs);
}
