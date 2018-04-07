#include "../include/Rect.h"
#include <math.h>

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

