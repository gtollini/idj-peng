#ifndef VEC2_CLASS
#define VEC2_CLASS

class Vec2 {
public:
	float x, y;
	Vec2 ();
	Vec2 (float X, float Y);
	Vec2 GetRotated(float theta);
	Vec2 operator+(const Vec2 a);
	Vec2 operator*(const float a);
private:

};





#endif
