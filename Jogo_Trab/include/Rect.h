#ifndef RECT_CLASS
#define RECT_CLASS

class Rect {
public:
	float x, y, w, h;
	Rect ();
	Rect (float X, float Y, float W, float H);
	Rect* add (Rect a, Rect b);
	Rect* sub (Rect a, Rect b);
	Rect* esc_mul (float a, Rect b);
	float abs(Rect a);
	Rect* uni(Rect b);
	float dist (Rect a, Rect b);
	bool Contains (float a, float b);

private:

};





#endif
