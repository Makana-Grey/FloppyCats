#ifndef _collidable_hpp
#define _collidable_hpp

struct RectCollider
{
	float x0 = 0;
	float y0 = 0;

	float x1 = 0;
	float y1 = 0;

	float x2 = 0;
	float y2 = 0;

	float x3 = 0;
	float y3 = 0;
};

template<class T>
class Collidable {
public:
	virtual const T& getCollider() = 0;
};

#endif // !_collidable_hpp