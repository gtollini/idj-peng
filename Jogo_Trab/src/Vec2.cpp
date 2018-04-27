#include "../include/Vec2.h"
#include <math.h>

Vec2::Vec2(): x(0), y(0){
}

Vec2::Vec2(float X, float Y):x(X), y(Y){
}


Vec2 Vec2::GetRotated(float theta){
	return Vec2(x*cos(theta) + y*sin(theta), y*cos(theta) + x*sin(theta));
}

Vec2 Vec2::operator+(const Vec2 a){
	Vec2 b;
	b.x=this->x+a.x;
	b.y=this->y+a.y;
	return b;
}

Vec2 Vec2::operator*(const float a){
	Vec2 b;
	b.x=this->x*a;
	b.y=this->y*a;
	return b;
}
