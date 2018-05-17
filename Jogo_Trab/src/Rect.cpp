#include "../include/Rect.h"
#include <math.h>
#include "../include/Vec2.h"

Rect::Rect (){
	x=0;
	y=0;
	w=0;
	h=0;
}
Rect::Rect(float X, float Y, float W, float H){
	x=X;
	y=Y;
	w=W;
	h=H;
}

Rect* Rect::add (Rect a, Rect b){
	return new Rect(a.x+b.x, a.y+b.y, a.w+b.w, a.h+b.h);
}

Rect* Rect::sub (Rect a, Rect b){
	return new Rect(a.x-b.x, a.y-b.y, a.w-b.w, a.h-b.h);
}

Rect* Rect::esc_mul (float a, Rect b){
	return new  Rect(a*b.x, a*b.y, a*b.w, a*b.h);
}

float Rect::abs(Rect a){
	return sqrt(a.x*a.x+a.y*a.y+a.w*a.w+a.h*a.h);
}

Rect* Rect::uni ( Rect b){
	float absb=abs(b);
	return new  Rect(b.x/absb, b.y/absb, b.w/absb, b.h/absb);
}

float Rect::dist (Rect a, Rect b){
	Rect *c=sub(a, b);
	float d = abs(*c);
	delete c;
	return d;
}

bool Rect::Contains (float a, float b){
	return (a-x<=w && b-y<=h)?(a-x>=0 && b-y>=0):(false);
}


Vec2 Rect::Pos(){
	Vec2 a;
	a.x=this->x;
	a.y=this->y;
	return a;
}


void Rect::SetPos(float x, float y){
	this->x=x;
	this->y=y;
};

void Rect::SetPos(Vec2 a){
	this->x=a.x;
	this->y=a.y;
};

Rect Rect::operator +(Vec2 a){
	Rect b;
	b.x+=a.x;
	b.y+=a.y;
	b.h=this->h;
	b.w=this->w;
	return b;
}

void Rect::Center(){
	this->x=this->x-this->h/2;
	this->y=this->y-this->w/2;

}

void Rect::CenterRot(float a, float b, float c, float d){
	this->x= a - c*sin(d);
	this->y= b - c*cos(d);
}

Vec2 Rect::GetCenter(){
	Vec2 a;
	a.x=this->x + this->w/2;
	a.y=this->y + this->h/2;
	return a;
}


bool Rect::IsColliding (Rect a){
	bool result;
	result =  (a.x > this->x && a.x < this->x + this->w) && (a.y > this->y && a.y < this->y + this->h); 					/* vertice de a dentro deste */
	result = result || ((this->y - a.y > 0 && this->y - a.y  < a.h)   && (a.x - this->x > 0 && a.x - this->x < this->w) ); 	/* vertice de a acima deste */
	result = result || ((a.y - this->y > 0 && a.y- this->y < this->h) && (this->x - a.x > 0 && this->x - a.x < a.w));		/* vertice de a à esquerda deste */
	return result;
}

