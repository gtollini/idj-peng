#ifndef VEC2_CLASS
#define VEC2_CLASS

class Vec2 {
public:
	float x, y;
	Vec2 ();
	Vec2 (float X, float Y);
	Vec2 (float X, float Y, float W);

	Vec2 GetRotated(float theta);
	float Abs();

	Vec2 Uni ();
	Vec2 operator+(const Vec2 a);
	Vec2 operator+(const float a);
	Vec2 operator*(const float a);
	Vec2 operator-(const Vec2 a);
	void operator=(const Vec2 a);

	bool operator==(const Vec2 a);
	bool operator>=(const Vec2 a);
	bool operator<=(const Vec2 a);


private:

};





#endif
