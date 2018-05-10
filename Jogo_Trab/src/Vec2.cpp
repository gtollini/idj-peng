#include "../include/Vec2.h"
#include <math.h>

Vec2::Vec2(): x(0), y(0){
}


Vec2::Vec2(float X, float Y):x(X), y(Y){
}

Vec2::Vec2(float X, float Y, float W){
	this->x = X*cos(W) + Y*sin(W);
	this->y = Y*cos(W) + X*sin(W);
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

Vec2 Vec2::operator+(const float a){
	Vec2 b;
	b.x=this->x+a;
	b.y=this->y+a;
	return b;
}

Vec2 Vec2::operator*(const float a){
	Vec2 b;
	b.x=this->x*a;
	b.y=this->y*a;
	return b;
}

Vec2 Vec2::operator-(const Vec2 a){
	Vec2 b;
	b.x=this->x-a.x;
	b.y=this->y-a.y;
	return b;
}

void Vec2::operator=(const Vec2 a){
	this->x=a.x;
	this->y=a.y;
}

bool Vec2::operator==(const Vec2 a){
	return this->x==a.x && this->y==a.y;
}

bool Vec2::operator>=(const Vec2 a){
	return this->x>=a.x && this->y>=a.y;
}

bool Vec2::operator<=(const Vec2 a){
	return (this)->Abs() <= sqrt(a.x*a.x + a.y*a.y);
}




float Vec2::Abs(){
	return sqrt(this->x*this->x + this->y*this->y);
}



Vec2 Vec2::Uni(){
	Vec2 b;
	b.x=this->x/this->Abs();
	b.y=this->y/this->Abs();
	return b;
}

