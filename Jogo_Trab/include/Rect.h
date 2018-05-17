#ifndef RECT_CLASS
#define RECT_CLASS
#include "Vec2.h"


class Rect {
public:
	float x, y, w, h;
	Rect ();
	Rect (float X, float Y, float W, float H);

	void SetPos(float x, float y);
	void SetPos(Vec2 a);

	Rect* add (Rect a, Rect b);
	Rect* sub (Rect a, Rect b);
	Rect* esc_mul (float a, Rect b);

	Rect operator+(Vec2 a);

	Vec2 GetCenter();
	void Center ();
	void CenterRot(float a, float b, float c, float d);
	float abs(Rect a);
	Rect* uni(Rect b);
	float dist (Rect a, Rect b);


	bool Contains (float a, float b);
	bool IsColliding (Rect a);


	Vec2 Pos ();

private:

};





#endif
